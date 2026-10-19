/* DRAFT. Remaining diff: 392 positional words differ; 1612/1580 bytes */
extern s32 D_8004EA78;
void func_800238C4(u8 *src,u8 *palette) {
    T022Sprite *sprite=&D_8004CED0[D_8004EA78];
    u16 *pixels=(u16 *)sprite->unk0;
    u8 *alpha=(u8 *)sprite->data;
    s16 width,height;
    s32 pitch,row,x,i,pos=8,end,pixelXor,alphaXor,skip,count;
    u8 coverage,*p;
    u16 color;
    sprite->halfWidth=(src[1]<<8)+src[0]; sprite->flags=0;
    sprite->halfHeight=(src[3]<<8)+src[2];
    width=(((src[5]<<8)+src[4])+5)&0xFFFC;
    height=(src[7]<<8)+src[6];
    pitch=(((src[5]<<8)+src[4])+9)&0xFFF8;
    sprite->width=width; sprite->width2=width; sprite->height=height; sprite->height2=height;
    p=src+8;
    for (row=0;row<height;row++) {
        pixelXor=(row&1)?2:0; alphaXor=(row&1)?4:0;
        end=*p+pos; p++; pos++; x=1;
        pixels[(row*width)^pixelXor]=0;
        if (alpha) alpha[(row*pitch)^alphaXor]=0;
        while (pos<end) {
            coverage=p[0]; skip=p[1]; count=p[2]; p+=3; pos+=3;
            for (i=0;i<skip;i++) {
                pixels[(row*width+x+i)^pixelXor]=0;
                if (alpha) alpha[(row*pitch+x+i)^alphaXor]=0;
            }
            x+=skip;
            color=(palette[*p+1]<<8)+palette[*p];
            pixels[(row*width+x-1)^pixelXor]=color;
            if (alpha) alpha[(row*pitch+x-1)^alphaXor]=coverage<<5;
            for (i=0;i<count;i++) {
                color=((palette[*p+1]<<8)+palette[*p])|1;
                p++; pos++;
                pixels[(row*width+x+i)^pixelXor]=color;
                if (alpha) alpha[(row*pitch+x+i)^alphaXor]=255;
            }
            x+=count;
            pixels[(row*width+x)^pixelXor]=color;
            if (alpha) alpha[(row*pitch+x)^alphaXor]=(coverage&0x38)*4;
        }
        for (i=x+1;i<width;i++) {
            pixels[(row*width+i)^pixelXor]=0;
            if (alpha) alpha[(row*pitch+i)^alphaXor]=0;
        }
    }
}
