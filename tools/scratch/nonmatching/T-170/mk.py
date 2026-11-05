#!/usr/bin/env python3
"""Apply a list of (pattern, replacement) pairs to a base draft, writing variants."""
import sys, json
from pathlib import Path
base_path = Path(sys.argv[1])
spec = json.loads(Path(sys.argv[2]).read_text())
base = base_path.read_text()
outdir = base_path.parent
prefix = sys.argv[3] if len(sys.argv) > 3 else 'w_'
for name, pairs in spec.items():
    s = base
    for pat, rep in pairs:
        if pat not in s:
            print(f'SKIP {name}: missing {pat[:60]!r}')
            s = None
            break
        s = s.replace(pat, rep)
    if s is None:
        continue
    p = outdir / f'{prefix}{name}.c'
    p.write_text(s)
    print(f'wrote {p.name}')
