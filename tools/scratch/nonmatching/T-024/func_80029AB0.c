/* DRAFT. Remaining diff: 69 differing words; 284/304 bytes */
typedef struct { u8 pad[0x90]; float velocity[12],position[12]; u8 padF0[0xC]; s16 age[12],duration[12],timer,limit; u8 tail[0x10]; } T024Effect;
extern T024Effect D_80061D60[];
void func_80029AB0(void) { s32 i,j; T024Effect *p=D_80061D60; for(i=0;i<4;i++,p++) { if(p->timer>=0) { p->timer++; if(p->limit<p->timer) p->timer=-1; for(j=0;j<12;j+=2) { if(p->age[j]<p->duration[j]) p->age[j]++; p->position[j]+=p->velocity[j]-(p->velocity[j]/3.0f*(float)p->age[j])/(float)p->duration[j]; if(p->age[j+1]<p->duration[j+1]) p->age[j+1]++; p->position[j+1]+=p->velocity[j+1]-(p->velocity[j+1]/3.0f*(float)p->age[j+1])/(float)p->duration[j+1]; } } } }
