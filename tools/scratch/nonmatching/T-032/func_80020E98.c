/* T-081 DRAFT: measured in owning TU; see T-081/REPORT.md. */
#ifndef T032_ROM_ENTRY_DEFINED
#define T032_ROM_ENTRY_DEFINED
typedef struct
{
    u8 *start, *end, *palette;
    u8 *spriteStart, *spriteEnd;
    u8 tail[8];
}
T032RomEntry;
#endif
typedef struct
{
    u8 *first,*second;
}
T032Cache20E;
extern T032RomEntry D_80045E50[];
extern T032Cache20E D_8004D278[][3];
extern u8 D_A94460[],D_A94560[],D_A94D80[],D_119F0[],D_13200[];
extern u8 D_80045D8C[][14],D_80063C60[],D_80064C60[];
extern u16 D_800460D4[];
extern u16 *D_800460E0[],*D_800460E8[],*D_800460F0[],*D_800460F8[];
extern u8 **D_800460D8[];
extern s32 D_8004EA78;
extern void boot_dma_chunked(void *,void *,s32),func_800238C4(u8 *,void *);
#define T032_LE20E(p) ((p)[0]+((p)[1]<<8)+((p)[2]<<16)+((p)[3]<<24))
#define T032_BE20E(p) ((p)[3]+((p)[0]<<24)+((p)[1]<<16)+((p)[2]<<8))
void func_80020E98(u8 player,u8 bank,void *destination)
{
    T032RomEntry *rom;
    T032Cache20E *entry;
    u8 *base,*end,*source,*frame,*previous,*scan,*out;
    u8 *romEnd;
    s32 i,j,count,decoded;
    u16 alternate=0,id;
    u8 *saved;
    if (!destination)
    {
        if (player==0) base=(u8 *)0x8020B480;
        else if (player==1) base=(u8 *)0x802D7A40;
        else base=(u8 *)0x801EE000;
    }
    else base=destination;
    rom=&D_80045E50[bank];
    romEnd=rom->end;
    if (player==2)
    {
        boot_dma_chunked(D_A94460,(void *)0x802D4000,D_A94560-D_A94460);
        boot_dma_chunked(D_A94560,(void *)0x802D4100,D_A94D80-D_A94560);
        D_8004EA78=15;
        source=(u8 *)0x802D4100;
        D_8004CED0[15].unk0=0x80206000;
        D_8004CED0[15].data=0;
        for (i=0;i<2;i++)
        {
            previous=0;
            count=source[2]+(source[3]<<8);
            for (j=0;j<source[2]+(source[3]<<8);j++)
            {
                frame=source+T032_LE20E(source+8+j*4);
                if (frame!=previous && (u32)frame<(u32)(source+T032_LE20E(source+4)))
                {
                    D_800460D8[i][j]=(u8 *)D_8004CED0[D_8004EA78].unk0;
                    func_800238C4(frame,(void *)0x802D4000);
                    previous=frame;
                    D_800460E0[i][j]=D_8004CED0[D_8004EA78].width2;
                    D_800460E8[i][j]=D_8004CED0[D_8004EA78].height;
                    D_800460F0[i][j]=D_8004CED0[D_8004EA78].halfWidth;
                    D_800460F8[i][j]=D_8004CED0[D_8004EA78].halfHeight;
                    D_8004CED0[D_8004EA78].unk0+=D_8004CED0[D_8004EA78].width2*D_8004CED0[D_8004EA78].height*2;
                }
                else if (j<D_800460D4[i])
                {
                    D_800460D8[i][j]=(u8 *)(D_8004CED0[D_8004EA78].unk0-D_8004CED0[D_8004EA78].height*D_8004CED0[D_8004EA78].width2*2);
                    D_800460E0[i][j]=D_8004CED0[D_8004EA78].width2;
                    D_800460E8[i][j]=D_8004CED0[D_8004EA78].height;
                    D_800460F0[i][j]=D_8004CED0[D_8004EA78].halfWidth;
                    D_800460F8[i][j]=D_8004CED0[D_8004EA78].halfHeight;
                }
            }
            source+=T032_LE20E(source+4);
        }
        boot_dma_chunked(rom->start,(void *)0x802D4000,romEnd-rom->start);
        source=(u8 *)0x802D4000;
        out=base;
        romEnd=rom->start;
        for (i=0;i<11;i++)
        {
            decoded=((s32 (*)(void *,void *,void *))boot_inflate)(source+4,out,(void *)0x803A2000);
            romEnd+=decoded;
            out+=decoded;
            source+=T032_BE20E(source);
        }
    }
    else boot_dma_chunked(rom->start,base,romEnd-rom->start);
    saved=bank==12?D_8004D278[199][player].second:0;
    for (i=0;i<256;i++)
    {
        D_8004D278[i][player].second=0;
        D_8004D278[i][player].first=0;
    }
    D_8004D278[199][player].second=saved;
    end=base+(romEnd-rom->start);
    scan=base;
    while ((u32)(scan+15)<(u32)end)
    {
        id=scan[0]+(scan[1]<<8);
        entry=&D_8004D278[id][player];
        if (id==D_80045D8C[bank][alternate])
        {
            alternate++;
            entry->second=scan;
        }
        else if (!entry->first) entry->first=scan;
        else entry->second=scan;
        scan+=T032_LE20E(scan+4);
    }
    if (bank==1)
    {
        out=(u8 *)(((u32)end+15)&~15);
        boot_dma(D_119F0,out,D_13200-D_119F0);
        D_8004D278[176][player].first=0;
        D_8004D278[176][player].second=out;
        D_8004D278[175][player].first=0;
        D_8004D278[175][player].second=out+T032_LE20E(out+4);
    }
    for (i=0;i<256;i++)
    {
        entry=&D_8004D278[i][player];
        if (!entry->first && !entry->second)
        {
            if (!D_80045D8C[bank][0]) entry->second=base;
            else entry->first=base;
        }
    }
    if (player!=2)
    {
        boot_dma(rom->palette,D_80063C60+(player<<11),0x800);
        boot_dma(rom->palette+0x800,D_80064C60+(player<<11),0x800);
    }
}
#undef T032_LE20E
#undef T032_BE20E
