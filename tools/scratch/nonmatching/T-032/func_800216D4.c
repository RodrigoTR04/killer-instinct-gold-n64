/* DRAFT. Remaining diff: 230 positional words differ; 1040/1032 bytes */
#ifndef T032_ROM_ENTRY_DEFINED
#define T032_ROM_ENTRY_DEFINED
typedef struct {
    u8 *start, *end, *palette;
    u32 flags;
    u8 *spriteStart, *spriteEnd;
    u8 tail[8];
} T032RomEntry;
#endif
typedef struct { u8 *first,*second; } T032Cache216;
extern T032RomEntry D_80045E50[];
extern T032Cache216 D_8004D278[][3];
extern u8 D_49FD0[],D_566D0[],D_1EB6D0[],D_1F3200[],D_469660[],D_470390[];
extern u8 D_8004F396[],D_80045D8C[][14],D_80063C60[],D_80064C60[];
extern void *memcpy(void *,void *,s32);
#define T032_LE216(p) ((p)[0]+((p)[1]<<8)+((p)[2]<<16)+((p)[3]<<24))
s32 func_800216D4(u8 player,s8 kind,u8 *destination,s32 wanted) {
    u8 *start,*end,*scan,*header,*p;
    T032RomEntry *rom;
    T032Cache216 *entry;
    s32 offset,size,loaded=0;
    u16 id,i,alternate=0;
    u8 bank=kind;
    wanted&=65535;
    if (bank>=128) { start=D_49FD0; end=D_566D0; bank-=128; }
    else if (bank==1 && wanted==132) { start=D_1EB6D0; end=D_1F3200; D_8004F396[player]=1; }
    else if (bank==4 && wanted==133) { start=D_469660; end=D_470390; D_8004F396[player]=1; }
    else { start=D_80045E50[bank].start; end=D_80045E50[bank].end; }
    if (player==2) return 0;
    rom=&D_80045E50[bank]; scan=start;
    do {
        offset=(u32)scan&7; start=scan-offset;
        boot_dma(start,destination,16);
        header=destination+offset;
        id=header[0]+(header[1]<<8); size=T032_LE216(header+4);
        if (wanted==id) {
            loaded=size+offset; loaded+=loaded&7;
            boot_dma(start,destination,loaded);
            if (offset) memcpy(destination,header,loaded-offset);
        }
        scan+=size;
    } while (wanted!=id && (u32)scan<(u32)end);
    for (i=0;i<256;i++) { D_8004D278[i][player].second=0; D_8004D278[i][player].first=0; }
    p=destination;
    while ((u32)(p+15)<(u32)(destination+size)) {
        id=p[0]+(p[1]<<8); entry=&D_8004D278[id][player];
        if (id==D_80045D8C[bank][alternate]) { alternate++; entry->second=p; }
        else if (!entry->first) entry->first=p;
        else entry->second=p;
        p+=T032_LE216(p+4);
    }
    for (i=0;i<256;i++) {
        entry=&D_8004D278[i][player];
        if (!entry->first && !entry->second) {
            if (D_80045D8C[bank][0]==0) entry->second=destination;
            else entry->first=destination;
        }
    }
    boot_dma(rom->palette,D_80063C60+(player<<11),0x800);
    boot_dma(rom->palette+0x800,D_80064C60+(player<<11),0x800);
    return loaded-offset;
}
#undef T032_LE216
