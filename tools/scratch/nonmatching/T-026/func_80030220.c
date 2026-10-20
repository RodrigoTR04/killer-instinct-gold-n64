/* T-045 DRAFT: 78 standalone relocation-masked positional words; 340 compiled bytes. Was 85 words/340 bytes. Changed separate input/output cursor locals; endpoint expressed from the input and count. Not linked/runtime validated. */
extern s32 guRandom(void);
extern u8 D_80069930;
void func_80030220(s16 *input, s16 *output, s32 count) {
    s16 *vertices; s16 *out;
    s16 z;
    vertices=input;if(count>0){out=output;
        do {
            out[0] = ((guRandom() & 15) + ((vertices[0] / D_80069930) >> 3)) - 8;
            out[1] = ((guRandom() & 15) + ((vertices[1] / D_80069930) >> 4)) - 8;
            z = vertices[2];
            vertices += 24;
            out += 3;
            out[-1] = ((guRandom() & 15) + ((z / D_80069930) >> 3)) - 8;
        } while ((u32)vertices < (u32)input+count*16);
    }
}
