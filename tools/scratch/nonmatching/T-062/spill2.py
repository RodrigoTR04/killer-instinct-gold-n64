import sys,itertools,re,collections
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
fn='func_801C4E38';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);counts=collections.Counter();n=0
variants=[]
for rt in ['void','s32','u32','f32','f64','u64','s64','void *']:
 for name in ['osViBlack','func_8002F9FC','func_801ADAD4','func_80012A8C','func_8002F6F4','func_8002A9DC','func_8002A8C4','func_801C4D28','func_801C4D6C','func_80016078']:
  variants.append((name+rt,s.replace('extern void '+name,'extern '+rt+' '+name)))
for cb in ['void','s32','u32','f32','f64','s64']:
 for args in ['void','','s32','u8']:
  variants.append(('callback'+cb+args,s.replace('extern void (*D_800451EC[])(void);','extern '+cb+' (*D_800451EC[])('+args+');')))
# A local holding the callback, table row, or selected global is plausible original source.
for typ,expr in [('void (*callback)(void)','D_800451EC[D_802D3985]'),('s32 mode','arg0'),('u8 mode','arg0'),('s32 player','D_80127CC1'),('u8 player','D_80127CC1'),('f32 *row','D_80291BCC[D_802D3985]')]:
 name=re.search(r'(callback|mode|player|row)',typ)[0]
 for init in ['declaration','assignment']:
  v=s.replace('        D_802D3985 = arg0;',typ+(' = '+expr if init=='declaration' else '')+';\n        D_802D3985 = arg0;')
  if name=='callback':point='    D_800451EC[D_802D3985]();';v=v.replace(point,('    callback = '+expr+';\n' if init=='assignment' else '')+'    callback();')
  elif name=='mode':
   point='    if (arg0 >= 11)';v=v.replace(point,('    mode = arg0;\n' if init=='assignment' else '')+point);a,b=v.split(point,1);v=a+point+b.replace('switch (arg0)','switch (mode)').replace('if (arg0 == 5)','if (mode == 5)')
  elif name=='player':
   point='    D_802D39BA = D_80292048[D_80127CC1];';v=v.replace(point,('    player = D_80127CC1;\n' if init=='assignment' else '')+point.replace('D_80127CC1','player'));v=v.replace('D_80291B5C[D_80127CC1]','D_80291B5C[player]')
  else:
   point='    func_801C4C64(D_80291BCC[D_802D3985], D_80291DDC[D_802D3985]);';v=v.replace(point,('    row = '+expr+';\n' if init=='assignment' else '')+point.replace(expr,'row'))
  variants.append((typ+init,v))
for name,v in variants:
 r=probe.probe(fn,pre+v);n+=1;counts[r]+=1
 if r<best:best=r;p.write_text(v);print(name,r,flush=True)
print(n,best,counts)
