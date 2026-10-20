/* T-072 DRAFT: 89 -> 77 differing words in owning TU; 560/556 bytes.
 * Requires TU declarations; see T-072/REPORT.md. */
typedef struct {
    float x,y,z;
    s16 speed,timer;
}
T024MovingParticle;
extern T024MovingParticle D_80061538[][20];
extern u8 D_800614D0,D_80061520[],D_8004A40C,D_8004AA28,D_801D87FE,D_80061CD5;
extern float D_80061CC8[],D_80061528;
extern u32 func_800326F0(void);
extern void func_8002970C(s32,s32);
void func_800287D4(void)
{
    s32 i,j;
    T024MovingParticle *p;
    for(i=0;
    i<D_800614D0;
    i++) for(j=0;
    j<D_80061520[i];
    j++) if(D_8004A40C==0 && (D_8004AA28!=0 || D_801D87FE==0))
    {
        p=&D_80061538[i][j];
        p->timer--;
        if(p->timer<50)
        {
            if(D_80061CD5==1 || i!=0) func_8002970C(i,j);
            else p->timer=10;
        }
        else
        {
            p->x+=D_80061CC8[0];
            p->y+=D_80061CC8[1];
            p->z+=D_80061CC8[2];
            p->y+=(float)p->speed*D_80061528;
            if(func_800326F0()>=0x7FFF0001U) p->x+=D_80061528;
            else p->x-=D_80061528;
            if(func_800326F0()>=0x7FFF0001U) p->z+=D_80061528;
            else p->z-=D_80061528;
        }
    }
}
