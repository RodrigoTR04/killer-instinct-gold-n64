import importlib.util, concurrent.futures, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
base = Path('tools/scratch/nonmatching/T-162/func_8001DE5C.c').read_text()
# insert extra locals after "s32 dyb;"
VARIANTS = {
 'v_none': '',
 'v_i32': '    s32 pad0;\n',
 'v_2i32': '    s32 pad0;\n    s32 pad1;\n',
 'v_u32': '    u32 pad0;\n    u32 pad1;\n',
 'v_f32': '    f32 pad0;\n',
 'v_f32f32': '    f32 pad0;\n    f32 pad1;\n',
 'v_ptr': '    u8 *p0;\n',
}
out = Path('tools/scratch/nonmatching/T-169/df'); out.mkdir(exist_ok=True)
paths=[]
for k, ins in VARIANTS.items():
    txt = base.replace('    s32 dyb;\n', '    s32 dyb;\n' + ins)
    p = out/f'{k}.c'; p.write_text(txt); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001DE5C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
