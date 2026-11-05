import itertools, importlib.util, subprocess, sys
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
    s32 temp_a1;
    s32 mid;
    u32 green;
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
    temp_a0 = *arg0;
    *arg0 = temp_a0 + 1;
    temp_a0->w0 = 0xFB000000;
    temp_f0 = (f64) var_a3;
'''

# middle variants
MIDS = {
 'm0': '''    temp_a1 = (u32) (temp_f0 * D_802928A8);
    mid = (u32) (temp_f0 * D_802928B0);
    green = var_a3 & 0xFF;
''',
 'm1': '''    green = var_a3 & 0xFF;
    temp_a1 = (u32) (temp_f0 * D_802928A8);
    mid = (u32) (temp_f0 * D_802928B0);
''',
 'm2': '''    temp_a1 = (u32) (temp_f0 * D_802928A8);
    green = var_a3 & 0xFF;
    mid = (u32) (temp_f0 * D_802928B0);
''',
 'm3': '''    temp_a1 = (u32) (temp_f0 * D_802928A8);
    mid = (u32) (temp_f0 * D_802928B0);
''',
}
STORES = {
 's0': '''    temp_a0->w1 = (temp_a1 << 24) | ((mid & 0xFF) << 16) | (green << 8);
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0xFA000000;
    temp_v1->w1 = (var_a3 & 0xFF) << 24;
''',
 's1': '''    temp_a0->w1 = (temp_a1 << 24) | ((mid & 0xFF) << 16) | (green << 8);
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w1 = (var_a3 & 0xFF) << 24;
    temp_v1->w0 = 0xFA000000;
''',
 's2': '''    temp_a0->w1 = (temp_a1 << 24) | (green << 8) | ((mid & 0xFF) << 16);
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0xFA000000;
    temp_v1->w1 = (var_a3 & 0xFF) << 24;
''',
 's3': '''    temp_a0->w1 = (temp_a1 << 24) | ((mid & 0xFF) << 16) | (green << 8);
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w1 = (green) << 24;
    temp_v1->w0 = 0xFA000000;
''',
}
TAIL = '''    return 1;
}
'''
def build(mid, store):
    m = MIDS[mid].replace('green = var_a3 & 0xFF;\n', '')
    body = HEAD
    if mid in ('m0','m1','m2'):
        pass
    s = STORES[store].replace('green', 'green')
    src = HEAD + MIDS[mid] + STORES[store] + TAIL
    if mid == 'm3':
        src = HEAD + MIDS[mid] + STORES[store].replace('green','(var_a3 & 0xFF)') + TAIL
    return src

out = Path('tools/scratch/nonmatching/T-169/gen'); out.mkdir(exist_ok=True)
results = []
for mid in MIDS:
    for st in STORES:
        p = out / f'{mid}_{st}.c'
        p.write_text(build(mid, st))
        try:
            r = dict(screen.measure('func_801AFFAC', p))
            results.append((r['words'], r['compiled'], p.name))
        except Exception as e:
            results.append((9999, 0, p.name + ' ERR ' + str(e)[:80]))
results.sort()
for r in results: print(r)
