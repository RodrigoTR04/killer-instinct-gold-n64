#!/usr/bin/env python3
"""Find candidate MIPS signatures in reference .s files or ELF32 objects.

No ROM bytes are stored; output contains bounds, names and hashes.

Usage: libultra_sig.py baserom.us.z64 /tmp/kig-t005/007 --output matches.json
Masks only reference-annotated relocations and absolute jump destinations.
Requires no packages. Reference code and decompression stay in memory.
"""
import argparse, hashlib, json, pathlib, re, struct, zlib

def regions(rom):
    return [('boot',0x80000400,rom[0x1000:0x7160]),
            ('main',0x8000F960,zlib.decompress(rom[0xA94D82:0xAB5800],-15)[:0x32FE0])]

def references(root):
    for path in sorted(pathlib.Path(root).rglob('*.s')):
        name=None; words=[]; masks=[]
        for line in path.read_text(errors='replace').splitlines()+['glabel END']:
            label=re.match(r'\s*glabel\s+(\w+)',line)
            if label:
                if name and len(words)>=2:
                    yield str(path.relative_to(root)),name,words,masks
                name=label[1]; words=[]; masks=[]
            ins=re.search(r'/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+([0-9A-Fa-f]{8})\s*\*/(.*)',line)
            if ins and name:
                w=int(ins[1],16); asm=ins[2]
                mask=0xFC000000 if w>>26 in (2,3) else (0xFFFF0000 if '%hi(' in asm or '%lo(' in asm else 0xFFFFFFFF)
                words.append(w); masks.append(mask)

def match(rom,root):
    result=[]
    for source,name,words,masks in references(root):
        # Tiny signatures are useful but can collide: retain every hit, never pick one silently.
        for segment,base,data in regions(rom):
            target=struct.unpack('>%dI'%(len(data)//4),data)
            for i in range(len(target)-len(words)+1):
                if all((target[i+j]&m)==(w&m) for j,(w,m) in enumerate(zip(words,masks))):
                    raw=struct.pack('>%dI'%len(words),*target[i:i+len(words)])
                    result.append(dict(segment=segment,address=f'0x{base+i*4:08X}',name=name,
                        size=len(raw),reference=source,match='exact' if list(target[i:i+len(words)])==words else 'masked',
                        sha256=hashlib.sha256(raw).hexdigest()))
    return result

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('rom');p.add_argument('reference');p.add_argument('--output');p.add_argument('--objects',action='store_true');a=p.parse_args()
    result=(match_objects if a.objects else match)(pathlib.Path(a.rom).read_bytes(),a.reference)
    out=json.dumps(result,indent=2)+'\n'
    if a.output:pathlib.Path(a.output).write_text(out)
    else:print(out,end='')

# ELF32 big-endian MIPS object signatures. Only relocation bits are masked;
# ordinary immediates, nonrelocated branches, registers and instruction order remain intact.
def elf_references(root):
    for path in sorted(pathlib.Path(root).rglob('*.o')):
        b=path.read_bytes()
        if b[:6]!=b'\x7fELF\x01\x02':continue
        shoff=struct.unpack_from('>I',b,32)[0]; ents,n,strings=struct.unpack_from('>HHH',b,46)
        sections=[struct.unpack_from('>10I',b,shoff+i*ents) for i in range(n)]
        def data(s):return b[s[4]:s[4]+s[5]]
        names=data(sections[strings])
        def string(blob,off):return blob[off:blob.index(b'\0',off)].decode(errors='replace')
        ti=next((i for i,s in enumerate(sections) if string(names,s[0])=='.text'),None)
        if ti is None:continue
        textdata=data(sections[ti]); rel={}
        for s in sections:
            if s[1]==9 and s[7]==ti:
                for off in range(s[4],s[4]+s[5],s[9]):
                    pos,info=struct.unpack_from('>II',b,off);kind=info&255
                    if kind not in (2,4,5,6,10):
                        raise ValueError(f'{path}: unsupported text relocation {kind}')
                    rel[pos]={2:0,4:0xFC000000,5:0xFFFF0000,6:0xFFFF0000,10:0xFFFF0000}[kind]
        if textdata and len(textdata)%4==0:
            words=list(struct.unpack('>%dI'%(len(textdata)//4),textdata))
            yield str(path.relative_to(root)), '@text', words, [rel.get(j*4,0xFFFFFFFF) for j in range(len(words))]
        for s in sections:
            if s[1]!=2:continue
            strs=data(sections[s[6]])
            for off in range(s[4],s[4]+s[5],s[9]):
                no,val,size,info,other,idx=struct.unpack_from('>IIIBBH',b,off)
                if idx!=ti or info&15!=2 or size<8 or val+size>len(textdata):continue
                raw=textdata[val:val+size-size%4]
                words=list(struct.unpack('>%dI'%(len(raw)//4),raw))
                masks=[rel.get(val+j*4,0xFFFFFFFF) for j in range(len(words))]
                yield str(path.relative_to(root)),string(strs,no),words,masks

def match_objects(rom,root):
    result=[]
    for source,name,words,masks in elf_references(root):
        # Use the longest unrelocated run as a fast search anchor.
        runs=[]; start=0
        for j,m in enumerate(masks+[0]):
            if m!=0xFFFFFFFF:
                if j>start:runs.append((start,j))
                start=j+1
        if not runs:continue
        lo,hi=max(runs,key=lambda x:x[1]-x[0]);anchor=struct.pack('>%dI'%(hi-lo),*words[lo:hi])
        for segment,base,data in regions(rom):
            pos=data.find(anchor)
            while pos>=0:
                i=pos-lo*4
                if i>=0 and i%4==0 and i+len(words)*4<=len(data):
                    raw=data[i:i+len(words)*4];target=struct.unpack('>%dI'%len(words),raw)
                    if all((t&m)==(w&m) for t,w,m in zip(target,words,masks)):
                        result.append(dict(segment=segment,address=f'0x{base+i:08X}',name=name,size=len(raw),reference=source,
                            match='exact' if list(target)==words else 'masked',sha256=hashlib.sha256(raw).hexdigest()))
                pos=data.find(anchor,pos+1)
    return result

if __name__=='__main__':main()
