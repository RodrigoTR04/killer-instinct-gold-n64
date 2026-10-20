#!/usr/bin/env python3
"""Score retained T-069 drafts in current owning TU, reconciling probe-only declarations.
Usage: .venv/bin/python tools/scratch/nonmatching/T-069/probe.py [func_800...]
Uses T-055/sc.py and its /tmp/t055ref/main.bin reference (copy from verified build).
"""
from pathlib import Path
import re,subprocess,sys
ROOT=Path(__file__).resolve().parents[4]
DRAFTS={'257FC':'T-032','31DD0':'T-026','15594':'T-033','1D7E4':'T-022','238C4':'T-032','24CE0':'T-032','14D5C':'T-033','330B0':'T-026','25FC4':'T-032'}
for suffix,directory in DRAFTS.items():
    name='func_800'+suffix
    if len(sys.argv)>1 and sys.argv[1]!=name: continue
    source=next(p for p in (ROOT/'src/main').glob('*.c') if '/'+name+'.s")' in p.read_text())
    draft=(ROOT/'tools/scratch/nonmatching'/directory/(name+'.c')).read_text().replace('#include "common.h"','')
    s=source.read_text()
    if suffix=='15594':
        declaration='typedef struct { u32 command,value; } T03315594Command;'
        draft=draft.replace(declaration,'')
        s=s.replace('extern void func_80015594();',declaration+'\nextern void func_80015594(T03315594Command **,s32 *,f32,s32,f32,f32,f32);')
    if suffix=='31DD0':
        draft='''typedef struct { s32 unk0; void *data; s16 halfWidth,halfHeight,width,height,width2,height2; u8 pad[4]; s16 flags,palette; } T022Sprite;
extern T022Sprite D_8004CED0[];
'''+draft
    s=s.replace(f'#pragma GLOBAL_ASM("asm/nonmatchings/main/{source.stem}/{name}.s")',draft)
    s=re.sub(r'#pragma GLOBAL_ASM\([^)]*\)','',s)
    out=Path('/tmp/t069_context_'+suffix+'.c');out.write_text(s)
    subprocess.run([sys.executable,str(ROOT/'tools/scratch/nonmatching/T-055/sc.py'),str(out),name]+sys.argv[2:],check=True)
