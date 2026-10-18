#!/usr/bin/env python3
"""Read-only, stdlib CPU function inventory for KI Gold US 1.0.

Boundaries are inferred from calls, stack frames, returns and curated SDK matches.
Boot boundaries were manually audited; main game boundaries remain candidates.
CSV ranges partition text (alignment belongs to the preceding function).
No extracted ROM data is written. Default output is tools/analysis/data/.
"""
import argparse,csv,json,pathlib,struct
from libultra_sig import regions

BOOT_STARTS='''00400 00450 004AC 00520 005EC 006B0 006FC 00740 007B4
00900 00960 00FA0 01410 01564 016CC 01BF0 01D10 01DF0 01EF4 01F2C
022C0 02420'''


def inventory(segment,base,data,evidence):
    end=base+len(data)
    if segment=='main':end=0x80042710
    words=dict(zip(range(base,end,4),struct.unpack('>%dI'%((end-base)//4),data[:end-base])))
    named={int(m['address'],16):m for m in evidence if m['segment']==segment}
    starts={base:{'entry'}}
    def add(a,why):
        if base<=a<end:starts.setdefault(a,set()).add(why)
    for a,m in named.items():add(a,'reference')
    if segment=='boot':
        for s in BOOT_STARTS.split():add(0x80000000|int(s,16),'audited')
    else:
        for a,w in words.items():
            if w>>26==3:add(0x80000000|((w&0x3FFFFFF)<<2),'jal')
            if w&0xFFFF8000==0x27BD8000:
                # A stack decrement can occur after entry setup instructions.
                prior=[p for p in starts if 0<=a-p<=0x40]
                if prior and not any(words.get(p)==0x03E00008 for p in range(max(prior),a,4)):continue
                add(a,'prologue')
        # Match extents exclude internal stack adjustments / return sites.
        for a,m in named.items():
            for p in list(starts):
                if a<p<a+m['size']:del starts[p]
        # Move a frame boundary back to instructions after the preceding return,
        # unless a known call/reference has already fixed the entry.
        for a in sorted(list(starts)):
            if starts[a]!={'prologue'}:continue
            for p in range(a-8,max(base-4,a-0x44),-4):
                if words.get(p)==0x03E00008:
                    q=p+8
                    while q<a and not words[q]:q+=4
                    if q<a and not any(q<=s<a for s in starts):
                        starts[q]=starts.pop(a)|{'return-boundary'}
                    break
        # Uncalled leaf routines can follow a return. A branch spanning that
        # return keeps subsequent code in its containing routine.
        for unused in range(3):
            changed=False;ss=sorted(starts)
            for a,z in zip(ss,ss[1:]+[end]):
                if a in named:continue
                for p in range(a,z-8,4):
                    if words[p]!=0x03E00008:continue
                    q=p+8
                    while q<z and not words[q]:q+=4
                    if q>=z:continue
                    cross=False
                    for x in range(a,z,4):
                        w=words[x];op=w>>26
                        if op in (1,4,5,6,7,20,21,22,23):
                            imm=w&65535;imm=imm if imm<32768 else imm-65536;t=x+4+imm*4
                            if (x<=p and t>=q) or (x>=q and t<=p):cross=True;break
                        if op==2:
                            t=0x80000000|((w&0x3ffffff)<<2)
                            if (x<=p and q<=t<z) or (x>=q and a<=t<=p):cross=True;break
                    if not cross:add(q,'leaf-after-return');changed=True;break
            if not changed:break
    rows=[];ss=sorted(starts)
    for a,z in zip(ss,ss[1:]+[end]):
        m=named.get(a);flags=set()
        for p in range(a,z,4):
            w=words[p];op=w>>26;rs=(w>>21)&31;rt=(w>>16)&31;rd=(w>>11)&31
            if op==16:flags.add('cp0')
            if w==0x42000018:flags.add('eret')
            regs=[rs,rt]+([rd] if op==0 else [])
            if op not in (2,3,17) and any(r in (26,27) for r in regs):flags.add('k0/k1')
        name=m['name'] if m else f'func_{a:08X}'
        rows.append(dict(start=f'0x{a:08X}',end=f'0x{z:08X}',size=f'0x{z-a:X}',name=name,
            kind='sdk' if m else ('entry' if a==base and segment=='boot' else 'unknown'),
            asm_candidate='yes' if flags else 'no',asm_evidence=';'.join(sorted(flags)),
            boundary_evidence=';'.join(sorted(starts[a])),confidence='audited' if segment=='boot' else ('reference' if m else 'candidate')))
    if segment=='main':
        rows.append(dict(start='0x80042710',end=f'0x{base+len(data):08X}',size=f'0x{base+len(data)-end:X}',
            name='rsp_microcode_scan_tail',kind='rsp_data',asm_candidate='n/a',asm_evidence='RSP CP0/SP DMA and IMEM jump targets',boundary_evidence='manual ISA inspection',confidence='high'))
    return rows


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('rom',nargs='?',default='baserom.us.z64');p.add_argument('--output-dir',default=str(pathlib.Path(__file__).with_name('data')));a=p.parse_args()
    rom=pathlib.Path(a.rom).read_bytes()
    import hashlib
    if hashlib.sha1(rom).hexdigest()!='ba52e91b44450c548467044b26951353dc491e04':raise SystemExit('Expected verified US 1.0 ROM SHA1')
    ev=json.loads(pathlib.Path(__file__).with_name('data').joinpath('libultra_matches.json').read_text())
    out=pathlib.Path(a.output_dir);out.mkdir(parents=True,exist_ok=True)
    for seg,base,data in regions(rom):
        rows=inventory(seg,base,data,ev)
        with (out/(seg+'_functions.csv')).open('w',newline='') as f:
            w=csv.DictWriter(f,fieldnames=list(rows[0]));w.writeheader();w.writerows(rows)
        cpu=[r for r in rows if r['kind']!='rsp_data'];print(f'{seg}: {len(cpu)} CPU entries, {sum(r["kind"]=="sdk" for r in cpu)} named SDK entries')
if __name__=='__main__':main()
