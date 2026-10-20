#!/usr/bin/env python3
"""Mark IDO's ELF32 MIPS III output as o32 for modern GNU ld.

IDO 5.3 emits o32 code with -mips3 -32 but omits EF_MIPS_ABI_O32 and
EF_MIPS_32BITMODE. This changes ELF metadata only, never section bytes.
"""
import pathlib
import struct
import sys

path = pathlib.Path(sys.argv[1])
blob = bytearray(path.read_bytes())
assert blob[:6] == b'\x7fELF\x01\x02', 'expected big-endian ELF32'
assert struct.unpack_from('>H', blob, 18)[0] == 8, 'expected MIPS'
flags = struct.unpack_from('>I', blob, 36)[0]
assert flags & 0xF0000000 == 0x20000000, 'expected MIPS III'
struct.pack_into('>I', blob, 36, flags | 0x1100)
path.write_bytes(blob)
