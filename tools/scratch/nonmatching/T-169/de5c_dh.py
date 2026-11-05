import importlib.util, concurrent.futures, re, itertools, random
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
txt = Path('tools/scratch/nonmatching/T-162/func_8001DE5C.c').read_text()
# split decl block
i = txt.index('    struct {')
j = txt.index('    if (arg1 != 0) {')
decls = txt[i:j]
# struct block stays; reorder the scalars after it
struct_end = decls.index('    } b;\n') + len('    } b;\n')
head = decls[:struct_end]
scalars = [l for l in decls[struct_end:].split('\n') if l.strip()]
pre = txt[:i]; post = txt[j:]
out = Path('tools/scratch/nonmatching/T-169/dh'); out.mkdir(exist_ok=True)
random.seed(7)
orders = [scalars]
for _ in range(120):
    o = scalars[:]; random.shuffle(o); orders.append(o)
def build(o): return pre + head + '\n'.join(o) + '\n' + post
def run(idx):
    o = orders[idx]
    p = out/f'o{idx}.c'; p.write_text(build(o))
    try:
        r = dict(screen.measure('func_8001DE5C', p))
        return (r['words'], r['compiled'], idx)
    except Exception:
        return (9999,0,idx)
with concurrent.futures.ThreadPoolExecutor(8) as pool:
    res = sorted(pool.map(run, range(len(orders))))
for w,b,idx in res[:8]: print(w, b, idx, [s.strip() for s in orders[idx]])
