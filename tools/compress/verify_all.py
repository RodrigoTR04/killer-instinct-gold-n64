#!/usr/bin/env python3
"""Read-only ROM verification of every boot table stream and two asset samples."""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import zlib
from rarezip import compress

ROM_SHA1 = 'ba52e91b44450c548467044b26951353dc491e04'


def streams(rom):
    for table in range(0x7DF0, 0x7EC8, 8):
        start, end = struct.unpack_from('>II', rom, table)
        yield f'{table:04X}', start, end
    for start in (0x121F70, 0x1F4290):
        yield f'asset_{start:06X}', start, None


def verify(rom, binary=None):
    rows = []
    for name, start, end in streams(rom):
        assert rom[start:start + 2] == b'\x11\x72'
        source = rom[start + 2:end]
        inflater = zlib.decompressobj(-15)
        data = inflater.decompress(source)
        assert inflater.eof
        stream_end = start + 2 + len(source) - len(inflater.unused_data)
        original = rom[start:stream_end]
        actual = compress(data, binary=binary)
        diff = next((i for i, (a, b) in enumerate(zip(original, actual)) if a != b),
                    None if len(original) == len(actual) else min(len(original), len(actual)))
        padding = rom[stream_end:end] if end is not None else b''
        row = dict(name=name, start=start, stream_end=stream_end, end=end,
                   expanded_size=len(data), compressed_size=len(original),
                   actual_size=len(actual), match=actual == original, first_difference=diff,
                   padding_size=len(padding), padding_hex=padding.hex())
        if end is not None:
            row['padding_valid'] = end == (stream_end + 15) & ~15 and not any(padding)
        rows.append(row)
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('rom', nargs='?', type=Path, default=Path('baserom.us.z64'))
    parser.add_argument('--binary', type=Path)
    parser.add_argument('--json', type=Path, help='optional metadata-only report')
    args = parser.parse_args()
    rom = args.rom.read_bytes()
    if hashlib.sha1(rom).hexdigest() != ROM_SHA1:
        parser.error('expected verified US V1.0 ROM SHA1')
    rows = verify(rom, args.binary)
    for row in rows:
        print(f"{row['name']:12} {'PASS' if row['match'] else 'FAIL'} "
              f"size={row['compressed_size']} first_difference={row['first_difference']} "
              f"padding={row['padding_size']}")
    if args.json:
        args.json.write_text(json.dumps(rows, indent=2) + '\n')
    ok = all(r['match'] and r.get('padding_valid', True) for r in rows)
    print(f"{sum(r['match'] for r in rows)}/{len(rows)} streams match; padding {'PASS' if ok else 'FAIL'}")
    raise SystemExit(0 if ok else 1)


if __name__ == '__main__':
    main()
