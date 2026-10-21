exec(open('tools/scratch/nonmatching/T-103/sweep.py').read().split('out=[]; best=19')[0])
p=Path('/tmp/kig-t103-late/output-677-1/source.c').read_text();x,y,_=extent(p,'func_801B2EF4');t=p[x:y];out=[]
for label,body in [('late-raw-diagnostic',t),('late-clean',t.replace('  volatile unsigned int new_var;\n','').replace('(new_var = D_802C87D0 & 0xFF)','(D_802C87D0 & 0xFF)'))]:
 r=compile('func_801B2EF4',s[:a]+body+s[b:],label,True);out.append(r);print(label,r.get('words'),r.get('bytes'),flush=True)
Path('/tmp/kig-t103-last-results.json').write_text(json.dumps(out,indent=2))
