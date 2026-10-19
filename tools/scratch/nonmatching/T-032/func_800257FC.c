/* DRAFT. Remaining diff: 343 positional words differ; 1216/1372 bytes */
typedef struct { u16 *pixels; u8 *alpha; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite257;
extern T032Sprite257 D_8004CED0[];
extern u16 D_80047DA0;
extern struct { u8 width[8]; } D_80047DA4;
extern u8 D_8004D26C;
extern s16 D_80061490[2];
extern s32 D_8004EA78;
extern u16 *D_80061488;
extern u8 *D_8006148C;
extern void func_80032360(s32,s32,u16,s32),func_80032504(s32,s32,s32),func_80025D58(s32,u16,s32,s32);
void func_800257FC(s32 unused,s32 health,s32 player,s32 flash) {
    u16 positions = D_80047DA0;
    struct { u8 width[8]; } widths;
    u8 *position = (u8 *)&positions;
    s32 y,left,right,fillStart,fillEnd,x,odd;
    u16 color;
    T032Sprite257 *sprite;
    widths.width[0]=D_80047DA4.width[0]; widths.width[1]=D_80047DA4.width[1];
    widths.width[2]=D_80047DA4.width[2]; widths.width[3]=D_80047DA4.width[3];
    widths.width[4]=D_80047DA4.width[4]; widths.width[5]=D_80047DA4.width[5];
    widths.width[6]=D_80047DA4.width[6]; widths.width[7]=D_80047DA4.width[7];
    player &= 255; health=(s16)health;
    D_80061490[player]=health;
    if (!(flash&255)) color=0x7C0;
    else if ((health>>8)>=24) color=0xF800;
    else color=(((D_8004D26C&15)>>1)*0x1E00+0x2600)&0xF100;
    for (y=2;y!=10;y++) {
        odd=y&1;
        if (player==0) {
            left=(position[player]-widths.width[y-2]+120)&255;
            right=(position[player]+120)&255;
            fillStart=(position[player]-(D_80061490[player]>>8)+120)&255;
            if (position[player]-(D_80061490[player]>>8)+120<left) fillStart=left;
            fillEnd=right < position[player]+120 ? right : (position[player]+120)&255;
        } else {
            left=position[player]; right=(widths.width[y-2]+position[player])&255;
            fillStart=position[player]<left?left:position[player];
            fillEnd=((D_80061490[player]>>8)+position[player])&255;
            if (right<(D_80061490[player]>>8)+position[player]) fillEnd=right;
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
        for (x=6;x<126-(D_80061490[player]>>8) && x<19;x++) func_80025D58(x,0,0,0);
        for (x=126-(D_80061490[player]>>8);x<19;x++) func_80025D58(x,x==126-(D_80061490[player]>>8)?0xFFFF:color,192,0);
    } else {
        for (x=123;x>=(D_80061490[player]>>8)+3 && x>=111;x--) func_80025D58(x,0,0,1);
        for (x=111;x<(D_80061490[player]>>8)+3;x++) func_80025D58(x,x==(D_80061490[player]>>8)+2?0xFFFF:color,192,1);
    }
}
