#!/usr/bin/env python3
"""Report progress by original function bytes, with counts kept separate."""
import argparse
import csv
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TIERS = ('T1', 'T2', 'T3', 'T4', 'excluded')


def read_inventory(path):
    with path.open(newline='') as stream:
        rows = list(csv.DictReader(stream))
    for row in rows:
        row['bytes'] = int(row['bytes'])
        if row['tier'] not in TIERS or row['bytes'] <= 0:
            raise ValueError(f'invalid inventory row: {row}')
    return rows


def summarize(rows):
    tiers = {t: {'bytes': sum(r['bytes'] for r in rows if r['tier'] == t),
                 'functions': sum(r['tier'] == t for r in rows)} for t in TIERS}
    eligible = sum(tiers[t]['bytes'] for t in TIERS[:-1])
    result = dict(total_bytes=sum(r['bytes'] for r in rows), eligible_bytes=eligible,
                  eligible_functions=sum(tiers[t]['functions'] for t in TIERS[:-1]), tiers=tiers)
    for metric, ts in [('M1', ('T3', 'T4')), ('M2', ('T4',))]:
        size = sum(tiers[t]['bytes'] for t in ts)
        result[metric] = dict(bytes=size, percent=100*size/eligible if eligible else None)
    return result


def report(rows):
    return {**summarize(rows), 'areas': {a: summarize([r for r in rows if r['area'] == a])
                                       for a in sorted({r['area'] for r in rows})}}


def markdown(data):
    lines = ['| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |',
             '|---|---:|---:|---:|---:|---:|---:|---:|---:|']
    for area, d in [('Total', data), *data['areas'].items()]:
        metrics = [f'{d[m]["bytes"]:,} ({d[m]["percent"]:.2f}%)' if d[m]['percent'] is not None else '0 (n/a)' for m in ('M1', 'M2')]
        counts = [str(d['tiers'][t]['functions']) for t in TIERS[:-1]]
        excluded = d['tiers']['excluded']
        lines.append('| ' + ' | '.join([area.replace('|', '\\|'), f'{d["eligible_bytes"]:,}', *metrics, *counts,
                                       f'{excluded["functions"]} ({excluded["bytes"]:,})']) + ' |')
    return '\n'.join(lines)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--input', type=Path, default=ROOT / 'docs/functions.csv')
    formats = p.add_mutually_exclusive_group()
    formats.add_argument('--markdown', action='store_true')
    formats.add_argument('--json', action='store_true')
    args = p.parse_args()
    data = report(read_inventory(args.input))
    if args.json:
        print(json.dumps(data, indent=2, sort_keys=True))
    else:
        print(markdown(data))
        if not args.markdown:
            print(f'Total: {data["total_bytes"]:,} bytes; eligible: {data["eligible_functions"]} functions. Counts and byte metrics are separate.')


if __name__ == '__main__':
    main()
