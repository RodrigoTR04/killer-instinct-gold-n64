/* T-149 DRAFT: 319 differing words in full TU; 1388/1372 bytes. */
extern u16 D_80047DA0;
typedef struct { u8 width[8]; } T069Widths;
extern T069Widths D_80047DA4;
extern u8 D_8004D26C;

extern s32 D_8004EA78;
extern u16 *D_80061488;
extern u8 *D_8006148C;
extern void func_80032360(s32,s32,u16,s32),func_80032504(s32,s32,s32),func_80025D58(s32,s32,s32,s32);
void func_800257FC(u8 unused,u16 health,u8 player,u8 flash) {
    u16 positions = D_80047DA0;
    T069Widths widths;
    u8 *position;
    u16 *healthPtr;
    s32 y,x,odd,pixelXor;
    u8 left,right,fillStart,fillEnd;
    u16 color;
    T032Sprite25D *sprite;
    widths = D_80047DA4;
    healthPtr = &D_80061490[player];
    *healthPtr=health;
    if (flash == 0) color=0x7C0;
    else if ((health>>8)>=24) color=0xF800;
    else color=(((D_8004D26C&15)>>1)*0x1E00+0x2600)&0xF100;
    position = &((u8 *)&positions)[player];
    for (y=2;y!=10;y++) {
        odd=y&1;
        pixelXor = odd ? 2 : 0;
        if (player==0) {
            left=(*position-widths.width[y-2]+120)&255;
            right=(*position+120)&255;
        } else {
            left=*position;
            right=(widths.width[y-2]+*position)&255;
        }
        if (player==0) {
            fillStart=(*position-(*healthPtr>>8)+120)&255;
            if (*position-(*healthPtr>>8)+120<left) fillStart=left;
            fillEnd=right < *position+120 ? right : (*position+120)&255;
        } else {
            fillStart=*position<left?left:*position;
            fillEnd=((*healthPtr>>8)+*position)&255;
            if (right<(*healthPtr>>8)+*position) fillEnd=right;
        }
        if (fillEnd<fillStart) fillEnd=fillStart;
        sprite=&D_8004CED0[D_8004EA78];
        D_80061488=sprite->pixels+sprite->w2*y;
        D_8006148C=sprite->alpha+((sprite->w2+7)&0xFFF8)*y;
        func_80032360(fillStart,fillEnd-fillStart,color,odd);
        if (player==0) {
            func_80032504(left,fillStart-left,odd);
            D_8004CED0[D_8004EA78].pixels[(y*D_8004CED0[D_8004EA78].w2+fillStart)^pixelXor]=0xFFFF;
        } else {
            func_80032504(fillEnd,right-fillEnd,odd);
            if (left==fillEnd) fillEnd=(fillEnd+1)&255;
            D_8004CED0[D_8004EA78].pixels[(y*D_8004CED0[D_8004EA78].w2+fillEnd-1)^pixelXor]=0xFFFF;
        }
    }
    if (player==0) {
        for (x=6;x<126-(*healthPtr>>8);x++) {
            if (x >= 19) break;
            func_80025D58(x,0,0,0);
        }
        for (x=126-(*healthPtr>>8);x<19;x++) {
            if (x == 126 - (*healthPtr >> 8)) func_80025D58(x, 0xFFFF, 192, 0);
            else func_80025D58(x, color, 192, 0);
        }
    } else {
        for (x=123;x>=(*healthPtr>>8)+3 && x>=111;x--) func_80025D58(x,0,0,1);
        for (x=111;x<(*healthPtr>>8)+3;x++) {
            if (x == (*healthPtr >> 8) + 2) func_80025D58(x, 0xFFFF, 192, 1);
            else func_80025D58(x, color, 192, 1);
        }
    }
}
