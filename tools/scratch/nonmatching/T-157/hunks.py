#!/usr/bin/env python3
"""hunks.py : after side.sh/cmp DUMP, print reg-masked LCS hunks (target vs draft) from /tmp/t157/t.txt m.txt"""
import difflib, re, sys
R = re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b')
t = open('/tmp/t157/t.txt').read().split('\n'); m = open('/tmp/t157/m.txt').read().split('\n')
tm = [R.sub('R', x) for x in t]; mm = [R.sub('R', x) for x in m]
sm = difflib.SequenceMatcher(None, tm, mm, autojunk=False)
n = 0
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal': continue
    n += max(i2 - i1, j2 - j1)
    print(f'--- {tag} target[{i1}:{i2}] draft[{j1}:{j2}]')
    for k in range(i1, i2): print('  T', t[k])
    for k in range(j1, j2): print('  D', m[k])
print('total', n)
