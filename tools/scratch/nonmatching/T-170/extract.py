#!/usr/bin/env python3
"""Extract the target function body from a permuter source.c into a draft file."""
import re, sys
from pathlib import Path

src = Path(sys.argv[1]).read_text()
fn = sys.argv[2]
out = Path(sys.argv[3])

pat = re.compile(r'^[A-Za-z_][\w \*]*\b' + re.escape(fn) + r'\s*\([^;{]*\)\s*\{', re.M)
matches = list(pat.finditer(src))
if not matches:
    raise SystemExit('function not found')
m = matches[-1]
i = src.index('{', m.start())
depth = 0
for j in range(i, len(src)):
    if src[j] == '{':
        depth += 1
    elif src[j] == '}':
        depth -= 1
        if depth == 0:
            break
body = src[m.start():j + 1]
# keep the externs the body needs (everything before the function that mentions them)
out.write_text(body + '\n')
print(f'wrote {out} ({len(body)} bytes)')
