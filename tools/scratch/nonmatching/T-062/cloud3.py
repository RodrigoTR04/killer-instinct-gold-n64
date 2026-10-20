import sys,itertools,re
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
fn='func_801C35D8';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);n=0;vs=[]
for typ in ['void *','u32 *','CloudCmd *','s32','s8 *']:
 v=s.replace('typedef struct { u32 w0,w1; } CloudCmd;','typedef struct CloudCmd { u32 w0; '+typ+' w1; } CloudCmd;').replace('dl->w1 = (u32)D_80290F90;','dl->w1 = ('+typ+')D_80290F90;');vs.append(('w1'+typ,v))
for ct,it,ot,st,et in itertools.product(['s32','u32','s8','u8'],['s32','u32'],['s32','u32'],['s16','s32','u32'],['s32','u32']):
 v=s.replace('s32 visible;',ct+' visible;').replace('s32 i, offset;',it+' i; '+ot+' offset;').replace('s16 start;',st+' start;').replace('s32 end;',et+' end;');vs.append(('types'+str((ct,it,ot,st,et)),v))
for expr in ['cloud++;','cloud = (T030Cloud *)((u8 *)cloud + 12);','cloud = &arg1[i];','cloud = (T030Cloud *)((u8 *)arg1 + offset);']:
 for counter in range(4):
  v=s.replace('cloud++;',expr)
  if counter:
   v=v.replace('s32 end;','s32 end;\n    s32 *counter;')
   point=['','    dl = (*arg0)++;','    i = 0;','        cloud = arg1;'][counter]
   v=v.replace(point,'    counter = &D_80290D88;\n'+point,1).replace('if (D_80290D88 >= 60) D_80290D88 = 0;','if (*counter >= 60) *counter = 0;')
  vs.append((expr+str(counter),v))
for callty in ['s32','u32','s8','u8','s16','u16']:
 for ret in ['void','s32','u32']:
  vs.append(('callee'+callty+ret,s.replace('extern void func_801C3758(CloudCmd **, T030Cloud *, s32);','extern '+ret+' func_801C3758(CloudCmd **, T030Cloud *, '+callty+');')))
for name,v in vs:
 r=probe.probe(fn,pre+v);n+=1
 if r<best:best=r;p.write_text(v);print(n,name,r,flush=True)
print('final',n,best)
