import importlib.util, concurrent.futures, itertools, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
base = Path('tools/scratch/nonmatching/T-169/de5c_v4.c').read_text()
i = base.index('    s32 mx;')
head = base[:i]
tail = base[i:]
# candidate extra live values that the original plausibly keeps
EXTRA = {
'e_none': '',
'e_w': '    s32 w;\n',
'e_wh': '    s32 w;\n    s32 h;\n',
'e_edges': '    s32 left;\n    s32 top;\n',
'e_spr': '    T022Sprite *spr2;\n    s32 w;\n',
'e_color': '    s32 color;\n    s32 w;\n',
}
out = Path('tools/scratch/nonmatching/T-169/dv7'); out.mkdir(exist_ok=True)
paths = []
for k, v in EXTRA.items():
    txt = head + v + tail
    p = out/f'{k}.c'; p.write_text(txt); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001DE5C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
