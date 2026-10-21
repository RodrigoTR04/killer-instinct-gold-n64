#!/usr/bin/env python3
"""Report progress by original function bytes, with counts kept separate."""
import argparse
import csv
import datetime
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TIERS = ('T1', 'T2', 'T3', 'T4', 'excluded')
BAR_W = 40
README_BEGIN = '<!-- progress-begin -->'
README_END = '<!-- progress-end -->'
AREA_ORDER = ('boot', 'main', 'ovl_7DF8', 'ovl_7E00')


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


def bar(percent, width=BAR_W):
    if percent is None:
        return '░' * width
    filled = min(width, max(0, round(percent / 100 * width)))
    return '█' * filled + '░' * (width - filled)


def format_percent(percent):
    return 'n/a' if percent is None else f'{percent:.1f}%'


def metric_fns(summary, metric):
    names = ('T3', 'T4') if metric == 'M1' else ('T4',)
    return sum(summary['tiers'][t]['functions'] for t in names)


def milestone_line(label, summary, metric):
    d = summary[metric]
    return (f'{metric}  {label}\n'
            f'    {bar(d["percent"])}  {format_percent(d["percent"])}   '
            f'{d["bytes"]:,} / {summary["eligible_bytes"]:,} B   '
            f'{metric_fns(summary, metric):,} / {summary["eligible_functions"]:,} fns')


def area_cell(summary, metric):
    d = summary[metric]
    if d['percent'] is None:
        return f'`{bar(None, 20)}` n/a'
    return (f'`{bar(d["percent"], 20)}` {format_percent(d["percent"])}: '
            f'{d["bytes"]:,} / {summary["eligible_bytes"]:,} B, '
            f'{metric_fns(summary, metric):,} / {summary["eligible_functions"]:,} fns')


def ordered_areas(data):
    names = list(AREA_ORDER) + [a for a in data['areas'] if a not in AREA_ORDER]
    return [(name, data['areas'][name]) for name in names if name in data['areas']]


def readme_block(data, today=None):
    today = today or datetime.date.today().isoformat()
    lines = [
        f'_Snapshot {today}._',
        '',
        '```',
        milestone_line('Contract-valid (T3 + T4)', data, 'M1'),
        milestone_line('Byte-exact (T4)', data, 'M2'),
        '```',
        '',
        '| Area | M1: contract-valid | M2: byte-exact |',
        '|---|---|---|',
    ]
    for name, summary in ordered_areas(data):
        lines.append(f'| **{name}** | {area_cell(summary, "M1")} | {area_cell(summary, "M2")} |')
    return '\n'.join(lines) + '\n'


def splice_readme(text, block):
    start, end = text.find(README_BEGIN), text.find(README_END)
    if start < 0 or end < 0 or end < start:
        sys.exit('progress: README.md is missing <!-- progress-begin --> / <!-- progress-end --> markers')
    head_end = text.find('\n', start) + 1
    return text[:head_end] + block + text[end:]


def write_readme(path, data, today=None, check=False):
    updated = splice_readme(path.read_text(), readme_block(data, today))
    if updated == path.read_text():
        print(f'{path.relative_to(ROOT) if path.is_relative_to(ROOT) else path}: progress block current')
        return 0
    if check:
        print(f'{path}: progress block is STALE — run tools/progress/progress.py --readme')
        return 1
    path.write_text(updated)
    print(f'Updated {path.relative_to(ROOT) if path.is_relative_to(ROOT) else path}')
    return 0


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--input', type=Path, default=ROOT / 'docs/functions.csv')
    formats = p.add_mutually_exclusive_group()
    formats.add_argument('--markdown', action='store_true')
    formats.add_argument('--json', action='store_true')
    p.add_argument('--readme', nargs='?', const=ROOT / 'README.md', type=Path,
                   help='rewrite the README progress markers (default: README.md)')
    p.add_argument('--check', action='store_true', help='exit 1 if the README progress block is stale')
    p.add_argument('--date', help='ISO date stamped into the README snapshot (default: today)')
    args = p.parse_args()
    data = report(read_inventory(args.input))
    status = 0
    if args.readme is not None:
        status = write_readme(args.readme, data, args.date, args.check)
    if args.json:
        print(json.dumps(data, indent=2, sort_keys=True))
    elif args.markdown or args.readme is None:
        print(markdown(data))
        if not args.markdown:
            print(f'Total: {data["total_bytes"]:,} bytes; eligible: {data["eligible_functions"]} functions. Counts and byte metrics are separate.')
    sys.exit(status)


if __name__ == '__main__':
    main()
