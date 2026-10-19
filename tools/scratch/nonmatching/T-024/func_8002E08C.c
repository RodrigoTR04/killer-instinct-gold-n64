/* DRAFT. Remaining diff: 19 differing words; 192/184 bytes */
typedef struct { s32 pad,x,y,z; u8 pad10[0x58]; float a,b; u32 distance; } T024CameraInput;
typedef struct { u8 pad[0xC]; float x,z,y; } T024CameraOutput;
extern float D_8004AC84,D_8004AC80;
extern void func_8002DCC8(float,float,float,u32 *);
extern void func_8002DDD4(float,float,void *,void *,float,float *,float *);
void func_8002E08C(T024CameraInput *in,T024CameraOutput *out) { out->x=(float)in->x/D_8004AC84; out->z=(float)in->z/D_8004AC84+D_8004AC80; out->y=(float)in->y/D_8004AC84; func_8002DCC8(out->x,out->z,out->y,&in->distance); func_8002DDD4(out->x,out->z,in,out,out->y,&in->a,&in->b); }
