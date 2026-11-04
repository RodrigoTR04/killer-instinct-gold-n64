import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""typedef struct { s32 x,y,z; f32 worldX,worldZ,worldY,height; u8 pad[8]; s32 top; } T020Position;
typedef struct { u32 x,y; s8 facing; u8 pad[3]; } T032Point23E;
extern T032Point23E D_8004F2D0[2][8];
extern u8 D_8004F390[2];
extern void func_8002E08C(T032Actor23E *, void *);
void func_80023EF0(void)
{
"""
inner="""        if (D_801D3430[i].kind == 31) {
            player = D_801D3430[i].player; count = &D_8004F390[player];
            if (*count >= 8) { *count = 7; }
            func_8002E08C(ARG, &position);
            if (D_801D3430[i].facing >= 128) facing = 1; else facing = 0;
            old = *count;
            D_8004F2D0[player][old].x = D_801D3430[i].x >> 4;
            D_8004F2D0[player][old].y = D_801D3430[i].y >> 4;
            D_8004F2D0[player][old].facing = facing;
            *count = old + 1;
        }
"""
decl="    s32 i; u8 player; u8 *count; s32 old; s32 facing; T020Position position; T032Actor23E *actor;\n    D_8004F390[0] = (D_8004F390[1] = 0);\n"
forms={
'a':decl+"    for (i = 0; i < 40; i++) {\n"+inner.replace('ARG','&D_801D3430[i]')+"    }\n}\n",
'b':decl+"    for (i = 0; i < 40; i++) {\n"+inner.replace('ARG','D_801D3430 + i')+"    }\n}\n",
'c':decl+"    for (i = 0; i < 40; i++) {\n        actor = &D_801D3430[i];\n"+inner.replace('ARG','actor')+"    }\n}\n",
}
cands=list(forms.items())
out=lib.run('func_80023EF0',[pre+c[1] for c in cands])
for r,(k,s) in zip(out,cands): print(r,k)
for k,s in cands: open(f'/tmp/w/r23e_{k}.c','w').write(pre+s)
