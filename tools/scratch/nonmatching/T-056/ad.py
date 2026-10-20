#!/usr/bin/env python3
# ad.py FN [draft.c]: difflib diff of target vs compiled instructions (relocs stripped)
import sys,re,pathlib,subprocess,difflib
sys.path.insert(0,str(pathlib.Path(__file__).parent))
import probe,tu
R=probe.ROOT
fn=sys.argv[1]; src=pathlib.Path(sys.argv[2]) if len(sys.argv)>2 else tu.draft(fn)
_,pre=tu.ctx(fn)
probe.probe(fn,pre+'\n'+src.read_text())
out=subprocess.check_output([str(R/'tools/ext/binutils/bin/mips64-elf-objdump'),'-d','--no-show-raw-insn',str('/tmp/t056-probe.o')],text=True)
def norm(l):
    l=re.sub(r'#.*','',l).strip(); return re.sub(r'\s+',' ',l)
ours=[];on=False
for l in out.splitlines():
    if re.match(r'^[0-9a-f]+ <'+fn+'>:',l): on=True; continue
    if on and re.match(r'^[0-9a-f]+ <',l): break
    m=re.match(r'\s+[0-9a-f]+:\s+(.*)',l)
    if on and m: ours.append(norm(m.group(1)))
asm=[]
for f in (R/'asm/nonmatchings/ovl_7DF8').glob('*/'+fn+'.s'):
    for l in f.read_text().splitlines():
        m=re.match(r'\s*/\* \w+ \w+ \w+ \*/\s+(.*)',l)
        if m: asm.append(norm(m.group(1)))
def key(s):
    s=re.sub(r'^or (\$?\w+), (\$?\w+), \$?zero$',r'move \1, \2',s); s=re.sub(r'^(jal|j) .*',r'\1',s)
    s=re.sub(r'^addiu (\$?\w+), \$?zero, ',r'li \1, ',s)
    s=s.replace('$','');s=re.sub(r'%(hi|lo)\([^)]*\)','X',s);s=re.sub(r'\b0x0\b|\b0\b','X',s)
    s=re.sub(r'\.L\w+|\b[0-9a-f]+ <[^>]*>','L',s)
    s=re.sub(r'-?0x[0-9a-fA-F]+',lambda m:str(int(m.group(0),16)),s); s=s.replace(', ',',').replace(' ,',',')
    s=re.sub(r'\b0\(','X(',s); s=re.sub(r'^(\w+) ',lambda m:m.group(1).replace('or','move')+' ' if False else m.group(0),s); return s
a=[key(x) for x in asm]; b=[key(x) for x in ours]
for l in difflib.unified_diff(a,b,'target','ours',n=2,lineterm=''): print(l)
