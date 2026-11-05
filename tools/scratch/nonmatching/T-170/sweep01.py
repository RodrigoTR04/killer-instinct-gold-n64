#!/usr/bin/env python3
"""01EC: sweep declaration orders, filtering on the target slot signature.

Target frame 0xB0; locals live at 0x48 (temporary), 0x60 (float spill),
0x64 (colour), 0x68 (result). Everything at 0x10..0x44 and 0xB4..0xBC is the
outgoing-argument area / incoming parameter homes. So the *local* signature is
{0x48, 0x60, 0x64, 0x68}.
"""
import importlib.util, sys, tempfile, re, itertools, concurrent.futures
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
spec2 = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec2); spec2.loader.exec_module(cm)

fn = 'func_801B01EC'
OUT = ROOT / 'tools/scratch/nonmatching/T-170'
SRC = (OUT / 'func_801B01EC.c').read_text()
HEAD = 's32 func_801B01EC(T164Gfx01EC **arg0, s32 arg1, u8 *arg2, u32 arg3)\n    {\n'
# normalise whatever the draft currently has to a known block
i = SRC.index(HEAD)
PRE = SRC[:i] + HEAD
body = SRC[i + len(HEAD):]
j = body.index('\n\n')
OLDDECL_ACTUAL = body[:j + 1]
BODY = body[j + 2:]

TARGET_FRAME = 0xb0
TARGET_LOCAL = {0x48, 0x60, 0x64, 0x68}

DECLS = {
    'lookat': '    u8 lookat[0x40];\n',
    'g': '    T164Gfx01EC *g;\n',
    'result': '    s32 result;\n',
    'angle': '    f32 angle;\n',
    'rise': '    f32 rise;\n',
    'alpha': '    s32 alpha;\n',
    'elapsed': '    u32 elapsed;\n',
}
KEYS = list(DECLS)


def sign(lines):
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


def run(order, tag):
    src = PRE + ''.join(DECLS[k] for k in order) + '\n' + BODY
    p = OUT / f'o_{tag}.c'
    p.write_text(src)
    try:
        r = screen.measure(fn, p)
        s, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(s, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(x, rl)) for _, x, rl in pairs]
    except Exception as e:
        return (False, 9999, f'{tag:14s} ERROR {str(e)[-50:]}')
    fr, sl = sign(mine)
    loc = {x for x in sl if 0x48 <= x <= 0x6c}
    ok = fr == TARGET_FRAME and loc == TARGET_LOCAL
    return (ok, r['words'], f'{tag:14s} frame=0x{fr:x} w={r["words"]:4d} {r["compiled"]}/{r["original"]} '
                           f'locals={sorted(hex(x) for x in loc)} {"MATCH" if ok else ""}')


if __name__ == '__main__':
    jobs = [(p, ''.join(k[0] for k in p)) for p in itertools.permutations(KEYS)]
    with concurrent.futures.ThreadPoolExecutor(max_workers=12) as pool:
        rows = list(pool.map(lambda x: run(*x), jobs))
    exact = [r for r in rows if r[0]]
    rows.sort(key=lambda r: (not r[0], r[1]))
    for r in (exact or rows[:12]):
        print(r[2])
    print(f'{len(exact)} exact of {len(rows)}')
