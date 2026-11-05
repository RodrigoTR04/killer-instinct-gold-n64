#!/usr/bin/env python3
"""T-169 1B1A7C: target body is 5 copies of (div.s, mul.s, add.s, mul.s,
cvt.d.s, trunc.w.s, mul.d, trunc.w.s, mfc1, nop, sll, sra, multu, trunc.w.d,
mfc1, mfc1, mflo, sra, sh, lh, sh, multu, mflo, sra, addu, sh) = 27 insns/copy.
Search honest C that produces div.s inside a 4x-unrolled copy."""
import concurrent.futures as cf
import itertools
import re
import subprocess
import tempfile
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
PRE = '#include "common.h"\ntypedef struct { s16 x, y, z; u8 rest[10]; } V;\nf32 func_801B1A14(f32, f32, f32);\n'


def build(decls, body, loop='    for (i = 0; i <= count; i++, arg0++, arg1++) {\n',
          guard='        if (arg1->z >= 6) {\n', close='        }\n    }\n'):
    src = ('f32 f(V *arg0, V *arg1, f32 distance, s32 count) {\n'
           '    f32 amount = func_801B1A14(distance, 50.0f, 200.0f);\n'
           + ''.join('    ' + d + '\n' for d in decls)
           + loop + guard + body + close
           + '    return (f32) ((f64) amount * 1.5);\n}\n')
    return PRE + src


BODY_CORE = '''            ratio = amount / 50.0f;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0->y = (arg1->y * scale) >> 8;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);
'''

# What if the two multiplies share ONE result: y and x both derived from a
# single multu by reusing `scale` differently? Try a helper local holding
# `arg1->y * scale` so only one multiply is visible... not honest. Instead try
# variants where the multiply is written on a u16 pixel, or where x uses the
# already-scaled y? Not honest either.

VARIANTS = {
 'base': (['f32 ratio;', 's16 scale;', 's32 i;'], BODY_CORE),
 'y_first_z_last': (['f32 ratio;', 's16 scale;', 's32 i;'],
                    '            ratio = amount / 50.0f;\n'
                    '            scale = (s32) ((ratio * 256.0f) + 256.0f);\n'
                    '            arg0->y = (arg1->y * scale) >> 8;\n'
                    '            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);\n'
                    '            arg0->z = (s32) ((f64) amount * 0.5);\n'),
 'z_first': (['f32 ratio;', 's16 scale;', 's32 i;'],
             '            arg0->z = (s32) ((f64) amount * 0.5);\n' + BODY_CORE.split('\n', 0)[0] +
             '            ratio = amount / 50.0f;\n'
             '            scale = (s32) ((ratio * 256.0f) + 256.0f);\n'
             '            arg0->y = (arg1->y * scale) >> 8;\n'
             '            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);\n'),
 'ratio_local_hoist_in_guard': (['f32 ratio;', 's16 scale;', 's32 i;'],
                                '            ratio = amount / 50.0f;\n'
                                '            scale = (s32) ((ratio * 256.0f) + 256.0f);\n'
                                '            arg0->y = (arg1->y * scale) >> 8;\n'
                                '            arg0->z = (s32) ((f64) amount * 0.5);\n'
                                '            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);\n'),
 # scale computed from ratio but x reuses arg0->y's multiply result via arg1->y? no.
 'mul_as_u16_ptr': (['f32 ratio;', 's16 scale;', 's32 i;'],
                    '            ratio = amount / 50.0f;\n'
                    '            scale = (s32) ((ratio * 256.0f) + 256.0f);\n'
                    '            *(s16 *) &arg0->y = (s16) ((arg1->y * scale) >> 8);\n'
                    '            arg0->z = (s32) ((f64) amount * 0.5);\n'
                    '            *(s16 *) &arg0->x = (s16) (((arg1->x * scale) >> 8) + (s32) (ratio * distance));\n'),
}


def run(name):
    decls, body = VARIANTS[name]
    src = build(decls, body)
    d = tempfile.mkdtemp(prefix='p13-')
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
        return name, 'FAIL ' + r.stderr.strip().splitlines()[0][:60]
    asm = subprocess.run([str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'), '-dr', '--no-show-raw-insn', str(o)],
                         capture_output=True, text=True).stdout
    m = re.search(r'andi\s+\w+,(\w+),0x([13])\b', asm)
    f = int(m.group(2)) + 1 if m else 1
    return name, f'{f}x div.s={len(re.findall(r"bdiv.sb", asm))} multu={len(re.findall(r"bmultub", asm))} n={len(re.findall(r"^ +[0-9a-f]+:", asm, re.M))}'


with cf.ThreadPoolExecutor(6) as pool:
    for n, res in pool.map(run, VARIANTS):
        print(f'{n:30s} {res}')
