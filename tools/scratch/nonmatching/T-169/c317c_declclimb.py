#!/usr/bin/env python3
"""T-169 1C317C: hill-climb local declaration ORDER (and scope) against the
official count. The target frame is 0x70 with s0-s7+fp+ra and f20/f22/f24 live;
the draft is 0x80/0x90 with fewer float registers, which is a live-range issue
set by which locals exist and in what order they are declared."""
import importlib.util
import random
import re
import sys
import tempfile
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
TMP = Path('/tmp/c317c_climb.c')


def score(text):
    TMP.write_text(text)
    try:
        return dict(screen.measure('func_801C317C', TMP))['words']
    except Exception:
        return 10 ** 6


src = Path(sys.argv[1]).read_text()
start = src.index('s32 func_801C317C(')
head, body = src[:start], src[start:]

# find the declaration block: from the '{' of the function to the first
# non-declaration statement
brace = body.index('{')
rest = body[brace + 1:]
decls, lines, buf = [], rest.split('\n'), []
i = 0
while i < len(lines):
    ln = lines[i]
    st = ln.strip()
    if st and not (st.endswith(';') and not st.startswith(('if', 'while', 'for', 'do', 'return', '}'))) or st.startswith('drawn'):
        break
    if st:
        decls.append(ln)
    else:
        decls.append(ln)
    i += 1
tail = '\n'.join(lines[i:])
nonempty = [d for d in decls if d.strip()]

best_decls, best = list(nonempty), score(src)
cur = list(nonempty)
rng = random.Random(7)
for it in range(400):
    c = cur[:]
    a, b = rng.sample(range(len(c)), 2)
    c[a], c[b] = c[b], c[a]
    text = head + body[:brace + 1] + '\n' + '\n'.join(c) + '\n' + tail
    s = score(text)
    if s < best:
        best, cur, best_decls = s, c, c[:]
        print(f'{best} iter={it}', flush=True)
    if s <= best:
        cur = c
print('final', best)
Path(sys.argv[2]).write_text(head + body[:brace + 1] + '\n' + '\n'.join(best_decls) + '\n' + tail)
