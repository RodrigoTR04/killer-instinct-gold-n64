#!/usr/bin/env python3
"""Validate fixed ROM code slots linked from compressed, built code images."""
import argparse
from pathlib import Path
import struct
import zlib

# Keep these slots in sync with kig.us.yaml's non-extracted code bins.
CODE_SLOTS = (
    ('main', 0xA94D80, 0xAB5800),
    ('ovl_7DF8', 0xAB5810, 0xB00EB0),
    ('ovl_7E00', 0xB00EB0, 0xB14BA0),
)


def splice(linked, image_dir):
    entries = [struct.unpack_from('>II', linked, offset)
               for offset in range(0x7DF0, 0x7EC8, 8)]
    if entries[26] != entries[20]:
        raise ValueError('boot table 0x7EC0 must duplicate 0x7E90')
    for start, end in entries:
        if not 0 <= start < end <= len(linked) or start % 16 or end % 16:
            raise ValueError(f'invalid boot table slot: {start:#x}–{end:#x}')
    result = bytearray(linked)
    slots = []
    for index, (name, start, end) in enumerate(CODE_SLOTS):
        if entries[index] != (start, end):
            raise ValueError(f'{name}: boot table disagrees with reserved YAML slot')
        image = (image_dir / f'{name}.bin').read_bytes()
        cache = image_dir / f'{name}.1172'
        stream = cache.read_bytes()
        inflater = zlib.decompressobj(-15)
        if (stream[:2] != b'\x11\x72' or inflater.decompress(stream[2:]) != image
                or not inflater.eof or inflater.unused_data):
            raise ValueError(f'{name}: compressed cache does not match built image')
        padded = stream + bytes(-len(stream) % 16)
        if len(padded) != end - start:
            raise ValueError(f'{name}: compressed image is {len(stream)} bytes, '
                             f'{len(padded)} aligned; fixed slot requires exactly '
                             f'{end - start} bytes. Non-matching build; relocation unsupported')
        if any(start < other_end and other_start < end for other_start, other_end in slots):
            raise ValueError('overlapping code slots')
        if linked[start:end] != padded:
            raise ValueError(f'{name}: linked slot does not contain built compressed image')
        slots.append((start, end))
        print(f'OK: verified built {name} at {start:#x}–{end:#x} ({len(stream)} + {len(padded) - len(stream)} padding bytes)')
    cursor = 0
    for start, end in sorted(slots):
        if result[cursor:start] != linked[cursor:start]:
            raise ValueError('ROM bytes outside spliced slots changed')
        cursor = end
    if len(result) != len(linked) or result[cursor:] != linked[cursor:]:
        raise ValueError('ROM bytes outside spliced slots changed')
    print('OK: ROM region outside spliced slots is untouched')
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('linked_rom', type=Path)
    parser.add_argument('output', type=Path)
    parser.add_argument('--image-dir', type=Path, default=Path('build'))
    args = parser.parse_args()
    if args.linked_rom.resolve() == args.output.resolve():
        parser.error('linked input and output must be separate files')
    try:
        result = splice(args.linked_rom.read_bytes(), args.image_dir)
    except (ValueError, OSError, struct.error, zlib.error) as error:
        parser.exit(1, f'FAIL: {error}\n')
    args.output.write_bytes(result)


if __name__ == '__main__':
    main()
