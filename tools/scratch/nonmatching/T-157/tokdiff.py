#!/usr/bin/env python3
"""tokdiff.py a.c b.c : token-level diff (whitespace and redundant parens ignored)"""
import difflib, re, sys
def toks(p):
    s = open(p).read()
    t = re.findall(r'[A-Za-z_]\w*|0[xX][0-9A-Fa-f]+|\d+\.?\d*f?|<<=|>>=|\+\+|--|->|&&|\|\||==|!=|<=|>=|<<|>>|[^\s]', s)
    return [x for x in t if x not in '()']
a, b = toks(sys.argv[1]), toks(sys.argv[2])
sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag != 'equal':
        ctx = ' '.join(a[max(0, i1 - 6):i1])
        print(f'{tag}: ... {ctx} | - {" ".join(a[i1:i2])} | + {" ".join(b[j1:j2])}')
