#!/usr/bin/env python3
"""Read only good KI Gold dumps; report all six pairwise byte comparisons.

Offsets are ROM offsets, end exclusive. Regions merge runs separated by at
most --gap equal bytes; changed_bytes excludes those equal-byte gaps.
No sequence alignment is implied by a same-offset comparison.
"""
import argparse
import hashlib
import itertools
import json
from pathlib import Path
import struct

NAMES = {
    'us10': 'Killer Instinct Gold (U) (V1.0) [!].z64',
    'us11': 'Killer Instinct Gold (U) (V1.1) [!].z64',
    'us12': 'Killer Instinct Gold (U) (V1.2) [!].z64',
    'eu': 'Killer Instinct Gold (E) [!].z64',
}

def regions(a, b, gap):
    result = []
    start = last = None
    count = total = runs = 0
    previous = -2
    for i, (x, y) in enumerate(itertools.zip_longest(a, b)):
        if x == y:
            continue
        total += 1
        if i != previous + 1:
            runs += 1
        previous = i
        if last is None or i - last - 1 > gap:
            if last is not None:
                result.append(dict(start=start, end=last + 1, size=last + 1 - start, changed_bytes=count))
            start, count = i, 0
        last = i
        count += 1
    if last is not None:
        result.append(dict(start=start, end=last + 1, size=last + 1 - start, changed_bytes=count))
    return dict(changed_bytes=total, exact_runs=runs, regions=result)

def header(b):
    return dict(raw_hex=b[:64].hex(), clock=hex(struct.unpack_from('>I', b, 4)[0]),
                entry=hex(struct.unpack_from('>I', b, 8)[0]),
                release=hex(struct.unpack_from('>I', b, 12)[0]),
                crc1=b[16:20].hex(), crc2=b[20:24].hex(),
                title=b[32:52].decode('ascii'), cartridge=b[59:63].decode('ascii'), revision=b[63])

def compare(a, b, gap):
    out = regions(a, b, gap)
    out['identical_percent'] = 100 * (1 - out['changed_bytes'] / max(len(a), len(b)))
    out['first_mib'] = regions(a[:0x100000], b[:0x100000], gap)
    out['header_changes'] = [dict(offset=i, before=a[i], after=b[i]) for i in range(64) if a[i] != b[i]]
    # Unique, nonconstant 256-byte anchors: local shifts in the first MiB.
    # Anchors provide evidence of relocation, not executable-segment discovery.
    anchors = []
    for pos in range(0x1000, min(len(a), 0x100000) - 255, 0x4000):
        chunk = a[pos:pos + 256]
        if len(set(chunk)) < 16:
            continue
        lo, hi = max(0x1000, pos - 0x10000), min(len(b), pos + 0x10100)
        found = b.find(chunk, lo, hi)
        if found >= 0 and b.find(chunk, found + 1, hi) < 0:
            anchors.append(dict(source=pos, target=found, delta=found - pos))
    out['first_mib_unique_anchors'] = anchors
    deltas = sorted({x['delta'] for x in anchors})
    out['anchor_shift_comparisons'] = []
    for delta in deltas:
        start, end = max(0x8000, -delta), min(len(a), len(b) - delta)
        aligned = regions(a[start:end], b[start + delta:end + delta], gap)
        for region in aligned['regions']:
            region['start'] += start
            region['end'] += start
        aligned.update(delta=delta, source_start=start, source_end=end,
                       identical_percent=100 * (1 - aligned['changed_bytes'] / (end - start)),
                       first_mib_changed_bytes=sum(a[i] != b[i + delta] for i in range(start, min(end, 0x100000))))
        out['anchor_shift_comparisons'].append(aligned)
    return out

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom-dir', type=Path, default=Path(__file__).resolve().parents[2] / 'ROMs')
    parser.add_argument('--gap', type=int, default=256)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    if args.gap < 0:
        parser.error('--gap must be nonnegative')
    blobs = {k: (args.rom_dir / v).read_bytes() for k, v in NAMES.items()}
    for k, b in blobs.items():
        if b[:4] != bytes.fromhex('80371240'):
            parser.error(f'{k}: expected big-endian z64')
    result = dict(gap=args.gap, end_convention='exclusive',
                  roms={k: dict(filename=NAMES[k], size=len(b), sha1=hashlib.sha1(b).hexdigest(), header=header(b)) for k, b in blobs.items()},
                  comparisons={f'{a}_vs_{b}': compare(blobs[a], blobs[b], args.gap) for a, b in itertools.combinations(blobs, 2)})
    serialized = json.dumps(result, indent=2) + '\n'
    if args.output:
        args.output.write_text(serialized)
    else:
        print(serialized, end='')

if __name__ == '__main__':
    main()
