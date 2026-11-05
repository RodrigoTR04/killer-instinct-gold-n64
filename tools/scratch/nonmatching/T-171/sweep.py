#!/usr/bin/env python3
"""Measure many draft variants of one function in parallel."""
import importlib.util, sys, json, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)

def run(item):
    name, path = item
    try:
        r = screen.measure(sys.argv[1], Path(path))
        return (name, r['words'], r['compiled'], r['original'], '')
    except Exception as e:
        return (name, None, None, None, str(e).splitlines()[-1][:120] if str(e) else 'error')

def main():
    items = []
    for p in sys.argv[2:]:
        path = Path(p)
        if not path.is_absolute():
            path = ROOT / path
        items.append((path.stem if str(path).startswith('/tmp') else p, str(path)))
    if len(items) == 1 and Path(items[0][1]).is_dir():
        pass
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:
        results = list(pool.map(run, items))
    for name, words, comp, orig, err in sorted(results, key=lambda r: (r[1] is None, r[1] or 0)):
        print(f'{words if words is not None else "ERR":>6} {comp or "":>6}/{orig or "":<6} {name} {err}')

main()
