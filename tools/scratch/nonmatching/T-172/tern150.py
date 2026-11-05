"""Ternary |x| combined with separate declaration statements (func_8002E150)."""
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
HDR = '''    s32 hi = *(s32 *)&x;
    s32 exponent = (hi >> 20) & 0x7FF;
'''
DECL = '    double w, u, r, t, a, q, p, z;'
ABS = '''        a = x;
        if (a < 0.0) a = -x;
'''
assert HDR in BASE and DECL in BASE and ABS in BASE

NAMES = ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z']


def decls(hi_pos, ex_pos, sep=True):
    if sep:
        lines = []
        for i in range(len(NAMES) + 1):
            if i == hi_pos:
                lines.append('    s32 hi;')
            if i == ex_pos:
                lines.append('    s32 exponent;')
            if i < len(NAMES):
                lines.append(f'    double {NAMES[i]};')
        return '\n'.join(lines)
    names = NAMES[:hi_pos] + ['hi'] + NAMES[hi_pos:]
    return '    double ' + ', '.join(names) + ';'


ABS_VARIANTS = {
    'tern': '        a = (x < 0.0) ? -x : x;\n',
    'tern_np': '        a = x < 0.0 ? -x : x;\n',
    'ifneg': '        a = x;\n        if (x < 0.0) a = -x;\n',
    'ifelse': '        if (x < 0.0) {\n            a = -x;\n        } else {\n            a = x;\n        }\n',
    'negif': '        a = -x;\n        if (x >= 0.0) a = x;\n',
}

v = {}
for aname, absrc in ABS_VARIANTS.items():
    for hi_pos in range(len(NAMES) + 1):
        body = BASE.replace(HDR + DECL,
                            decls(hi_pos, len(NAMES)) + '\n'
                            '    hi = *(s32 *)&x;\n    exponent = (hi >> 20) & 0x7FF;\n')
        body = body.replace(ABS, absrc)
        v[f'{aname}_hi{hi_pos}'] = body
print(len(v), 'variants', flush=True)
detail.run('func_8002E150', v, jobs=16)
