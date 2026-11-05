#!/usr/bin/env python3
"""0CDC: search honest local declarations that reproduce the target 0xD8 frame."""
import importlib.util, sys, tempfile, re, itertools, json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801B0CDC'
outdir = ROOT / 'tools/scratch/nonmatching/T-170'
BASE = (outdir / 'func_801B0CDC.c').read_text()
OLD = ("    u8 sp98[0x40];\n    s32 sp94;\n    struct { f32 x, y, z; } eye;\n"
       "    f32 temp_f0; f32 temp_f12;\n    f64 var_f18;\n    u32 alpha;\n    T025Gfx0CDC *temp_v1;\n")
assert OLD in BASE


def score(src, tag):
    p = outdir / f'q_{tag}.c'
    p.write_text(src)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
        fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
        return (int(fr.group(1)) if fr else 0, r['words'], r['compiled'], len(mine))
    except Exception as e:
        return (0, 99999, 0, 0)


if __name__ == '__main__':
    lines = OLD.rstrip('\n').split('\n')
    res = []
    # try moving eye to each position and various kinds; and inserting a struct with n floats
    for n in range(3, 13):
        for pos in range(len(lines) + 1):
            decl = f'    struct {{ f32 v[0x{n:X}]; }} aux;\n'
            new = list(lines)
            new.insert(pos, decl.rstrip('\n'))
            src = BASE.replace(OLD, '\n'.join(new) + '\n', 1)
            fr, w, comp, n_ = score(src, f'a{n}_{pos}')
            res.append((fr, w, comp, n_, f'a{n}_{pos}'))
    for fr, w, comp, n_, tag in sorted(res, key=lambda x: (x[0] != 216, x[1])):
        print(f'{tag:10s} frame={fr} w={w} {comp} n={n_}')
