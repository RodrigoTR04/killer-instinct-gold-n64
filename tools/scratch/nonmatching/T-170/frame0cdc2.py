#!/usr/bin/env python3
"""0CDC: find an honest declaration set that puts the 0x40 lookat buffer at
sp+0x98 (frame 0xD8) and the sin/cos spill temps at sp+0x58/0x5C."""
import importlib.util, sys, tempfile, re, itertools, concurrent.futures
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

# extra honest locals that the function genuinely needs but currently reuses temps
EXTRAS = {
    'eye': '    struct { f32 x, y, z; } eye;\n',
    'e2': '    f32 eyeX, eyeY;\n',
    't0': '    f32 temp_f0;\n',
    't12': '    f32 temp_f12;\n',
    'vf18': '    f64 var_f18;\n',
    'n1': '    f32 n1;\n',
}


def score(src, tag):
    p = outdir / f'y_{tag}.c'
    p.write_text(src)
    try:
        r = screen.measure(fn, p)
        source, tu = cm.build_source(fn, p, False)
        with tempfile.TemporaryDirectory() as d:
            o = cm.compile_source(source, Path(d)/'c.c')
            pairs = cm.draft_raw(o, fn)
        mine = [cm.canon(cm.apply_relocs(i, rl)) for _, i, rl in pairs]
    except Exception:
        return (0, 99999, '')
    fr = re.search(r'addiu sp,sp,-(\d+)', ' '.join(mine))
    fr = int(fr.group(1)) if fr else 0
    buf = re.search(r'addiu a0,sp,(\d+)', ' '.join(mine))
    buf = int(buf.group(1)) if buf else -1
    n58 = sum(1 for x in mine if re.search(r',(88|92)\(sp\)', x))
    return (fr, r['words'], f'{tag:16s} frame=0x{fr:x} buf=0x{buf:x} w={r["words"]:4d} {r["compiled"]}/{r["original"]} n58={n58}')


if __name__ == '__main__':
    lines = OLD.rstrip('\n').split('\n')
    jobs = []
    # insert each extra at every position
    for name, decl in EXTRAS.items():
        for pos in range(len(lines) + 1):
            new = list(lines)
            new.insert(pos, decl.rstrip('\n'))
            if name in ('eye',):
                new = [l for l in new if 'struct { f32 x, y, z; }' in l or 'eye' not in l or 'struct' in l]
            jobs.append((BASE.replace(OLD, '\n'.join(new) + '\n', 1), f'{name}{pos}'))
    with concurrent.futures.ThreadPoolExecutor(max_workers=12) as pool:
        rows = list(pool.map(lambda j: score(*j), jobs))
    rows.sort(key=lambda r: (r[0] != 216, r[1]))
    for r in rows[:20]:
        print(r[2])
