from find_struct_includes import *
from dataclasses import dataclass, field
import clang.cindex
import functools
import itertools
import operator
import os.path
import sys
import yaml
loc = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/libclang.dylib"
clang.cindex.Config.set_library_file(loc)

with open("pointers.yaml") as f:
    pointers = yaml.safe_load(f)


def _collect_array_dims(t):
    """Return (base_type, dims) where dims is [d0, d1, ...] in declarator order."""
    dims = []
    cur = t.get_canonical()

    while cur.kind in (clang.cindex.TypeKind.CONSTANTARRAY, clang.cindex.TypeKind.INCOMPLETEARRAY, clang.cindex.TypeKind.VARIABLEARRAY):
        n = cur.get_array_size()  # -1 for incomplete
        dims.append(n)
        cur = cur.get_array_element_type().get_canonical()

    return cur, dims  # cur is base element type


@dataclass(frozen=True, order=True)
class GameState:
    File: str
    Name: str
    Type: str = field(compare=False)
    Size: str
    cursor: any = field(compare=False)

# dear read this is chat gpt
    # -------------------------
    # Helpers
    # -------------------------

    @property
    def _type(self):
        return self.cursor.type

    @property
    def _canonical(self):
        return self._type.get_canonical()

    @property
    def is_array(self):
        return self._canonical.kind in (
            clang.cindex.TypeKind.CONSTANTARRAY,
            clang.cindex.TypeKind.INCOMPLETEARRAY,
            clang.cindex.TypeKind.VARIABLEARRAY,
        )

    @property
    def is_pointer(self):
        return self._canonical.kind == clang.cindex.TypeKind.POINTER

    @property
    def is_function_pointer(self):
        t = self._canonical
        if t.kind != clang.cindex.TypeKind.POINTER:
            return False
        return t.get_pointee().kind == clang.cindex.TypeKind.FUNCTIONPROTO

    @property
    def is_const(self):
        return self._type.is_const_qualified()

    # -------------------------
    # extern emission
    # -------------------------
    @property
    def extern(self) -> str:
        t = self._type.get_canonical()
        name = self.Name

        # Array case: rebuild declarator correctly, including multi-d arrays
        if t.kind in (clang.cindex.TypeKind.CONSTANTARRAY, clang.cindex.TypeKind.INCOMPLETEARRAY, clang.cindex.TypeKind.VARIABLEARRAY):
            base, dims = _collect_array_dims(t)

            # Replace unknown dims (-1) if possible (only for the first incomplete layer).
            # NOTE: For true incomplete like `int x[]`, clang gives INCOMPLETEARRAY for the outermost.
            # If you computed Size, we can infer that outer count from Size/sizeof(element) ONLY if exactly 1 incomplete layer.
            if -1 in dims:
                # Only attempt inference if exactly one -1 and we can size base.
                if dims.count(-1) == 1:
                    idx = dims.index(-1)
                    base_size = base.get_size()
                    if base_size > 0:
                        # bytes per element includes any remaining inner dimensions already folded into base
                        # (because base is after peeling all array layers)
                        inferred = self.Size // base_size
                        dims[idx] = inferred

            # Build `name[dim0][dim1]...`
            decl = name
            for d in dims:
                if d is None or d < 0:
                    decl += "[]"
                else:
                    decl += f"[{d}]"

            return f"extern {base.spelling} {decl};"

        # Non-array: simple
        return f"extern {t.spelling} {name};"
    # -------------------------
    # save emission
    # -------------------------

    @property
    def save(self) -> str:
        """
        Emit correct mod_write_bytes call.
        Applies:
        - & for scalar
        - no & for arrays
        - & for pointer variables (to save pointer value)
        - skip const
        - skip function pointer arrays
        """

        # Skip const globals (rodata)
        if self.is_const:
            return ""

        # Skip function pointer tables
        if self.is_function_pointer:
            return ""

        name = self.Name
        size = self.Size

        # Array: decay to pointer automatically
        if self.is_array:
            return f"off = mod_write_bytes(out, off, {name}, {size});"

        # Scalar or pointer variable: take address
        return f"off = mod_write_bytes(out, off, &{name}, {size});"
