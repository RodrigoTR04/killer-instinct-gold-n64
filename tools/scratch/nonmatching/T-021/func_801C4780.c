/* DRAFT. Remaining diff: Argument representation/spills, temporary registers and scheduling differ. */
typedef union { f64 alignment; struct { s32 x,y; } value; } T021Input;
extern s32 D_802D3678[],D_802D367C[];
extern u8 D_80295720,D_802D3958;
void func_801C4780(s32 arg0,T021Input arg2) { if((arg2.value.y&0xD00F)&&arg0+1==D_80295720) D_802D3958=3; D_802D3678[arg0*2]=arg2.value.x; D_802D367C[arg0*2]=arg2.value.y; }