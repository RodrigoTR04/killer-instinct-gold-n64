#!/usr/bin/env python3
"""T-169 D47C: make the grayscale store cursor a pointer so IDO allocates the
counter into t0 (the target) instead of a1."""
import concurrent.futures as cf
import importlib.util
import itertools
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/d47cg3'
OUT.mkdir(exist_ok=True)

HEAD = '''extern u8 D_8004AC88;
extern u8 D_8004EA9E[];
extern s32 D_8004EA78;
extern u8 D_8004EA9A;
extern u8 D_8004EAB8;
extern u16 D_800614A0;
extern u8 D_801D3433;

void func_8001D47C(u8 arg0) {
    u16 *var_v0;
    u16 *dst;
    s32 i;
    if (D_8004EA9A == 0xB) {
        var_v0 = &D_800614A0;
    } else {
        var_v0 = (u16 *)((arg0 << 5) + (u8 *)D_8004CE90);
    }
    if (D_8004AC88 == 0xC) {
        if (D_8004EA78 == 1) {
            var_v0 = (u16 *)0x803A3FC0;
        } else if ((D_8004EA78 == 0) && (D_801D3433 != 0)) {
            var_v0 = (u16 *)0x803A3FE0;
        }
    }
'''

G = '((var_v0[i] & 0x3E) >> 1)'
R = '((var_v0[i] & 0xF800) >> 11)'
B = '((var_v0[i] & 0x7C0) >> 6)'
SUM = f'{R} + {B} + {G}'

GRAY = {
    # pointer cursor stepping 4 elements, store through dst[k]
    'ptr4': f'''        dst = (u16 *)0;
        for (i = 0; i != 16; i += 4) {{
            s32 l = ({SUM}) / 3;
            dst[0] = (l << 11) | (l << 6) | (l << 1);
            l = ({(G.replace('[i]', '[i + 1]'))} + {(R.replace('[i]', '[i + 1]'))} + {(B.replace('[i]', '[i + 1]'))}) / 3;
            dst[1] = (l << 11) | (l << 6) | (l << 1);
            l = ({(G.replace('[i]', '[i + 2]'))} + {(R.replace('[i]', '[i + 2]'))} + {(B.replace('[i]', '[i + 2]'))}) / 3;
            dst[2] = (l << 11) | (l << 6) | (l << 1);
            l = ({(G.replace('[i]', '[i + 3]'))} + {(R.replace('[i]', '[i + 3]'))} + {(B.replace('[i]', '[i + 3]'))}) / 3;
            dst[3] = (l << 11) | (l << 6) | (l << 1);
            dst += 4;
        }}''',
    'ptrstep': f'''        dst = (u16 *)0;
        for (; dst != (u16 *)0x20; dst += 4) {{
            s32 l = ((((u16 *)0)[0] & 0x3E) >> 1);
            l = 0;
            dst[0] = l;
        }}''',
}

# simpler: keep index loop but make the destination a pointer variable assigned each step
GRAY['ptrassign'] = f'''        for (i = 0; i != 16; i++) {{
            s32 l = ({SUM}) / 3;
            dst = (u16 *)0;
            dst[i] = (l << 11) | (l << 6) | (l << 1);
        }}'''
GRAY['nullptr'] = f'''        for (i = 0; i != 16; i++) {{
            s32 l = ({SUM}) / 3;
            ((u16 *)(i * 2))[0] = (l << 11) | (l << 6) | (l << 1);
        }}'''
GRAY['base'] = f'''        for (i = 0; i != 16; i++) {{
            s32 l = ({SUM}) / 3;
            ((u16 *)0)[i] = (l << 11) | (l << 6) | (l << 1);
        }}'''
GRAY['u32i'] = f'''        for (i = 0; i != 16; i++) {{
            s32 l = ({SUM}) / 3;
            ((u16 *)0)[i] = (l << 11) | (l << 6) | (l << 1);
        }}'''

ZERO = '        for (i = 0; i != 16; i++) ((u16 *)0)[i] = 0;'
COPY = '        for (i = 0; i != 16; i++) ((u16 *)0)[i] = var_v0[i];'

tasks = []
for name, gray in GRAY.items():
    for itype in ('s32', 'u32', 's16'):
        src = HEAD.replace('    s32 i;', f'    {itype} i;')
        if name == 'u32i':
            src = HEAD.replace('    s32 i;', '    u32 i;')
        src += '    if (D_8004EAB8 == 1) {\n' + gray + '''
    } else if ((D_8004EA9E[arg0] == 9) && (D_8004EA78 < 2)) {
''' + ZERO + '''
    } else {
''' + COPY + '''
    }
}
'''
        p = OUT / f'{name}_{itype}.c'
        p.write_text(src)
        tasks.append(p)


def score(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (10**6, 0, p.name + ' ' + str(e)[:60])


with cf.ThreadPoolExecutor(8) as pool:
    for r in sorted(pool.map(score, tasks)):
        print(r)
