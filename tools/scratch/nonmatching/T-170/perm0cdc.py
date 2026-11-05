#!/usr/bin/env python3
"""0CDC: search declaration order to grow the frame 0xC0 -> 0xD8."""
import importlib.util, sys, tempfile, re, difflib, itertools
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)
fn = 'func_801B0CDC'
T = None


def target():
    global T
    if T is None:
        t = [cm.canon(x) for x in cm.target_raw(fn)]
        T = [x for x in t if not x.startswith(('dlabel', 'enddlabel'))]
    return T


def score(txt, tag):
    p = ROOT / 'tools/scratch/nonmatching/T-170' / f'k_{tag}.c'
    p.write_text(txt)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (9999, 9999, tag, f'{tag:22s} ERROR {str(e)[-90:]}')
    th = target()
    sm = difflib.SequenceMatcher(None, th, mine, autojunk=False)
    bad = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    return (r['words'], bad, tag, f'{tag:22s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} diff={bad:3d}')


BASE = open(ROOT / 'tools/scratch/nonmatching/T-149/func_801B0CDC.c').read()
DECL_RE = re.compile(r'    u8 sp98\[0x40\];\n    s32 sp94;\n    struct \{ f32 x, y, z; \} eye;\n    f32 temp_f0; f32 temp_f12;\n    f64 var_f18;\n    u32 alpha;\n    T025Gfx0CDC \*temp_v1;\n')
assert DECL_RE.search(BASE)
DECLS = {
 'arr': '    u8 sp98[0x40];\n',
 'sp94': '    s32 sp94;\n',
 'eye': '    struct { f32 x, y, z; } eye;\n',
 'f0': '    f32 temp_f0;\n',
 'f12': '    f32 temp_f12;\n',
 'f18': '    f64 var_f18;\n',
 'alpha': '    u32 alpha;\n',
 'tv1': '    T025Gfx0CDC *temp_v1;\n',
}


def build(order):
    body = ''.join(DECLS[k] for k in order)
    return DECL_RE.sub(body, BASE, count=1)


def main():
    res = []
    keys = list(DECLS)
    import json
    sub = [list(o) for o in itertools.permutations(keys)]
    print(len(sub), flush=True)
    for i, order in enumerate(sub):
        res.append(score(build(order), f'{i}'))
    for w, b, t, line in sorted(res)[:14]:
        print(line, flush=True)


main()
