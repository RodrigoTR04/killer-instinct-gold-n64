#!/usr/bin/env python3
"""Extract the verified US 1.0 1172 segment table; ROM is read-only."""
import hashlib,json,pathlib,struct,sys,zlib

def payloads(rom):
    """Yield metadata and bytes, preserving duplicate table entries."""
    if hashlib.sha1(rom).hexdigest() != 'ba52e91b44450c548467044b26951353dc491e04':
        raise ValueError('Expected verified US V1.0 big-endian ROM')
    for table in range(0x7df0,0x7ec8,8):
        start,end=struct.unpack_from('>II',rom,table)
        if rom[start:start+2]!=b'\x11\x72': raise ValueError(f'Bad header at {start:x}')
        dec=zlib.decompressobj(-15); data=dec.decompress(rom[start+2:end])+dec.flush()
        if not dec.eof: raise ValueError(f'Incomplete stream at {start:x}')
        name='main' if table==0x7df0 else f'ovl_{table:04X}'
        yield dict(name=name,rom_start=start,rom_end=end,table_offset=table,size=len(data),sha1=hashlib.sha1(data).hexdigest(),stream_end=end-len(dec.unused_data)),data

def extract(rom, outdir):
    outdir=pathlib.Path(outdir); outdir.mkdir(parents=True,exist_ok=True)
    records=[]
    for record,data in payloads(rom):
        (outdir/(record['name']+'.bin')).write_bytes(data)
        records.append(record)
    (outdir/'manifest.json').write_text(json.dumps(records,indent=2)+'\n')
    return records
if __name__=='__main__':
    extract(pathlib.Path(sys.argv[1]).read_bytes(),sys.argv[2] if len(sys.argv)>2 else 'build/segments')
