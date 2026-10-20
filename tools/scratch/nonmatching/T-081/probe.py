#!/usr/bin/env python3
"""Measure T-081 drafts in their owning TUs; reconcile probe declarations only."""
from pathlib import Path
import re, subprocess, sys
ROOT=Path(__file__).resolve().parents[4]
DRAFTS={'306B8':'T-026','20E98':'T-032','1E33C':'T-022','142E0':'T-033','2E724':'T-024'}
def context(suffix,draft):
    name='func_800'+suffix
    source=next(p for p in (ROOT/'src/main').glob('*.c') if '/'+name+'.s")' in p.read_text())
    s=source.read_text()
    if suffix=='1E33C':
        draft='extern f32 D_8004A7A0[],D_8004A740[],D_8004A800[],D_8004A920[],D_8004A8C0[];\nextern u8 D_8004AC88,D_8004A401,D_800698C4;\n'+draft
    if suffix=='142E0':
        declaration='typedef struct { u32 command, value; } T033142E0Command;'
        draft=re.sub(r'typedef\s+struct\s*\{\s*u32 command, value;\s*\}\s*T033142E0Command;', '', draft)
        s=s.replace('extern void func_800142E0();',declaration+'\nextern void func_800142E0(T033142E0Command **,s32 *,s32,s32,f32,f32,f32);')
    if suffix=='2E724':
        if 'extern s16 *D_80069928;' in draft:
            s=s.replace('extern u16 *D_80069928;', 'extern s16 *D_80069928;')
        # Existing TU call sites use compatible opaque pointers. Use those same
        # declarations in the probe and cast at the recovered typed entry.
        draft=re.sub(r'void func_8002E724\(T024EventPlayer \*player,T024VoiceEvent \*event\)\s*\{','void func_8002E724(T040Player *opaquePlayer,void *opaqueEvent) {\n    T024EventPlayer *player=(T024EventPlayer *)opaquePlayer;\n    T024VoiceEvent *event=opaqueEvent;',draft)
        draft=draft.replace('func_8002F2B0(void *)','func_8002F2B0(T024EventVoice *)')
        # Other definitions use older partial voice types. Reuse a compatible
        # non-prototype for the pointer-only call, and the actual FA5C signature.
        draft=draft.replace(',func_8002F2B0(T024EventVoice *)','')
        draft=draft.replace('extern void func_8002FA5C(void *,s16,s32);','')
        draft='extern void func_8002F2B0();\nextern void func_8002FA5C(s32,s16,s32);\n'+draft
    s=s.replace(f'#pragma GLOBAL_ASM("asm/nonmatchings/main/{source.stem}/{name}.s")',draft)
    return re.sub(r'#pragma GLOBAL_ASM\([^)]*\)','',s)
if __name__=='__main__':
    for suffix,directory in DRAFTS.items():
        if len(sys.argv)>1 and sys.argv[1]!=suffix: continue
        path=Path(sys.argv[2]) if len(sys.argv)>2 else ROOT/'tools/scratch/nonmatching'/directory/('func_800'+suffix+'.c')
        out=Path('/tmp/t081_'+suffix+'.c');out.write_text(context(suffix,path.read_text()))
        subprocess.run([sys.executable,str(ROOT/'tools/scratch/nonmatching/T-055/sc.py'),str(out),'func_800'+suffix]+sys.argv[3:])
