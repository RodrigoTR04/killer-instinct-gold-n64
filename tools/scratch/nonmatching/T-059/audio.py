from attempts import *
n='2A4F0';s=(ROOT/(n+'-entry_end.c')).read_text()
t=s.replace('size,i,length;','size,length;').replace('for(i=0,entry=','for(entry=').replace('i++,entry++','entry++').replace('D_800669D0[i]','D_800669D0[entry - D_80066C28->entries]')
test(n,'pointer_only',t)
s=(ROOT/(n+'-sequence_cursor.c')).read_text()
test(n,'fixed_do_loop',s.replace('for(i=0,entry=D_80066C28->entries;i<48;i++,entry++) {','i=0; entry=D_80066C28->entries; do {').replace('if(length&1) D_800669D0[i]=length+1; }','if(length&1) D_800669D0[i]=length+1; i++; entry++; } while (i != 48);'))
# Replacing index with explicit byte displacement follows original byte counter.
t=s.replace('i<48','i<384').replace('i++,entry++','i+=8,entry++').replace('D_800669D0[i]','*(u16 *)((u8 *)D_800669D0 + i / 4)')
test(n,'byte_counter',t)
(ROOT/'audio-results.json').write_text(json.dumps(rows,indent=2))
