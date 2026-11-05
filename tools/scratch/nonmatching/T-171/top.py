#!/usr/bin/env python3
"""Measure the top-N permuter outputs by re-embedding each body in the draft header."""
import concurrent.futures, importlib.util, subprocess, sys, tempfile, os
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)

TOOLS = ROOT / 'tools/scratch/nonmatching/T-171'

def extract(fn, source):
    import re
    lines = source.splitlines()
    for i, line in enumerate(lines):
        if re.match(r'^[A-Za-z_][\w \t*]*\b' + re.escape(fn) + r'\s*\(', line):
            depth, started, out = 0, False, []
            for j in range(i, len(lines)):
                l = lines[j]
                out.append(l)
                depth += l.count('{') - l.count('}')
                if '{' in l: started = True
                if started and depth == 0:
                    return '\n'.join(out) + '\n'
    return None

def head(fn, draft):
    import re
    lines = draft.splitlines()
    for i, line in enumerate(lines):
        if re.match(r'^[A-Za-z_][\w \t*]*\b' + re.escape(fn) + r'\s*\(', line):
            return '\n'.join(lines[:i]) + '\n'
    return draft

def main():
    fn, draft = sys.argv[1], Path(sys.argv[2])
    directory = Path(sys.argv[3])
    n = int(sys.argv[4]) if len(sys.argv) > 4 else 25
    outs = []
    for d in directory.glob('output-*'):
        try: score = int((d / 'score.txt').read_text().strip())
        except Exception: continue
        outs.append((score, d))
    outs.sort()
    outs = outs[:n]
    hdr = head(fn, draft.read_text())
    tmpdir = Path(tempfile.mkdtemp(prefix='kig-top-'))
    todo = []
    for score, d in outs:
        body = extract(fn, (d / 'source.c').read_text())
        if body is None: continue
        p = tmpdir / (d.name + '.c')
        p.write_text(hdr + body)
        todo.append((score, d, p))

    def run(item):
        score, d, p = item
        try:
            r = screen.measure(fn, p)
            return (r['words'], score, str(d))
        except Exception as e:
            return (9999, score, str(d) + ' ' + str(e).splitlines()[-1][:70])

    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as pool:
        for words, score, d in sorted(pool.map(run, todo)):
            print(f'{words:>6} score={score:<7} {d}')

main()
