/* T-137 DRAFT: 66 differing words, 380/380 B. Pass the buffer field directly to DMA. Not matching. */
/* T-108 draft: shared audio types; see T-108/REPORT.md. */
#include "audio_game.h"
extern s32 osSetIntMask(s32);
extern u32 osVirtualToPhysical(void *);
extern s32 osPiStartDma(void *,s32,s32,u32,void *,u32,void *);

s32 func_8002B22C(s32 address,s32 length,void *unused)
{
    AudioDmaBuffer *p=D_80068158.used,*previous=0;
    u8 odd;
    u8 *buffer;
    while(p)
    {
        s32 end=p->address+0x800;
        if ((u32)address < p->address) break;
        previous=p;
        if(end>=(s32)(address+length))
        {
            p->frame=D_80048150;
            return osVirtualToPhysical(p->buffer+address-p->address);
        }
        p=p->next;
    }
    odd=address&1;
    p=D_80068158.free;
    D_80068158.free=p->next;
    alUnlink((ALLink *)p);
    if(previous) alLink((ALLink *)p,(ALLink *)previous);
    else if(D_80068158.used)
    {
        AudioDmaBuffer *head=D_80068158.used;
        D_80068158.used=p;
        p->next=head;
        p->prev=0;
        head->prev=p;
    }
    else
    {
        D_80068158.used=p;
        p->next=0;
        p->prev=0;
    }
    buffer=p->buffer;
    p->address=address-odd;
    p->frame=D_80048150;
    osPiStartDma(&D_80068178[D_80048154++],0,0,address-odd,p->buffer,0x800,&D_800683F8);
    return osVirtualToPhysical(buffer)+odd;
}
