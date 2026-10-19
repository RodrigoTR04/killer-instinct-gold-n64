/* DRAFT. Remaining diff: 2 differing words; 100/100 bytes */
typedef struct { float x,y,z; s16 active,timer; } T024Particle;
extern T024Particle D_80061538[][20];
extern u32 func_800326F0(void);
void func_8002970C(s32 group,s32 index) { T024Particle *p=&D_80061538[group][index]; p->active=1; p->x=0.0f; p->y=0.0f; p->z=0.0f; p->timer=(func_800326F0() >> 28)+100; }
