"""Batch-scoring harness for T-172 draft variants (official words, in-process)."""
import concurrent.futures
import importlib.util
import re
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)


def score_one(item):
    name, text, function = item
    with tempfile.TemporaryDirectory(prefix='t172-') as d:
        path = Path(d) / f'{name}.c'
        path.write_text(text)
        try:
            r = screen.measure(function, path)
            return name, r['words'], r['compiled'], ''
        except Exception as error:
            return name, None, None, str(error)[-200:]


def run(function, variants, jobs=12):
    items = [(n, t, function) for n, t in variants.items()]
    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as pool:
        results = list(pool.map(score_one, items))
    results.sort(key=lambda r: (r[1] is None, r[1] if r[1] is not None else 10**9))
    for name, words, size, error in results:
        print(f'{words}\t{size}\t{name}\t{error}')
    return results
