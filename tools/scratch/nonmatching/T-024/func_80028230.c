/* DRAFT. Remaining diff: 242 differing words; 932/976 bytes */
typedef struct { u32 w0,w1; } T024BackgroundCommand;
extern u8 D_80048020[];
extern s16 D_80061CD8,D_80061CDA;
extern u32 D_801D7490[];
extern u8 D_801D7DF0;
extern u32 osVirtualToPhysical(void *);
void func_80028230(T024BackgroundCommand **list) { T024BackgroundCommand *g; s32 height,aligned,load,i,x,y,right,bottom,s,t; u32 packed; g=(*list)++; g->w0=0x06000000; g->w1=(u32)D_80048020; g=(*list)++; g->w0=0xF5700000; g->w1=0x01080200; aligned=(D_80061CD8+7)&0xFFF8; height=(4096/aligned)&0xFFFE; g=(*list)++; g->w0=((((D_80061CD8+7)>>3)&0x1FF)<<9)|0xF5680000; g->w1=0x03080200; g=(*list)++; g->w0=0xF2000000; g->w1=((((aligned-1)*4)&0xFFF)<<12)|0x03000000|(((D_80061CDA-1)*4)&0xFFF); g=(*list)++; g->w0=0xFD700000; g->w1=osVirtualToPhysical((void *)0x803A5208); g=(*list)++; g->w0=0xF3000000; load=((aligned*height+1)>>1)-1; if(load>2047) load=2047; g->w1=((load&0xFFF)<<12)|0x01000000; g=(*list)++; g->w1=0; g->w0=0xE7000000; g=(*list)++; g->w1=-1; g->w0=0xFA000100; g=(*list)++; g->w0=0xFB000000; g->w1=0x808080FF; for(i=0;i<D_801D7DF0;i++) { packed=D_801D7490[i*12]; x=(((packed>>8)&255)*320)>>8; y=packed>>24; right=(D_80061CD8+x)*4; if(right<0) right=0; bottom=(D_80061CDA+y)*4; if(bottom<0) bottom=0; g=(*list)++; g->w0=(bottom&0xFFF)|0xE4000000|((right&0xFFF)<<12); s=x*4; t=y*4; if(s<0) s=0; if(t<0) t=0; g->w1=(t&0xFFF)|0x03000000|((s&0xFFF)<<12); g=(*list)++; g->w0=0xB3000000; s=(x*4<<10)>>7; t=(y*4<<10)>>7; if(s>0) s=0; if(t>0) t=0; g->w1=(-t&0xFFFF)|(s*-65536); g=(*list)++; g->w1=0x04000400; g->w0=0xB2000000; } }
