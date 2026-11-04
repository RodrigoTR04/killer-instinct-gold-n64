import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold; f32 bi; f32 ia; f32 nv; f32 nv2; s32 var_s0; u8 *temp_v1;
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
thr_chains={'c1':(["threshold = arg2;"],'threshold'),'c2':(["nv = arg2;","threshold = nv;"],'threshold'),'c3':(["nv = arg2;","nv2 = nv;","threshold = nv2;"],'threshold'),'c2b':(["nv = arg2;"],'nv')}
scale_opts={'arg2d':(["arg2 = D_800489F4;"],'arg2'),'arg2i':(["ia = D_800489F4;","arg2 = ia;"],'arg2'),'ia':(["ia = D_800489F4;"],'ia')}
for tk,(tst,T) in thr_chains.items():
  for sk,(sst,S) in scale_opts.items():
    bst=["bi = D_800489F0;"]; B='bi'
    allst=tst+sst+bst
    # keep chain internal order; interleave slots
    n=len(allst)
    for perm in itertools.permutations(range(n)):
        # respect intra-chain order
        pos={i:perm.index(i) for i in range(n)}
        ok=True
        for chain in (range(0,len(tst)),range(len(tst),len(tst)+len(sst))):
            c=list(chain)
            for a,b in zip(c,c[1:]):
                if pos[a]>pos[b]: ok=False
        # thr chain must read arg2 before arg2 is reassigned
        if S=='arg2':
            last_arg2_def=len(tst)+len(sst)-1
            if pos[len(tst)-1]>pos[len(tst)]: ok=False if tk!='c2b' else ok
        if not ok: continue
        # bias must be defined before scale (emission order bias->scale)
        if pos[n-1]>pos[len(tst)+len(sst)-1]: continue
        order=[allst[i] for i in sorted(range(n),key=lambda i:pos[i])]
        for cuts in itertools.combinations_with_replacement('ABC',n):
            slots={'A':[],'B':[],'C':[]}
            for st,c in zip(order,cuts): slots[c].append(st)
            src=tmpl.replace('{A}',' '.join(slots['A'])+' ').replace('{B}',' '.join(slots['B'])).replace('{C}',' '.join(slots['C'])).replace('SCALE',S).replace('BIAS',B).replace('THR',T)
            if src in seen: continue
            seen.add(src); cands.append(((tk,sk,tuple(order),cuts),head+src))
print(len(cands),flush=True)
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:10]: print(r,k)
open('/tmp/w/r8001l_best.c','w').write(res[0][1][1])
