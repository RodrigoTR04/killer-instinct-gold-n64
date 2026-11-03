#!/usr/bin/env python3
"""usage: try.py fn base.c  name:old=>new[;;old2=>new2] ...   (run INSIDE toolbox)
Each arg builds a variant of base.c by replacements and prints exact/regmask word diff counts."""
import sys, os, subprocess, re
from pathlib import Path
here = Path(__file__).resolve().parent
root = here.parents[3]
fn = sys.argv[1]; bp = Path(sys.argv[2]); bp = bp if bp.exists() else here / bp; base = bp.read_text()
out = here / 'v'
out.mkdir(exist_ok=True)
def run(path, env):
    e = dict(os.environ, COUNT='1', RONORM='1', **env)
    r = subprocess.run([str(root/'.venv/bin/python'), str(here/'cmp.py'), fn, str(path)], cwd=root, env=e, capture_output=True, text=True)
    m = re.search(r'diffwords=(\d+)', r.stdout)
    return int(m.group(1)) if m else ('ERR ' + r.stderr[-300:])
for spec in sys.argv[3:]:
    name, _, reps = spec.partition(':')
    s = base
    for rep in reps.split('@@') if reps else []:
        old, _, new = rep.partition('=>')
        old = old.replace('\\n', '\n'); new = new.replace('\\n', '\n')
        if old not in s:
            print(name, 'MISSING', old[:40]); break
        s = s.replace(old, new)
    else:
        p = out / (name + '.c')
        p.write_text(s)
        print(f'{name:20s} exact={run(p, {})} regmask={run(p, {"REGMASK":"1"})}', flush=True)
