/* T-125: 23 differing words, exact 544 B in full TU. Branch-local cursor updates and signed address intermediate recover structure. */
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
                out[1]=address>>16;
                out[2]=address>>8;
                out[3]=address;
                data++;
                out += 4;
                break;
                case 0x40:
                out[0] = 0xFD;
                address = textures[data[0]&63];
                out[1]=data[1];
                out[2]=data[2];
                out[3]=data[3];
                out[4]=address>>24;
                out[5]=address>>16;
                out[6]=address>>8;
                out[7]=address;
                data += 4;
                out += 8;
                break;
            }
            i++;
        }
        while (i != count);
    }
}
