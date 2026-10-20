#!/usr/bin/env python3
# Probe a draft inside its TU context: TU text before the function's GLOBAL_ASM (pragmas stripped) + draft.
import sys,re,pathlib,os
sys.path.insert(0,str(pathlib.Path(__file__).parent))
import probe
from reconcile import reconcile
ROOT=probe.ROOT
def ctx(fn):
    for tu in sorted((ROOT/'src/main').glob('*.c')):
        t=tu.read_text()
        m=re.search(r'#pragma GLOBAL_ASM\("[^"]*/'+fn+r'\.s"\)',t)
        if m:
            pre=t[:m.start()]
            pre=re.sub(r'#pragma GLOBAL_ASM\([^)]*\)','',pre)
            pre=pre.replace('#include "common.h"','')
            return tu,pre
    return None,''
def draft(fn):
    c=list((ROOT/'tools/scratch/nonmatching').glob('T-0*/'+fn+'.c'))
    return c[0] if c else None
if __name__=='__main__':
    for a in sys.argv[1:]:
        fn=pathlib.Path(a).stem
        if not fn.startswith('func_'): fn=pathlib.Path(a).parent.name
        src=pathlib.Path(a) if a.endswith('.c') else draft(fn)
        tu,pre=ctx(fn)
        r=probe.probe(fn,pre+'\n'+reconcile(fn,src.read_text()),bool(os.environ.get('SHOW')))
        print(fn,src.relative_to(ROOT) if src.is_absolute() else src,tu.name if tu else None,r,flush=True)
