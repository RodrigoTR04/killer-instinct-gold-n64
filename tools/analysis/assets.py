#!/usr/bin/env python3
"""Read-only US 1.0 asset inventory. Bounds are half-open; CSV contains no payloads.

Run from any directory: python3 tools/analysis/assets.py [ROM] [--output CSV].
Parent containers and child records overlap; only depth=0 and gap rows partition
coverage. Reference fields are static evidence, not observed runtime loads.
"""
import argparse
import csv
import hashlib
from pathlib import Path
import struct
import zlib

ROOT = Path(__file__).resolve().parents[2]
START, END = 0x7ED0, 0xA94D80
SHA1 = 'ba52e91b44450c548467044b26951353dc491e04'


def inventory(rom):
    assert hashlib.sha1(rom).hexdigest() == SHA1, 'Requires verified US 1.0 ROM'
    def u(p): return struct.unpack_from('>I', rom, p)[0]
    def h(p): return struct.unpack_from('>H', rom, p)[0]
    def le(p): return int.from_bytes(rom[p:p+4], 'little')
    def inflate(p, end):
        if rom[p:p+2] != b'\x11\x72': return None
        z = zlib.decompressobj(-15)
        try: data = z.decompress(rom[p+2:end], 16*1024*1024)
        except zlib.error: return None
        if not z.eof: return None
        return end-len(z.unused_data), data
    def image(pair):
        a,b = u(pair),u(pair+4)
        return inflate(a,b)[1]
    main, ovl = image(0x7DF0), image(0x7DF8)
    rows=[]
    def add(a,b,cls,ref,call,depth=0,parent='',stream=None):
        assert START <= a < b <= (len(rom) if cls == 'stage_packet' else END), (hex(a),hex(b))
        got=inflate(a if stream is None else stream,b)
        se,data=got if got else (None,None)
        row=dict(start=a,end=b,size=b-a,depth=depth,parent=parent,classification=cls,
                 confidence=('unknown' if cls in ('unresolved','unreferenced') else
                             'medium' if cls in ('packed_graphics','graphics_record','palette') else 'high'),
                 reference=ref,loader=call,compressed='y' if got else 'n',
                 stream_start=(a if stream is None else stream) if got else '',
                 stream_end=se if got else '',expanded_size=len(data) if got else '',
                 trailing_size=b-se if got else '',
                 trailing_zero=int(not any(rom[se:b])) if got else '',
                 sha1=hashlib.sha1(rom[a:b]).hexdigest(),
                 expanded_sha1=hashlib.sha1(data).hexdigest() if got else '')
        rows.append(row);return row
    # Four start/end pairs per 32-byte record, fourteen records.
    for i in range(14):
        p=0x80045E50+i*32
        vals=struct.unpack_from('>8I',main,p-0x8000F960)
        for j,cls,call in [(0,'character_sprites','800213E4;80021880'),
                           (1,'huffman_tree','8002167C;8002169C;80021A78;80021A98'),
                           (2,'unresolved','80021B1C'),
                           (3,'palette16','8001D3CC;8001D414;8001D464')]:
            a,b=vals[j*2:j*2+2]
            add(a,b,cls,f'main:{p+j*8:08X}',call)
    for i in range(10):
        p=0x80291FE8+i*8
        a,b=struct.unpack_from('>II',ovl,p-0x801ABB20)
        add(a,b,'portrait_ci8',f'7DF8:{p:08X}','801C5F84')
    direct=[
      (0x8B70,0x119F0,'packed_graphics','800244B0;80024570'),
      (0x119F0,0x13200,'packed_graphics','80021594;80024428'),
      (0x13200,0x1D640,'packed_graphics','80024234'),
      (0x1D640,0x24D60,'packed_graphics','800242DC'),
      (0x24D60,0x2ECB0,'packed_graphics','8002431C'),
      (0x49FD0,0x566D0,'packed_graphics','80021880'),
      (0x1EB6D0,0x1F3200,'packed_graphics','800247A0;80021880'),
      (0x1F4290,0x1F6700,'packed_graphics','80014270'),
      (0x1F6700,0x1F7780,'packed_graphics','800142AC'),
      (0x2C2280,0x2CF0A0,'packed_graphics','80024814'),
      (0x469660,0x470390,'packed_graphics','800248F0;80021880'),
      (0x471440,0x472FB0,'packed_graphics','8002435C'),
      (0x53CC40,0x543D10,'packed_graphics','80024964'),
      (0x543D10,0x54D720,'packed_graphics','800243B4'),
      (0x54E7D0,0x551E60,'packed_graphics','80013CA4'),
      (0x8F6AE0,0x8F9FA0,'packed_graphics','80024D2C'),
      (0xA68A20,0xA69A20,'unresolved','8001BB30'),
      (0xA69A20,0xA69A40,'metadata','800281FC'),
      (0xA69A40,0xA69A70,'metadata','800281FC'),
      (0xA69A70,0xA6A990,'packed_graphics','800123BC'),
      (0xA6A990,0xA6AA70,'metadata','80012484'),
      (0xA6AA70,0xA73980,'packed_graphics','801ADF38'),
      (0xA73980,0xA77960,'packed_graphics','801AC384'),
      (0xA94460,0xA94560,'metadata','80020F70'),
      (0xA94560,0xA94D80,'metadata','80020F94')]
    auxiliary = {0x13200,0x1D640,0x24D60,0x49FD0,0x1EB6D0,0x2C2280,0x469660,0x53CC40,0x543D10}
    for a,b,c,call in direct:
        cls = ('character_sprites' if a in auxiliary else 'ui_sprites') if c == 'packed_graphics' else c
        add(a,b,cls,'immediate',call)
    # Stage streams lie beyond the asset-region partition; boot-table children.
    for slot in range(0x7E60,0x7EC8,8):
        a,b=u(slot),u(slot+4)
        add(a,b,'stage_packet',f'ROM:{slot:06X}','80012AE4;80012B0C',1,'boot_stage_table')
    # ALBankFile -> ALBank -> ALInstrument -> ALSound -> ALWaveTable.
    for ctl,stop,base,call in [(0x8F9FA0,0x907580,0x907580,'8002A5B8'),
                               (0x9AF4B0,0x9B9AD0,0x9B9AD0,'8002A610')]:
        assert rom[ctl:ctl+2]==b'B1'
        add(ctl,stop,'audio_bank','immediate',call)
        waves={}
        for i in range(h(ctl+2)):
            bank=ctl+u(ctl+4+4*i)
            assert u(bank+4)==22050
            insts=[u(bank+8)]+[u(bank+12+4*j) for j in range(h(bank))]
            for ip in insts:
                if not ip:continue
                inst=ctl+ip
                for j in range(h(inst+14)):
                    sound=ctl+u(inst+16+4*j);wave=ctl+u(sound+8)
                    a=base+u(wave);b=a+u(wave+4)
                    assert rom[wave+8] in (0,1) # AL_ADPCM_WAVE / AL_RAW16_WAVE
                    waves.setdefault((a,b,rom[wave+8]),set()).add(wave)
        for (a,b,kind),refs in sorted(waves.items()):
            add(a,b,'audio_adpcm' if kind==0 else 'audio_raw16','ROM:'+ ';'.join(f'{p:06X}' for p in sorted(refs)),
                '80037808;8002B37C')
    seq=0x992AF0;n=h(seq+2)
    assert rom[seq:seq+2]==b'S1' and n==48
    add(seq,seq+4+n*8,'audio_sequence_index','immediate','8002A670;8002A6BC')
    for i in range(n):
        off,size=u(seq+4+i*8),u(seq+8+i*8)
        add(seq+off,seq+off+size,'audio_sequence',f'ROM:{seq+4+i*8:06X}',
            '8002A950;8002AA20')
    # Merge duplicate ranges, retaining every referring table slot/call site.
    unique={}
    for row in rows:
        k=row['start'],row['end']
        if k in unique:
            old=unique[k]
            for f in ('reference','loader'):
                old[f]=';'.join(sorted(set(old[f].split(';')+row[f].split(';'))))
        else:unique[k]=row
    rows=list(unique.values())
    # Self-sized little-endian graphics records; preserve residual bytes inside
    # the parent instead of guessing another record from a magic scan.
    for row in list(rows):
        a,b=row['start'],row['end']
        if row['classification'] not in ('character_sprites','ui_sprites') or row['compressed']=='y':continue
        if rom[a+4:a+6]==b'\x11\x72':
            p=a
            while p+6<b and rom[p+4:p+6]==b'\x11\x72':
                size=u(p);assert size>=6 and p+size<=b
                add(p,p+size,row['classification'],row['reference'],'8002136C',1,f'{a:06X}',p+4)
                p+=size
            continue
        p=a
        while p+8<=b:
            size=le(p+4)
            if size<8 or p+size>b:break
            add(p,p+size,'graphics_record',row['reference'],row['loader'],1,f'{a:06X}')
            p+=size
    # Byte accounting uses referenced interval union; no scan hit creates cover.
    spans=sorted((r['start'],r['end']) for r in rows if r['depth']==0)
    cursor=START;gaps=[]
    for a,b in spans:
        if a>cursor:gaps.append((cursor,a))
        cursor=max(cursor,b)
    if cursor<END:gaps.append((cursor,END))
    for a,b in gaps:add(a,b,'unreferenced','','')
    rows = sorted(rows,key=lambda r:(r['start'],r['depth'],r['end']))
    partition = [r for r in rows if r['depth'] == 0]
    assert partition[0]['start'] == START and partition[-1]['end'] == END
    assert all(a['end'] == b['start'] for a,b in zip(partition,partition[1:]))
    assert sum(r['size'] for r in partition) == END-START
    return rows


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('rom',nargs='?',type=Path,default=ROOT/'baserom.us.z64')
    ap.add_argument('--output',type=Path,default=ROOT/'tools/analysis/data/assets.csv')
    args=ap.parse_args();rows=inventory(args.rom.read_bytes())
    fields=list(rows[0]);args.output.parent.mkdir(parents=True,exist_ok=True)
    with args.output.open('w',newline='') as f:
        w=csv.DictWriter(f,fieldnames=fields,lineterminator='\n');w.writeheader()
        for row in rows:
            row=row.copy()
            for k in ('start','end','stream_start','stream_end'):
                if row[k]!='':row[k]=f'0x{row[k]:08X}'
            w.writerow(row)
    assert args.output.stat().st_size<1_000_000
    gaps=[r for r in rows if r['classification']=='unreferenced']
    missing=sum(r['size'] for r in gaps)
    print(f'{len(rows)} rows; region {END-START:,}; referenced {END-START-missing:,}; unreferenced {missing:,}')
    for r in gaps:print(f"gap {r['start']:08X}-{r['end']:08X} {r['size']}")

if __name__=='__main__':main()
