import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold; f32 nv1; f32 nv2; s32 var_s0; u8 *temp_v1;
    {A}if (D_8004AA28 != 1) { temp_v1 = *arg0; {B}
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); {C}
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = E1;
        if (temp_f0 <= THR) { func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {
                goto loop_2; } }
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0_2 = E2;
        if (THR < temp_f0_2) {
            func_8001BF1C(arg0, arg1, var_s0, temp_f0_2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {
                goto loop_5;
            }
        }
    }
}
"""
X="(*(f32 *)((u8 *)(var_s1) + 0xF0))"
exprs={
 'ms':lambda S,B: f"{X} * {S} - {B}",
 'sm':lambda S,B: f"{X} * {S} + (-{B})",
 'neg':lambda S,B: f"-{B} + {X} * {S}",
 'sm2':lambda S,B: f"{S} * {X} - {B}",
}
cands=[]
for ek,ef in exprs.items():
  for sk in ('lit','g','nv1'):
    for bk in ('lit','g','nv2'):
      for tk in ('arg2','threshold'):
        for pos in 'ABC':
          S={'lit':'1500.0f','g':'D_800489F4','nv1':'nv1'}[sk]
          B={'lit':'590.0f','g':'D_800489F0','nv2':'nv2'}[bk] if bk!='nv1' else 'nv2'
          if bk=='nv2': B='nv2'
          st=[]
          if tk=='threshold': st.append('threshold = arg2;')
          if bk=='nv2': st.append('nv2 = D_800489F0;')
          if sk=='nv1': st.append('nv1 = D_800489F4;')
          for order in (st, st[::-1]):
            slots={'A':[], 'B':[], 'C':[]}
            slots[pos]=order
            T='threshold' if tk=='threshold' else 'arg2'
            src=tmpl.replace('{A}',' '.join(slots['A'])+' ').replace('{B}',' '.join(slots['B'])).replace('{C}',' '.join(slots['C'])).replace('E1',ef(S,B)).replace('E2',ef(S,B)).replace('THR',T)
            cands.append(((ek,sk,bk,tk,pos,tuple(order)),head+src))
print(len(cands),flush=True)
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:12]: print(r,k)
print('---')
for r,(k,s) in zip(out,cands):
    if k[1]=='lit' and k[2]=='lit' and k[0]=='ms': print(r,k)
