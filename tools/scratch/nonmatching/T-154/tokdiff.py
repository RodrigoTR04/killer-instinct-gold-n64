#!/usr/bin/env python3
"""Token diff of function bodies ignoring whitespace/parens: tokdiff.py a.c b.c fn"""
import re, sys, difflib
def body(p, fn):
    s = open(p).read()
    i = s.index(fn + '(')
    return s[i:]
def toks(s):
    return [t for t in re.findall(r'[A-Za-z_]\w*|\d[\w.]*|\S', s) if t not in '()']
a, b = toks(body(sys.argv[1], sys.argv[3])), toks(body(sys.argv[2], sys.argv[3]))
sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
for t, i1, i2, j1, j2 in sm.get_opcodes():
    if t != 'equal':
        ctx = ' '.join(a[max(0, i1-6):i1])
        print(f'{t}: ... {ctx} | - {" ".join(a[i1:i2])} | + {" ".join(b[j1:j2])}')
