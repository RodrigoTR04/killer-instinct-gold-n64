#!/usr/bin/env python3
"""23C0: the 181 draft declares 19 locals; the target's frame only needs ~7.
Drop declarations whose names appear nowhere else, then drop groups, and report
score + frame + buffer offsets. Filter: frame 0x70 and buffers at 0x64/0x58.
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
SRC = (OUT / 'func_801C23C0.c').read_text()
i = SRC.index('u8 func_801C23C0')
bs = SRC.index('{', i) + 1
DE = SRC.index('    var_f0 = (f32)', bs)
DECL = SRC[bs:DE]
PRE, POST = SRC[:bs], SRC[DE:]
LINES = [l for l in DECL.splitlines() if l.strip()]
NAMES = [re.search(r'(\w+)\s*(\[|;|=)', l.strip()).group(1) for l in LINES]
print('locals:', len(NAMES))


def uses(name):
    return len(re.findall(r'\b' + re.escape(name) + r'\b', POST))


UNUSED = {i for i, n in enumerate(NAMES) if uses(n) == 0}
print('unused:', sorted(NAMES[i] for i in UNUSED))


def build(drop):
    keep = [l for i, l in enumerate(LINES) if i not in drop]
    return PRE + '\n'.join(keep) + '\n' + POST


def run(drop, tag):
    p = OUT / f's23_{tag}.c'
    p.write_text(build(drop))
    try:
        r = screen.measure(fn, p)
        s, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(s, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(x, rl)) for _, x, rl in pairs]
    except Exception:
        return (9999, 0, '', f'{tag:16s} ERR')
    fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
    frv = int(fr.group(1)) if fr else 0
    a2 = re.search(r'addiu a2,sp,(\d+)', ' '.join(mine))
    a3 = re.search(r'addiu a3,sp,(\d+)', ' '.join(mine))
    ok = frv == 0x70 and a2 and a3 and int(a2.group(1)) == 0x64 and int(a3.group(1)) == 0x58
    return (r['words'], r['compiled'], f'{tag:16s} w={r["words"]:4d} {r["compiled"]}/{r["original"]} '
                                        f'frame=0x{frv:x} pos=0x{int(a2.group(1)):x} vel=0x{int(a3.group(1)):x} '
                                        f'{"LAYOUT" if ok else ""}')


if __name__ == '__main__':
    jobs = []
    base = set(UNUSED)
    jobs.append((base, 'base'))
    # also try dropping each of the remaining scalars in combination with UNUSED
    rest = [i for i in range(len(LINES)) if i not in UNUSED]
    for k in (1, 2, 3):
        for combo in itertools.combinations(rest, k):
            jobs.append((base | set(combo), ''.join(map(str, sorted(combo)))))
    with concurrent.futures.ThreadPoolExecutor(max_workers=12) as pool:
        rows = list(pool.map(lambda j: run(*j), jobs))
    layout = [r for r in rows if 'LAYOUT' in r[3]]
    rows.sort(key=lambda r: (not ('LAYOUT' in r[3]), r[0]))
    for r in (layout[:12] or rows[:12]):
        print(r[3])
    print(f'{len(layout)} layout matches of {len(rows)}')
