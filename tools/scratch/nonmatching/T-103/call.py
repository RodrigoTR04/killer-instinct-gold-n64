exec(open('tools/scratch/nonmatching/T-103/sweep.py').read().split('out=[]; best=19')[0])
vs=[]
for temps in [1,2,3]:
 for where in ['entry','branch']:
  for rev in [False,True]:
   for result in [False,True]:
    for joined in [False,True]:
     t=base;decl=[];args=['0.0f','255.0f']
     for i,(name,val) in enumerate([('start','0.0f'),('finish','255.0f')]):
      if temps & (1<<i):decl.append('f32 '+name+' = '+val+';');args[i]=name
     if rev:decl.reverse()
     decl=(' ' if joined else '\n        ').join(decl)
     if where=='entry':t=t.replace('    u8 alpha;','    '+decl+'\n    u8 alpha;')
     else:t=t.replace('        value =','        '+decl+'\n        value =')
     t=t.replace('func_801B19F0(0.0f, 255.0f,','func_801B19F0('+', '.join(args)+',')
     if result:t=t.replace('    u8 alpha;','    f32 intermediate;\n    u8 alpha;').replace('value = (u32) func_801B19F0','intermediate = func_801B19F0').replace('*counter = arg1, 10);','*counter = arg1, 10);\n        value = (u32) intermediate;')
     vs.append((f'call-{temps}-{where}-{rev}-{result}-{joined}',t))
out=[]
for label,t in vs:
 r=compile('func_801B2EF4',s[:a]+t+s[b:],label);out.append(r)
 if r.get('words',999)<19:Path('/tmp/kig-t103-call-best.c').write_text(t);print(label,r['words'],flush=True)
Path('/tmp/kig-t103-call-results.json').write_text(json.dumps(out,indent=2));print('done',len(out),min(r.get('words',999) for r in out),flush=True)
