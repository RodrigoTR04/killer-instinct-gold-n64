#!/usr/bin/env python3
"""fnbody.py file fn  -> prints the function definition text (from 'fn(' to matching brace)"""
import re, sys
s = open(sys.argv[1]).read(); fn = sys.argv[2]
m = None
for mm in re.finditer(r'\b' + fn + r'\s*\(', s):
    # find definition: following ') {' 
    j = s.find('{', mm.end())
    k = s.find(';', mm.end())
    if j != -1 and (k == -1 or j < k):
        m = mm; break
i = s.rfind('\n', 0, m.start()) + 1
j = s.find('{', m.end()); d = 0; p = j
while True:
    c = s[p]
    d += c == '{'; d -= c == '}'
    p += 1
    if d == 0: break
print(s[i:p])
