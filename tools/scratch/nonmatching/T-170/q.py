#!/usr/bin/env python3
"""Quick score: official words + register-masked diffwords for one or more drafts."""
import importlib.util, sys, os, subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT/'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)

fn = sys.argv[1]
for d in sys.argv[2:]:
    p = Path(d) if Path(d).is_absolute() else ROOT / d
    try:
        r = screen.measure(fn, p)
        print(f'{p.name}: words={r["words"]} bytes={r["compiled"]}/{r["original"]}')
    except Exception as e:
        print(f'{p.name}: ERROR {str(e)[-500:]}')
        continue
    env = dict(os.environ, REGMASK='1', COUNT='1')
    q = subprocess.run([str(ROOT/'.venv/bin/python'), str(ROOT/'tools/scratch/nonmatching/T-155/cmp.py'), fn, str(p)],
                       capture_output=True, text=True, env=env)
    line = q.stdout.strip().splitlines()[-1] if q.stdout.strip() else 'diff-fail'
    print('   ' + line)
