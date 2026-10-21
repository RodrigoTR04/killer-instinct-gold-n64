exec(open('tools/scratch/nonmatching/T-103/sweep.py').read().split('out=[]; best=19')[0])
vs=[]
for pred in ['arg1++ < 10','++arg1 <= 10','(arg1 += 1) <= 10','arg1 < 10']:
 for late in ['*counter = arg1;','D_801D30C0 = arg1;','*counter = arg1, counter = 0;','arg1 = (*counter = arg1);','value = (*counter = arg1);','*counter += 1;']:
  for flag in ['D_801D308C += 1;','D_801D308C = arg1 + 1;','++*flag;']:
   for scope in ['outer','inner']:
    t=base.replace('arg1++ < 10',pred).replace('        *counter = arg1;', '        '+late)
    if pred=='arg1 < 10': t=t.replace('    if (arg1 < 10)','    if (arg1++ < 10)')
    if flag=='D_801D308C = arg1 + 1;':t=t.replace('        if ((s32) D_801D308C < 2)','        arg1 = D_801D308C;\n        if (arg1 < 2)')
    if flag=='++*flag;':
     if scope=='outer':t=t.replace('    u8 alpha;','    u8 alpha;\n    u8 *flag = &D_801D308C;')
     else:t=t.replace('        *counter = arg1;','        u8 *flag = &D_801D308C;\n        *counter = arg1;')
     t=t.replace('(s32) D_801D308C','(s32) *flag')
    t=t.replace('D_801D308C += 1;',flag)
    vs.append((f'counter-{pred}-{late}-{flag}-{scope}',t))
# Two branch-local pointer declarations expose separate address computations.
for lateptr in ['&D_801D30C0','counter']:
 for flagpos in ['before','after']:
  for flagtyp in ['u8 *','void *']:
   t=base.replace('        *counter = arg1;', '        s32 *lateCounter = '+lateptr+';\n        '+flagtyp+'completion = &D_801D308C;\n        *lateCounter = arg1;')
   t=t.replace('(s32) D_801D308C','(s32) *(u8 *)completion').replace('D_801D308C += 1','++*(u8 *)completion')
   if flagpos=='after':t=t.replace('        '+flagtyp+'completion = &D_801D308C;\n','').replace('        color2 =','        '+flagtyp+'completion = &D_801D308C;\n        color2 =')
   vs.append((f'local-{lateptr}-{flagpos}-{flagtyp}',t))
out=[];best=19
for label,t in vs:
 r=compile('func_801B2EF4',s[:a]+t+s[b:],label,True);out.append(r)
 if r.get('words',999)<best:
  best=r['words'];Path('/tmp/kig-t103-counter-best.c').write_text(t);print(label,best,flush=True)
Path('/tmp/kig-t103-counter-results.json').write_text(json.dumps(out,indent=2));print('done',len(out),best,flush=True)
