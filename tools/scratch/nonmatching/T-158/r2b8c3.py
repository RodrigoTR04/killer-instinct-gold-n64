import sys, itertools, re
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
src=open('tools/scratch/nonmatching/T-158/w_2b8c_sib.c').read()
def variant(counter_ptr, timer_ptr, np, use_packed, use_color2, use_prim):
    s=src
    if not counter_ptr:
        s=s.replace("    s32 *counter = &D_801D30B8;\n","").replace("*counter","D_801D30B8")
    if not timer_ptr:
        s=s.replace("    s32 *timer = &D_801D30BC;\n","").replace("*timer","D_801D30BC")
    # pointers: map p0..p5 -> fewer names
    maps={6:{},5:{'p5':'p4'},4:{'p5':'p3','p4':'p3'},3:{'p3':'p1','p4':'p1','p5':'p1'},2:{'p2':'p1','p3':'p1','p4':'p1','p5':'p1'},1:{k:'p0' for k in ('p1','p2','p3','p4','p5')}}[np]
    s=s.replace('T025Gfx2B8C *p0, *p1, *p2, *p3, *p4, *p5;','@@PDECL@@')
    for a,b in maps.items(): s=re.sub(r'\b'+a+r'\b',b,s)
    names=sorted({f'p{i}' for i in range(6)}-set(maps))
    s=s.replace('@@PDECL@@','T025Gfx2B8C '+', '.join('*'+n for n in names)+';')
    if not use_packed:
        s=s.replace("    s32 packed;\n","").replace("packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);","value = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);").replace("(s32) packed","(s32) value")
        # value reused: alpha = value must precede
        s=s.replace("        alpha = value;\n        p2 =","        p2 =").replace("        color = (u16)value;\n","        color = (u16)value;\n        alpha = value;\n")
    if not use_color2:
        s=s.replace("    s32 color2;\n","").replace("color2","value")
    if not use_prim:
        s=s.replace("    u32 primitive;\n","").replace("    primitive = 0xFA000000;\n","").replace("primitive","0xFA000000")
    return s
cands=[]
for cp,tp,np,pk,c2,pr in itertools.product((1,0),(1,0),(6,5,4,3,2),(1,0),(1,0),(1,0)):
    cands.append(((cp,tp,np,pk,c2,pr),variant(cp,tp,np,pk,c2,pr)))
out=lib.run('func_801B2B8C',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[2]!=184,(t[0] or (999,999))[1]))
for r,(k,s) in res[:15]: print(r,k)
open('/tmp/w/r2b8c3_best.c','w').write(res[0][1][1])
