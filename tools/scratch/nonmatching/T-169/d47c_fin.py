import importlib.util, itertools, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
base = Path('tools/scratch/nonmatching/T-169/func_8001D47C.c').read_text()
V = {}
# rotate zero-fill / copy store order using unrolled 4-wide bodies with while loops
def variant(zorder, corder, zlen, clen):
    t = base
    zs = '\n'.join(f'            dst[i + {k}] = 0;' for k in zorder)
    cs = '\n'.join(f'            dst[i + {k}] = src[i + {k}];' for k in corder)
    t = t.replace('''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 16; i++) dst[i] = 0;
    } else {
        for (i = 0; i != 16; i++) dst[i] = src[i];
    }''', f'''    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        for (i = 0; i != {zlen}; i += 4) {{
{zs}
        }}
    }} else {{
        for (i = 0; i != {clen}; i += 4) {{
{cs}
        }}
    }}''')
    return t
ORD = [(0,1,2,3), (1,2,3,0), (2,3,0,1), (3,0,1,2)]
out = Path('tools/scratch/nonmatching/T-169/fin'); out.mkdir(exist_ok=True)
paths = []
for zo, co in itertools.product(ORD, ORD):
    p = out / f'z{"".join(map(str,zo))}c{"".join(map(str,co))}.c'
    p.write_text(variant(zo, co, 16, 16)); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(8) as pool:
    res = sorted(pool.map(run, paths))
for r in res[:8]: print(r)
