#!/usr/bin/env python3
"""T-016: reproduce conservative byte-based ovl_7E00 provenance inventory.
Run after extract_segments.py; no asm/ input, ROM writes, or build edits.
"""
import csv
import hashlib
import pathlib
import re
import subprocess
from collections import Counter
ROOT = pathlib.Path(__file__).resolve().parents[2]
BASE = 0x801AD900

def main():
    blob = (ROOT / 'build/segments/ovl_7E00.bin').read_bytes()
    output = subprocess.check_output([str(ROOT / 'tools/ext/binutils/bin/mips64-elf-objdump'), '-D', '-z', '-b', 'binary', '-m', 'mips:4300', '-EB', '--adjust-vma=0x801ad900', str(ROOT / 'build/segments/ovl_7E00.bin')], text=True)
    ins = {int(m[1], 16): m[2] for line in output.splitlines() if (m := re.match(r'\s*([0-9a-f]{8}):\s+[0-9a-f]{8}\s+(.+)', line))}
    with (ROOT / 'docs/functions.csv').open() as f:
        funcs = [r for r in csv.DictReader(f) if r['area'] == 'ovl_7E00']
    bounds = [(int(r['vram'], 16), int(r['vram'], 16) + int(r['bytes'])) for r in funcs]
    def owner(p):
        return next((a for a,b in bounds if a <= p < b), None)
    rows = []
    for r, (a,b) in zip(funcs, bounds):
        seq = [(p, ins[p]) for p in range(a,b,4)]
        ev = []
        def add(p,t,why):
            ev.append(f'{p:08X}: {t} ({why})')
        # Strong local signatures. Merely mentioning s8 is insufficient: require
        # no save of it, or use k0/k1 which IDO does not allocate in normal C.
        for p,t in seq:
            if re.search(r'\b(k0|k1)\b',t):
                add(p,t,'reserved kernel register in game code'); break
        for p,t in seq:
            if 's8' in t and not any(re.match(r'sw\s+s8,',u) for _,u in seq):
                add(p,t,'persistent s8 object register without local ABI save'); break
        for p,t in seq:
            if re.match(r'li\s+at,',t):
                add(p,t,'assembler-style immediate comparison/scratch at'); break
        for p,t in seq:
            if re.match(r'sw\s+ra,0\(sp\)',t):
                add(p,t,'ra at frame base; custom save layout, no o32 argument area'); break
        for p,t in seq:
            if re.match(r'(mfc0|mtc0)\s',t):
                add(p,t,'CP0 access requires assembly/intrinsic'); break
        for p,t in seq:
            m=re.match(r'(?:j|b\w*)\s+.*?(0x[0-9a-f]+)$',t)
            if m:
                target=int(m[1],16); o=owner(target)
                if o is not None and o!=a and target!=o:
                    add(p,t,f'cross-inventory branch to interior of {o:08X}'); break
        # Detect fall-through across an inventory boundary, including boundaries
        # which are themselves the preceding transfer's delay slot.
        last=seq[-1][1]
        prev=seq[-2][1] if len(seq)>1 else ins.get(a-4,'')
        if b in ins and owner(b) is not None and not re.match(r'(j|jr|b)\s',prev):
            add(seq[-1][0],last,'falls through inventory boundary; shared entry/body')
        if re.match(r'(j|jr|jal|jalr|b\w*)\s', ins.get(a-4,'')):
            ev.append(f'{a:08X}: inventory entry is the preceding control transfer delay slot')
        # Callee-saved registers used as scratch, with neither frame save nor
        # restoration: enough to distinguish these leaf helpers from o32 C.
        for p,t in seq:
            m=re.match(r'(?:lui|li|move|lw|lbu|lh|lhu|lb|addiu|addu|sll|srl|andi|xor|subu)\s+(s[0-7]),',t)
            if m and not any(re.match(r'sw\s+'+m[1]+r',-?[0-9]+\(sp\)',u) for _,u in seq):
                add(p,t,'writes callee-saved register without local ABI preservation'); break
        # Explicitly reviewed nonstandard live-ins/outputs for small helpers.
        manual = {
            0x801BC4C0:'gp used as comparison data/sentinel at 801BC4D8/4EC/500; non-ABI t8 input',
            0x801BAEC0:'mult by fixed 5 at 801BAED0 instead of IDO O2 shift/add strength reduction',
            0x801AEC00:'stores live s7/t8/t1 as arguments; non-o32 helper convention',
            0x801AF0B8:'returns byte in t1 (801AF110), not ABI v0; t0-first allocation',
            0x801B28C0:'live v1 base and f2/f4 inputs; shared floating-point store tail',
            0x801B9B20:'live t4/t5 inputs and t7 result; unchecked divu at 801B9B28',
            0x801B5018:'stores ra in global 801D882C before jumping to custom shared body',
            0x801BA4B0:'reloads ra from global at 801BA4C4/C8 after jal; custom return convention',
            0x801BC5A0:'saves ra in caller-clobbered t3 around jal; falls into next body',
            0x801C247C:'v0/v1 coordinate inputs; returns multiple values in f0/f2/f4/f10/f12 using cvt.w.s',
            0x801AE43C:'shared epilogue restores ra at sp+0 and pops caller-owned 8-byte frame',
        }
        if a in manual: ev.append(manual[a])
        if ev:
            cls='handwritten_asm'; confidence='medium' if a == 0x801BAEC0 else 'high'
        else:
            cls='uncertain'; confidence='low'
            ev=['ABI-compatible tiny/leaf body; provenance not identifiable from these instructions alone; surrounding module is assembly']
        rows.append(dict(vram=r['vram'],bytes=r['bytes'],**{'class':cls},confidence=confidence,evidence='; '.join(ev)))
    dest=ROOT / 'tools/analysis/data/ovl_7E00_asm.csv'
    with dest.open('w') as f:
        w=csv.DictWriter(f,fieldnames=['vram','bytes','class','confidence','evidence']); w.writeheader(); w.writerows(rows)
    print('overlay SHA256',hashlib.sha256(blob).hexdigest())
    for c in ['ido_c','handwritten_asm','uncertain']:
        selected=[r for r in rows if r['class']==c]
        print(c,len(selected),sum(int(r['bytes']) for r in selected))
    print('uncertain',[(r['vram'],r['bytes']) for r in rows if r['class']=='uncertain'])

if __name__ == '__main__':
    main()
