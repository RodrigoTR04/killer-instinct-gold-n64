exec(open('tools/scratch/nonmatching/T-103/sweep.py').read().split('out=[]; best=19')[0])
start=base.index('    arg1 = *counter;');end=base.index('    guTranslate'); original=base[start:end]
e=original[original.index('        value ='):original.index('    }\n    else')]
l=original[original.index('        *counter = arg1;'):original.rindex('    }')]
vs=[]
for layout in range(5):
 for flag in ['direct','pointer']:
  for line in ['normal','joined']:
   if layout==0: mid='    arg1 = *counter;\n    if (arg1++ >= 10) goto complete;\n'+e+'    goto translate;\ncomplete:\n'+l+'translate:\n'
   if layout==1: mid='    arg1 = *counter;\n    if (arg1++ < 10) goto interpolate;\n'+l+'    goto translate;\ninterpolate:\n'+e+'translate:\n'
   if layout==2: mid='    arg1 = *counter;\n    if (arg1++ < 10) {\n'+e+'    goto translate;\n    }\n'+l+'translate:\n'
   if layout==3: mid='    arg1 = *counter;\n    if (arg1++ >= 10) {\n'+l+'    goto translate;\n    }\n'+e+'translate:\n'
   if layout==4: mid=original.replace('    else\n    {','    else\n    {\n        goto complete;\n    }\n    goto translate;\ncomplete:\n    {')+'translate:\n'
   t=base[:start]+mid+base[end:]
   if flag=='pointer':t=t.replace('    u8 alpha;','    u8 alpha;\n    u8 *flag;').replace('        alpha = 0xFF;','        alpha = 0xFF;\n        flag = &D_801D308C;').replace('(s32) D_801D308C','(s32) *flag').replace('D_801D308C += 1','*flag += 1')
   if line=='joined':t=t.replace('\n',' ')
   vs.append((f'flow-{layout}-{flag}-{line}',t))
out=[]
for label,t in vs:
 r=compile('func_801B2EF4',s[:a]+t+s[b:],label,True);out.append(r);print(label,r.get('words',r.get('error')),flush=True)
 if r.get('words',999)<19:Path('/tmp/'+label+'.c').write_text(t)
Path('tools/scratch/nonmatching/T-103/flow.json').write_text(json.dumps(out,indent=2)+'\n')
