import os
import clang.cindex
from clang.cindex import TypeKind

PROJECT_ROOT = os.path.abspath(".")
INCLUDE_ROOTS = [os.path.abspath("./include")]  # adjust if needed


def rel_include_path(path: str) -> str | None:
    """Convert an absolute header path into something you can #include.
    Prefers paths under ./include/.
    """
    if not path:
        return None
    ap = os.path.abspath(path)

    # Prefer include-relative
    for r in INCLUDE_ROOTS:
        if ap.startswith(r + os.sep):
            return ap[len(r) + 1:].replace(os.sep, "/")  # "game/race.h"
    # Otherwise, if it's inside the repo, return repo-relative
    if ap.startswith(PROJECT_ROOT + os.sep):
        return ap[len(PROJECT_ROOT) + 1:].replace(os.sep, "/")
    return None  # system header or outside repo


def peel_type(t: clang.cindex.Type) -> clang.cindex.Type:
    """Peel arrays / pointers / typedefs to get toward the underlying record type."""
    cur = t.get_canonical()
    while True:
        if cur.kind in (TypeKind.CONSTANTARRAY, TypeKind.INCOMPLETEARRAY, TypeKind.VARIABLEARRAY):
            cur = cur.get_array_element_type().get_canonical()
            continue
        if cur.kind == TypeKind.POINTER:
            cur = cur.get_pointee().get_canonical()
            continue
        # typedefs should already be resolved by canonical, but keep safe:
        if cur.kind == TypeKind.TYPEDEF:
            cur = cur.get_canonical()
            continue
        return cur


def record_definition_file(t: clang.cindex.Type) -> str | None:
    """If t is a struct/union/enum record, return the file where it's defined."""
    decl = t.get_declaration()
    if decl is None or decl.kind == clang.cindex.CursorKind.NO_DECL_FOUND:
        return None
    # decl.location.file may be None for builtin / invalid
    if decl.location is None or decl.location.file is None:
        return None
    return decl.location.file.name


def type_requires_complete_definition(var_cursor: clang.cindex.Cursor) -> bool:
    """Arrays of record types require the record to be complete in the current TU.
    Also structs/unions by value require completeness.
    Pointers do not.
    """
    t = var_cursor.type.get_canonical()

    # Any array anywhere -> need completeness of the ultimate element type
    cur = t
    while cur.kind in (TypeKind.CONSTANTARRAY, TypeKind.INCOMPLETEARRAY, TypeKind.VARIABLEARRAY):
        cur = cur.get_array_element_type().get_canonical()
        # keep peeling nested arrays
        continue

    # If original was an array, return True if base is a record
    if t.kind in (TypeKind.CONSTANTARRAY, TypeKind.INCOMPLETEARRAY, TypeKind.VARIABLEARRAY):
        # strips any pointers too, but arrays of pointers don't need record completeness
        base = peel_type(t)
        # We actually need the element type without pointer peeling:
        elem = t
        while elem.kind in (TypeKind.CONSTANTARRAY, TypeKind.INCOMPLETEARRAY, TypeKind.VARIABLEARRAY):
            elem = elem.get_array_element_type().get_canonical()
        # element being POINTER => fine
        if elem.kind == TypeKind.POINTER:
            return False
        return elem.kind in (TypeKind.RECORD, TypeKind.ENUM)

    # Non-array by-value record (rare for globals but possible)
    if t.kind in (TypeKind.RECORD, TypeKind.ENUM):
        return True

    return False


def collect_required_record_headers(game_states) -> list[str]:
    """game_states: iterable of your GameState objects (with .cursor).
    Returns sorted list of include paths (strings) for record definitions.
    """
    headers = set()

    for gs in game_states:
        c = gs.cursor
        # You probably already skip const/function-pointer tables/pointers elsewhere
        if not type_requires_complete_definition(c):
            continue

        # For arrays-of-struct, we want the array element type (no pointer peeling)
        t = c.type.get_canonical()
        while t.kind in (TypeKind.CONSTANTARRAY, TypeKind.INCOMPLETEARRAY, TypeKind.VARIABLEARRAY):
            t = t.get_array_element_type().get_canonical()

        # If element is a typedef of a record, canonical will land on the record.
        base = t.get_canonical()
        if base.kind not in (TypeKind.RECORD, TypeKind.ENUM):
            continue

        def_file = record_definition_file(base)
        inc = rel_include_path(def_file) if def_file else None
        if inc and inc.endswith(".h"):
            headers.add(inc)

    return sorted(headers)
