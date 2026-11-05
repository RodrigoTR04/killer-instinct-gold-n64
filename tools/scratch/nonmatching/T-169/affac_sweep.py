import importlib.util, itertools, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)

HEAD = '''f32 func_801AFA80(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
typedef struct { u32 w0, w1; } T025GfxFFAC;
extern void guTranslate(void *, f32, f32, f32);
extern s32 func_8002F6F4();
extern s32 D_801D2EAC;
extern f64 D_802928A8;
extern f64 D_802928B0;

s32 func_801AFFAC(T025GfxFFAC **arg0, s32 arg1, u8 *arg2, u32 arg3) {
    f64 temp_f0;
    s32 var_a3;
    s32 red;
    s32 mid;
    s32 green;
    T025GfxFFAC *temp_a0;
    T025GfxFFAC *temp_v1;

    if (arg3 >= 0x4CU) {
        if (arg3 >= 0x97U) {
            D_801D2EAC = (s32) func_801AFA80(255.0f, 10.0f, arg3 - 0x96, 0x36);
        }
    } else {
        D_801D2EAC = (s32) func_801AFA80(0.0f, 255.0f, arg3, 0x4B);
    }
    guTranslate(arg2, 0.0f, 135.0f, 0.0f);
    var_a3 = D_801D2EAC;
    green = var_a3 & 0xFF;
    temp_a0 = *arg0;
    *arg0 = temp_a0 + 1;
    temp_f0 = (f64) var_a3;
    temp_a0->w0 = 0xFB000000;
'''

def mkw1(greenExpr, redExpr, midExpr, order):
    parts = {
        'r': redExpr,
        'g': greenExpr,
        'b': midExpr,
    }
    return '    temp_a0->w1 = ' + ' | '.join(parts[c] for c in order) + ';\n'

RED = {'L': 'red << 24', 'I': '((u32) (temp_f0 * D_802928A8) << 24)'}
MID = {'L': '(mid & 0xFF) << 16', 'I': '(((u32) (temp_f0 * D_802928B0) & 0xFF) << 16)'}
GRN = {'L': 'green << 8', 'I': '((var_a3 & 0xFF) << 8)'}
PRE = {
 'pL': '    red = (u32) (temp_f0 * D_802928A8);\n    mid = (u32) (temp_f0 * D_802928B0);\n',
 'pN': '',
}
TAIL1 = '''    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w1 = GREEN2 << 24;
    temp_v1->w0 = 0xFA000000;
    return 1;
}
'''
TAIL2 = '''    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0xFA000000;
    temp_v1->w1 = GREEN2 << 24;
    return 1;
}
'''
TAILS = {'tW1W0': TAIL1, 'tW0W1': TAIL2}
G2 = {'L': 'green', 'I': '(var_a3 & 0xFF)'}

out = Path('tools/scratch/nonmatching/T-169/gen'); out.mkdir(exist_ok=True)
res = []
for pre, r, m, g, order, tk, g2 in itertools.product(PRE, RED, MID, GRN, ['rgb','rbg','grb','gbr','brg','bgr'], TAILS, G2):
    src = HEAD + PRE[pre] + mkw1(GRN[g], RED[r], MID[m], order) + TAILS[tk].replace('GREEN2', G2[g2])
    name = f'{pre}_{r}{m}{g}_{order}_{tk}_{g2}.c'
    p = out / name
    p.write_text(src)
    try:
        rr = dict(screen.measure('func_801AFFAC', p))
        res.append((rr['words'], rr['compiled'], name))
    except Exception as e:
        res.append((9999, 0, name + ' ERR'))
res.sort()
seen = set()
for w, b, n in res[:25]:
    print(w, b, n)
print('total', len(res), 'best', res[0])
