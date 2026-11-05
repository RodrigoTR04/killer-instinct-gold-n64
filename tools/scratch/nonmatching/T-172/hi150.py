"""Move the int declaration among the doubles in func_8002E150 (target homes hi at sp+0x1C)."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
HDR = '''    s32 hi = *(s32 *)&x;
    s32 exponent = (hi >> 20) & 0x7FF;
'''
DECL = '    double w, u, r, t, a, q, p, z;'
assert HDR in BASE and DECL in BASE

names = 'w, u, r, t, a, q, p, z'.split(', ')
v = {}
# hi declared at each position inside the double list, exponent computed after
for i in range(len(names) + 1):
    seq = names[:i] + ['hi'] + names[i:]
    body = BASE.replace(HDR, '    s32 hi;\n    s32 exponent;\n').replace(
        DECL, '    double ' + ', '.join(seq) + ';\n    hi = *(s32 *)&x;\n    exponent = (hi >> 20) & 0x7FF;\n')
    v[f'hi_at_{i}'] = body

# separate int declaration lines interleaved (C89 requires all decls first, so group them)
for i in range(len(names) + 1):
    seq = names[:i] + ['hi'] + names[i:]
    body = BASE.replace(HDR + DECL,
                        '    s32 hi, exponent;\n    double ' + ', '.join(seq) + ';\n'
                        '    hi = *(s32 *)&x;\n    exponent = (hi >> 20) & 0x7FF;\n')
    v[f'ints_then_hi_at_{i}'] = body
detail.run('func_8002E150', v, jobs=12)
