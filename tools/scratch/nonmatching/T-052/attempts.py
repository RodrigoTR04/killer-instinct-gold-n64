"""Time-boxed honest-C alternatives, using production IDO flags. Run at repo root."""
from probe import *
import itertools
fix={
'8002F5F0': lambda s:s.replace('T024FreeVoice *voice','void *voice'),
'8001C43C': lambda s:'extern s8 D_8004A738,D_8004A730,D_8004A5E0;\n'+s,
'80023EF0': lambda s:'typedef struct { u8 pad[12]; f32 x,y,z; } T020Position;\n'+s,
'8001CD50': lambda s:'extern u8 D_8004EA9C[];\n'+s,
'800191F0': lambda s:'extern u8 D_8004AA28; extern f32 D_8004A920[];\n'+s,
'8001AA90': lambda s:'extern u8 D_8004AC88;\n'+s,
'8001DE5C': lambda s:'extern u8 D_8004CED0;\n'+s,
}
def variants(a,s):
 v=[('baseline',s)]
 def add(label,x):
  if x!=s and x not in [z[1] for z in v]:v.append((label,x))
 if a=='8002A9DC':
  add('word index with mask',s.replace('u16 index','s32 index').replace('{ if(index','{ index &= 0xFFFF; if(index'))
  add('do wait',s.replace('while(alCSPGetState(D_800669C4)!=0) {}','do {} while(alCSPGetState(D_800669C4)!=0);'))
  add('word index',s.replace('u16 index','s32 index'))
 if a=='8002F5F0':
  add('clear next then prev',s.replace('p->prev=0; p->next=0;','p->next=0; p->prev=0;'))
  add('owner temporary',s.replace('T024ReleasedVoice *p=','T024ReleasedVoice **owner; T024ReleasedVoice *p=').replace('if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; }','owner=p->owner; if(owner) { if(p==*owner) *owner=0; p->owner=0; }'))
  add('early free head',s.replace('if(D_80048270.free) {','p->next=D_80048270.free; p->prev=0; if(D_80048270.free) {').replace('p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p;','D_80048270.free->prev=p;'))
 if a=='8002A900':
  add('u16 index',s.replace('s32 index','u16 index').replace('index &= 0xFFFF;',''))
  add('for wait',s.replace('if(alCSPGetState(D_800669C0)!=0) { do { count++; } while(alCSPGetState(D_800669C0)!=0 && count<0x3D0900); }','for(;alCSPGetState(D_800669C0)!=0 && count<0x3D0900;count++) {}'))
  add('signed count',s.replace('u32 count','s32 count'))
 if a=='8002DF98':
  add('row loop',s[:s.index('void func_')]+'''void func_8002DF98(float m[4][4],float x,float y,float z,float w,float *a,float *b,float *c,float *d) { float v[4]; s32 i; for(i=0;i<4;i++) v[i]=m[3][i]*w+(m[0][i]*x+m[1][i]*y+m[2][i]*z); *a=v[0]; *b=v[1]; *c=v[2]; *d=v[3]; }''')
  add('sum operand order',re.sub(r'm\[3\]\[(\d)\]\*w\+\((.*?)\)',r'(\2)+m[3][\1]*w',s))
  add('float temporaries',s.replace('{ *a=','{ float ax,by,cz,dw; ax=').replace('; *b=','; by=').replace('; *c=','; cz=').replace('; *d=','; dw=').replace('; }','; *a=ax; *b=by; *c=cz; *d=dw; }'))
 if a=='8001C43C':
  add('indexed loops','''extern u8 D_8004A730[],D_8004A738[],D_8004A5E0[][7],D_8004A688[][7];
void func_8001C43C(s32 count,u8 *n,u8 *data,u8 *m,u8 *other) {
 s32 i,j,first=0,second=0;
 for(i=0;i<count;i++) {
  D_8004A730[i]=n[i];
  for(j=0;j<n[i];j++) D_8004A5E0[j][i]=data[first++];
  D_8004A738[i]=m[i];
  for(j=0;j<m[i];j++) D_8004A688[j][i]=other[second++];
 }
}''')
  add('pointer parameters',s.replace('void *arg1, void *arg2, void *arg3, void *arg4','u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4').replace('s8 *var_a1','u8 *var_a1').replace('s8 *var_t1','u8 *var_t1').replace('s8 *var_t3','u8 *var_t3'))
 if a=='8001373C':
  # Existing constants are read-only, values taken from original asm.
  asm=next(Path('asm/nonmatchings/main').glob('*/func_8001373C.s')).read_text()
  consts={name:val for name,val in re.findall(r'dlabel (D_\w+)\s+.*?\.float ([^\n]+)',asm)}
  x=s
  for name,val in consts.items():
   x=re.sub(r'extern f32 '+name+r'[^;]*;', '',x) if False else x
   x=x.replace(name,str(float(val))+'f')
  x=re.sub(r'extern f32 [^;]+;','',x)
  add('literal constants',x)
  add('separate divisions',s.replace('arg0->vx =','dx = (f32)(arg4 * 30000) / distance;\n    arg0->vx =').replace('(s32)((f32)(arg4 * 30000) / distance)','(s32)dx'))
  add('reordered distance locals',s.replace('f32 dy;\n    f32 dz;\n    f32 dx;','f32 dx;\n    f32 dy;\n    f32 dz;'))
 if a=='80015F6C':
  add('chain white stores',s.replace('D_8004ACD0[1] = 255;\n        D_8004ACD0[0] = 255;\n        D_8004ACD0[2] = 255;','D_8004ACD0[0] = D_8004ACD0[1] = D_8004ACD0[2] = 255;'))
  add('reload timer',s.replace('if (timer > 0) {\n        D_8004ACF8 = timer - 1;','if (D_8004ACF8 > 0) {\n        D_8004ACF8--;'))
  add('compound timer decrement',s.replace('D_8004A986--;\n        if (D_8004A986 == 1)','if (--D_8004A986 == 1)'))
 if a=='8002A300':
  add('word run length',s.replace('s8 value=0,delta,runLength','s8 value=0,delta; s32 runLength'))
  add('do run',s.replace('while(runLength-->=0) *out++=value;','do { *out++=value; } while(runLength-->0);'))
  add('indexed run',s.replace('s32 i;','s32 i,j;').replace('while(runLength-->=0) *out++=value;','for(j=0;j<=runLength;j++) *out++=value;'))
 if a=='80029AB0':
  add('indexed effects',s.replace('T024Effect *p=D_80061D60; for(i=0;i<4;i++,p++) {','T024Effect *p; for(i=0;i<4;i++) { p=&D_80061D60[i];'))
  add('single element loop',re.sub(r'for\(j=0;j<12;j\+=2\)', 'for(j=0;j<12;j++)',s).replace(' if(p->age[j+1]<p->duration[j+1]) p->age[j+1]++; p->position[j+1]+=p->velocity[j+1]-(p->velocity[j+1]/3.0f*(float)p->age[j+1])/(float)p->duration[j+1];',''))
  add('postincrement age',s.replace('p->age[j]++','++p->age[j]').replace('p->age[j+1]++','++p->age[j+1]'))
 if a=='80023EF0':
  add('word player index',s.replace('u8 player, *count, old;','s32 player; u8 *count, old;'))
  add('direct count access',s.replace('count = &D_8004F390[player];','count = &D_8004F390[actor->player];').replace('old = (*count)++;','old = D_8004F390[player]++;'))
  add('boolean facing',s.replace('facing = 0;\n            if (actor->facing >= 128) facing = 1;','facing = actor->facing >= 128;'))
 if a=='80012950':
  add('chain floats',s.replace('D_8004AD0C = 0.0f;\n    D_8004AD10 = 0.0f;\n    D_8004AC80 = 0.0f;','D_8004AD0C = D_8004AD10 = D_8004AC80 = 0.0f;'))
  add('forward clears',s.replace('D_8004AC92[2] = 0;\n    D_8004AC92[1] = 0;\n    D_8004AC92[0] = 0;','D_8004AC92[0] = 0;\n    D_8004AC92[1] = 0;\n    D_8004AC92[2] = 0;').replace('D_8004AC8E[2] = 0;\n    D_8004AC8E[1] = 0;\n    D_8004AC8E[0] = 0;','D_8004AC8E[0] = 0;\n    D_8004AC8E[1] = 0;\n    D_8004AC8E[2] = 0;'))
  add('word argument',s.replace('u8 arg0','s32 arg0'))
 if a=='8001BDE0':
  add('structured forward loop',s.replace('loop_2:\n','').replace('goto loop_2;','continue;').replace('        temp_f0 =','        do { temp_f0 =',1).replace('        var_s1 = &D_801D8550;','        } while (var_s0 < 0x28 && temp_f0 <= arg2);\n        var_s1 = &D_801D8550;'))
  add('load factors reverse',s.replace('temp_f24 = D_800489F0;\n        temp_f22 = D_800489F4;','temp_f22 = D_800489F4;\n        temp_f24 = D_800489F0;'))
  add('inline factor loads',s.replace('temp_f24 = D_800489F0;','').replace('temp_f22 = D_800489F4;','').replace('* temp_f22','* D_800489F4').replace('- temp_f24','- D_800489F0'))
 if a=='8002AEE4':
  add('while message loop',s.replace('do { osRecvMesg','while(!done) { osRecvMesg').replace('} while(!done);','}'))
  add('signed frame modulo',s.replace('extern u32 D_80048150','extern s32 D_80048150'))
  add('word message type',s.replace('s16 type;','s32 type;'))
 if a=='800245B4':
  add('indexed rows',s.replace('T032Cache245 (*row)[6] = D_8004D290;','s32 i;').replace('do {\n        p = entry[0].data; row++;','for(i=0;i<((u32)D_8004EA60-(u32)D_8004D290)/sizeof(D_8004D290[0]);i++) {\n        p = entry[0].data;').replace('} while (row != D_8004EA60);','}'))
  add('field copies',s.replace('entry[0] = *bank','{ entry[0].data=bank->data; entry[0].offset=bank->offset; }').replace('entry[3] = *bank','{ entry[3].data=bank->data; entry[3].offset=bank->offset; }'))
 if a=='8001256C':
  add('unsigned color',s.replace('s32 color','u32 color'))
  add('store command first',re.sub(r'g->value = ([^;]+);\s*g->command = ([^;]+);',r'g->command = \2; g->value = \1;',s))
  add('cursor indexed commands',s.replace('s32 color;','s32 color; T033Gfx *cursor=*arg0;').replace('T033Gfx *g = (*arg0)++;','T033Gfx *g = cursor++; *arg0=cursor;'))
 if a=='8002B57C':
  add('typed controller loop','''typedef struct { u16 type; u8 status,error; } T052ContStatus;
extern T052ContStatus D_800684A8[4]; extern u8 D_80068518,D_80068520,D_800684E0[]; extern s32 D_800684A0;
extern s32 osContInit(void *,u8 *,void *);
void func_8002B57C(void) { s32 i; while(osContInit(D_800684E0,&D_80068518,D_800684A8)) {} D_800684A0=0; for(i=0;i<4;i++) if((D_80068518&(1<<i)) && !(D_800684A8[i].error&8)) { D_80068520|=1<<i; D_800684A0++; } }''')
  add('do initialization wait',s.replace('while(osContInit(D_800684E0,&D_80068518,D_800684A8)!=0) {}','do {} while(osContInit(D_800684E0,&D_80068518,D_800684A8)!=0);'))
 if a=='8002B22C':
  add('for cache traversal',s.replace('while(p && address>=p->address) {','for(;p && address>=p->address;p=p->next) {').replace(' p=p->next; }',' }'))
  add('unsigned length',s.replace('s32 length','u32 length'))
  add('mask aligned address',s.replace('address-odd','address&~1U'))
 if a=='80026738':
  add('word scale',s.replace('u16 scale,width','s32 scale; u16 width'))
  add('late advance effect',s.replace('y=(effect->y>>8)+4; effect++;','y=(effect->y>>8)+4;').replace('} while (effect->id != 0);','effect++; } while (effect->id != 0);'))
  add('unsigned kind',s.replace('u8 kind','u32 kind'))
 if a=='8002F45C':
  add('key after interrupt',s.replace('T024KeyMap *key=sound->key','T024KeyMap *key').replace('voice->flags=key->flags','key=sound->key; voice->flags=key->flags'))
  add('word pan',s.replace('s8 pan','s32 pan'))
  add('clear next first',s.replace('voice->prev=0; voice->next=0;','voice->next=0; voice->prev=0;'))
 if a=='8002B034':
  add('unsigned sample compare',s.replace('(u32)task->samples<D_80068164','(u16)task->samples<D_80068164'))
  add('command byte mask',s.replace('((end-D_80066C50[D_80048158])>>3)*8','(end-D_80066C50[D_80048158])&~7'))
  add('direct command subtraction',s.replace('((end-D_80066C50[D_80048158])>>3)*8','((u32)end-(u32)D_80066C50[D_80048158])&~7'))
 if a=='8002DDD4':
  add('float depth test',s.replace('(double)depth<0.5','depth<0.5f'))
  add('reorder screen locals',s.replace('float sx,sy,savedY','float sy,sx,savedY'))
  add('explicit screen conversions',s.replace('*screenX=sx*65536.0f','*screenX=(s32)(sx*65536.0f)').replace('*screenY=sy*65536.0f','*screenY=(s32)(sy*65536.0f)'))
 if a=='8001CD50':
  add('share zero local',s.replace('void func_8001CD50(void) {','void func_8001CD50(void) { s32 zero=0;').replace(' = 0;', ' = zero;').replace('s32 zero=0','s32 zero=0'))
  add('chain paired clears',s.replace('D_8004EA78 = 0;\n    D_8004EA90 = 0;','D_8004EA78 = D_8004EA90 = 0;').replace('D_8004EA88 = 1;\n    D_800614C0 = 1;','D_8004EA88 = D_800614C0 = 1;'))
 if a=='80012390':
  add('simple byte sentinel',s.replace('*cursor * 0x01010101 == 0','*cursor == 0'))
  add('indexed pixel copy',s.replace('i++;\n                    dst++;\n                    dst[-1] = src[8];\n                    src++;','dst[i] = src[i+8];\n                    i++;'))
  add('copy then advance',s.replace('i++;\n                    dst++;\n                    dst[-1] = src[8];\n                    src++;','*dst++ = src[8]; src++; i++;'))
 if a=='80016078':
  add('unsigned color',s.replace('s32 color','u32 color'))
  add('postincrement command pointers',s.replace('g->command = 0xE7000000;\n    g->value = 0;\n    g++;','{ T033DisplayCommand *p=g++; p->command=0xE7000000; p->value=0; }'))
  add('integer dimensions',s.replace('(s32)((f32)(320 << D_8004AA28) * 4.0f)','((320 << D_8004AA28) * 4)').replace('(s32)((f32)(240 << D_8004AA28) * 4.0f)','((240 << D_8004AA28) * 4)'))
 if a=='8002E4A0':
  add('signed loops',s.replace('u32 i','s32 i'))
  add('pointer voice linking',s.replace('u32 i;','u32 i; u8 *voice;').replace('for(i=1;i<config->voices;i++) alLink((u8 *)p->voices+(i<<6),(u8 *)p->voices+((i-1)<<6));','for(i=1,voice=(u8 *)p->voices+64;i<config->voices;i++,voice+=64) alLink(voice,voice-64);'))
  add('clear current late',s.replace('p->current=0;','').replace('p->next=0;','p->current=0; p->next=0;'))
 if a=='800191F0':
  add('typed indexed actor loop','''typedef struct { u8 kind,pad[0x53]; s16 velocity; u8 tail[0xAA]; } T052Actor;
extern T052Actor D_801D3430[],D_801D5C30[]; extern f32 D_8004A920[]; extern u8 D_8004AA28;
void func_800191F0(void) { T052Actor *p; if(D_8004AA28==0) for(p=D_801D3430;p!=D_801D5C30;p++) if(p->kind==60) { *D_8004A920-=(f32)p->velocity/256.0f; p->velocity=(s32)((f32)p->velocity+*D_8004A920*256.0f/200.0f); } }''')
  add('remove redundant stores',re.sub(r'\s*\(\*\(s16 \*\)\(\(u8 \*\)\((\w+)\) \+ 0x54\)\) = \(s16\) \(\*\(s16 \*\)\(\(u8 \*\)\(\1\) \+ 0x54\)\);','',s))
 if a=='8001AA90':
  add('simple increment',s.replace('temp_t8 = D_8004AD09 + 1;\n    D_8004AD09 = temp_t8;','temp_t8 = ++D_8004AD09;'))
  add('while wrapping',re.sub(r'if \((D_8004AD(?:0C|10) [<>] [^\n]+)\) \{\n        do \{\n            ([^\n]+)\n        \} while \(\1\);\n    \}',r'while (\1) { \2 }',s))
  add('reuse sine local',s.replace('var_f2 = sp24;','').replace('var_f2 *=','sp24 *=').replace('D_8004AD0C += var_f2','D_8004AD0C += sp24'))
 if a=='8002F6F4':
  add('clear bit complement',s.replace('voice->flags&=0xFFEF','voice->flags&=~0x10'))
  add('signed word repeat',s.replace('s16 repeat=0','s32 repeat=0'))
  add('event local order',s.replace('T024ChainEvent start,event','T024ChainEvent event,start'))
 if a=='8002D9C4':
  fields=['x','y','z','pitch','yaw']
  add('explicit pose copies',s.replace('to=*pose;',''.join('to.'+f+'=pose->'+f+';' for f in fields)).replace('from=*pose;',''.join('from.'+f+'=pose->'+f+';' for f in fields)))
  add('separate frame conversion',s.replace('float t=frame,total=duration','float total=duration,t=frame'))
  add('reverse pose local order',s.replace('T024CameraPose to,from','T024CameraPose from,to'))
 if a=='8001272C':
  add('for objects',s.replace('obj = D_801D3430;\n    do {','for(obj=D_801D3430;obj!=D_801D5C30;obj++) {').replace('        obj++;\n    } while (obj != D_801D5C30);','    }'))
  add('word fade',s.replace('u8 fade','s32 fade'))
  add('local fade compare',s.replace('if (D_801D87AC >= 12)','if (fade >= 12)'))
 if a=='8002FB80':
  add('unsigned loop',s.replace('s32 i;','u32 i;').replace('s32 count','u32 count'))
  add('pointer end loop',s.replace('s32 i; u32 address; for(i=0;i<count;i++)','u8 *end=out+count*8; u32 address; for(;out<end;)'))
  add('signed byte input',s.replace('u8 *data','s8 *data'))
 if a=='800287D4':
  add('advance particle cursor',s.replace('for(j=0;j<D_80061520[i];j++)','for(j=0,p=D_80061538[i];j<D_80061520[i];j++,p++)').replace('p=&D_80061538[i][j];',''))
  add('reverse random comparison',s.replace('func_800326F0()>=0x7FFF0001U','func_800326F0()>0x7FFF0000U'))
  add('xyz store order',s.replace('p->y+=D_80061CC8[1]; p->x+=D_80061CC8[0];','p->x+=D_80061CC8[0]; p->y+=D_80061CC8[1];'))
 if a=='8002FDA0':
  add('word flags',s.replace('u16 flags','u32 flags'))
  add('explicit initial vertex',s.replace('T024PackedVertex initial=D_80048290,*previous=&initial;','T024PackedVertex initial,*previous=&initial;').replace('s16 value;','s16 value; initial=D_80048290;'))
  add('unsigned decoded value',s.replace('s16 value','u16 value'))
 if a=='8001DE5C':
  add('literal sign extension',s.replace('(s32) (var_v0 + &D_FFFEFFFF)','var_v0 - 0x10001').replace('(s32) (var_t0 + &D_FFFEFFFF)','var_t0 - 0x10001').replace('(s32) (var_a1 + &D_FFFEFFFF)','var_a1 - 0x10001'))
  add('word flag argument',s.replace('u8 arg2','s32 arg2'))
  add('signed aligned width',s.replace('s16 temp_t6_2','s32 temp_t6_2'))
 return v
if __name__=='__main__':
 summary={}
 for line in ROOT.joinpath('functions.txt').read_text().splitlines():
  a,size,task=line.split();fn='func_'+a
  if a in ['8002B1EC','8002B91C','8002AA98','8002AAEC','8002B95C','800281C4','8002A1E0','8002B7E0','8002DCC8']:continue
  if not Path('tools/scratch/nonmatching',task,fn+'.c').exists():
   print(fn, 'already promoted; see REPORT.md', flush=True); continue
  s=draft(fn);s=fix.get(a,lambda s:s)(s);v=variants(a,s)
  rows=run(fn,v);best=min(range(len(rows)),key=lambda i:rows[i].get('words',9999)+abs(rows[i].get('bytes',int(size))-int(size))//4)
  ROOT.joinpath(fn+'.best.c').write_text(v[best][1]);summary[fn]={'baseline':rows[0],'best':rows[best],'variants':len(rows)}
 ROOT.joinpath('summary.json').write_text(json.dumps(summary,indent=2)+'\n')
