import sys, itertools, random
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold; f32 sc; f32 bi; f32 ia; f32 ib; s32 var_s0; u8 *temp_v1;
    {A}if (D_8004AA28 != 1) { temp_v1 = *arg0; {B}
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); {C}
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * SCALE) - BIAS;
        if (temp_f0 <= THR) { func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {
                goto loop_2; } }
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0_2 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * SCALE) - BIAS;
        if (THR < temp_f0_2) {
            func_8001BF1C(arg0, arg1, var_s0, temp_f0_2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {
                goto loop_5;
            }
        }
    }
}
"""
cands=[]; seen=set()
for thr in ('threshold','arg2'):
 for S in ('arg2','sc'):
  for B in ('bi','arg2','sc'):
   if S==B: continue
   if thr=='arg2' and 'arg2' in (S,B): continue
   for isc in (0,1):
    for ibi in (0,1):
      st={}
      if thr=='threshold': st['t']="threshold = arg2;"
      if isc: st['si']="ia = D_800489F4;"; st['s']=f"{S} = ia;"
      else: st['s']=f"{S} = D_800489F4;"
      if ibi: st['bi']="ib = D_800489F0;"; st['b']=f"{B} = ib;"
      else: st['b']=f"{B} = D_800489F0;"
      keys=list(st)
      for order in itertools.permutations(keys):
        pos={k:i for i,k in enumerate(order)}
        if isc and pos['si']>pos['s']: continue
        if ibi and pos['bi']>pos['b']: continue
        if thr=='threshold':
            ow=[k for k,v in (('s',S),('b',B)) if v=='arg2']
            if ow and pos[ow[0]]<pos['t']: continue
        for cuts in itertools.combinations_with_replacement('ABC',len(order)):
            slots={'A':[],'B':[],'C':[]}
            for k,c in zip(order,cuts): slots[c].append(st[k])
            T='threshold' if thr=='threshold' else 'arg2'
            src=tmpl.replace('{A}',' '.join(slots['A'])+' ').replace('{B}',' '.join(slots['B'])).replace('{C}',' '.join(slots['C'])).replace('SCALE',S).replace('BIAS',B).replace('THR',T)
            if src in seen: continue
            seen.add(src); cands.append(((thr,S,B,isc,ibi,order,cuts),head+src))
random.seed(1); random.shuffle(cands)
print(len(cands),flush=True)
cands=cands[:int(sys.argv[1])]
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:12]: print(r,k)
open('/tmp/w/r8001h_best.c','w').write(res[0][1][1])
