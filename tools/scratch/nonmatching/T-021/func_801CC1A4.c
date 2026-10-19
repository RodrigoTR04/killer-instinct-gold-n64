/* DRAFT. Remaining diff: Checksum accumulation and saved-register allocation/scheduling differ. */
extern s32 __osContDataCrc();
s32 func_801CC1A4(s32 arg0,s32 arg1) { s32 n,i,j,sum; n=(arg1+127)>>7; for(i=0;i<n-1;i++) { sum=0; for(j=0;j<4;j++) { sum += __osContDataCrc((i<<6)+arg0+(j<<5)); sum &= 255; } *(u8 *)(arg0+arg1-n+i+1)=sum; } return 0; }