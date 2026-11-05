#!/usr/bin/env python3
"""T-169 1B1A7C probe 2: the pointer-walk shape unrolls 4x. Find which parts of
the body must be hoisted and which can stay inside, matching the target's
5 copies => 5 div.s and 10 multu."""
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

BODIES = {
 'walk_hoist_both': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i;
    ratio = amount / 50.0f;
    scale = (s32)((ratio * 256.0f) + 256.0f);
    for (i = 0; i <= count; i++, a0++, a1++) {
        if (a1->z >= 6) {
            a0->y = (a1->y * scale) >> 8;
            a0->z = (s32)((f64)amount * 0.5);
            a0->x = ((a1->x * scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 'walk_inline_both': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i;
    for (i = 0; i <= count; i++, a0++, a1++) {
        if (a1->z >= 6) {
            ratio = amount / 50.0f;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            a0->y = (a1->y * scale) >> 8;
            a0->z = (s32)((f64)amount * 0.5);
            a0->x = ((a1->x * scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 'walk_index_i': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i;
    ratio = amount / 50.0f;
    scale = (s32)((ratio * 256.0f) + 256.0f);
    for (i = 0; i <= count; i++) {
        if (a1[i].z >= 6) {
            a0[i].y = (a1[i].y * scale) >> 8;
            a0[i].z = (s32)((f64)amount * 0.5);
            a0[i].x = ((a1[i].x * scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 'walk_hoist_scale_only': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i;
    scale = (s32)(((amount / 50.0f) * 256.0f) + 256.0f);
    for (i = 0; i <= count; i++, a0++, a1++) {
        if (a1->z >= 6) {
            ratio = amount / 50.0f;
            a0->y = (a1->y * scale) >> 8;
            a0->z = (s32)((f64)amount * 0.5);
            a0->x = ((a1->x * scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 'walk_noscale_local': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s32 i;
    ratio = amount / 50.0f;
    for (i = 0; i <= count; i++, a0++, a1++) {
        if (a1->z >= 6) {
            a0->y = (a1->y * (s16)(s32)((ratio * 256.0f) + 256.0f)) >> 8;
            a0->z = (s32)((f64)amount * 0.5);
            a0->x = ((a1->x * (s16)(s32)((ratio * 256.0f) + 256.0f)) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 'walk_ratio_pp': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i;
    ratio = amount / 50.0f;
    for (i = 0; i <= count; i++, a0++, a1++) {
        if (a1->z >= 6) {
            scale = (s32)((ratio * 256.0f) + 256.0f);
            a0->y = (a1->y * scale) >> 8;
            a0->z = (s32)((f64)amount * 0.5);
            a0->x = ((a1->x * scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 'walk_z_double_inloop': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i; f64 half;
    ratio = amount / 50.0f;
    scale = (s32)((ratio * 256.0f) + 256.0f);
    for (i = 0; i <= count; i++, a0++, a1++) {
        if (a1->z >= 6) {
            a0->y = (a1->y * scale) >> 8;
            a0->x = ((a1->x * scale) >> 8) + (s32)(ratio * d);
            half = (f64)amount * 0.5;
            a0->z = (s32)half;
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 'walk_while': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i; V *e;
    ratio = amount / 50.0f;
    scale = (s32)((ratio * 256.0f) + 256.0f);
    e = a1 + count + 1;
    for (; a1 != e; a0++, a1++) {
        if (a1->z >= 6) {
            a0->y = (a1->y * scale) >> 8;
            a0->z = (s32)((f64)amount * 0.5);
            a0->x = ((a1->x * scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 'walk_do': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i = 0;
    ratio = amount / 50.0f;
    scale = (s32)((ratio * 256.0f) + 256.0f);
    do {
        if (a1->z >= 6) {
            a0->y = (a1->y * scale) >> 8;
            a0->z = (s32)((f64)amount * 0.5);
            a0->x = ((a1->x * scale) >> 8) + (s32)(ratio * d);
        }
        i++; a0++; a1++;
    } while (i <= count);
    return (f32)((f64)amount * 1.5);
}''',
 'walk_hoist_both_ge': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i;
    ratio = amount / 50.0f;
    scale = (s32)((ratio * 256.0f) + 256.0f);
    for (i = 0; i <= count; i++, a0++, a1++) {
        if (a1->z < 6) {
            continue;
        }
        a0->y = (a1->y * scale) >> 8;
        a0->z = (s32)((f64)amount * 0.5);
        a0->x = ((a1->x * scale) >> 8) + (s32)(ratio * d);
    }
    return (f32)((f64)amount * 1.5);
}''',
}


def run(name, body):
    src = PRE + body + '\n'
    d = tempfile.mkdtemp(prefix='probe1b-')
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
        return name, 'FAIL ' + r.stderr.strip().splitlines()[0][:70]
    asm = subprocess.run([str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'), '-dr', '--no-show-raw-insn', str(o)],
                         capture_output=True, text=True).stdout
    m = re.findall(r'andi\s+\w+,(\w+),0x([13])\b', asm)
    return name, (f'masks={m} multu={len(re.findall(chr(92)+"bmultu"+chr(92)+"b", asm))} '
                  f'div.s={len(re.findall(chr(92)+"bdiv"+chr(92)+r".s"+chr(92)+"b", asm))} '
                  f'insns={len(re.findall(r"^ +[0-9a-f]+:", asm, re.M))}')


with cf.ThreadPoolExecutor(6) as pool:
    for name, res in pool.map(lambda kv: run(*kv), BODIES.items()):
        print(f'{name:24s} {res}')
