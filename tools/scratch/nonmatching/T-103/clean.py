exec(open('tools/scratch/nonmatching/T-103/sweep.py').read().split('out=[]; best=19')[0])
p=Path('/tmp/kig-t103-permute/output-395-1/source.c').read_text();x,y,_=extent(p,'func_801B2EF4');body=p[x:y]
body=__import__('re').sub(r' goto dummy_label_\d+; dummy_label_\d+: ;','',body)
vs=[('clean-permuter',body)]
for n in range(7):
 t=body
 if n&1:t=t.replace('    *counter = arg1;','    D_801D30C0 = arg1;')
 if n&2:t=t.replace('    alpha = 0xFF;','    alpha = 0xFF;\n    arg1 = D_801D308C;').replace('((s32) D_801D308C) < 2','arg1 < 2').replace('D_801D308C += 1','D_801D308C = arg1 + 1')
 if n&4:t=t.replace('    p1->w0 = 0xFA000000;\n','').replace('    color2 =','    p1->w0 = 0xFA000000;\n    color2 =')
 vs.append((f'clean-{n}',t))
out=[]
for label,t in vs:
 r=compile('func_801B2EF4',s[:a]+t+s[b:],label,True);out.append(r);print(label,r.get('words',r.get('error')),flush=True)
Path('/tmp/kig-t103-clean-results.json').write_text(json.dumps(out,indent=2))
