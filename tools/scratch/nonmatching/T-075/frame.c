#include "common.h"
typedef struct ALPlayer {struct ALPlayer *next; void *clientData; s32 (*handler)(void *); s32 pad; s32 samplesLeft;} ALPlayer;
typedef struct Acmd {u32 w0,w1;} Acmd;
typedef struct ALFilter {s32 type; Acmd *(*handler)(void *,s16 *,s32,s32,Acmd *); void (*setParam)(void *,s32,void *);} ALFilter;
typedef struct {ALPlayer *head; u8 pad[0x18];s32 paramSamples,curSamples;u8 pad2[0x14];ALFilter *outputFilter;u8 pad3[8];s32 outputRate,maxOutSamples;} ALSynth;
extern ALSynth *D_80048440;
extern f64 D_80049348;
extern void _collectPVoices(void *);
Acmd *func_80039C08(Acmd *cmdList,s32 *cmdLen,s16 *outBuf,s32 outLen){
 ALPlayer *client;
 ALFilter *output;
 ALSynth *drvr=D_80048440;
 s16 tmp=0;
 Acmd *cmdlEnd=cmdList;
 Acmd *cmdPtr;
 s32 nOut;
 s16 *lOutBuf=outBuf;
 if(drvr->head==0){*cmdLen=0;return cmdList;}
client=0;
 {s32 delta=0x7fffffff; ALPlayer *cl;
 for(cl=drvr->head;cl!=0;cl=cl->next) {
 if(cl->samplesLeft-drvr->curSamples<delta){client=cl;delta=cl->samplesLeft-drvr->curSamples;}
 }
 }
 drvr->paramSamples=client->samplesLeft;
 while(drvr->paramSamples-drvr->curSamples<outLen){
 drvr->paramSamples&=~0xf;
 {f32 tmp=((f32)(*client->handler)(client))*drvr->outputRate/D_80049348+0.5;
 client->samplesLeft+=(s32)tmp;}
client=0;
 {s32 delta=0x7fffffff; ALPlayer *cl;
 for(cl=drvr->head;cl!=0;cl=cl->next) {
 if(cl->samplesLeft-drvr->curSamples<delta){client=cl;delta=cl->samplesLeft-drvr->curSamples;}
 }
 }
 drvr->paramSamples=client->samplesLeft;
 }
 while(outLen>0){
 nOut=drvr->maxOutSamples<outLen?drvr->maxOutSamples:outLen;
 cmdPtr=cmdlEnd;
 cmdPtr->w0=0x07000000;cmdPtr->w1=0;cmdPtr++;
 output=drvr->outputFilter;
 (*output->setParam)(output,6,lOutBuf);
 cmdlEnd=(*output->handler)(output,&tmp,nOut,drvr->curSamples,cmdPtr);
 outLen-=nOut;
 lOutBuf+=nOut<<1;
 drvr->curSamples+=nOut;
 }
 *cmdLen=(s32)(cmdlEnd-cmdList);
 _collectPVoices(drvr);
 return cmdlEnd;
}
