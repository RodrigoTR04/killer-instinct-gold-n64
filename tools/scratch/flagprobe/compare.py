#!/usr/bin/env python3
"""Compile independent C probes; compare complete function bodies using ELF relocations.

Run from any directory. Inputs are read-only; every generated file goes to /tmp.
No disassembly tree or extracted segment file is needed.
"""
import argparse
import hashlib
import itertools
import json
from pathlib import Path
import shlex
import struct
import subprocess
import sys
import tempfile
import zlib

ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
# Audited body sizes exclude alignment after jr ra and its delay slot.
SIZES = {
    '80013BE0': 0xA4, '80017064': 0x60, '8001BA18': 0x7C,
    '8001C2D4': 0x9C, '801ACE04': 0x58, '801ACE5C': 0x64,
    '801ACEC0': 0x5C, '801ACFC8': 0x68, '801ADE48': 0x54,
    '801B1A14': 0x68, '801B55DC': 0x74, '801BF914': 0x74,
}
UNMATCHED = {'80013BE0', '801BF914'}
BASE_FLAGS = '-G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul'


def targets(rom_path):
    rom = rom_path.read_bytes()
    if hashlib.sha1(rom).hexdigest() != 'ba52e91b44450c548467044b26951353dc491e04':
        raise ValueError('Expected verified US V1.0 ROM')
    images = {}
    for table, base in ((0x7DF0, 0x8000F960), (0x7DF8, 0x801ABB20)):
        start, end = struct.unpack_from('>II', rom, table)
        if rom[start:start + 2] != b'\x11\x72':
            raise ValueError('Bad segment header')
        images[base] = zlib.decompress(rom[start + 2:end], -15)
    result = {}
    for name, size in SIZES.items():
        addr = int(name, 16)
        base = 0x8000F960 if addr < 0x80100000 else 0x801ABB20
        result[name] = images[base][addr - base:addr - base + size]
    return result


def elf_function(path, function):
    """Read ELF32 BE symbols/REL; never heuristically mask instructions."""
    data = path.read_bytes()
    if data[:6] != b'\x7fELF\x01\x02':
        raise ValueError('Expected big-endian ELF32')
    shoff = struct.unpack_from('>I', data, 32)[0]
    entsize, count, names_index = struct.unpack_from('>HHH', data, 46)
    sections = [struct.unpack_from('>10I', data, shoff + i * entsize) for i in range(count)]
    def blob(section):
        return data[section[4]:section[4] + section[5]]
    def string(strings, offset):
        return strings[offset:strings.index(b'\0', offset)].decode()
    names = blob(sections[names_index])
    text_index = next(i for i, sec in enumerate(sections) if string(names, sec[0]) == '.text')
    found = []
    for sec in sections:
        if sec[1] != 2:
            continue
        strings = blob(sections[sec[6]])
        for off in range(sec[4], sec[4] + sec[5], sec[9]):
            name, value, size, info, _, index = struct.unpack_from('>IIIBBH', data, off)
            if info & 15 == 2 and index == text_index and string(strings, name) == function:
                found.append((value, size))
    if len(found) != 1:
        raise ValueError(f'Expected exactly one symbol {function}')
    start, size = found[0]
    code = blob(sections[text_index])[start:start + size]
    masks = [0xFFFFFFFF] * (size // 4)
    relocations = []
    for sec in sections:
        if sec[1] != 9 or sec[7] != text_index:
            continue
        for off in range(sec[4], sec[4] + sec[5], sec[9]):
            pos, info = struct.unpack_from('>II', data, off)
            if not start <= pos < start + size:
                continue
            kind = info & 255
            if kind not in (4, 5, 6):
                raise ValueError(f'Unsupported text relocation {kind}; refusing broad masking')
            masks[(pos - start) // 4] = 0xFC000000 if kind == 4 else 0xFFFF0000
            relocations.append({'offset': pos - start, 'type': kind})
    return code, masks, relocations


def compare(name, version, flags, originals, scratch):
    obj = scratch / 'probe.o'
    command = [str(ROOT / 'tools/ext/ido' / version / 'cc'), '-c',
               *shlex.split(flags), str(HERE / (name + '.c')), '-o', str(obj)]
    proc = subprocess.run(command, cwd=ROOT, capture_output=True, text=True)
    if proc.returncode:
        return {'match': False, 'error': proc.stderr.strip(), 'command': command}
    code, masks, rels = elf_function(obj, 'func_' + name)
    original = originals[name]
    bad = []
    for i in range(min(len(code), len(original)) // 4):
        actual = struct.unpack_from('>I', code, i * 4)[0]
        expected = struct.unpack_from('>I', original, i * 4)[0]
        if actual & masks[i] != expected & masks[i]:
            bad.append(i * 4)
    return {'match': len(code) == len(original) and not bad,
            'compiled_size': len(code), 'target_size': len(original),
            'different_words': len(bad), 'first_differences': bad[:12],
            'relocations': rels}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path, default=ROOT / 'baserom.us.z64')
    parser.add_argument('--function', choices=sorted(SIZES))
    parser.add_argument('--version', choices=['5.3', '7.1'], default='5.3')
    parser.add_argument('--cflags', default=BASE_FLAGS + ' -O2 -mips2')
    parser.add_argument('--matrix', action='store_true', help='both versions/ISAs; O1/O2/O3/g/g3/O2+g/O2+g3, plus no-mul control')
    parser.add_argument('--json', type=Path, help='write measurements (no binary bytes)')
    args = parser.parse_args()
    originals = targets(args.rom)
    names = [args.function] if args.function else sorted(SIZES)
    candidates = [(args.version, args.cflags)]
    if args.matrix:
        candidates = [(ver, BASE_FLAGS + ' ' + opt + ' ' + isa)
                      for ver, opt, isa in itertools.product(
                          ['5.3', '7.1'], ['-O1', '-O2', '-O3', '-g', '-g3', '-O2 -g', '-O2 -g3'],
                          ['-mips2', '-mips1'])]
        candidates += [(ver, BASE_FLAGS.replace(' -Wab,-r4300_mul', '') + ' -O2 -mips2')
                       for ver in ['5.3', '7.1']]
    result = {}
    with tempfile.TemporaryDirectory(prefix='kig-t010-') as directory:
        for name in names:
            result[name] = {}
            for version, flags in candidates:
                key = version + ' ' + flags
                result[name][key] = compare(name, version, flags, originals, Path(directory))
            matching = [key for key, value in result[name].items() if value['match']]
            print(name + ': ' + ('MATCH ' + ' | '.join(matching) if matching else 'NO MATCH'), flush=True)
    if args.json:
        args.json.write_text(json.dumps(result, indent=2) + '\n')
    if args.matrix:
        return 0
    if args.function:
        return 0 if next(iter(result[args.function].values()))['match'] else 1
    # Baseline checks include two deliberately retained unresolved reconstructions.
    return 0 if all(next(iter(rows.values()))['match'] == (name not in UNMATCHED)
                    for name, rows in result.items()) else 1


if __name__ == '__main__':
    sys.exit(main())
