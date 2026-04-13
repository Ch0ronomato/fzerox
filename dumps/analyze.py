# gTotalRacers = 0x800E5EC0;
# gGamePaused =  0x800DCE5C;
#                  80800000

import argparse
import base64
import clang.cindex
import glob
import functools
import operator
import os.path
import multiprocessing.pool
import re
import sys
loc = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/libclang.dylib"
clang.cindex.Config.set_library_file(loc)


@functools.cache
def read_bin(binfile):
    with open(binfile, "rb") as f:
        rdram = f.read()
    # gGamePaused is a u8
    assert (len(rdram) ==
            0x800000), f"Rom length is weird {len(rdram)} bytes"
    return rdram


def find(binfile, symbols, show_hex, do_base64):
    rdram = read_bin(binfile)
    for symbol, data in sorted(symbols.items(), key=lambda x: int(x[1]['loc'], 16)):
        index = int(data['loc'], 16) - 0x80_00_00_00
        boxed = rdram[index:index + data['size']]
        if data["int_type"]:
            boxed = int.from_bytes(boxed, byteorder="big")
        elif data["bool_type"]:
            boxed = boxed[0].__bool__()
        elif data["float_type"]:
            boxed = "floating"
        elif show_hex:
            boxed = boxed.hex()
        elif do_base64:
            boxed = base64.b64encode(boxed)
        else:
            continue
        print(f"{symbol}@{data['loc']} =", boxed)


def main():
    # It's hard to know what the cause of the freeze is. So what I hope we can
    # investigate is given a drump of the RDRAM, what vars changed in the pause
    # screen. Then, we can generate a targeted set of vars and see if what
    # causes the freeze
    hex_address = re.compile("0x[0-9A-F]{8}")
    parser = argparse.ArgumentParser()
    parser.add_argument("bin", help="The binary file to search")
    parser.add_argument("--show_hex", action='store_true',
                        help="Print the full hex value")
    parser.add_argument("--base64", action='store_true',
                        help="Print the bas64 of the bytes")
    args = parser.parse_args()

    if args.show_hex and args.base64:
        print("You can't do both show_hex and base64")
        sys.exit(1)

    # lets get the location
    all_symbol_locations = dict()
    for f in ("symbol_addrs.txt", "symbol_addrs_nlib_vars.txt",
              "symbol_addrs_overlays.txt"):
        with open(os.path.join("linker_scripts/us/rev0", f)) as h:
            for sym in [x for x in h.read().strip().split("\n")
                        if x and "=" in x]:
                addrs = hex_address.findall(sym)
                key = sym[:sym.index("=")-1]
                all_symbol_locations[key] = addrs[0]
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

    int_types = {
        "s32",
        "s16",
        "s64",
        "u32",
        "u16",
        "u64"
    }

    float_types = {
        "float",
        "double",
    }

    bool_types = {
        "s8",
    }

    def scan(f):
        index = clang.cindex.Index.create()
        ast = index.parse(f, args=flags)
        vars = dict()
        for node in ast.cursor.get_children():
            if (
                node.kind == clang.cindex.CursorKind.VAR_DECL
                and node.location.file.name == f
                and node.storage_class == clang.cindex.StorageClass.NONE
            ):
                if node.type.spelling == "s32":
                    size = 4
                else:
                    size = node.type.get_size()
                if (size < 0):
                    continue
                if node.spelling in all_symbol_locations.keys():
                    vars[node.spelling] = {
                        "size": size,
                        "loc": all_symbol_locations[node.spelling],
                        "int_type": node.type.spelling in int_types,
                        "float_type": node.type.spelling in float_types,
                        "bool_type": node.type.spelling in bool_types}
        return vars
    with multiprocessing.pool.ThreadPool() as pool:
        all_symbols = functools.reduce(
            operator.ior,
            pool.map(scan, glob.glob("**/*.c", recursive=True)))
    print("Loaded all symbols")
    find(args.bin, all_symbols, args.show_hex, args.base64)


if __name__ == "__main__":
    main()
