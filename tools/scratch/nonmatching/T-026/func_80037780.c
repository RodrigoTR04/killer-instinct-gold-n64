/* T-075 DRAFT: 63 relocation-masked words differ in owning TU; 252/244 bytes (was 64, 256/244). SDK _bnkfPatchInst with inlined sound/wave patches. Original has an additional return stub; private fourth-argument table ABI. */
#include "common.h"
typedef struct {u8 *base;s32 len;u8 type,flags;u8 pad[2];void *loop,*book;} Wave;
typedef struct {void *envelope,*keyMap;Wave *wavetable;u8 pan,vol,flags;} Sound;
typedef struct {u8 volume,pan,priority,flags;u8 rest[10];s16 soundCount;Sound *soundArray[1];} Instrument;
void func_80037780(Instrument *inst,s32 offset,s32 unused,s32 table){
 s32 i;
 if(inst->flags)return;
 inst->flags=1;
 for(i=0;i<inst->soundCount;i++){
 Sound *s;
 inst->soundArray[i]=(Sound *)((u8 *)inst->soundArray[i]+offset);
 s=inst->soundArray[i];
 if(!s->flags){
 Wave *w;
 s->flags=1;
 s->envelope=(u8 *)s->envelope+offset;
 s->keyMap=(u8 *)s->keyMap+offset;
 s->wavetable=(Wave *)((u8 *)s->wavetable+offset);
 w=s->wavetable;
 if(!w->flags){
 w->flags=1;
 w->base+=table;
 if(w->type==0){
 w->book=(u8 *)w->book+offset;
 if(w->loop)w->loop=(u8 *)w->loop+offset;
 }else if(w->type==1){
 if(w->loop)w->loop=(u8 *)w->loop+offset;
 }
 }
 }
 }
}