# dear reader this was chat gpt

    @property
    def load(self):
        # Skip const globals (rodata)
        if self.is_const:
            return ""

        # Skip function pointer tables
        if self.is_function_pointer:
            return ""

        name = self.Name
        size = self.Size

        # Array: decay to pointer automatically
        if self.is_array:
            return f"off = mod_read_bytes(out, off, {name}, {size});"

        # Scalar or pointer variable: take address
        return f"off = mod_read_bytes(out, off, &{name}, {size});"

    def record_pointer(self):
        if "LEAVE_AS_IS" in pointers['pointers'].get(self.Name, ""):
            return False
        return True

    @property
    def pointer_policy(self):
        return pointers['pointers'].get(self.Name)

    @property
    def is_pointer_global(self):
        return self.is_pointer and self.pointer_policy is not None


def generate_pointer_relocs(game_states):
    save_lines = []
    load_lines = []

    for gs in sorted(game_states, key=lambda x: x.Name):
        policy = pointers['pointers'].get(gs.Name)

        if not policy or policy == "PTR_LEAVE_AS_IS":
            continue
        if not gs.is_pointer:
            continue

        name = gs.Name

        # ---- SAVE SIDE ----
        save_lines.append(f"    /* {name} */")
        save_lines.append("    {")
        save_lines.append("        s16 arena_index = -1;")
        save_lines.append("        u32 offset_val = 0;")
        save_lines.append("")
        save_lines.append(f"        if ({name} != NULL)")
        save_lines.append("        {")
        for i in range(3):
            cond = (
                f"((uintptr_t){name} >= gArenaStartPtrs[{i}] && "
                f"(uintptr_t){name} < gArenaEndPtrs[{i}])"
            )
            if i == 0:
                save_lines.append(f"            if {cond}")
            else:
                save_lines.append(f"            else if {cond}")
            save_lines.append("            {")
            save_lines.append(f"                arena_index = {i};")
            save_lines.append(
                f"                offset_val = (u32)((uintptr_t){
                    name} - gArenaStartPtrs[{i}]);"
            )
            save_lines.append("            }")
        save_lines.append("        }")
        save_lines.append("")
        save_lines.append(
            "        off = mod_write_bytes(out, off, &arena_index, sizeof(arena_index));")
        save_lines.append(
            "        off = mod_write_bytes(out, off, &offset_val, sizeof(offset_val));")
        save_lines.append("    }")
        save_lines.append("")

        # ---- LOAD SIDE ----
        load_lines.append(f"    /* {name} */")
        load_lines.append("    {")
        load_lines.append("        s16 arena_index;")
        load_lines.append("        u32 offset_val;")
        load_lines.append("")
        load_lines.append(
            "        off = mod_read_bytes(in, off, &arena_index, sizeof(arena_index));")
        load_lines.append(
            "        off = mod_read_bytes(in, off, &offset_val, sizeof(offset_val));")
        load_lines.append("")
        load_lines.append("        if (arena_index >= 0)")
        load_lines.append("        {")
        load_lines.append(
            f"            {
                name} = (void*)(gArenaStartPtrs[arena_index] + offset_val);"
        )
        load_lines.append("        }")
        load_lines.append("        else")
        load_lines.append("        {")
        load_lines.append(f"            {name} = NULL;")
        load_lines.append("        }")
        load_lines.append("    }")
        load_lines.append("")

    return save_lines, load_lines


def new_game_state(file, *args):
    name = str(file)\
        .replace(r"src/", "")\
        .replace(".c", "")\
        .replace(r"/", "__")
    return GameState(name, *args)


def fix_size(field):
    size = field.type.get_size()
    if field.type.spelling == "s32":
        return 4
    return size


# see if we have the generated torch yaml file
if not os.path.exists("fzerox.us.rev0.yaml"):
    print("Run `make extract` to make the big yaml")
    sys.exit(1)

with open("fzerox.us.rev0.yaml") as f:
    splat_file = yaml.safe_load(f)

main = None
ovl_2 = None
ovl_3 = None
for x in splat_file['segments']:
    if type(x) is dict:
        if x.get("name") == "main":
            main = x
        elif x.get("name") == "ovl_i2":
            ovl_2 = x
        elif x.get("name") == "ovl_i3":
            ovl_3 = x
        if None not in (main, ovl_2, ovl_3):
            break
    elif None not in (main, ovl_2, ovl_3):
        break
