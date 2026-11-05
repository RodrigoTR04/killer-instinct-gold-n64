#!/usr/bin/env python3
"""Extract a function body from a permuter source.c (whole TU) into a standalone draft."""
import sys, re
from pathlib import Path
src = Path(sys.argv[1]).read_text()
fn = sys.argv[2]
m = re.search(r'^[A-Za-z_][\w \*]*\b' + re.escape(fn) + r'\s*\([^;]*?\)\s*\{', src, re.M)
if not m:
    raise SystemExit('not found')
start = m.start()
i = src.index('{', m.start())
depth = 0
for j in range(i, len(src)):
    if src[j] == '{':
        depth += 1
    elif src[j] == '}':
        depth -= 1
        if depth == 0:
            break
body = src[start:j+1]
# also copy typedefs/externs for the types used
out = Path(sys.argv[3])
out.write_text(body + '\n')
print(body)
