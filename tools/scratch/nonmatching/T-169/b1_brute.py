#!/usr/bin/env python3
"""T-169 1B1A7C: brute-force which honest body keeps IDO 5.3's 4x unroller
while containing div.s + 2 multu per copy (target: 218 instrs, mask &3)."""
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

# Pieces
RATIO_IN = '            ratio = amount / 50.0f;\n'
SCALE_IN = '            scale = (s32) ((ratio * 256.0f) + 256.0f);\n'
Z = '            arg0->z = (s32) ((f64) amount * 0.5);\n'


def y_stmt(how):
    if how == 'plain':
        return '            arg0->y = (arg1->y * scale) >> 8;\n'
    if how == 'div256':
        return '            arg0->y = (arg1->y * scale) / 256;\n'
    if how == 's16cast':
        return '            arg0->y = (s16) ((arg1->y * scale) >> 8);\n'
    if how == 'temp':
        return '            sy = (arg1->y * scale) >> 8; arg0->y = sy;\n'
    raise KeyError(how)


def x_stmt(how):
    if how == 'plain':
        return '            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);\n'
    if how == 'div256':
        return '            arg0->x = ((arg1->x * scale) / 256) + (s32) (ratio * distance);\n'
    if how == 's16cast':
        return '            arg0->x = (s16) (((arg1->x * scale) >> 8) + (s32) (ratio * distance));\n'
    if how == 'temp':
        return '            sx = ((arg1->x * scale) >> 8) + (s32) (ratio * distance); arg0->x = sx;\n'
    raise KeyError(how)


def combo_stmt():
    return ('            arg0->y = (arg1->y * scale) >> 8, '
            'arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);\n')


LOOPS = {
 'incr': '    for (i = 0; i <= count; i++, arg0++, arg1++) {\n',
 'incr_ge': '    for (i = 0; i <= count; i++, arg0++, arg1++) {\n',
 'n': '    for (i = 0, n = count + 1; i < n; i++, arg0++, arg1++) {\n',
 'idx': '    for (i = 0; i <= count; i++, arg0++, arg1++) {\n',
}

GUARD = {
 'ge': '        if (arg1->z >= 6) {\n',
 'ltcont': '        if (arg1->z < 6) { continue; }\n',
}

VARIANTS = {}
for loop, guard, yh, xh, zpos in itertools.product(
        ['incr', 'n'], ['ge'], ['plain', 'div256', 'temp'], ['plain', 'div256', 'temp'], ['mid', 'first', 'last']):
    key = f'{loop}_{guard}_{yh}_{xh}_{zpos}'
    body = ''
    if zpos == 'first':
        body += Z
    body += y_stmt(yh) if yh != 'temp' else y_stmt(yh)
    if zpos == 'mid':
        body += Z
    body += x_stmt(xh) if xh != 'temp' else x_stmt(xh)
    if zpos == 'last':
        body += Z
    VARIANTS[key] = loop, guard, body

VARIANTS['comma'] = ('incr', 'ge', combo_stmt())
VARIANTS['comma_z'] = ('incr', 'ge', combo_stmt() + Z)


def run(item):
    name, spec = item
    loop, guard, body = spec
    loop = LOOPS[loop]
    guard = GUARD[guard]
    decls = '    f32 amount = func_801B1A14(distance, 50.0f, 200.0f);\n'
    decls += '    f32 ratio; s16 scale; s32 i, n, sy, sx;\n'
    src = PRE + 'f32 f(V *arg0, V *arg1, f32 distance, s32 count) {\n' + decls + loop + guard + body + \
          '        }\n    }\n    return (f32) ((f64) amount * 1.5);\n}\n'
    if guard == 'ltcont':
        src = src.replace('{ continue; }\n', '\n').replace('        if (arg1->z < 6) {\n', '        if (arg1->z < 6) continue;\n')
    d = tempfile.mkdtemp(prefix='p6-')
    c = Path(d) / 'p.c'
    c.write_text(src)
    o = c.with_suffix('.o')
    cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
           ROOT / 'tools/ext/ido/5.3/cc', '--',
           ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
           '-I', str(ROOT / 'include'), '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
           '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', o, c]
    r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        return name, None
    asm = subprocess.run([str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'), '-dr', '--no-show-raw-insn', str(o)],
                         capture_output=True, text=True).stdout
    m = re.search(r'andi\s+\w+,(\w+),0x([13])\b', asm)
    factor = int(m.group(2)) + 1 if m else 1
    return name, (factor, len(re.findall(r'\bmultu\b', asm)), len(re.findall(r'\bdiv\.s\b', asm)),
                  len(re.findall(r'^ +[0-9a-f]+:', asm, re.M)))


rows = []
with cf.ThreadPoolExecutor(8) as pool:
    for name, res in pool.map(run, VARIANTS.items()):
        if res:
            rows.append((name, res))
rows.sort(key=lambda kv: (-kv[1][0], abs(kv[1][3] - 218)))
for name, (f, mu, dv, n) in rows[:25]:
    print(f'{name:30s} unroll={f}x multu={mu} div.s={dv} n={n}')
