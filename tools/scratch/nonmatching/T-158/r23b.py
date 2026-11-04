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
def body(variant):
    L=[]
    return L
forms={
'f1':"""    s32 i;
    u8 player;
    u8 *count;
    s32 old;
    s32 facing;
    T020Position position;
    D_8004F390[0] = (D_8004F390[1] = 0);
    for (i = 0; i < 40; i++) {
        if (ACT(i).kind == 31) {
            player = ACT(i).player; count = &D_8004F390[player];
            if (*count >= 8) { *count = 7; }
            func_8002E08C(&ACT(i), &position);
            if (ACT(i).facing >= 128) facing = 1; else facing = 0;
            old = *count;
            D_8004F2D0[player][old].x = ACT(i).x >> 4;
            D_8004F2D0[player][old].y = ACT(i).y >> 4;
            D_8004F2D0[player][old].facing = facing;
            *count = old + 1;
        }
    }
}
""",
'f2':"""    s32 i;
    u8 player;
    u8 *count;
    s32 facing;
    T020Position position;
    D_8004F390[0] = (D_8004F390[1] = 0);
    for (i = 0; i < 40; i++) {
        if (ACT(i).kind == 31) {
            player = ACT(i).player; count = &D_8004F390[player];
            if (*count >= 8) { *count = 7; }
            func_8002E08C(&ACT(i), &position);
            if (ACT(i).facing >= 128) facing = 1; else facing = 0;
            D_8004F2D0[player][*count].x = ACT(i).x >> 4;
            D_8004F2D0[player][*count].y = ACT(i).y >> 4;
            D_8004F2D0[player][*count].facing = facing;
            (*count)++;
        }
    }
}
""",
}
cands=list(forms.items())
out=lib.run('func_80023EF0',[pre+c[1] for c in cands])
for r,(k,s) in zip(out,cands): print(r,k)
for k,s in cands: open(f'/tmp/w/r23b_{k}.c','w').write(pre+s)
