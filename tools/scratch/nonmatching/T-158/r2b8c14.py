import sys, itertools, re, random, tempfile
from pathlib import Path
import concurrent.futures as cf
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
sys.argv=[sys.argv[0]]+sys.argv[1:]
cm=lib.cm
exec(open('tools/scratch/nonmatching/T-158/r2b8c12.py').read().split("keys=")[0].split("code=")[0])
def asm_of(src):
    with tempfile.TemporaryDirectory(prefix='a158-') as d:
        p=Path(d)/'draft.c'; p.write_text(src)
        source,tu=cm.build_source('func_801B2B8C',p,True)
        o=cm.compile_source(source,Path(d)/'c.c')
        pairs=cm.draft_raw(o,'func_801B2B8C')
    return [cm.canon(cm.apply_relocs(i,r)) for _,i,r in pairs]
def regs(a):
    A1=A2=None
    for l in a:
        m=re.match(r'lui (\w+),%hi\(0x801d308c\)',l)
        if m: A1=m.group(1)
        m=re.match(r'lui (\w+),%hi\(0x801d3094\)',l)
        if m: A2=m.group(1)
    fr=next((abs(int(re.search(r'-?\d+$',x).group())) for x in a if x.startswith('addiu sp,sp,')),0)
    return A1,A2,fr
dw=open('tools/scratch/nonmatching/T-158/w_2b8c_dw.c').read()
head=dw[:dw.index("s32 func_801B2B8C")]
def gen(names,phase):
    c1,c2,cT,cE,cB,cF,c6=names
    used=[]
    for n in names:
        if n not in used: used.append(n)
    decl="    u8 alpha;\nAnimationState *state = &D_801D30B8; u8 matrix[64];\n    u32 value;\n    u8 color;\n    "+"T025Gfx2B8C "+", ".join('*'+n for n in used)+";\n"+("    f64 phase;\n" if phase else "")+"    CameraEye eye;\n"
    ph="phase = (f64)arg3; eye.y = (f32)(phase * D_80292970);" if phase else "eye.y = (f32)((f64)arg3 * D_80292970);"
    body=f"""    if ((s32)D_801D3088 <= 0) return 0;
    eye.x = sinf((f32)((f64)state->timer * D_80292968)); arg3 = state->timer; {ph} state->timer = ++arg3; eye.y = cosf(eye.y);
    eye.z = 220.0f;
    guLookAtReflect(&matrix, &D_802C87D8, eye.x * 60.0f, eye.y * 60.0f, eye.z, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); arg1 = state->fade;
    {c1} = (*arg0)++;
    {c1}->w0 = 0x03840010; {c1}->w1 = (u32)&D_802C87D8;
    {c2} = (*arg0)++;
    {c2}->w0 = 0x03820010; {c2}->w1 = (u32)&D_802C87E8;
    if (arg1++ < 10) {{
        value = (u32)func_801B19F0(0.0f, 255.0f, state->fade = arg1, 10); color = (u16)value;
        alpha = value;
        value = ((color & 0xFF) << 24) | ((color & 0xFF) << 16) | ((color & 0xFF) << 8) | (color & 0xFF); {cT} = (*arg0)++;
        {cT}->w0 = 0xFA000000; {cT}->w1 = value;
    }}
    else
    {{
        state->fade = arg1;
        do {{
            {cE} = (*arg0)++;
            {cE}->w0 = 0xFA000000;
            value = D_802C87D0 & 0xFF;
            {cE}->w1 = (value << 24) | (value << 16) | (value << 8) | (alpha & 0xFF);
            alpha = 0xFF;
            if ((s32)D_801D308C >= 1) {{
                break;
            }}
            D_801D308C += 1;
        }} while (0);
    }}
    guTranslate(arg2, -175.0f, 0.0f, (f32)D_801D3094);
    if (D_801D3094 < 0) D_802C87D0 = D_801D3094 + 255; else D_802C87D0 = 255; {cB} = (*arg0)++; {cB}->w0 = 0xB900031D; {cB}->w1 = 0x0F0A4000;
    {cF} = (*arg0)++; {cF}->w0 = 0xFB000000; {cF}->w1 = (alpha + D_801D3094) & 0xFF;
    {c6} = (*arg0)++; {c6}->w0 = 0x06000000; {c6}->w1 = (u32)&D_801D3030;
    return 1; }}
"""
    return head+"s32 func_801B2B8C(T025Gfx2B8C **arg0, s32 arg1, u8 *arg2, s32 arg3)\n{\n"+decl+body
R=random.Random(3)
P=['p0','p1','p2','p3','p4','p5']
cands=[]
seen=set()
for _ in range(1500):
    k=(tuple(R.choice(P[:R.choice([2,3,4,5,6])]) for _ in range(7)),R.random()<0.5)
    if k in seen: continue
    seen.add(k); cands.append(k)
def run(k):
    try: return k,regs(asm_of(gen(*k)))
    except SystemExit: return k,None
with cf.ThreadPoolExecutor(12) as ex: res=list(ex.map(run,cands))
good=[k for k,r in res if r and r[0]=='a2' and r[1]=='a3']
print(len(res),'good A regs',len(good))
good184=[k for k,r in res if r and r[0]=='a2' and r[1]=='a3' and r[2]==184]
print('with frame 184',len(good184))
sc=lib.run('func_801B2B8C',[gen(*k) for k in good[:80]])
for k,r in sorted(zip(good[:80],sc),key=lambda t:(t[1] or (999,999))[1])[:8]: print(r,k)
