import sys, itertools, re
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
s=open('tools/scratch/nonmatching/T-158/w_2b8c_dw.c').read()
def feat(bits):
    t=s
    a,b,c,d,e,f,g,h,i = bits
    if a: # counter pointer for fade
        t=t.replace("AnimationState *state = &D_801D30B8;","AnimationState *state = &D_801D30B8; s32 *counter = &D_801D30B8.fade;").replace("state->fade","*counter")
    if b:
        t=t.replace("AnimationState *state = &D_801D30B8;","AnimationState *state = &D_801D30B8; s32 *timer = &D_801D30B8.timer;").replace("state->timer","*timer")
    if c:
        t=t.replace("{ T025Gfx2B8C *first = (*arg0)++;\n    first->w0 = 0x03840010; first->w1 = (u32)&D_802C87D8;\n    }","p1 = (*arg0)++; p1->w0 = 0x03840010; p1->w1 = (u32)&D_802C87D8;")
        t=t.replace("T025Gfx2B8C *p1;","T025Gfx2B8C *p1;") 
    if d:
        t=t.replace("u32 value;","u32 value; u32 primitive;").replace("p0->w0 = 0xFA000000;","p0->w0 = primitive;").replace("p1->w0 = 0xFA000000;","p1->w0 = primitive;").replace("    if ((s32)D_801D3088 <= 0) return 0;","    if ((s32)D_801D3088 <= 0) return 0;\n    primitive = 0xFA000000;")
    if e:
        t=t.replace("u32 value;","u32 value; s32 color2;").replace("value = D_802C87D0 & 0xFF;\n            p0->w1 = (value << 24) | (value << 16) | (value << 8) | (alpha & 0xFF);","color2 = D_802C87D0 & 0xFF;\n            p0->w1 = (color2 << 24) | (color2 << 16) | (color2 << 8) | (alpha & 0xFF);")
    if f:
        t=t.replace("u32 value;","u32 value; s32 packed;").replace("value = ((color & 0xFF) << 24) | ((color & 0xFF) << 16) | ((color & 0xFF) << 8) | (color & 0xFF); p1 = (*arg0)++;\n        p1->w0 = 0xFA000000; p1->w1 = value;","packed = ((color & 0xFF) << 24) | ((color & 0xFF) << 16) | ((color & 0xFF) << 8) | (color & 0xFF); p1 = (*arg0)++;\n        p1->w0 = 0xFA000000; p1->w1 = packed;")
    if g:
        t=t.replace("p0 = (*arg0)++; p0->w0 = 0xB900031D;","p1 = (*arg0)++; p1->w0 = 0xB900031D;").replace("p0->w1 = 0x0F0A4000;","p1->w1 = 0x0F0A4000;")
    if h:
        t=t.replace("arg3","tick").replace("s32 func_801B2B8C(T025Gfx2B8C **arg0, s32 arg1, u8 *arg2, s32 tick)","s32 func_801B2B8C(T025Gfx2B8C **arg0, s32 arg1, u8 *arg2, s32 arg3)").replace("    u8 alpha;","    u8 alpha; s32 tick;",1)
    if i:
        t=t.replace("    f64 phase; CameraEye eye;","    CameraEye eye;").replace("phase = (f64)arg3; eye.y = (f32)(phase * D_80292970);","eye.y = (f32)((f64)arg3 * D_80292970);").replace("phase = (f64)tick; eye.y = (f32)(phase * D_80292970);","eye.y = (f32)((f64)tick * D_80292970);")
    return t
cands=[(b,feat(b)) for b in itertools.product((0,1),repeat=9)]
out=lib.run('func_801B2B8C',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999,999))[2]!=184,(t[0] or (999,999))[1]))
for r,(b,x) in res[:12]: print(r,b)
open('/tmp/w/r2b8c11_best.c','w').write(res[0][1][1])
