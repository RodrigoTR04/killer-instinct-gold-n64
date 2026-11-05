#!/usr/bin/env python3
"""T-169 1B1A7C: search loop/guard spellings for 4x unroll WITH div.s inside."""
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

BODY = '''            ratio = amount / 50.0f;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0->y = (arg1->y * scale) >> 8;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);
'''

HEAD = 'f32 f(V *arg0, V *arg1, f32 distance, s32 count) {\n' \
       '    f32 amount = func_801B1A14(distance, 50.0f, 200.0f);\n' \
       '    f32 ratio;\n    s16 scale;\n    s32 i, n;\n'

LOOPS = {
 'le': ('    for (i = 0; i <= count; i++, arg0++, arg1++) {\n', '        if (arg1->z >= 6) {\n', BODY, '        }\n    }\n'),
 'lt_n': ('    for (i = 0, n = count + 1; i < n; i++, arg0++, arg1++) {\n', '        if (arg1->z >= 6) {\n', BODY, '        }\n    }\n'),
 'lt_n_eq': ('    n = count + 1;\n    for (i = 0; i < n; i++, arg0++, arg1++) {\n', '        if (arg1->z >= 6) {\n', BODY, '        }\n    }\n'),
 'ne_n': ('    for (i = 0, n = count + 1; i != n; i++, arg0++, arg1++) {\n', '        if (arg1->z >= 6) {\n', BODY, '        }\n    }\n'),
 'cont': ('    for (i = 0; i <= count; i++, arg0++, arg1++) {\n', '        if (arg1->z < 6) {\n            continue;\n        }\n        {\n', BODY, '        }\n    }\n'),
 'cont_bare': ('    for (i = 0; i <= count; i++, arg0++, arg1++) {\n', '        if (arg1->z < 6) continue;\n        {\n', BODY, '        }\n    }\n'),
 'while_le': ('    i = 0;\n    while (i <= count) {\n', '        if (arg1->z >= 6) {\n', BODY, '        }\n        i++; arg0++; arg1++;\n    }\n'),
 'for_body_only': ('    for (i = 0; i <= count; i++, arg0++, arg1++) {\n', '        if (arg1->z >= 6) {\n            do {\n', BODY, '            } while (0);\n        }\n    }\n'),
}

VARIANTS = {}
for k, v in LOOPS.items():
    VARIANTS[k] = v
# with s16 scale declared but ratio hoisted out of the if
VARIANTS['hoist_ratio_in_if'] = ('    for (i = 0; i <= count; i++, arg0++, arg1++) {\n', '        ratio = amount / 50.0f;\n        if (arg1->z >= 6) {\n',
                                 '            scale = (s32) ((ratio * 256.0f) + 256.0f);\n' + BODY.split('\n', 2)[2], '        }\n    }\n')


def run(item):
    name, (loop, guard, body, tail) = item
    src = PRE + HEAD + loop + guard + body + tail + '    return (f32) ((f64) amount * 1.5);\n}\n'
    d = tempfile.mkdtemp(prefix='p8-')
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
    factor = int(m.group(2)) + 1 if m else 1
    return name, f'unroll={factor}x multu={len(re.findall(chr(92)+"bmultu"+chr(92)+"b", asm))} div.s={len(re.findall(chr(92)+"bdiv"+chr(92)+".s"+chr(92)+"b", asm))} n={len(re.findall(r"^ +[0-9a-f]+:", asm, re.M))}'


with cf.ThreadPoolExecutor(8) as pool:
    for name, res in pool.map(run, VARIANTS.items()):
        print(f'{name:22s} {res}')
