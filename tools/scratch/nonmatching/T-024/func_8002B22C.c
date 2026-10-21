/* T-102 DRAFT: 85 differing words, 396/380 bytes; list traversal and frame allocation remain. */
typedef struct T024CacheBlock {
    struct T024CacheBlock *next,*prev;
    u32 address,frame;
    u8 *buffer;
}
T024CacheBlock;
typedef struct {
    u8 initialized;
    T024CacheBlock *used,*free;
}
T024Cache;
extern T024Cache D_80068158;
extern u32 D_80048150,D_80048154;
extern u8 D_80068178[][20],D_800683F8[];
extern void alUnlink(void *),alLink(void *,void *);
extern u32 osVirtualToPhysical(void *);
extern s32 osPiStartDma(void *,s32,s32,u32,void *,u32,void *);
u32 func_8002B22C(u32 address,s32 length,s32 unused)
{
    T024CacheBlock *p=D_80068158.used,*previous=0;
    u32 odd;
    u8 *buffer;
    while(p && address>=p->address)
    {
        previous=p;
        if((s32)(p->address+0x800)>=(s32)(address+length))
        {
            p->frame=D_80048150;
            return osVirtualToPhysical(p->buffer+address-p->address);
        }
        p=p->next;
    }
    p=D_80068158.free;
    D_80068158.free=p->next;
    alUnlink(p);
    if(previous) alLink(p,previous);
    else if(D_80068158.used)
    {
        T024CacheBlock *head=D_80068158.used;
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
    odd=address&1;
    buffer=p->buffer;
    p->address=address-odd;
    p->frame=D_80048150;
    osPiStartDma(D_80068178[D_80048154++],0,0,address-odd,buffer,0x800,D_800683F8);
    return osVirtualToPhysical(buffer)+odd;
}
