/* T-045 DRAFT: 47 standalone relocation-masked positional words; 192 compiled bytes. Was 49 words/200 bytes. Changed typed sequence cursor/repeat/count arrays and postincrement reads. Not linked/runtime validated. */
typedef struct {u8 pad[0x18];u8 *cursor[16];u8 *repeat[16];u8 remaining[16];} T045Sequence;
u8 func_80038DE0(T045Sequence *seq,s32 track){
 u8 byte,hi,lo,count;
 if(seq->remaining[track]) {
 byte=*seq->repeat[track]++;
 seq->remaining[track]--;
 }else{
 byte=*seq->cursor[track]++;
 if(byte==0xFE){
 hi=*seq->cursor[track]++;
 if(hi!=0xFE){
 lo=*seq->cursor[track]++;
 count=*seq->cursor[track]++;
 seq->repeat[track]=seq->cursor[track]-((hi<<8)+lo)-4;
 seq->remaining[track]=count;
 byte=*seq->repeat[track]++;
 seq->remaining[track]--;
 }
 }
 }
 return byte;
}
