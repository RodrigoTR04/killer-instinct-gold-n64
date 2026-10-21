from pathlib import Path
import sys,itertools,json,concurrent.futures
R=Path.cwd();O=Path('/tmp/kig-t114');sys.path.insert(0,str(R/'tools/scratch/nonmatching/T-096'));from probe import compile;from context import extent
fn='func_8002F6F4';s=(O/(fn+'-full.c')).read_text();a,b,_=extent(s,fn);body=s[a:b]
decls=['GameAudioVoice *voice;','ALSound *sound;','s32 step;','GameAudioVoice *last = 0;','s16 repeat = 0;','s32 repeatTime;','ALKeyMap *key;','s32 delay = 0;','GameAudioEvent start;','GameAudioEvent event;']
jobs=[]
for i,j in itertools.combinations(range(len(decls)),2):
 t=body.replace(decls[i],'T114_PLACEHOLDER').replace(decls[j],decls[i]).replace('T114_PLACEHOLDER',decls[j]);jobs.append((f'swap-{i}-{j}',t))
def run(job):
 label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
 if 0<r.get('bytes',0) and r.get('words',999)<2:
  p=O/(fn+'-'+label+'.c');p.write_text(t);r['candidate']=str(p);print('BETTER',r,flush=True)
 return r
with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:rows=list(pool.map(run,jobs))
(R/'tools/scratch/nonmatching/T-114/swaps.json').write_text(json.dumps(rows,indent=2)+'\n')
