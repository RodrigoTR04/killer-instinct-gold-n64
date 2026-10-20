from attempts import *
s=(ROOT/'func_800170C4-single_copy_struct.c').read_text();rows=[]
for tag,t in [('eight_copies',s.replace('var_a0 != &D_8004AEB8','var_a0 != &D_8004AE08 + 8')),('eight_indexed',s.replace('    s32 temp_t4;','    s32 temp_t4; s32 i;').replace('''        do {
            **var_v0++ = *var_a0++;
        } while (var_a0 != &D_8004AEB8);''','''        for (i = 0; i < 8; i++) *var_v0[i] = var_a0[i];''')),('eight_pointer_bound',s.replace('var_a0 != &D_8004AEB8','var_v0 != &D_80045068 + 8'))]:
 r=probe(t,'func_800170C4');rows.append({'tag':tag,**r});(ROOT/('func_800170C4-'+tag+'.c')).write_text(t);print(tag,r)
(ROOT/'vertex.json').write_text(json.dumps(rows,indent=2)+'\n')
