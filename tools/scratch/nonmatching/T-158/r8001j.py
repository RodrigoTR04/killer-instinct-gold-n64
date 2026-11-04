import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold; f32 bi; s32 var_s0; u8 *temp_v1;
    {A}if (D_8004AA28 != 1) { temp_v1 = *arg0; {B}
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); {C}
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * SCALE) - BIAS;
        if (temp_f0 <= threshold) { func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {
                goto loop_2; } }
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0_2 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * SCALE) - BIAS;
        if (threshold < temp_f0_2) {
            func_8001BF1C(arg0, arg1, var_s0, temp_f0_2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {
                goto loop_5;
            }
        }
    }
}
"""
cands=[]
for scale in ('1500.0f','arg2'):
  for bias in ('590.0f','bi'):
    for sp in 'ABC':
      for bp in 'ABC':
        st_s="arg2 = 1500.0f;" if scale=='arg2' else ""
        st_b="bi = 590.0f;" if bias=='bi' else ""
        for tpos in 'A':
          slots={'A':['threshold = arg2;'],'B':[],'C':[]}
          if st_s: slots[sp].append(st_s)
          if st_b: slots[bp].append(st_b)
          for o in (0,1):
            sl={k:(v if o==0 else v[::-1]) for k,v in slots.items()}
            if sl['A'] and sl['A'][0]!='threshold = arg2;' and 'arg2 = 1500.0f;' in sl['A'] and sl['A'].index('arg2 = 1500.0f;')<sl['A'].index('threshold = arg2;'): continue
            src=tmpl.replace('{A}',' '.join(sl['A'])+' ').replace('{B}',' '.join(sl['B'])).replace('{C}',' '.join(sl['C'])).replace('SCALE',scale).replace('BIAS',bias)
            cands.append(((scale,bias,sp,bp,o),head+src))
seen=set(); uc=[]
for k,s in cands:
    if s in seen: continue
    seen.add(s); uc.append((k,s))
out=lib.run('func_8001BDE0',[c[1] for c in uc])
res=sorted(zip(out,uc),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:10]: print(r,k)
open('/tmp/w/r8001j_best.c','w').write(res[0][1][1])
