#!/usr/bin/env python3
"""Permute the order of named statement groups inside one draft function.

Statement order is a real source-level property, so a hit is honest C. This
searches group orders (not arbitrary tokens) around the regions that the
instruction diff says are scheduled differently.
"""
import argparse
import concurrent.futures
import importlib.util
import itertools
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function')
    ap.add_argument('draft')
    ap.add_argument('--groups', required=True,
                    help='path to a python file defining GROUPS = [[stmt, ...], ...]')
    ap.add_argument('-j', type=int, default=8)
    args = ap.parse_args()

    draft = Path(args.draft)
    if not draft.is_absolute():
        draft = ROOT / draft
    base = draft.read_text()
    ns = {}
    exec(Path(args.groups).read_text(), ns)
    anchor, variants = ns['ANCHOR'], ns['VARIANTS']

    if anchor not in base:
        raise SystemExit('anchor not found in draft')
    out_dir = Path('/tmp/kig-stmt-' + args.function)
    out_dir.mkdir(parents=True, exist_ok=True)
    for old in out_dir.glob('*.c'):
        old.unlink()

    names = []
    for i, body in enumerate(variants):
        p = out_dir / f'v{i:03d}.c'
        p.write_text(base.replace(anchor, body))
        names.append(p)

    def score(p):
        try:
            r = screen.measure(args.function, p, False, False)
            return (r['words'], r['compiled'], r['original'], p.name)
        except Exception as error:
            return (10 ** 9, None, None, p.name + ' ' + screen.diagnostic(str(error))[:80])

    with concurrent.futures.ThreadPoolExecutor(max_workers=args.j) as pool:
        results = list(pool.map(score, names))
    for words, compiled, original, name in sorted(results):
        print(f'{name} words={words} size={compiled}/{original}')


if __name__ == '__main__':
    sys.exit(main())
