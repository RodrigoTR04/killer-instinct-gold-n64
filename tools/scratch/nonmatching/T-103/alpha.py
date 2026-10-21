exec(open('tools/scratch/nonmatching/T-103/sweep.py').read().split('out=[]; best=19')[0])
vs=[]
for typ in ['u8','s8','u16','s16','u32','s32']:
 for name in ['old','color','value','packed','color2','arg3']:
  for expr in [name,'(u8)'+name,'('+name+' & 0xFF)']:
   for pos in ['first','last']:
    t=base
    if name=='old':t=t.replace('    u8 alpha;',('    '+typ+' old;\n' if pos=='first' else '')+'    u8 alpha;'+('\n    '+typ+' old;' if pos=='last' else ''))
    elif name not in ['arg3']:t=t.replace({'color':'    u8 color;','value':'    u32 value;','packed':'    s32 packed;','color2':'    s32 color2;'}[name],'    '+typ+' '+name+';')
    t=t.replace('| alpha);','| '+expr+');')
    vs.append((f'old-{typ}-{name}-{expr}-{pos}',t))
# Access via non-volatile local pointer; no new byte or changed storage extent.
for init in ['&alpha','&color']:
 for where in ['entry','late']:
  for mask in ['*ap','(u8)*ap','(*ap & 0xFF)']:
   t=base.replace('    u8 alpha;','    u8 alpha;\n    u8 *ap'+(' = '+init if where=='entry' else '')+';')
   if where=='late':t=t.replace('        *counter = arg1;','        *counter = arg1;\n        ap = '+init+';')
   t=t.replace('| alpha);','| '+mask+');');vs.append((f'ptr-{init}-{where}-{mask}',t))
out=[];best=19
for label,t in vs:
 r=compile('func_801B2EF4',s[:a]+t+s[b:],label,True);out.append(r)
 if r.get('words',999)<best:
  best=r['words'];Path('/tmp/kig-t103-alpha-best.c').write_text(t);print(label,best,flush=True)
Path('/tmp/kig-t103-alpha-results.json').write_text(json.dumps(out,indent=2));print('done',len(out),best,flush=True)
