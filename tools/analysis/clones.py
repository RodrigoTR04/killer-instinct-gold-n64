#!/usr/bin/env python3
"""Screen T2/T4 original MIPS instruction streams for clones (make extract first).

Run with .venv/bin/python tools/analysis/clones.py. No rebuilt code is used.
Similarity is normalized instruction Levenshtein similarity, with a size-ratio prefilter.
Edges >= threshold form connected components; transitive pairs may score lower.
"""
import argparse
from collections import Counter
import csv
import json
from pathlib import Path
import re
import struct
import rabbitizer

ROOT = Path(__file__).resolve().parents[2]
BASES = {'boot': 0x80000400, 'main': 0x8000F960, 'ovl_7DF8': 0x801ABB20}


def normalize(text):
    """Keep opcode, operand arity, register class, and memory addressing shape."""
    text = re.sub(r'\$(?:f\d+)', 'F', text)
    text = re.sub(r'\$\w+', 'R', text)
    text = re.sub(r'%\w+\([^)]*\)', 'I', text)
    text = re.sub(r'(?<!\w)-?(?:0x[0-9a-fA-F]+|\d+)(?!\w)', 'I', text)
    # Branch/jump symbolic destinations in splat assembly.
    text = re.sub(r'\.L[0-9A-Fa-f]+\b|\b(?:[A-Za-z_]\w*\.)?[LD]_\w+\b|\bfunc_[0-9A-Fa-f]+\b', 'I', text)
    return re.sub(r'\s+', ' ', text.strip())


