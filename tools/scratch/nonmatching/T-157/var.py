#!/usr/bin/env python3
"""var.py base.c out.c 'old=>new' ['old2=>new2' ...]   exact-substring replacement (must match once unless suffix ' *')"""
import sys
s=open(sys.argv[1]).read()
for e in sys.argv[3:]:
    a,b=e.split('=>',1)
    a=a.replace('\\n','\n'); b=b.replace('\\n','\n')
    if a not in s: sys.exit('missing: '+a)
    s=s.replace(a,b)
open(sys.argv[2],'w').write(s)
