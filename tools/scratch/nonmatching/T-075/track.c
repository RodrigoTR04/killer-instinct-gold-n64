#include "common.h"
typedef struct {u8 pad[0x18];u8 *curLoc[16];u8 *curBUPtr[16];u8 curBULen[16];} ALCSeq;
u8 func_80038DE0(ALCSeq *seq,u32 track)
{
    u8      theByte;

    
    if(seq->curBULen[track])  
    {
        theByte = *seq->curBUPtr[track];
        seq->curBUPtr[track]++;
        seq->curBULen[track]--;
    }
    else  /* need to handle backup mode */
    {
        theByte = *seq->curLoc[track];
        seq->curLoc[track]++;
        if(theByte == 0xFE)
        {
            u8   loBackUp,hiBackUp,theLen,nextByte;
            u32  backup;
            
            nextByte = *seq->curLoc[track];
            seq->curLoc[track]++;
            if(nextByte != 0xFE)
            {
                /* if here, then got a backup section. get the amount of
                   backup, and the len of the section. Subtract the amount of
                   backup from the curLoc ptr, and subtract four more, since
                   curLoc has been advanced by four while reading the codes. */
                hiBackUp = nextByte;
                loBackUp = *seq->curLoc[track];
                seq->curLoc[track]++;
                theLen = *seq->curLoc[track];
                seq->curLoc[track]++;
                backup = (u32)hiBackUp;
                backup = backup << 8;
                backup += loBackUp;
                seq->curBUPtr[track] = seq->curLoc[track] - (backup + 4);
                seq->curBULen[track] = (u32)theLen;

                /* now get the byte */
                theByte = *seq->curBUPtr[track];
                seq->curBUPtr[track]++;
                seq->curBULen[track]--;
            }
        }
    }

    return theByte;    
}

