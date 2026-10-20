/* T-069 DRAFT: 337 relocation-masked positional words differ in TU context; 1232 bytes. See T-069/REPORT.md. */
typedef struct { u16 *pixels; u8 *alpha; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite257;
extern T032Sprite257 D_8004CED0[];
extern u16 D_80047DA0;
typedef union { u8 width[8]; u32 words[2]; } T069Widths;
extern T069Widths D_80047DA4;
extern u8 D_8004D26C;

extern s32 D_8004EA78;
extern u16 *D_80061488;
extern u8 *D_8006148C;
extern void func_80032360(s32,s32,u16,s32),func_80032504(s32,s32,s32),func_80025D58(s32,u16,s32,s32);
void func_800257FC(s32 unused,u16 health,u8 player,u8 flash) {
    u16 positions = D_80047DA0;
    T069Widths widths;
    u8 *position = (u8 *)&positions;
    s32 y,x,odd;
    u8 left,right,fillStart,fillEnd;
    u16 color;
    T032Sprite257 *sprite;
    widths = D_80047DA4;
    ((u16 *)D_80061490)[player]=health;
    if (!(flash&255)) color=0x7C0;
    else if ((health>>8)>=24) color=0xF800;
    else color=(((D_8004D26C&15)>>1)*0x1E00+0x2600)&0xF100;
    for (y=2;y!=10;y++) {
        odd=y&1;
        if (player==0) {
            left=(position[player]-widths.width[y-2]+120)&255;
            right=(position[player]+120)&255;
            fillStart=(position[player]-(((u16 *)D_80061490)[player]>>8)+120)&255;
            if (position[player]-(((u16 *)D_80061490)[player]>>8)+120<left) fillStart=left;
            fillEnd=right < position[player]+120 ? right : (position[player]+120)&255;
        } else {
            left=position[player]; right=(widths.width[y-2]+position[player])&255;
            fillStart=position[player]<left?left:position[player];
            fillEnd=((((u16 *)D_80061490)[player]>>8)+position[player])&255;
            if (right<(((u16 *)D_80061490)[player]>>8)+position[player]) fillEnd=right;
        }
        if (fillEnd<fillStart) fillEnd=fillStart;
        sprite=&D_8004CED0[D_8004EA78];
        D_80061488=sprite->pixels+sprite->w2*y;
        D_8006148C=sprite->alpha+((sprite->w2+7)&0xFFF8)*y;
        func_80032360(fillStart,fillEnd-fillStart,color,odd);
        if (player==0) {
            func_80032504(left,fillStart-left,odd);
            D_8004CED0[D_8004EA78].pixels[(y*D_8004CED0[D_8004EA78].w2+fillStart)^(odd?2:0)]=0xFFFF;
        } else {
            func_80032504(fillEnd,right-fillEnd,odd);
            if (left==fillEnd) fillEnd=(fillEnd+1)&255;
            D_8004CED0[D_8004EA78].pixels[(y*D_8004CED0[D_8004EA78].w2+fillEnd-1)^(odd?2:0)]=0xFFFF;
        }
    }
    if (player==0) {
        for (x=6;x<126-(((u16 *)D_80061490)[player]>>8) && x<19;x++) func_80025D58(x,0,0,0);
        for (x=126-(((u16 *)D_80061490)[player]>>8);x<19;x++) func_80025D58(x,x==126-(((u16 *)D_80061490)[player]>>8)?0xFFFF:color,192,0);
    } else {
        for (x=123;x>=(((u16 *)D_80061490)[player]>>8)+3 && x>=111;x--) func_80025D58(x,0,0,1);
        for (x=111;x<(((u16 *)D_80061490)[player]>>8)+3;x++) func_80025D58(x,x==(((u16 *)D_80061490)[player]>>8)+2?0xFFFF:color,192,1);
    }
}
