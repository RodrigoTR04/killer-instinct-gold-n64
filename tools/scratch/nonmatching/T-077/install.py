import sys,pathlib,itertools,json,re,random,struct,subprocess,os
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
results={}
for n in '2010 21B4 2358 24FC 26A0 2844 29E8'.split():
 fn='func_801B'+n;p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);base=probe.probe(fn,pre+s);a=s.index('    arg1 = D_');b=s.index('    guTranslate',a)
 counter=re.search(r'arg1 = (D_\w+);',s[a:b])[1];x,y=re.search(r'position = func_801B19F0\(([^,]+), ([^,]+),',s[a:b]).groups()
 block=f'''    arg1 = {counter};
    if (arg1 < 1)
    {{
        position = func_801B19F0({x}, {y}, {counter} = ++arg1, 1);
    }}
    else
    {{
        ++arg1;
        {counter} = arg1;
        position = {y};
    }}
'''
 # vary only line boundaries inside changed block; preserve known matched tail
 chunks=re.findall(r'[^;{}(),\s]+|[;{}(),]|\s+',block);tokens=[t for t in chunks if not t.isspace()]
 # whitespace between operators/tokens always legal; no changes to tokens
 best=base;bs=s;label='baseline'
 rng=random.Random(77)
 for k in range(300):
  if k==0:bb=block
  else:
   # Keep lexical tokens (including ++arg1) intact.
   bb=''.join(t+ ('\n' if rng.random()<.25 else ' ') for t in tokens)
  cand=s[:a]+bb+'\n'+s[b:];r=probe.probe(fn,pre+cand)
  if r[0]<best[0]:best=r;bs=cand;label=k;print(fn,k,base,best,flush=True)
 # tidy using newline per statement and conventional indentation, retain score
 if best[0]<base[0]:
  # try original readable block first
  tidy=s[:a]+block+s[b:]
  if probe.probe(fn,pre+tidy)[0]<=best[0]:bs=tidy
  bs=re.sub(r'/\* T-071 DRAFT:.*?\*/',f'/* T-077 DRAFT: {best[0]} differing words; {best[1]} bytes. Not matching. */',bs, count=1)
  p.write_text(bs)
 results[fn]={'old':base,'new':best,'layout':label}
for n in '2EF4 310C 3324 353C 3754 396C'.split():
 fn='func_801B'+n;p=tu.draft(fn);_,pre=tu.ctx(fn);r=probe.probe(fn,pre+p.read_text());results[fn]={'old':r,'new':r}
pathlib.Path(__file__).with_name('results.json').write_text(json.dumps(results,indent=2)+'\n')
