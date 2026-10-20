import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
fn='func_801B446C';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);n=0
for store,ft,bt,ct,pt,init in itertools.product(['*flagsp = flags | bit;','*flagsp |= bit;','D_802C8CE0 |= bit;','flags |= bit; *flagsp = flags;'],['s32','u32','u8'],['s32','u32'],['s32','u32'],['u8','u32'],range(3)):
 v=s.replace('*flagsp = flags | bit;',store).replace('s32 flags;',ft+' flags;').replace('s32 bit;',bt+' bit;').replace('s32 choice;',ct+' choice;').replace('u8 pos;',pt+' pos;')
 if init==1:v=v.replace('flags = *flagsp;\n    bit = 1 << arg0;','bit = 1 << arg0;\n    flags = *flagsp;')
 if init==2:v=v.replace('flags = *flagsp;\n    bit = 1 << arg0;','bit = 1 << arg0;').replace('if (!(flags & bit))','if (!((flags = *flagsp) & bit))')
 r=probe.probe(fn,pre+v);n+=1
 if r<best:best=r;p.write_text(v);print(n,r,store,ft,bt,ct,pt,init,flush=True)
print('phase1',n,best,flush=True)
s=p.read_text()
# Store the new cursor using a preincrement or an explicitly narrowed local.
for incr,mask,table in itertools.product(['*cursor = pos + 1;\n            pos = *cursor;','pos = ++*cursor;','*cursor = ++pos;','pos++; *cursor = pos;'],['pos & 15','pos % 16','(u8)(pos & 15)'],['s8','u8']):
 v=s.replace('*cursor = pos + 1;\n            pos = *cursor;',incr).replace('pos & 15',mask).replace('extern s8 D_80127CE8','extern '+table+' D_80127CE8').replace('extern s8 D_802C8CF0','extern '+table+' D_802C8CF0')
 r=probe.probe(fn,pre+v);n+=1
 if r<best:best=r;p.write_text(v);print(n,r,incr,mask,table,flush=True)
print('final',n,best)
