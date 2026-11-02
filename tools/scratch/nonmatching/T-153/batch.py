#!/usr/bin/env python3
"""Score many candidate bodies for one function in a single process.

Each variant is a directory of `<name>.c` files; the owner TU context is taken
from the repository exactly like tools/permuter/screen.py.
"""
import argparse
import concurrent.futures
import importlib.util
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function')
    ap.add_argument('directory')
    ap.add_argument('--mode', default='auto', choices=['auto', 'full', 'prefix'])
    ap.add_argument('-j', type=int, default=8)
    args = ap.parse_args()
    d = Path(args.directory)
    if not d.is_absolute():
        d = ROOT / d
    variants = sorted(d.glob('*.c'))

    def score(v):
        attempts = {'auto': ((False, False), (True, False)), 'full': ((False, False),),
                    'prefix': ((True, False),)}[args.mode]
        out = None
        for prefix, declarations in attempts:
            try:
                out = screen.measure(args.function, v, prefix, declarations)
                break
            except Exception as error:
                out = {'words': None, 'compiled': None, 'original': None,
                       'error': screen.diagnostic(str(error))}
        return (out['words'] if out['words'] is not None else 10 ** 9,
                out['compiled'], out['original'], v.name, out.get('error', ''))

    with concurrent.futures.ThreadPoolExecutor(max_workers=args.j) as pool:
        results = list(pool.map(score, variants))
    for words, compiled, original, name, error in sorted(results):
        w = words if words != 10 ** 9 else 'ERR'
        print(f'{name:32s} words={w!s:>5} size={compiled}/{original} {error[:100]}')


if __name__ == '__main__':
    sys.exit(main())