else:
    print("Failed to find the something")
    sys.exit(1)

# do we need sys?
files = set()
for segment in (main, ovl_2, ovl_3):
    for sub in segment['subsegments']:
        if (type(sub) is list
                and sub[1] == 'c'
                and all(f not in sub[2] for f in ("libultra", "sys"))):
            files.add(os.path.join(
                "src", segment.get("dir", ""), sub[2]) + ".c")

# lets start gathering data
flags = [
    "-x", "c",
    "-std=gnu89",
    "-I./include",
    "-Ibin/us/rev0",
    "-I.",
    "-I./include/PR",
    "-I./include/leo",
    "-I./include/libc",
    "-I./include/libultra",
    "-D_LANGUAGE_C",
    "-target mips64-unknown-elf"
]
asts = dict()
for first in files:
    assert os.path.exists(first)
    if first not in asts:
        index = clang.cindex.Index.create()
        ast = index.parse(first, args=flags)
        asts[first] = ast
    else:
        ast = asts[first]

# we should now have all possible pieces of data used in ovl_3 (game)
total_size = 0
vars = 0
usage = list()
for file, ast in asts.items():
    for node in ast.cursor.get_children():
        if (
            node.kind == clang.cindex.CursorKind.VAR_DECL
            and node.location.file.name == file
            and node.storage_class == clang.cindex.StorageClass.NONE
        ):
            vars += 1
            size = fix_size(node)
            if (size < 0):
                continue
            # lots of output here
            print(file, node.spelling, node.type.spelling, size)
            total_size += size
            usage.append(new_game_state(node.location.file, node.spelling,
                                        node.type.spelling, size, node))
print(vars, f"{total_size / 1000} kb")
v = 0
for k, vars in itertools.groupby(sorted(usage), key=operator.attrgetter("File")):
    externs = []
    memcpys = []
    loads = []
    for var in filter(lambda x: x.record_pointer(), vars):
        externs.append(var.extern)
        memcpys.append(var.save)
        loads.append(var.load)
    with open(f"src/mod/{k}.c.inc", "w") as fw:
        fw.write("\n".join(externs))
        fw.write(f"\nstatic u32 {k}__save(u8* out, u32 off)")
        fw.write("\n{")
        fw.write("\n\t".join([""] + memcpys))
        fw.write("\n\treturn off;")
        fw.write("\n}")
        fw.write("\n")

        fw.write(f"\nstatic u32 {k}__load(u8* out, u32 off)")
        fw.write("\n{")
        fw.write("\n\t".join([""] + loads))
        fw.write("\n\treturn off;")
        fw.write("\n}")
        fw.write("\n")


with open("src/mod/save_runner.c.inc", "w") as f:
    includes = []
    calls = []
    read_calls = []
    for k, vars in itertools.groupby(sorted(usage), key=operator.attrgetter("File")):
        includes.append(f"#include \"src/mod/{k}.c.inc\"")
        calls.append(f"off = {k}__save(out, off);")
        read_calls.append(f"off = {k}__load(out, off);")
    f.write("\n".join(includes))
    f.write("\nu32 global_write(u8* out, u32 off)")
    f.write("\n{")
    f.write("\n\t".join([""] + calls))
    f.write("\n\treturn off;")
    f.write("\n}")
    f.write("\n")

    f.write("\nu32 global_load(u8* out, u32 off)")
    f.write("\n{")
    f.write("\n\t".join([""] + read_calls))
    f.write("\n\treturn off;")
    f.write("\n}")
    f.write("\n")

with open("src/mod/pointer_relocs.c.inc", "w") as fw:
    save_lines, load_lines = generate_pointer_relocs(usage)
    fw.write("static void save_pointer_relocs(void)\n{\n")
    fw.write("\n".join(save_lines))
    fw.write("\n}\n\n")

    fw.write("static void load_pointer_relocs(void)\n{\n")
    fw.write("\n".join(load_lines))
    fw.write("\n}\n")

# ---- Example usage after you build `usage` ----
required_headers = collect_required_record_headers(usage)
for h in required_headers:
    print(f'#include "{h}"')
