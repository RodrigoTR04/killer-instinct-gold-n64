#!/usr/bin/env python3
"""Compare a draft's stack-slot signature against the target's.

Reports the frame size, the set of sp offsets each side touches (with the
mnemonics), and a symmetric difference. Filtering on this signature finds the
declaration order that produces the original's frame, which the word score
cannot see through the scheduling noise.
"""
import importlib.util, sys, tempfile, re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)

OFF = re.compile(r'^(-?\d+)\(sp\)$')


def slots(lines):
    d = defaultdict(set)
    for l in lines:
        m = re.match(r'^(\w+)\s+(.*)$', l)
        if not m:
            continue
        op, rest = m.group(1), m.group(2)
        for part in rest.split(','):
            g = OFF.match(part.strip())
            if g:
                d[int(g.group(1))].add(op)
    return d


def frame(lines):
    for l in lines:
        m = re.search(r'addiu\s+sp,sp,-(\d+)', l)
        if m:
            return int(m.group(1))
    return 0


def target_lines(fn):
    t = [cm.canon(x) for x in cm.target_raw(fn)]
    return [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]


def draft_lines(fn, path):
    src, tu = cm.build_source(fn, Path(path), False)
    with tempfile.TemporaryDirectory() as d:
        o = cm.compile_source(src, Path(d) / 'c.c')
        pairs = cm.draft_raw(o, fn)
    return [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]


if __name__ == '__main__':
    fn = sys.argv[1]
    th = target_lines(fn)
    ts = slots(th)
    tf = frame(th)
    print(f'target frame 0x{tf:x}  slots ' + ' '.join(f'{k:#04x}' for k in sorted(ts)))
    for p in sys.argv[2:]:
        try:
            mine = draft_lines(fn, p)
        except Exception as e:
            print(f'{Path(p).name}: ERROR {str(e)[-120:]}')
            continue
        ms = slots(mine)
        mf = frame(mine)
        extra = sorted(set(ms) - set(ts))
        missing = sorted(set(ts) - set(ms))
        ok = (mf == tf and not extra and not missing)
        print(f'{Path(p).name:28s} frame=0x{mf:x} {"MATCH" if ok else ""}')
        if extra:
            print('   extra   ' + ' '.join(f'{k:#04x}({",".join(sorted(ms[k]))})' for k in extra))
        if missing:
            print('   missing ' + ' '.join(f'{k:#04x}' for k in missing))
