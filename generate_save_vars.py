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
        """
        Emit correct C89 extern declaration.
        """

        t = self._type
        name = self.Name

        # Function pointer arrays must preserve full spelling.
        if self.is_function_pointer and self.is_array:
            # Use original type spelling safely.
            # Example: Gfx *(*[22])(Gfx *)
            # We rewrite to: extern Gfx *(*name[22])(Gfx *);
            type_spelling = t.spelling

            # Replace anonymous array with named one
            # clang gives something like:
            # "Gfx *(*[22])(Gfx *)"
            # We inject name before [22]
            bracket_index = type_spelling.find('[')
            if bracket_index != -1:
                rewritten = (
                    type_spelling[:bracket_index]
                    + name
                    + type_spelling[bracket_index:]
                )
                return f"extern {rewritten};"

        # Arrays
        if self.is_array:
            elem_type = self._canonical.get_array_element_type()
            count = self._canonical.get_array_size()

            # If incomplete array, fallback to size/sizeof element
            if count < 0:
                count = self.Size // elem_type.get_size()

            type_spelling = elem_type.spelling
            return f"extern {type_spelling} {name}[{count}];"

        # Scalar or pointer
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

    def record_pointer(self):
        if "LEAVE_AS_IS" in pointers['pointers'].get(self.Name, ""):
            return False
        return True


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
            and node.storage_class != clang.cindex.StorageClass.EXTERN
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
    for var in filter(lambda x: x.record_pointer(), vars):
        externs.append(var.extern)
        # u8* out, u32& off, void* src, u32 size
        memcpys.append(var.save)
    with open(f"src/mod/{k}.c.inc", "w") as fw:
        fw.write("\n".join(externs))
        fw.write(f"\nstatic u32 {k}__save(u8* out, u32 off)")
        fw.write("\n{")
        fw.write("\n\t".join([""] + memcpys))
        fw.write("\n\treturn off;")
        fw.write("\n}")
        fw.write("\n")


with open("src/mod/save_runner.c.inc", "w") as f:
    includes = []
    calls = []
    for k, vars in itertools.groupby(sorted(usage), key=operator.attrgetter("File")):
        includes.append(f"#include \"mod/{k}.c.inc\"")
        calls.append(f"off = {k}__save(out, off);")
    f.write("\n".join(includes))
    f.write("\nu32 global_write(u8* out, u32 off)")
    f.write("\n{")
    f.write("\n\t".join([""] + calls))
    f.write("\n\treturn off;")
    f.write("\n}")
    f.write("\n")
