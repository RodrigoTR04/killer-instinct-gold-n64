exec(open('tools/scratch/nonmatching/T-103/sweep.py').read().split('out=[]; best=19')[0])
vs=[]
for kind in ['block','do']:
 for first in ['        *counter = arg1;','        p1 = (*arg0)++;','        color2 = D_802C87D0 & 0xFF;']:
  for last in ['        p1->w0 = 0xFA000000;','        alpha = 0xFF;','        color2 = D_802C87D0 & 0xFF;']:
   for scope in [False,True]:
    t=base;i=t.index(first);j=t.index(last,i)+len(last) if last in t[i:] else -1
    if j<0:continue
    region=t[i:j]
    if scope:region='        T025Gfx2EF4 *p1;\n'+region
    t=t[:i]+('        do {\n' if kind=='do' else '        {\n')+region+('\n        } while (0);' if kind=='do' else '\n        }')+t[j:]
    vs.append((f'scope-{kind}-{first}-{last}-{scope}',t))
out=[]
for label,t in vs:
 r=compile('func_801B2EF4',s[:a]+t+s[b:],label,True);out.append(r)
 if r.get('words',999)<19:Path('/tmp/kig-t103-scope-best.c').write_text(t);print(label,r['words'],flush=True)
Path('/tmp/kig-t103-scope-results.json').write_text(json.dumps(out,indent=2));print('done',len(out),min(r.get('words',999) for r in out),flush=True)
