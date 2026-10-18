#!/usr/bin/env python3
"""Evidence-backed US V1.0 decompressed segment inventory (JSON stdout).

All addresses/ranges are integers, ranges are half-open. See docs/segments.md
for evidence and limitations. No writes, third-party packages or ROM mutation.
"""
import json,pathlib,struct,sys
sys.dont_write_bytecode = True
from extract_segments import payloads

CODE = {
    0x7df0: (0x8000f960,0x80042710,0x80044a10,[(0x8004a230,0x80127c30),(0x80128350,0x801726d0)],[0x800005a8,0x800005c4]),
    0x7df8: (0x801abb20,0x801cd450,0x801cd450,[(0x802956f0,0x802d3ff0)],[0x800122b8,0x800122d4]),
    0x7e00: (0x801ad900,0x801c3f40,0x801c3f40,[(0x801d3230,0x801da030)],[0x8000fc54,0x8000fc6c]),
}

def span(start,end,kind,confidence='verified'):
    return dict(start=start,end=end,kind=kind,confidence=confidence)

def inventory(rom):
    result=[]
    for rec,data in payloads(rom):
        t=rec['table_offset']; r=dict(rec)
        r.update(vram=None,text_end=None,data_ranges=[],bss_ranges=[],loaded_by=[],confidence={})
        if t in CODE:
            vram,text_end,data_start,bss,callers=CODE[t]
            r.update(vram=vram,text_end=text_end,kind='cpu_code',loaded_by=callers,
                     data_ranges=[span(data_start,vram+len(data),'initialized_mixed')],
                     bss_ranges=[span(a,b,'bss') for a,b in bss])
            r['confidence']=dict(kind='verified',vram='verified',text_end='verified',bss='verified',rodata_boundary='unresolved')
            # Concrete read-only contents; these do not assert ELF section ownership.
            words=struct.unpack('>'+str(len(data)//4)+'I',data)
            runs=[]; start=None
            for i,w in enumerate(words+(0,)):
                hit=i*4>=data_start-vram and vram<=w<text_end and w%4==0
                if hit and start is None: start=i
                if not hit and start is not None:
                    if i-start>=4:runs.append(span(vram+start*4,vram+i*4,'text_pointer_table','candidate: may be callbacks or jump table'))
                    start=None
            r['rodata_candidates']=runs
        elif t<0x7e60:
            r.update(vram=[0x801db000,0x801e5000],kind='byte_table_data',
                     loaded_by=[0x80012138,0x8001215c,0x8001218c,0x800121b0],
                     data_ranges=[span(v,v+len(data),'byte_table_data') for v in (0x801db000,0x801e5000)])
            r['confidence']=dict(kind='verified data; semantic format unresolved',vram='verified indexed loader; two alternative slots',bss='not applicable')
            r['loader_index']=(t-0x7e08)//8
        else:
            r.update(vram=0x802d4000,kind='packed_graphics_data',loaded_by=[0x80012ae4,0x80012b0c],
                     data_ranges=[span(0x802d4000,0x802d4000+len(data),'packed_graphics_data')])
            r['confidence']=dict(kind='high: packed graphics command signatures; packet format unresolved',vram='verified indexed loader and destination array',bss='not applicable')
            r['loader_index']=(t-0x7e60)//8
        if t==0x7ec0:r['alias_of']='ovl_7E90'
        if t==0x7df8:
            r['subsegments']=[span(vram,text_end,'cpu_text'),
                span(text_end,0x802927b0,'data','hypothesis: data/rodata boundary'),
                span(0x802927b0,0x802956f0,'rodata','hypothesis: first ordered switch tables, then strings/floats')]
        if t==0x7e00:
            r['subsegments']=[span(vram,text_end,'cpu_text'),span(text_end,vram+len(data),'initialized_mixed')]
        if 0x7e08<=t<0x7e60:r['loader_called_by']=[0x8000fd28,0x80011b68]
        if t>=0x7e60:r['loader_called_by']=[0x8000fe14,0x801c228c,0x801c4ec8]
        if t==0x7df0:
            r['subsegments']=[span(0x8000f960,0x80042710,'cpu_text'),
                span(0x80042710,0x800427e0,'rsp_boot_text'),
                span(0x800427e0,0x80043bf0,'rsp_graphics_text'),
                span(0x80043bf0,0x80044a10,'rsp_audio_text'),
                span(0x80044a10,0x80048760,'data','hypothesis: data/rodata boundary'),
                span(0x80048760,0x80049770,'rodata','hypothesis: includes display list at 0x800496d0'),
                span(0x80049770,0x80049f70,'rsp_graphics_data'),
                span(0x80049f70,0x8004a230,'rsp_audio_data')]
        result.append(r)
    return result

if __name__=='__main__':
    rom=pathlib.Path(sys.argv[1] if len(sys.argv)>1 else 'baserom.us.z64').read_bytes()
    print(json.dumps(inventory(rom),indent=2))
