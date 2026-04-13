
import argparse
import clang.cindex
import glob
import multiprocessing.pool
loc = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/libclang.dylib"
clang.cindex.Config.set_library_file(loc)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("diffs", help="The binary file to search")
    args = parser.parse_args()

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

    with open(args.diffs) as f:
        changed_vars = set(f.read().strip().split())

    def scan(f):
        index = clang.cindex.Index.create()
        ast = index.parse(f, args=flags)
        for node in ast.cursor.get_children():
            if (
                node.kind == clang.cindex.CursorKind.VAR_DECL
                and node.location.file.name == f
                and node.storage_class == clang.cindex.StorageClass.NONE
                and node.spelling in changed_vars
            ):
                return node.spelling, node.type.spelling, node.location.file.name

        return False
    with multiprocessing.pool.ThreadPool() as pool:
        for x in pool.map(scan, glob.glob("**/*.c", recursive=True)):
            if x:
                print(",".join(x))


if __name__ == "__main__":
    main()
