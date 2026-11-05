#!/usr/bin/env python3
"""T-169 1B1A7C: declaring `s32 i, n, sy, sx;` flipped the loop to 4x. Find the
full-body spelling (ratio + scale + div.s inside) that keeps 4x and lands on
the target's 218 instrs."""
import concurrent.futures as cf
import itertools
import re
import subprocess
import tempfile
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
PRE = '''#include "common.h"
typedef struct { s16 x, y, z; u8 rest[10]; } V;
f32 func_801B1A14(f32, f32, f32);
'''

DECLS = {
    'i': '    s32 i;\n',
    'ii_n': '    s32 i, n;\n',
    'i_sy': '    s32 i, sy;\n',
    'i_n_sy': '    s32 i, n, sy;\n',
    'i_n_sy_sx': '    s32 i, n, sy, sx;\n',
    'i_sy_sx': '    s32 i, sy, sx;\n',
    'sep': '    s32 i;\n    s32 n;\n    s32 sy;\n    s32 sx;\n',
}

BODIES = {}

ratio_in = '            ratio = amount / 50.0f;\n'
scale_in = '            scale = (s32) ((ratio * 256.0f) + 256.0f);\n'
Y = '            arg0->y = (arg1->y * scale) >> 8;\n'
Z = '            arg0->z = (s32) ((f64) amount * 0.5);\n'
X = '            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);\n'

BODIES['full_yzx'] = ratio_in + scale_in + Y + Z + X
BODIES['full_yxz'] = ratio_in + scale_in + Y + X + Z
BODIES['full_zyx'] = ratio_in + scale_in + Z + Y + X
BODIES['full_xyz'] = ratio_in + scale_in + X + Y + Z
BODIES['hoist'] = Y + Z + X  # ratio/scale hoisted before loop
BODIES['full_sep_lines'] = ratio_in + '\n' + scale_in + Y + '\n' + Z + '\n' + X

LOOP = '    for (i = 0; i <= count; i++, arg0++, arg1++) {\n'
GUARD = '        if (arg1->z >= 6) {\n'
TAIL = '        }\n    }\n    return (f32) ((f64) amount * 1.5);\n}\n'


def build(decl, body):
    src = PRE + 'f32 f(V *arg0, V *arg1, f32 distance, s32 count) {\n'
    src += '    f32 amount = func_801B1A14(distance, 50.0f, 200.0f);\n'
    src += '    f32 ratio;\n    s16 scale;\n'
    src += DECLS[decl]
    if body == BODIES['hoist']:
        src += '    ratio = amount / 50.0f;\n    scale = (s32) ((ratio * 256.0f) + 256.0f);\n'
    src += LOOP + GUARD + body + TAIL
    return src


def run(args):
    decl, bname = args
    d = tempfile.mkdtemp(prefix='p7-')
    c = Path(d) / 'p.c'
    c.write_text(build(decl, BODIES[bname]))
    o = c.with_suffix('.o')
    cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
           ROOT / 'tools/ext/ido/5.3/cc', '--',
           ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
           '-I', str(ROOT / 'include'), '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
           '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', o, c]
    r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        return f'{decl}_{bname}', None
    asm = subprocess.run([str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'), '-dr', '-d', '--no-show-raw-insn', str(o)],
                         capture_output=True, text=True).stdout
    m = re.search(r'andi\s+\w+,(\w+),0x([13])\b', asm)
    factor = int(m.group(2)) + 1 if m else 1
    return f'{decl}_{bname}', (factor, len(re.findall(r'\bmultu\b', asm)), len(re.findall(r'\bdiv\.s\b', asm)),
                               len(re.findall(r'^ +[0-9a-f]+:', asm, re.M)))


rows = []
with cf.ThreadPoolExecutor(8) as pool:
    for name, res in pool.map(run, itertools.product(DECLS, BODIES)):
        if res:
            rows.append((name, res))
rows.sort(key=lambda kv: (-kv[1][0], abs(kv[1][3] - 218)))
for name, (f, mu, dv, n) in rows[:20]:
    print(f'{name:30s} unroll={f}x multu={mu} div.s={dv} n={n}')
