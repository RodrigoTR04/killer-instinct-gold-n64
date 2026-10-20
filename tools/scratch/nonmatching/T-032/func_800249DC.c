/* DRAFT T-051: 10 relocation-masked positional differing words; 304 bytes. Search loop now increments its counter before testing the entry and uses a common found label. Remaining loop setup/register allocation and signed bounds comparison differ; rodata ownership is resolved. */
extern u8 D_8004EA9C[],D_80046010[][14],D_8004EA9A;
extern s32 D_8004EA78;
void func_800249DC(s32 player,s32 id,u8 *kind) {
    u8 *entry,*start;
    s32 i;
    if (id==199) *kind=5;
    else {
        start=D_80046010[D_8004EA9C[player]]; entry=start;
        i=0;
        do {
            i+=2;
            if(id==entry[0]) goto found;
            entry+=2;
        } while(i<14);
        entry=start;
found:
        *kind=entry[1];
        if (id==176 && D_8004EA9C[player]==9) *kind=5;
    }
    switch (*kind) {
        case 0: D_8004EA78=player+2; break;
        case 1: D_8004EA78=player+18; break;
        case 2: D_8004EA78=player+20; break;
        case 3: D_8004EA78=player+22; break;
        case 4: D_8004EA78=player+24; break;
        case 5: D_8004EA78=player+26; break;
        default: D_8004EA78=player+2; break;
    }
    D_8004EA9A=*kind+5;
}