def similarity(a, b):
    if len(a) > len(b):
        a, b = b, a
    prev = list(range(len(a) + 1))
    for j, y in enumerate(b, 1):
        row = [j]
        for i, x in enumerate(a, 1):
            row.append(min(row[-1] + 1, prev[i] + 1, prev[i-1] + (x != y)))
        prev = row
    return 1 - prev[-1] / len(b)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--threshold', type=float, default=.85)
    parser.add_argument('--measurements', type=Path, help='optional JSON mapping function names to latest word counts/results')
    parser.add_argument('--output', type=Path, default=ROOT / 'docs/clones.md')
    args = parser.parse_args()
    if not 0 < args.threshold <= 1:
        parser.error('threshold must be in (0, 1]')
    measured = json.loads(args.measurements.read_text()) if args.measurements else {}
    inventory = list(csv.DictReader((ROOT / 'docs/functions.csv').open()))
    overrides = {r['name_or_vram']: r['tier'] for r in csv.DictReader((ROOT / 'tools/progress/status.csv').open())}
    original = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
    images = {area: (ROOT / f'build/segments/{area}.bin').read_bytes() for area in BASES if area != 'boot'}
    images['boot'] = (ROOT / 'baserom.us.z64').read_bytes()[0x1000:]
    screen = {}
    for line in (ROOT / 'tools/scratch/nonmatching/T-099/screen.md').read_text().splitlines():
        parts = [p.strip() for p in line.split('|')]
        if len(parts) > 5 and parts[1].startswith('func_'):
            screen[parts[1]] = parts[4]
    functions = []
    for r in inventory:
        tier = overrides.get(r['function'], overrides.get(r['vram'], r['tier']))
        if tier not in ('T2', 'T4') or r['area'] not in BASES:
            continue
        key = r['area'] + ':' + r['vram']
        orig = original[key]
        size = orig['bytes']
        offset = int(r['vram'], 16) - BASES[r['area']]
        data = images[r['area']][offset:offset+size]
        if len(data) != size:
            raise ValueError(f"Missing original bytes: {key}")
        # Decode original words for BOTH tiers, avoiding disassembler spelling
        # differences and retaining matched originals after splat removes asm.
        stream = [normalize(rabbitizer.Instruction(w).disassemble()) for (w,) in struct.iter_unpack('>I', data)]
        paths = list((ROOT / 'asm/nonmatchings' / r['area']).rglob(r['function'] + '.s'))
        if tier == 'T2' and not paths:
            raise ValueError(f"Missing T2 assembly: {r['function']}")
        functions.append(dict(r, tier=tier, size=size, stream=stream, counts=Counter(stream)))
    edges = {}
    parent = list(range(len(functions)))
    def find(i):
        while parent[i] != i:
            parent[i] = parent[parent[i]]
            i = parent[i]
        return i
    for i, a in enumerate(functions):
        for j in range(i):
            b = functions[j]
            if min(a['size'], b['size']) / max(a['size'], b['size']) < args.threshold:
                continue
            # Opcode multiset overlap is an upper bound on edit similarity.
            ca, cb = a['counts'], b['counts']
            if sum((ca & cb).values()) / max(len(a['stream']), len(b['stream'])) < args.threshold:
                continue
            score = similarity(a['stream'], b['stream'])
            if score >= args.threshold:
                edges[j, i] = score
                parent[find(i)] = find(j)
    groups = {}
    for i in range(len(functions)):
        groups.setdefault(find(i), []).append(i)
    groups = [g for g in groups.values() if len(g) > 1 and any(functions[i]['tier'] == 'T2' for i in g)]
    groups.sort(key=lambda g: (not any(functions[i]['tier'] == 'T4' for i in g), -sum(functions[i]['size'] for i in g if functions[i]['tier'] == 'T2')))
    lines = ['# Original-code clone candidates', '', f'Generated by `tools/analysis/clones.py --threshold {args.threshold}' + (f' --measurements {args.measurements}' if args.measurements else '') + '` after `make extract`.', '',
             'Tiers use status.csv overrides and the inventory. Original words come from untouched extracted images (boot from the ROM); T2 assembly presence is checked. Registers, constants, relocation destinations and branch offsets are masked; opcodes, operand classes and memory addressing shape remain. Score = normalized instruction edit similarity; size ratio must also meet the threshold. Components use qualifying edges, so similarity to the first member may be below threshold. This is a screening aid, never matching evidence.', '',
             'Differing words are the **historical T-099 screen**, not current measurements; T4 members are 0. Later improvements (notably family B 19 and BB258 20 / BADEC 118) supersede that screen. Missing screen entries are “—”. T4-only clusters are omitted. T2 singletons remain screened but are not clusters.', '',
             f'Screened {len(functions)} functions; {sum(f["tier"] == "T2" for f in functions)} T2; {len(groups)} clusters containing T2.', '']
    for n, group in enumerate(groups, 1):
        anchor = group[0]
        lines += [f'## Cluster {n} — {sum(functions[i]["size"] for i in group if functions[i]["tier"] == "T2")} T2 bytes', '', '| Member | Image | Tier | Bytes | Similarity to first | T-099 differing words | Latest supplied words |', '|---|---|---|---:|---:|---:|---:|']
        for i in group:
            f = functions[i]
            score = 1 if i == anchor else similarity(f['stream'], functions[anchor]['stream'])
            latest = measured.get(f['function'], {})
            latest = latest.get('words', '—') if isinstance(latest, dict) else latest
            if f['tier'] == 'T4':
                latest = 0
            lines.append(f'| {f["function"]} | {f["area"]} | {f["tier"]} | {f["size"]} | {score:.3f} | {"0" if f["tier"] == "T4" else screen.get(f["function"], "—")} | {latest} |')
        lines += ['', 'Qualifying edges: ' + '; '.join(f'{functions[a]["function"]} ↔ {functions[b]["function"]} {v:.3f}' for (a,b),v in edges.items() if a in group and b in group) + '.', '']
    if measured:
        lines += ['## Supplied measurements', '', 'These supplement the historical screen; their provenance is in the supplied JSON and task report.', '', '| Function | Words | Context |', '|---|---:|---|']
        for name, result in sorted(measured.items()):
            if isinstance(result, dict):
                lines.append(f'| {name} | {result.get("words", "—")} | {result.get("context", "supplied")} |')
            else:
                lines.append(f'| {name} | {result} | supplied |')
        lines.append('')
    args.output.write_text('\n'.join(lines))
    print(f'Wrote {args.output}: {len(groups)} clusters')


if __name__ == '__main__':
    main()
