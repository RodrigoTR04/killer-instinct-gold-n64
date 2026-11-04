import sys, itertools, random, re
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head="""f32 func_801B19F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
typedef struct { u32 w0, w1; } T025Gfx2B8C;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30B8;
extern s32 D_801D30BC;
extern f64 D_80292968;
extern f64 D_80292970;
extern s16 D_802C87D0;
extern u8 D_802C87D8[];
extern u8 D_802C87E8[];
typedef struct { f32 x, y, z; } CameraEye;
"""
R=random.Random(int(sys.argv[1]))
def gen():
    o={}
    o['phase']=R.random()<0.5
    o['tickmode']=R.choice(['arg3','local','direct'])
    o['counter']=R.choice(['ptr','direct'])
    o['np']=R.choice([2,3,4,5,6])
    o['packed']=R.random()<0.5
    o['color2']=R.random()<0.5
    o['prim']=R.random()<0.5
    o['first']=R.random()<0.5
    D=[]
    D.append("u8 alpha;")
    if o['counter']=='ptr': D.append("s32 *counter = &D_801D30B8;")
    D.append("u8 matrix[64];")
    names=[f"p{i}" for i in range(o['np'])]
    D.append("T025Gfx2B8C "+", ".join("*"+n for n in names)+";")
    D.append("u8 color;")
    if o['packed']: D.append("s32 packed;")
    if o['color2']: D.append("s32 color2;")
    D.append("u32 value;")
    if o['prim']: D.append("u32 primitive;")
    if o['phase']: D.append("f64 phase;")
    D.append("CameraEye eye;")
    if o['tickmode']=='local': D.append("s32 tick;")
    if R.random()<0.5: R.shuffle(D)
    cnt="*counter" if o['counter']=='ptr' else "D_801D30B8"
    tick={'arg3':'arg3','local':'tick','direct':None}[o['tickmode']]
    P=lambda k: names[min(k,len(names)-1)]
    prim="primitive" if o['prim'] else "0xFA000000"
    L=[]
    L.append("    if ((s32) D_801D3088 <= 0) { return 0; }")
    if tick:
        L.append(f"    eye.x = sinf((f32)((f64)D_801D30BC * D_80292968)); {tick} = D_801D30BC;")
        if o['phase']: L.append(f"    phase = (f64){tick}; eye.y = (f32)(phase * D_80292970);")
        else: L.append(f"    eye.y = (f32)((f64){tick} * D_80292970);")
        L.append(f"    D_801D30BC = ++{tick}; eye.y = cosf(eye.y);")
    else:
        L.append("    eye.x = sinf((f32)((f64)D_801D30BC * D_80292968));")
        L.append("    eye.y = cosf((f32)((f64)D_801D30BC * D_80292970)); D_801D30BC += 1;")
    L.append("    eye.z = 220.0f;")
    L.append("    guLookAtReflect(&matrix, &D_802C87D8, eye.x * 60.0f, eye.y * 60.0f, eye.z, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);")
    if o['prim']: L.append("    primitive = 0xFA000000;")
    L.append(f"    arg1 = {cnt};")
    L.append(f"    {P(0)} = (*arg0)++; {P(0)}->w0 = 0x03840010; {P(0)}->w1 = (u32)&D_802C87D8;")
    L.append(f"    {P(1)} = (*arg0)++; {P(1)}->w0 = 0x03820010; {P(1)}->w1 = (u32)&D_802C87E8;")
    L.append("    if (arg1++ < 10) {")
    L.append(f"        value = (u32)func_801B19F0(0.0f, 255.0f, {cnt} = arg1, 10); color = (u16)value;")
    pk="packed" if o['packed'] else "value"
    if not o['packed']: L.append("        alpha = value;")
    L.append(f"        {pk} = ((color & 0xFF) << 24) | ((color & 0xFF) << 16) | ((color & 0xFF) << 8) | (color & 0xFF);")
    if o['packed']: L.append("        alpha = value;")
    L.append(f"        {P(2)} = (*arg0)++; {P(2)}->w0 = {prim}; {P(2)}->w1 = {pk};")
    L.append("    } else {")
    L.append(f"        {cnt} = arg1;")
    c2="color2" if o['color2'] else "value"
    L.append("        do {")
    L.append(f"            {P(2)} = (*arg0)++; {P(2)}->w0 = {prim};")
    L.append(f"            {c2} = D_802C87D0 & 0xFF;")
    L.append(f"            {P(2)}->w1 = ({c2} << 24) | ({c2} << 16) | ({c2} << 8) | (alpha & 0xFF);")
    L.append("            alpha = 0xFF;")
    L.append("            if ((s32) D_801D308C >= 1) { break; }")
    L.append("            D_801D308C += 1;")
    L.append("        } while (0);")
    L.append("    }")
    L.append("    guTranslate(arg2, -175.0f, 0.0f, (f32)D_801D3094);")
    L.append("    if (D_801D3094 < 0) { D_802C87D0 = D_801D3094 + 255; } else { D_802C87D0 = 255; }")
    L.append(f"    {P(3)} = (*arg0)++; {P(3)}->w0 = 0xB900031D; {P(3)}->w1 = 0x0F0A4000;")
    L.append(f"    {P(4)} = (*arg0)++; {P(4)}->w0 = 0xFB000000; {P(4)}->w1 = (alpha + D_801D3094) & 0xFF;")
    L.append(f"    {P(5)} = (*arg0)++; {P(5)}->w0 = 0x06000000; {P(5)}->w1 = (u32)&D_801D3030;")
    L.append("    return 1;")
    src=head+"s32 func_801B2B8C(T025Gfx2B8C **arg0, s32 arg1, u8 *arg2, s32 arg3) {\n"+''.join('    '+d+'\n' for d in D)+'\n'.join(L)+"\n}\n"
    return o,src
cands=[gen() for _ in range(int(sys.argv[2]))]
out=lib.run('func_801B2B8C',[c[1] for c in cands])
from collections import Counter
print(Counter((r[2] if r else None) for r in out))
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999,999))[2]!=184,(t[0] or (999,999))[1]))
for r,(o,s) in res[:6]: print(r,o)
open('/tmp/w/r2b8c9_best.c','w').write(res[0][1][1])
