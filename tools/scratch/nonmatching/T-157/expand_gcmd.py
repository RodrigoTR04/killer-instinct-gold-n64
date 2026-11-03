#!/usr/bin/env python3
"""expand_gcmd.py in.c out.c : replace GCMD(pkt, a, b); invocations by multi-line blocks (one statement per line)"""
import re, sys
s = open(sys.argv[1]).read()
out = []; i = 0
while True:
    j = s.find('GCMD(', i)
    if j < 0: out.append(s[i:]); break
    ls = s.rfind('\n', 0, j) + 1
    if s[ls:j].startswith('#define'):
        e = s.find('\n', j); out.append(s[i:e + 1]); i = e + 1; continue
    out.append(s[i:j])
    k = j + 5; d = 1
    while d:
        c = s[k]; d += c == '('; d -= c == ')'; k += 1
    inner = s[j + 5:k - 1]
    parts = []; d = 0; cur = ''
    for c in inner:
        if c == '(': d += 1
        if c == ')': d -= 1
        if c == ',' and d == 0: parts.append(cur.strip()); cur = ''
        else: cur += c
    parts.append(cur.strip())
    pkt, a, b = parts
    line = s[ls:j]; ind = ' ' * (len(line) - len(line.lstrip()))
    out.append("{\n%s    T157Gfx *_g = %s;\n%s    _g->w0 = %s;\n%s    _g->w1 = %s;\n%s}" % (ind, pkt, ind, re.sub(r'\s+', ' ', a), ind, re.sub(r'\s+', ' ', b), ind))
    i = k
    if s[i:i + 1] == ';': i += 1
t = ''.join(out)
t = re.sub(r'#define GCMD[^\n]*\n', '', t)
open(sys.argv[2], 'w').write(t)
