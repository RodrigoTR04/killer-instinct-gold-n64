import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read()
head,body=base.split('void func_8001BDE0')
head=head
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold;
    f32 temp_f24; f32 new_var3; s32 var_s0; u8 *temp_v1;
    threshold = arg2; {A}if (D_8004AA28 != 1) {{ temp_v1 = *arg0; {B}
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); {C}
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * arg2) - temp_f24;
        if (temp_f0 <= threshold) {{ func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {{
                goto loop_2; }} }}
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0_2 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * arg2) - temp_f24;
        if (threshold < temp_f0_2) {{
            func_8001BF1C(arg0, arg1, var_s0, temp_f0_2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {{
                goto loop_5;
            }}
        }}
    }}
}}
""".replace("{A}","{A}").replace("{{","{").replace("}}","}")
stmts={'b':"temp_f24 = D_800489F0;",'s':"new_var3 = D_800489F4;",'c':"arg2 = new_var3;"}
cands=[]
import re
def build(pos):
    # pos: dict stmt -> slot A/B/C
    slots={'A':[], 'B':[], 'C':[]}
    for k in 'bsc': slots[pos[k]].append(stmts[k])
    return head+tmpl.replace("{A}",' '.join(slots['A'])+' ').replace("{B}",' '.join(slots['B'])).replace("{C}",' '.join(slots['C']))
for pb in 'ABC':
  for ps in 'ABC':
    for pc in 'ABC':
      for order in itertools.permutations('bsc'):
        pos={'b':pb,'s':ps,'c':pc}
        # order within slot given by 'order'
        slots={'A':[], 'B':[], 'C':[]}
        for k in order: slots[pos[k]].append(stmts[k])
        # require c after s
        if order.index('c')<order.index('s') and pos['c']==pos['s']: continue
        if ord(pos['c'])<ord(pos['s']): continue
        src=head+tmpl.replace("{A}",' '.join(slots['A'])+' ').replace("{B}",' '.join(slots['B'])).replace("{C}",' '.join(slots['C']))
        cands.append(((pb,ps,pc,''.join(order)),src))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:10]: print(r,k)
