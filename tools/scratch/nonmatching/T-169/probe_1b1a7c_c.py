#!/usr/bin/env python3
"""T-169 1B1A7C probe 3: which multiply spelling gives the target's
`sll 16 / sra 16 / multu` pair, and which body keeps the 4x unroller with
div.s inside the loop."""
import concurrent.futures as cf
import re
import subprocess
import tempfile
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')

PRE = '''#include "common.h"
typedef struct { s16 x, y, z; u8 rest[10]; } V;
f32 func_801B1A14(f32, f32, f32);
'''

# each: (ratio placement, scale decl, y expr, x expr, z placement)
VARIANTS = {}

for sc in ('s16', 's32', 'u16'):
    for where in ('in', 'out'):
        for cast in ('plain', 'cast'):
            for xf in ('yx_normal', 'zfirst', 'zlast'):
                key = f'{sc}_{where}_{cast}_{xf}'
                if where == 'out':
                    ratio_lines = '    ratio = amount / 50.0f;\n'
                    scale_lines = f'    {sc} scale = ({"s16" if sc != "s16" else "s16"}) (s32) ((ratio * 256.0f) + 256.0f);\n'
                    inner_ratio = ''
                else:
                    ratio_lines = ''
                    scale_lines = f'    {sc} scale;\n'
                    inner_ratio = '            ratio = amount / 50.0f;\n            scale = (s16) (s32) ((ratio * 256.0f) + 256.0f);\n'
                yexpr = '(arg1->y * (s16) scale) >> 8' if cast == 'cast' else '(arg1->y * scale) >> 8'
                xexpr = '((arg1->x * (s16) scale) >> 8)' if cast == 'cast' else '((arg1->x * scale) >> 8)'
                zstmt = '            arg0->z = (s32) ((f64) amount * 0.5);\n'
                ys = f'            arg0->y = {yexpr};\n'
                xs = f'            arg0->x = {xexpr} + (s32) (ratio * distance);\n'
                if xf == 'yx_normal':
                    body = ys + zstmt + xs
                elif xf == 'zfirst':
                    body = zstmt + ys + xs
                else:
                    body = ys + xs + zstmt
                VARIANTS[key] = f'''f32 f(V *arg0, V *arg1, f32 distance, s32 count) {{
    f32 amount = func_801B1A14(distance, 50.0f, 200.0f);
    f32 ratio;
{scale_lines}{ratio_lines}    s32 i;
    for (i = 0; i <= count; i++, arg0++, arg1++) {{
        if (arg1->z >= 6) {{
{inner_ratio}{body}        }}
    }}
    return (f32) ((f64) amount * 1.5);
}}'''


def run(item):
    name, body = item
    d = tempfile.mkdtemp(prefix='p3-')
    c = Path(d) / 'p.c'
    c.write_text(PRE + body + '\n')
    o = c.with_suffix('.o')
    cmd = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py',
           ROOT / 'tools/ext/ido/5.3/cc', '--',
           ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0',
           '-I', str(ROOT / 'include'), '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm',
           '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', o, c]
    r = subprocess.run([str(x) for x in cmd], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        return name, 'FAIL'
    asm = subprocess.run([str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'), '-dr', '--no-show-raw-insn', str(o)],
                         capture_output=True, text=True).stdout
    m = re.findall(r'andi\s+\w+,(\w+),0x([13])\b', asm)
    multu = len(re.findall(r'\bmultu\b', asm))
    mult = len(re.findall(r'\bmult\b', asm))
    divs = len(re.findall(r'\bdiv\.s\b', asm))
    insns = len(re.findall(r'^ +[0-9a-f]+:', asm, re.M))
    return name, f'unroll={m} multu={multu} mult={mult} div.s={divs} n={insns}'


with cf.ThreadPoolExecutor(8) as pool:
    rows = list(pool.map(run, VARIANTS.items()))
for name, res in rows:
    print(f'{name:34s} {res}')
