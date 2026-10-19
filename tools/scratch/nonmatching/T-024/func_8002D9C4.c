/* DRAFT. Remaining diff: 134 differing words; 476/536 bytes */
typedef struct { float x,y,z,pitch,yaw; } T024CameraPose;
extern float D_800695CC,D_800695D0,D_800695D4,D_800695D8,D_800695DC;
extern void func_8002DBDC(float,float *),func_8002DC48(float *);
void func_8002D9C4(T024CameraPose *pose,s32 frame,s32 duration,s32 reverse) { T024CameraPose to,from; float t=frame,total=duration; if(reverse==0) { to=*pose; from.x=D_800695CC; from.y=D_800695D0; from.z=D_800695D4; from.pitch=D_800695D8; from.yaw=D_800695DC; } else { from=*pose; to.x=D_800695CC; to.y=D_800695D0; to.z=D_800695D4; to.pitch=D_800695D8; to.yaw=D_800695DC; } D_800695CC=(to.x-from.x)*t/total+from.x; D_800695D0=(to.y-from.y)*t/total+from.y; D_800695D4=(to.z-from.z)*t/total+from.z; func_8002DBDC(to.pitch,&from.pitch); D_800695D8=(to.pitch-from.pitch)*t/total+from.pitch; func_8002DC48(&D_800695D8); func_8002DBDC(to.yaw,&from.yaw); D_800695DC=(to.yaw-from.yaw)*t/total+from.yaw; func_8002DC48(&D_800695DC); }
