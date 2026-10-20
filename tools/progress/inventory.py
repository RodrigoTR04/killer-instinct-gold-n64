#!/usr/bin/env python3
"""Regenerate original-byte inventory; see README for conservative T4 rules."""
import argparse
import csv
import json
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[2]
FIELDS = ['area', 'function', 'vram', 'rom', 'bytes', 'tier', 'note']
COMMENT = re.compile(r'/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/')


def scan(root):
    rows = {}
    for path in sorted((root / 'asm').rglob('*.s')):
        source = path.read_text()
        # Splat's IDO per-function files omit an explicit .text directive.
        parts = path.relative_to(root / 'asm').parts
        per_function = parts[0] == 'nonmatchings' and len(parts) >= 4
        # Require a function label for implicit-text files; data dlabels do not qualify.
        implicit_text = per_function and re.search(r'^glabel\s+', source, re.M)
        if not re.search(r'\.section\s+\.text', source) and not implicit_text:
            continue
        labels = list(re.finditer(r'^(?:glabel\s+(\w+)|dlabel\s+(func_\w+))\s*$', source, re.M))
        for i, label in enumerate(labels):
            name = label[1] or label[2]
            before = source[labels[i-1].end() if i else 0:label.start()]
            body = source[label.end():labels[i+1].start() if i+1 < len(labels) else len(source)]
            end = re.search(r'^end(?:d)?label\s+' + re.escape(name) + r'\s*$', body, re.M)
            if end:
                body = body[:end.start()]
            comments = list(COMMENT.finditer(body))
            if not comments:
                raise ValueError(f'{path}: no instruction addresses for {name}')
            macro = re.search(r'nonmatching\s+' + re.escape(name) + r',\s*(0x[\da-fA-F]+|\d+)', before)
            vram = int(comments[0][2], 16)
            size = int(macro[1], 0) if macro else int(comments[-1][2], 16) + 4 - vram
            area = parts[1] if per_function else parts[0]
            if area.endswith('.s'):
                area = 'boot'
            row = dict(area=area, function=name,
                       vram=f'0x{vram:08X}', rom=f'0x{int(comments[0][1],16):X}',
                       bytes=size, handwritten='Handwritten function' in before)
            key = f'{area}:{row["vram"]}'
            if key in rows:
                raise ValueError(f'duplicate function segment/VRAM: {row["vram"]}')
            rows[key] = row
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT)
    args = parser.parse_args()
    root = args.root.resolve()
    folder = root / 'tools/progress'
    baseline = folder / 'original-functions.json'
    current = scan(root)
    if not current and not baseline.exists():
        raise ValueError('No assembly functions found; run make extract first')
    original = json.loads(baseline.read_text()) if baseline.exists() else {}
    # Migrate the original boot-only baseline without resetting sizes or tiers.
    original = {(f"boot:{key}" if key.startswith('0x') else key):
                {**row, 'area': 'boot' if row['area'].startswith('asm/') else row['area']}
                for key, row in original.items()}
    # Persist original sizes/addresses when assembly disappears during migration to C.
    for address, row in current.items():
        if address in original and any(original[address][k] != row[k] for k in ('rom', 'bytes', 'area')):
            raise ValueError(f'original function changed at {address}; review baseline explicitly')
        original[address] = row
    baseline.write_text(json.dumps(original, indent=2, sort_keys=True) + '\n')
    overrides = {}
    with (folder / 'status.csv').open(newline='') as stream:
        for row in csv.DictReader(stream):
            key = row['name_or_vram']
            if ':' in key:
                area, address = key.split(':', 1)
                key = f'{area}:0x{int(address,16):08X}'
            elif key.startswith('0x'):
                key = f'0x{int(key,16):08X}'
            matches = [address for address, fn in original.items()
                       if key in (address, fn['vram'], fn['function'])]
            if len(matches) != 1:
                raise ValueError(f'unknown/ambiguous override {key}; use segment:0xVRAM')
            key = matches[0]
            if row['tier'] not in ('T1', 'T2', 'T3', 'excluded') or key in overrides:
                raise ValueError(f'invalid/duplicate override: {row}')
            overrides[key] = row
    sources = '\n'.join(p.read_text() for p in sorted((root / 'src').rglob('*.c')))
    sources = re.sub(r'/\*.*?\*/|//[^\n]*', '', sources, flags=re.S)
    # T4 requires disappearance from assembly, a real C definition, no assembly
    # inclusion mentioning the symbol, and a fresh successful matching make.
    candidates = set()
    for address, row in original.items():
        name = re.escape(row['function'])
        definition = re.search(r'\b' + name + r'\s*\([^;{}]*\)\s*(?:[^;{}()]+;\s*)*\{', sources)  # also K&R param decls
        included = any(re.search(r'\b' + name + r'\b', m[0]) for m in re.finditer(r'(?:INCLUDE_ASM|GLOBAL_ASM)\s*\(.*?\)', sources, re.S))
        if address not in current and definition and not included:
            candidates.add(address)
    if candidates:
        subprocess.run(['make'], cwd=root, check=True)
        # Verify independently too: a successful custom/default target alone is insufficient.
        if (root / 'build/kig.us.z64').read_bytes() != (root / 'baserom.us.z64').read_bytes():
            raise ValueError('build ROM does not match baserom')
        for area in {original[key]['area'] for key in candidates} - {'boot'}:
            if (root / f'build/{area}.bin').read_bytes() != (root / f'build/segments/{area}.bin').read_bytes():
                raise ValueError(f'build image {area} does not match extracted original')
    # Confirm the linker actually took each symbol from a src object, at its
    # original address. An unused C definition must never earn T4 credit.
    linked = set()
    if candidates:
        for area in sorted({original[key]['area'] for key in candidates}):
            owner = ''
            map_path = root / ('build/kig.us.map' if area == 'boot' else f'build/{area}.map')
            if not map_path.exists():
                continue
            for line in map_path.read_text().splitlines():
                obj = re.search(r'\s(\S+\.o)\s*$', line)
                if obj:
                    owner = obj[1]
                symbol = re.fullmatch(r'\s*0x([0-9a-fA-F]+)\s+(\w+)\s*', line)
                if symbol and ('/src/' in owner or owner.startswith('src/')):
                    address = f'{area}:0x{int(symbol[1],16):08X}'
                    if address in candidates and original[address]['function'] == symbol[2]:
                        linked.add(address)
        candidates &= linked
    used = set()
    output = []
    for address, row in sorted(original.items(), key=lambda pair: (pair[1]['area'], int(pair[1]['vram'], 16))):
        keys = [address] if address in overrides else []
        override = overrides[keys[0]] if keys else {}
        used.update(keys)
        tier = override.get('tier', 'T1')
        note = override.get('note', '')
        if row['handwritten'] and tier != 'excluded':
            note = (note + '; splat: Handwritten function').lstrip('; ')
        if address in candidates and tier != 'excluded':
            tier = 'T4'
        output.append({**{k: row[k] for k in FIELDS[:5]}, 'tier': tier, 'note': note})
    if set(overrides) - used:
        raise ValueError(f'unresolved overrides: {sorted(set(overrides)-used)}')
    with (root / 'docs/functions.csv').open('w', newline='') as stream:
        writer = csv.DictWriter(stream, fieldnames=FIELDS, lineterminator='\n')
        writer.writeheader()
        writer.writerows(output)
    print(f'{len(output)} functions, {sum(r["bytes"] for r in output)} bytes → docs/functions.csv')


if __name__ == '__main__':
    main()
