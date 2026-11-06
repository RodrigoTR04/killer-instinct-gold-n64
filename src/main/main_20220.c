#include "render.h"

void func_8002FB80(u8 *data, s32 count, u32 vertexBase, u32 *textures, u8 *out) {
    s32 i = 0;
    u32 address;
    if (count > 0) {
        do {
            switch (data[0] & 0xC0) {
                case 0x80:
                out[0] = 0xBF;
                out[4] = (data[0] >> 4) & 3;
                out[5] = (data[0] & 15) * 10;
                out[6] = (data[1] >> 4) * 10;
                out[7] = (data[1] & 15) * 10;
                out += 8;
                data += 2;
                break;
                case 0:
                out[0]=data[1];
                out[1]=data[2];
                out[2]=data[3];
                out[3]=data[4];
                out[4]=data[5];
                out[5]=data[6];
                out[6]=data[7];
                out[7]=data[8];
                out += 8;
                data += 9;
                break;
                case 0xC0:
                out[0] = 4;
                address = ((data[0]&63)<<12) + (s32)(data[1]*16 + vertexBase);
                data += 2;
                out[1] = data[0];
                out += 2;
                if (data[0] >= 0xF0) {
                    out[0]=1;
                    out[1]=0;
                    out += 2;
                }
                else {
                    out[0]=0;
                    out[1]=(data[0]+16)&0xF0;
                    out += 2;
                }
                out[0]=address>>24;
                data++;
                out[1]=(address>>16) & 0xFF;
                out[2]=(address>>8) & 0xFF;
                out[3]=address;
                out += 4;
                break;
                case 0x40:
                out[0] = 0xFD;
                address = textures[(u8)(data[0] & 63)];
                out[1] = data[1];
                out[2] = data[2];
                out[3] = data[3];
                out[4] = address >> 24;
                out[5] = (address >> 16) & 255;
                out[6] = (address >> 8) & 255;
                out[7] = address;
                data += 4;
                out += 8;
                break;
            }
            i++;
        }
        while (i != count);
    }
}

void func_8002FDA0(u8 *data,s32 count,RenderVertex *out) {
    u16 flags;
    s32 j;
    RenderVertex initial;
    s32 i;
    RenderVertex *previous;
    RenderVertex *vertex;
    initial = D_80048290;
    previous = &initial;
    vertex = out;
    i=0;
    if(count>0) do {
        flags=(data[0]<<8)+data[1];
        data+=2;
        for(j=0;
        j<3;
        j++) {
            switch(flags&3) {
                case 0: vertex->position[j]=previous->position[j];
                break;
                case 1: case 2: vertex->position[j]=previous->position[j]-(s8)*data++;
                break;
                case 3: vertex->position[j] = previous->position[j] - (s16)((data[0]<<8)+data[1]); data += 2;
                break;
            }
            flags>>=2;
        }
        if(flags&1) {
            vertex->uv[0]=(data[0]<<8)+data[1];
            data+=2;
        }
        else vertex->uv[0]=previous->uv[0];
        flags>>=1;
        if(flags&1) {
            vertex->uv[1]=(data[0]<<8)+data[1];
            data+=2;
        }
        else vertex->uv[1]=previous->uv[1];
        for (j = 0; j < 4; j++) {
            flags >>= 1;
            if (flags & 1) vertex->color[j] = *data++;
            else vertex->color[j] = previous->color[j];
        }
        previous=vertex;
        vertex++;
        i++;
    }
    while(i != count);
}

void func_8002FFDC(u8 *a, s32 b, u8 *c, s32 d, u32 *e, RenderVertex *f, u8 *g) {
    func_8002FB80(a, b, (u32)f, e, g);
    func_8002FDA0(c, d, f);
}


void func_80030020(void **sources, void **targets, u16 *lengths, u16 count) {
    void **src;
    void **dst;
    u16 *len;
    s32 i;
    s32 kind, length;
    void *source, *target;

    i = 0;
    if (count > 0) {
        src = sources;
        dst = targets;
        len = lengths;
        do {
            length = *len;
            source = *src;
            target = *dst;
            kind = length >> 13;
            length &= 0x1FFF;
            switch (kind) {
                case 0: func_800300DC(source, target, length); break;
                case 1: func_8002A40C(source, target, length); break;
            }
            src++;
            dst++;
            len++;
            i++;
        } while (i != count);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_20220/func_800300DC.s")

void func_80030218(void) {
}

extern s32 guRandom(void);
extern u8 D_80069930;
void func_80030220(s16 *input, s16 *output, s32 count)
{
    s32 i;
    for (i = 0; i < count; i += 3) {
        output[i] = ((input[i * 8] / D_80069930) >> 3) + (guRandom() & 15) - 8;
        output[i + 1] = ((input[i * 8 + 1] / D_80069930) >> 4) + (guRandom() & 15) - 8;
        output[i + 2] = ((input[i * 8 + 2] / D_80069930) >> 3) + (guRandom() & 15) - 8;
    }
}

void func_8003037C(s16 *input, s16 *deltas, s32 count) {
    s16 *vertices;
    s16 *delta;
    s16 *end;
    if (count > 0) {
        vertices = input;
        delta = deltas; end = deltas + count;
        do {
            vertices[0] += delta[0];
            vertices[8] += delta[0];
            vertices[16] += delta[0];
            vertices[1] +=
            delta[1];
            vertices[9] += delta[1];
            vertices[17] += delta[1];
            vertices[2] += delta[2];
            vertices[10] += delta[2];
            vertices[18] += delta[2];
            delta += 3;
            vertices += 24;
        }
        while ((u32)delta < (u32)end);
    }
}
