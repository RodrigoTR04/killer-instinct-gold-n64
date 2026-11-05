#!/usr/bin/env python3
"""T-169 1B1A7C probe: does ANY honest body with two integer multiplies keep
IDO 5.3's 4x unroller? Compile standalone TUs with the real flags and grep the
preheader mask (`andi ...,0x3` => 4x, `andi ...,0x1` => 2x)."""
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
 'base2mul': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i;
    for (i = 0; i <= count; i++) {
        if (a1[i].z >= 6) {
            ratio = amount / 50.0f;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            a0[i].y = (a1[i].y * scale) >> 8;
            a0[i].z = (s32)((f64)amount * 0.5);
            a0[i].x = ((a1[i].x * scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 'u16scale': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; u16 scale; s32 i;
    for (i = 0; i <= count; i++) {
        if (a1[i].z >= 6) {
            ratio = amount / 50.0f;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            a0[i].y = (a1[i].y * scale) >> 8;
            a0[i].z = (s32)((f64)amount * 0.5);
            a0[i].x = ((a1[i].x * scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 # scale held as s32 (no s16 narrowing) -> sll16/sra16 come from the cast target
 's32scale': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s32 scale; s32 i;
    for (i = 0; i <= count; i++) {
        if (a1[i].z >= 6) {
            ratio = amount / 50.0f;
            scale = (s16)(s32)((ratio * 256.0f) + 256.0f);
            a0[i].y = (s16)((a1[i].y * scale) >> 8);
            a0[i].z = (s32)((f64)amount * 0.5);
            a0[i].x = (s16)(((a1[i].x * scale) >> 8) + (s32)(ratio * d));
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 # z stored first, x last (target order: y, z, x)
 'zxfirst': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i;
    for (i = 0; i <= count; i++) {
        if (a1[i].z >= 6) {
            ratio = amount / 50.0f;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            a0[i].z = (s32)((f64)amount * 0.5);
            a0[i].y = (a1[i].y * scale) >> 8;
            a0[i].x = ((a1[i].x * scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 # x via a named local temp holding the scaled value
 'xtemp': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i; s32 xs;
    for (i = 0; i <= count; i++) {
        if (a1[i].z >= 6) {
            ratio = amount / 50.0f;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            a0[i].y = (a1[i].y * scale) >> 8;
            a0[i].z = (s32)((f64)amount * 0.5);
            xs = (a1[i].x * scale) >> 8;
            a0[i].x = xs + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 # multiply by scale expressed as (scale >> 8) * 256 trick? no -- try (v * scale) / 256
 'div256': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 scale; s32 i;
    for (i = 0; i <= count; i++) {
        if (a1[i].z >= 6) {
            ratio = amount / 50.0f;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            a0[i].y = (a1[i].y * scale) / 256;
            a0[i].z = (s32)((f64)amount * 0.5);
            a0[i].x = ((a1[i].x * scale) / 256) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 # scale as a pointer deref (inhibit some folding)
 'ptrscale': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    f32 ratio; s16 s; s16 *scale = &s; s32 i;
    for (i = 0; i <= count; i++) {
        if (a1[i].z >= 6) {
            ratio = amount / 50.0f;
            s = (s32)((ratio * 256.0f) + 256.0f);
            a0[i].y = (a1[i].y * *scale) >> 8;
            a0[i].z = (s32)((f64)amount * 0.5);
            a0[i].x = ((a1[i].x * *scale) >> 8) + (s32)(ratio * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 # amount kept only as f32, ratio computed twice (2 div.s)
 'tworatio': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
    f32 amount = func_801B1A14(d, 50.0f, 200.0f);
    s16 scale; s32 i;
    for (i = 0; i <= count; i++) {
        if (a1[i].z >= 6) {
            scale = (s32)(((amount / 50.0f) * 256.0f) + 256.0f);
            a0[i].y = (a1[i].y * scale) >> 8;
            a0[i].z = (s32)((f64)amount * 0.5);
            a0[i].x = ((a1[i].x * scale) >> 8) + (s32)((amount / 50.0f) * d);
        }
    }
    return (f32)((f64)amount * 1.5);
}''',
 # struct-field pointer walk with a running source/dest pointer (target's a1/a0 cursors)
 'walk': '''f32 f(V *a0, V *a1, f32 d, s32 count) {
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
}


def compile_and_scan(name, body):
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
    mult = len(re.findall(r'\bmultu\b', asm))
    divs = len(re.findall(r'\bdiv\.s\b', asm))
    return name, f'masks={m} multu={mult} div.s={divs}'


with cf.ThreadPoolExecutor(6) as pool:
    for name, res in pool.map(lambda kv: compile_and_scan(*kv), BODIES.items()):
        print(f'{name:12s} {res}')
