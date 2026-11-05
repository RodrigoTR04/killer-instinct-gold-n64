import importlib.util, itertools, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
base = Path('tools/scratch/nonmatching/T-169/func_8001D47C.c').read_text()
OLD = '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;'''
ORD = [(0,1,2,3), (1,2,3,0), (2,3,0,1), (3,0,1,2)]
out = Path('tools/scratch/nonmatching/T-169/rot'); out.mkdir(exist_ok=True)
paths = []
for o in ORD:
    st = '\n'.join(f'            *(u16 *)(i + {2*k}) = 0;' for k in o)
    new = f'''    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        for (i = 0; i != 32; i += 8) {{
{st}
        }}'''
    p = out / f'r{"".join(map(str,o))}.c'
    p.write_text(base.replace(OLD, new)); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(4) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
