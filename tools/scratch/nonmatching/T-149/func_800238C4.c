/* T-149 DRAFT: 336 differing words, 1580/1580 bytes in the full TU. */
extern s32 D_8004EA78;
void func_800238C4(u8 *src,u8 *palette) {
    T022Sprite *sprite;
    u16 *pixels;
    u8 *alpha;
    s32 width,height;
    s32 pitch;
    s32 row;
    s32 rowBase;
    s32 x;
    s32 i;
    s32 pos;
    s32 end;
    s32 pixelXor;
    s32 alphaXor;
    u8 skip;
    s32 count;
    u8 coverage,*p;
    u32 color;
    u8 *entry;
    sprite=&D_8004CED0[D_8004EA78];
    rowBase=0;
    pos=8;
    sprite->halfWidth=(src[1]<<8)+src[0]; sprite->flags=0;
    sprite->halfHeight=(src[3]<<8)+src[2];
    width=(((src[5]<<8)+src[4])+5)&0xFFFC;
    alpha=(u8 *)sprite->data;
    height=(src[7]<<8)+src[6];
    pitch=(((src[5]<<8)+src[4])+9)&0xFFF8;
    pixels=(u16 *)sprite->unk0;
    sprite->width=width; sprite->width2=width; sprite->height=height; sprite->height2=height;
    p=src+8;
    for (row=0;row<height;row++,rowBase+=width) {
        alphaXor=(row&1)?4:0; pixelXor=(row&1)?2:0;
        end=*p+pos; p++; pos++; x=1;
        pixels[(rowBase)^pixelXor]=0;
        if (alpha) alpha[(row*pitch)^alphaXor]=0;
        while (pos<end) {
            coverage=p[0]; skip=p[1]; count=p[2]; p+=3; pos+=3;
            for (i=0;i<skip;i++) {
                pixels[(rowBase+x+i)^pixelXor]=0;
                if (alpha) alpha[(row*pitch+x+i)^alphaXor]=0;
            }
            x+=skip;
            entry = &palette[*p];
            color=(entry[1]<<8)+entry[0];
            pixels[(rowBase+x-1)^pixelXor]=color;
            if (alpha) alpha[(row*pitch+x-1)^alphaXor]=coverage<<5;
            for (i=0;i<count;i++) {
                entry = &palette[*p];
                color=((entry[1]<<8)+entry[0])|1;
                p++; pos++;
                pixels[(rowBase+x+i)^pixelXor]=color;
                if (alpha) alpha[(row*pitch+x+i)^alphaXor]=255;
            }
            x+=i;
            pixels[(rowBase+x)^pixelXor]=color;
            if (alpha) alpha[(row*pitch+x)^alphaXor]=(coverage&0x38)*4;
        }
        for (i=x+1;i<width;i++) {
            pixels[(rowBase+i)^pixelXor]=0;
            if (alpha) alpha[(row*pitch+i)^alphaXor]=0;
        }
    }
}
