#!/usr/bin/env python3
"""23C0: sweep declaration orders of the real locals and filter on the target's
exact stack signature (frame 0x70, position at 0x64, velocity at 0x58 only
address-taken, three temps at 0x4c/0x50/0x54, s32 at 0x3c, u8 at 0x4b).
"""
import importlib.util, sys, tempfile, re, itertools, concurrent.futures
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801C23C0'
OUT = ROOT / 'tools/scratch/nonmatching/T-170'
BASE = (OUT / 'c23_clean.c').read_text()
TARGET_FRAME = 0x70
TARGET_SLOTS = {0x4b, 0x4c, 0x50, 0x54, 0x58, 0x64}

HEAD = 'u8 func_801C23C0(FrontendGfxWords **arg0, FrontendRenderContext *arg1) {\n'
OLD_DECL = """    f32 position[3];
    f32 velocity[3];
    f32 angle;
    f32 rise;
    f32 fade;
    f32 t2;
    f32 pitch;
    f32 yaw;
    f32 f14;
    u8 result;
    FrontendGfxWords *g;
"""
assert HEAD + OLD_DECL in BASE

# group -> declaration text. Order in the tuple is the permutation unit.
GROUPS = {
    'pos': '    f32 position[3];\n',
    'vel': '    f32 velocity[3];\n',
    't3': '    f32 fade;\n    f32 pitch;\n    f32 yaw;\n',
    'res': '    u8 result;\n',
    'sh': '    s32 t2;\n',
    'p2': '    f32 angle;\n    f32 rise;\n',
    'g': '    FrontendGfxWords *g;\n',
}


def slots_and_frame(lines):
    d = set()
    fr = 0
    for l in lines:
        m = re.search(r'addiu\s+sp,sp,-(\d+)', l)
        if m:
            fr = int(m.group(1))
        for part in l.split(','):
            g = re.match(r'^(-?\d+)\(sp\)$', part.strip())
            if g:
                d.add(int(g.group(1)))
    return fr, d


def score(order, tag):
    decl = ''.join(GROUPS[g] for g in order)
    src = BASE.replace(OLD_DECL, decl, 1)
    p = OUT / f'w23_{tag}.c'
    p.write_text(src)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception as e:
        return (False, 9999, f'{tag:14s} ERROR {str(e)[-60:]}')
    fr, sl = slots_and_frame(mine)
    sl = {x for x in sl if x >= 0x40}
    ok = fr == TARGET_FRAME and sl == TARGET_SLOTS
    return (ok, r['words'], f'{tag:14s} frame=0x{fr:x} w={r["words"]:4d} {r["compiled"]}/{r["original"]} '
                            f'{"SLOTMATCH" if ok else ""} n={len(sl)}')


if __name__ == '__main__':
    keys = list(GROUPS)
    jobs = [(p, ''.join(k[0] for k in p)) for p in itertools.permutations(keys)]
    with concurrent.futures.ThreadPoolExecutor(max_workers=12) as pool:
        rows = list(pool.map(lambda j: score(*j), jobs))
    exact = [r for r in rows if r[0]]
    rows.sort(key=lambda r: (not r[0], r[1]))
    for r in (exact or rows[:15]):
        print(r[2])
    print(f'{len(exact)} exact slot matches of {len(rows)}')
