import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""typedef struct { s32 x,y,z; f32 worldX,worldZ,worldY,height; u8 pad[8]; s32 top; } T020Position;
typedef struct { u8 kind; u8 pad1[0x23]; u8 facing; u8 pad25[0x43]; u32 x,y; u8 pad70[0x44]; u8 player; u8 tail[0x4B]; } T032Actor23E;
typedef struct { u32 x,y; s8 facing; u8 pad[3]; } T032Point23E;
extern T032Point23E D_8004F2D0[2][8];
extern u8 D_8004F390[2];
extern void func_8002E08C(T032Actor23E *, void *);
#define ACT(i) (((T032Actor23E *)&D_801D3430)[i])
void func_80023EF0(void)
{
"""
inner="""        if (ACT(i).kind == 31) {
            player = ACT(i).player; count = &D_8004F390[player];
            if (*count >= 8) { *count = 7; }
            func_8002E08C(ARG, &position);
            if (ACT(i).facing >= 128) facing = 1; else facing = 0;
            old = *count;
            D_8004F2D0[player][old].x = ACT(i).x >> 4;
            D_8004F2D0[player][old].y = ACT(i).y >> 4;
            D_8004F2D0[player][old].facing = facing;
            *count = old + 1;
        }
"""
decl="    s32 i; u8 player; u8 *count; s32 old; s32 facing; T020Position position; T032Actor23E *actor;\n    D_8004F390[0] = (D_8004F390[1] = 0);\n"

forms={}
for name,arg in [('kind','(T032Actor23E *)&ACT(i).kind'),('plus','(T032Actor23E *)((u8 *)&D_801D3430 + i * 256)'),('arr','&((T032Actor23E *)&D_801D3430)[i]')]:
    forms['a_'+name]=decl+"    for (i = 0; i < 40; i++) {\n"+inner.replace('ARG',arg)+"    }\n}\n"
    forms['p_'+name]=decl+"    for (i = 0; i < 40; i++) {\n        actor = "+arg+";\n"+inner.replace('ARG','actor')+"    }\n}\n"
    forms['w_'+name]=decl+"    i = 0;\n    while (i < 40) {\n"+inner.replace('ARG',arg)+"        i++;\n    }\n}\n"
    forms['d_'+name]=decl+"    i = 0;\n    do {\n"+inner.replace('ARG',arg)+"        i++;\n    } while (i != 40);\n}\n"
cands=list(forms.items())
out=lib.run('func_80023EF0',[pre+c[1] for c in cands])
for r,(k,s_) in sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1]): print(r,k)
for k,s_ in cands: open(f'/tmp/w/r23d_{k}.c','w').write(pre+s_)
