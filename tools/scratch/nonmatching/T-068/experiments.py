import sys,itertools,json
from pathlib import Path
sys.path.insert(0,str(Path(__file__).parent))
import probe,tu
results={}
def test(fn,variants):
 p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s)
 for label,v in variants(s):
  r=probe.probe(fn,pre+v)
  if r<best:
   print(fn,label,r,flush=True);best=r;Path('/tmp/'+fn+'-best.c').write_text(v)
 results[fn]=best
# unsigned intermediate and switch constant widths
fn='func_801C7998'
test(fn,lambda s: ((str((expr,typ)),s.replace('(u64)(buttons & 0xFFFF)',expr).replace('case 0x8000:', 'case '+typ+':')) for expr,typ in itertools.product(['(u64)(u32)(buttons & 0xFFFF)','(u64)(buttons & 0xFFFFU)','(u64)(u32)buttons','(u64)buttons','(u64)(buttons & 0xFFFFUL)'],['0x8000','0x8000U','0x8000ULL'])))
# float zero initialized before depth
fn='func_801C5064'
def variants(s):
 for typ in ['f32','f64']:
  for placement in ['depth = D_80294890;', 'do {']:
   v=s.replace('f32 depth;', 'f32 depth; '+typ+' zero;').replace(placement,'zero = 0.0f;\n        '+placement).replace(', 0.0f,', ', zero,')
   yield str((typ,placement)),v
 for expr in ['(f32)0','0','0.0','scale-scale','origin * 0.0f']:
  yield expr,s.replace(', 0.0f,', ', '+expr+',')
test(fn,variants)
fn='func_801C2D34'
def variants(s):
 for first,last in itertools.product([False,True],repeat=2):
  v=s
  if first:v=v.replace('temp_v0->words.w0 = 0xBA001301;\n    temp_v0->words.w1 = 0x80000;', 'temp_v0->words.w1 = 0x80000;\n    temp_v0->words.w0 = 0xBA001301;')
  if last:v=v.replace('temp_v0_7->words.w0 = 0x06000000;\n    temp_v0_7->words.w1 = (u32)&D_80285168;', 'temp_v0_7->words.w1 = (u32)&D_80285168;\n    temp_v0_7->words.w0 = 0x06000000;')
  yield str((first,last)),v
 test=0
test(fn,variants)
print(results)
