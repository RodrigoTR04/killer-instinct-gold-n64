/* T-132 DRAFT: 305 differing words; see T-132/REPORT.md. */
#include "common.h"
typedef struct { u32 command,value; } T03315594Command;
extern u8 D_80044A24,D_8004AA28,D_80068930;
extern u32 D_8004A428[];
#define CMD(a,b) { T03315594Command *c=g++; c->command=(a); c->value=(b); }
void func_80015594(T03315594Command **arg0,s32 *arg1,f32 arg2,s32 arg3,f32 arg4,f32 arg5,f32 arg6) {
 T03315594Command *g=(T03315594Command *)(&D_80068930+D_80044A24*0x640);
 s32 offset,clip,top,i,y,a,b,xx,yy,tex,y1,y2;
 *arg0=g;
 if(arg6<180.0f) offset=(f32)(s32)((f64)arg2/10.0)+arg6*14.0f;
 else offset=(f64)(s32)((f64)arg2/10.0)-(360.0-(f64)arg6)*14.0;
 while(arg5<0.0f) arg5+=360.0f;
 if(arg5>180.0f) arg5-=360.0f;
 if(offset<0) {clip=-offset*2;offset=0;} else clip=offset/2*2-offset;
 CMD(0xED000000,(((s32)((f32)(320<<D_8004AA28)*4.0f)&0xFFF)<<12)|((s32)((f32)(240<<D_8004AA28)*4.0f)&0xFFF));
 CMD(0xED000000,0x5003C0);
 CMD(0xFCFFFFFF,0xFFFE793C);
 CMD(0xFF10013F,D_8004A428[D_80044A24]);
 CMD(0x2F300000,0); CMD(0xF7000000,0);
 top=-arg5*8.0f;
 if(top>0) {CMD(0xF64FC000|((top&0x3FF)*4),0);CMD(0xE7000000,0);}
 CMD(0xFCFFFFFF,0xFFFCF87C);CMD(0x2F002CC0,0);
 CMD(0xF5106400,0x94290);CMD(0xF5106400,0x01094290);CMD(0xF2000000,0x0131C024);
 i=0;y=0;y1=0;y2=36; do {
  CMD(0xFD1000C7,0x803A4208);
  CMD(0xF4000000|((offset&0xFFF)<<12)|(y1&0xFFF),(((offset+0x31C)&0xFFF)<<12)|(y2&0xFFF));
  a=(y+top+20)*4;if(a<0)a=0;
  xx=clip;if(xx<0)xx=0;
  b=(y+top)*4;if(b<0)b=0;
  CMD(0xE4500000|(a&0xFFF),0x01000000|((xx&0xFFF)<<12)|(b&0xFFF));
  tex=(clip<<9)>>7;if(tex>0)tex=0;
  yy=(((y+top)*4)<<9)>>7;if(yy>0)yy=0;
  CMD((tex*-0x10000)|(-yy&0xFFFF),0x02000200);
 i++;y+=20;y1+=40;y2+=40; } while(i<10);
 CMD(0xE7000000,0);CMD(0x2F300000,0);CMD(0xF7000000,0);
 a=y+top-1;if(a<0)a=0;
 if(clip/4>=2) {CMD(0xF6000000|(((clip/4-1)&0x3FF)<<14)|((a&0x3FF)*4),0);}
 CMD(0xF64FC3BC,(a&0x3FF)*4);CMD(0xE9000000,0);
 *arg1=(g-*arg0)*8;
}
#undef CMD
