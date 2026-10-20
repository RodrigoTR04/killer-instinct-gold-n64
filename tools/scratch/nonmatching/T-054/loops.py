from attempts import *
src=(ROOT/'refine.py').read_text();exec(src[src.index('def stage'):src.index("run('170C4'")])
rows=[]
def test(n,tag,s):
 r=probe(s,'func_800'+n);rows.append({'function':'func_800'+n,'tag':tag,**r});(ROOT/('func_800'+n+'-'+tag+'.c')).write_text(s);print(n,tag,r.get('words',r.get('error','')[:90]),r.get('bytes'),flush=True)
s=(ROOT/'func_800170C4-base.c').read_text();t=vertex(s);a=t.index('        var_a0 = &D_8004AE08;');b=t.index('    }\n    var_v0_2',a)
t=t[:a]+'''        var_a0 = &D_8004AE08;
        var_v0 = &D_80045068;
        do {
            **var_v0++ = *var_a0++;
        } while (var_a0 != &D_8004AEB8);
'''+t[b:]
for ty in ['union','struct']:
 u=t.replace('typedef union { s32 words[4]; u8 bytes[16]; }','typedef '+ty+' { s32 words[4]; }');test('170C4','single_copy_'+ty,u)
for n in ['25D58','30440']:
 s=(ROOT/('func_800'+n+'-base.c')).read_text()
 if n=='25D58':
  for ty in ['s32','u32','u16']:
   t=s.replace('s32 y, end, pixelXor, alphaXor;',ty+' y; s32 end, pixelXor, alphaXor;').replace('y<end','y!=end')
   test(n,'equality_'+ty,t)
 else:
  # Decode one pixel per run count; row cursor and run counter reflect original RLE assembly.
  a=s.index('    for (y = 0;');b=s.index('    for (x = 0; x < stride;',a)
  t=s[:a]+'''    for (y = 0; y < height; y++) {
        s32 swap = (y & 1) ? 4 : 0;
        s32 remaining = 0;
        u8 run;
        for (x = 0; x < width; x++) {
            if (remaining == 0) {
                run = image[source++];
                remaining = (run & 15) + 1;
            }
            out[y*stride + (x^swap)] = run & 0xF0;
            remaining--;
        }
        while (x < stride) { out[y*stride + (x^swap)] = 0; x++; }
    }
'''+s[b:]
  test(n,'pixel_run_counter',t)
  test(n,'pixel_run_counter_short',t.replace('s32 y;','s16 y;').replace('s32 x;','s16 x;'))
# A simple short counter should let IDO select original unroll, not hand-unrolled four samples.
s=(ROOT/'func_8001D47C-base.c').read_text();src=(ROOT/'refine.py').read_text();exec(src[src.index('def gray'):src.index("run('1D47C'")]);t=gray(s)
for ty in ['s16','u16','u32']:
 test('1D47C','palette_'+ty,t.replace('s32 i;',ty+' i;'))
(ROOT/'loops.json').write_text(json.dumps(rows,indent=2)+'\n')
