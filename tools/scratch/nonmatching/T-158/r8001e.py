import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
V=['arg2','threshold','nv1','nv2','nv3']
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold; f32 nv1; f32 nv2; f32 nv3; s32 var_s0; u8 *temp_v1;
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
cands=[]
seen=set()
for T,S,B in itertools.permutations(V,3):
    st={'t':f"{T} = arg2;" if T!='arg2' else None,'s':f"{S} = D_800489F4;",'b':f"{B} = D_800489F0;"}
    for order in itertools.permutations('tsb'):
        # arg2 overwritten before t copy -> invalid
        ow=[k for k in 'sb' if {'s':S,'b':B}[k]=='arg2']
        if T!='arg2' and ow and order.index(ow[0])<order.index('t'): continue
        seq=[k for k in order if st[k]]
        for cuts in itertools.combinations_with_replacement('ABC',len(seq)):
            if list(cuts)!=sorted(cuts): continue
            slots={'A':[], 'B':[], 'C':[]}
            for k,c in zip(seq,cuts): slots[c].append(st[k])
            src=tmpl.replace('{A}',' '.join(slots['A'])+' ').replace('{B}',' '.join(slots['B'])).replace('{C}',' '.join(slots['C'])).replace('SCALE',S).replace('BIAS',B).replace('THR',T)
            if src in seen: continue
            seen.add(src)
            cands.append(((T,S,B,''.join(order),cuts),head+src))
print(len(cands),flush=True)
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:15]: print(r,k)
open('/tmp/w/r8001e_best.c','w').write(res[0][1][1])
