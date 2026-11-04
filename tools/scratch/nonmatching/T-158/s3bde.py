import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern u8 D_8004AA28;
extern u8 D_8004AC88;
void func_8001BF1C(u8 **, s32, s32, f32);
extern f32 D_800489F0;
extern f32 D_800489F4;
extern u8 D_8004A4C8;
extern u8 D_801D7E00;
extern u8 D_801D8550;
"""
VARS=['arg2','T','X','Y']
def gen(mapping, order, litmode, copy_first):
    # mapping: dict role->var name
    names={'T':'threshold','X':'tx','Y':'ty','arg2':'arg2'}
    defs={'t':f"{names[mapping['t']]} = arg2;" if mapping['t']!='arg2' else None,
          's':f"{names[mapping['s']]} = "+("1500.0f" if litmode else "D_800489F4")+";",
          'b':f"{names[mapping['b']]} = "+("590.0f" if litmode else "D_800489F0")+";"}
    stm=' '.join(defs[c] for c in order if defs[c])
    # arg2 must be preserved until the copy happens: ensure thr copy comes before any arg2 overwrite
    used=set(mapping.values())
    if mapping['t']!='arg2':
        # copy of arg2 must precede reuse of arg2
        pass
    T,S,B=[names[mapping[r]] for r in 'tsb']
    decl="u8 *var_s1; f32 temp_f0; f32 temp_f0_2; s32 var_s0; u8 *temp_v1; f32 threshold; f32 tx; f32 ty;"
    return pre+f"""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {{ {decl}
    if (D_8004AA28 != 1) {{ temp_v1 = *arg0;
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); {stm}
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * {S}) - {B};
        if (temp_f0 <= {T}) {{ func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {{
                goto loop_2; }} }}
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0_2 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * {S}) - {B};
        if ({T} < temp_f0_2) {{
            func_8001BF1C(arg0, arg1, var_s0, temp_f0_2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {{
                goto loop_5;
            }}
        }}
    }}
}}
"""
cands=[]
for p in itertools.permutations(VARS,3):
    m=dict(zip('tsb',p))
    # a copy var for thr is needed if thr isn't arg2 and arg2 is reassigned for another role
    for order in itertools.permutations('tsb'):
        # arg2 overwritten by role r before copy 't' => invalid
        if m['t']!='arg2' and 'arg2' in (m['s'],m['b']):
            r='s' if m['s']=='arg2' else 'b'
            if order.index(r)<order.index('t'): continue
        for lit in (0,1):
            cands.append(((p,''.join(order),lit),gen(m,order,lit,0)))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1])
for r,(k,s) in res[:12]: print(r,k)
