#!/usr/bin/env python3
"""Slot-signature hill climb over declaration mutations.

Cheap, targeted search: start from a draft, try small declaration edits (move a
decl, add/remove a same-type decl, change an array extent, split a struct into
members), and keep only edits that move the draft's stack-slot signature closer
to the target's. Accepts on a lexicographic key:
  (frame wrong?, extra slots, missing slots, official words)
so it prioritises the frame and the exact slot set before the score.
"""
import argparse
import importlib.util
import itertools
import random
import re
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

FN_START = re.compile(r'^[A-Za-z_][\w \*]*\b{f}\s*\(', re.M)


def split(src, fn):
    m = re.search(r'^[A-Za-z_][\w \*]*\b' + re.escape(fn) + r'\s*\([^\n]*\)\s*\{?\s*\n', src, re.M)
    if not m:
        raise SystemExit('signature not found')
    open_brace = src.index('{', m.end() - 2)
    # first blank line after the opening brace separates declarations from body
    j = src.index('\n\n', open_brace)
    return src[:j + 1], src[j + 2:]


def target_signature(fn):
    t = [cm.canon(x) for x in cm.target_raw(fn)]
    t = [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]
    fr = 0
    sl = set()
    for l in t:
        m = re.search(r'addiu\s+sp,sp,-(\d+)', l)
        if m:
            fr = int(m.group(1))
        for part in l.split(','):
            g = re.match(r'^(-?\d+)\(sp\)$', part.strip())
            if g:
                sl.add(int(g.group(1)))
    return fr, sl


def signature(fn, path):
    src, tu = cm.build_source(fn, Path(path), False)
    with tempfile.TemporaryDirectory() as d:
        o = cm.compile_source(src, Path(d) / 'c.c')
        pairs = cm.draft_raw(o, fn)
    lines = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    fr = 0
    sl = set()
    for l in lines:
        m = re.search(r'addiu\s+sp,sp,-(\d+)', l)
        if m:
            fr = int(m.group(1))
        for part in l.split(','):
            g = re.match(r'^(-?\d+)\(sp\)$', part.strip())
            if g:
                sl.add(int(g.group(1)))
    return fr, sl


def mutations(decl_lines, rng):
    """Yield (description, new_decl_lines) candidates."""
    n = len(decl_lines)
    for i in range(n):
        for j in range(n):
            if i != j:
                d = list(decl_lines)
                d.insert(j, d.pop(i))
                yield f'move{i}->{j}', d
    for i in range(n):
        d = list(decl_lines)
        del d[i]
        yield f'drop{i}', d
    for i in range(n):
        line = decl_lines[i]
        m = re.match(r'^(\s*)(.+?)\s+(\w+)\[(\w+)\];$', line)
        if m:
            for ext in ('1', '2', '3', '4', '6', '8'):
                d = list(decl_lines)
                d[i] = f'{m.group(1)}{m.group(2)} {m.group(3)}[{ext}];'
                yield f'ext{i}={ext}', d
        m2 = re.match(r'^(\s*)(f32|s32|u32|u8|s8)\s+(\w+);$', line)
        if m2:
            for ty in ('f32', 's32', 'u32', 'u8', 's8', 'f64'):
                if ty != m2.group(2):
                    d = list(decl_lines)
                    d[i] = f'{m2.group(1)}{ty} {m2.group(3)};'
                    yield f'ty{i}={ty}', d


def evaluate(fn, path):
    try:
        r = screen.measure(fn, Path(path))
        fr, sl = signature(fn, path)
        return r['words'], r['compiled'], r['original'], fr, sl
    except Exception:
        return None


def key(w, extra, missing, frame_ok):
    return (not frame_ok, len(extra) + len(missing), len(extra), len(missing), w)


if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument('function')
    ap.add_argument('draft', type=Path)
    ap.add_argument('--seconds', type=float, default=180)
    ap.add_argument('--local-region', default='0x40',
                    help='lowest sp offset considered a local slot (hex)')
    args = ap.parse_args()

    import time
    deadline = time.time() + args.seconds
    fn = args.function
    floor = int(args.local_region, 16)
    tfr, tsl = target_signature(fn)
    tloc = {x for x in tsl if floor <= x < tfr}
    print(f'target frame=0x{tfr:x} locals={sorted(hex(x) for x in tloc)}')

    src = args.draft.read_text()
    head, body = split(src, fn)
    decls = [l for l in head.rstrip('\n').split('\n') if l.strip().startswith((' ', '\t'))]
    prefix = head[:head.index(decls[0])] if decls else head
    best = None
    out = args.draft.parent / 'hc'
    out.mkdir(exist_ok=True)
    rng = random.Random(7)
    cur = decls
    cur_path = out / 'cur.c'
    cur_path.write_text(prefix + '\n'.join(cur) + '\n\n' + body)
    ev = evaluate(fn, cur_path)
    if ev is None:
        raise SystemExit('baseline does not compile')
    w, comp, orig, fr, sl = ev
    cloc = {x for x in sl if floor <= x < fr}
    curkey = key(w, cloc - tloc, tloc - cloc, fr == tfr)
    print(f'baseline w={w} {comp}/{orig} frame=0x{fr:x} key={curkey}')
    rounds = 0
    while time.time() < deadline:
        rounds += 1
        improved = False
        for desc, cand in mutations(cur, rng):
            if time.time() > deadline:
                break
            p = out / 'cand.c'
            p.write_text(prefix + '\n'.join(cand) + '\n\n' + body)
            e = evaluate(fn, p)
            if e is None:
                continue
            w2, c2, o2, fr2, sl2 = e
            l2 = {x for x in sl2 if floor <= x < fr2}
            k2 = key(w2, l2 - tloc, tloc - l2, fr2 == tfr)
            if k2 < curkey:
                curkey, cur = k2, cand
                best = (desc, k2, w2, c2, fr2, l2)
                (out / 'best.c').write_text(prefix + '\n'.join(cand) + '\n\n' + body)
                print(f'  {desc:14s} w={w2} {c2}/{o2} frame=0x{fr2:x} '
                      f'extra={sorted(hex(x) for x in l2 - tloc)} miss={sorted(hex(x) for x in tloc - l2)}')
                improved = True
        if not improved:
            break
    print(f'rounds={rounds} final key={curkey}')
    if best:
        print(f'best: {best[0]}')
