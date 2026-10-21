/* T-112: structural reconstruction; nonmatching, see REPORT.md. */
void func_8002FDA0(u8 *data,s32 count,RenderVertex *out) {
    RenderVertex initial=D_80048290,*previous=&initial;
    s32 i,j;
    u16 flags;
    i=0;
    if(count>0) do {
        flags=(data[0]<<8)+data[1];
        data+=2;
        for(j=0;
        j<3;
        j++) {
            switch(flags&3) {
                case 0: out->position[j]=previous->position[j];
                break;
                case 1: case 2: out->position[j]=previous->position[j]-(s8)*data++;
                break;
                case 3: out->position[j]=previous->position[j]-((data[0]<<8)+data[1]);
                data+=2;
                break;
            }
            flags>>=2;
        }
        if(flags&1) {
            out->uv[0]=(data[0]<<8)+data[1];
            data+=2;
        }
        else out->uv[0]=previous->uv[0];
        flags>>=1;
        if(flags&1) {
            out->uv[1]=(data[0]<<8)+data[1];
            data+=2;
        }
        else out->uv[1]=previous->uv[1];
        flags>>=1;
        if(flags&1) out->color[0]=*data++;
        else out->color[0]=previous->color[0];
        flags>>=1;
        if(flags&1) out->color[1]=*data++;
        else out->color[1]=previous->color[1];
        flags>>=1;
        if(flags&1) out->color[2]=*data++;
        else out->color[2]=previous->color[2];
        flags>>=1;
        if(flags&1) out->color[3]=*data++;
        else out->color[3]=previous->color[3];
        previous=out;
        out++;
        i++;
    }
    while(i != count);
}
