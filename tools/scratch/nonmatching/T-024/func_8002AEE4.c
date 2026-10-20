/* T-052 DRAFT: 48 relocation-masked positional words differ; 336/336 bytes. */
typedef struct { s16 type; s32 samples; } T024AudioMessage;
extern u8 D_80066E18[],D_80066E50[],D_80066E88[];
extern void *D_80066C50[];
extern u32 D_80048150;
extern s32 osRecvMesg(void *,void *,s32),func_8002B034(void *,s32);
extern void func_8002B1EC(s32),alClose(void *);
void func_8002AEE4(s32 unused) { T024AudioMessage *message; u8 client[12]; s32 done=0,samples=0,ready=1; func_80001EF4(client,D_80066E18); while(!done) { osRecvMesg(D_80066E18,&message,1); switch(message->type) { case 4: break; case 1: if(func_8002B034(D_80066C50[D_80048150%3+2],samples)) { ready=0; if(!ready) { osRecvMesg(D_80066E50,&message,1); func_8002B1EC(message->samples); samples=message->samples; } } break; case 10: done=1; break; } } alClose(D_80066E88); }
