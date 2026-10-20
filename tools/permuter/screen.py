#!/usr/bin/env python3
"""Screen T2 drafts in their owning TU (make extract first). No build files change.

Full TU is preferred; incompatible legacy declarations fall back to the TU
prefix, explicitly labeled. Scores mask only ELF relocation fields and include
missing/extra words. A zero is a candidate, never an integration claim.
"""
import argparse
import concurrent.futures
import csv
import importlib.util
import json
from pathlib import Path
import re
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('elf_compare', ROOT / 'tools/scratch/flagprobe/compare.py')
elf = importlib.util.module_from_spec(spec)
spec.loader.exec_module(elf)


def measure(function, draft, prefix=False, declarations=False, source_output=None):
    owners = []
    for tu in (ROOT / 'src').glob('*/*.c'):
        text = tu.read_text()
        match = re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/' + re.escape(function) + r'\.s"\)', text)
        if match:
            owners.append((tu, text, match))
    if len(owners) != 1:
        raise ValueError(f'expected one owner, got {len(owners)}')
    tu, text, match = owners[0]
    candidate = draft.read_text()
    if function == 'func_8002F45C':
        candidate = candidate.replace('extern T024AllocationLists D_80048270;', '')
        candidate = candidate.replace('D_80048270.', '((T024AllocationLists *)&D_80048270)->')
    source = text[:match.start()] + candidate + ('' if prefix else text[match.end():])
    if prefix:
        source = re.sub(r'#pragma GLOBAL_ASM\([^\n]*\)', '', source)
    if declarations:
        # Older drafts rely on shared views recorded in main_D3F0, but their
        # split owning TU does not declare them. Supply only audited views.
        sprite_users = {'func_80021B6C', 'func_80028A00', 'func_80031A38', 'func_80031DD0'}
        support = ''
        if function in sprite_users:
            shared = (ROOT / 'src/main/main_D3F0.c').read_text()
            support += re.search(r'typedef struct \{\s*s32 unk0;.*?\} T022Sprite;', shared, re.S)[0] + '\n'
            if function in sprite_users:
                support += 'extern T022Sprite D_8004CED0[];\n'
        if function == 'func_80021B6C':
            shared = (ROOT / 'src/main/main_2FF0.c').read_text()
            support += re.search(r'typedef struct \{[^}]*\} T020Position;', shared, re.S)[0] + '\n'
        missing = {
            'func_80021B6C': 'extern u8 D_8004AC88, D_8004AA28, D_8004A9D8, D_8004A998, D_8004AC89, D_8004AC8A;',
            'func_8001CD50': 'extern u8 D_8004EA9C[];',
            'func_8001D080': 'extern u8 D_8004AC88;',
            'func_8001EC74': 'extern u8 D_8004AA28;',
            'func_80031050': 'extern u8 D_8004CED0[];',
            'func_800310C0': 'extern u8 D_8004CED0[];',
            'func_80018AE0': 'extern s8 D_8004A730, D_8004A738;',
        }
        candidate = support + missing.get(function, '') + '\n' + candidate
        # Keep TU types and declarations, but let the draft's explicit alternate
        # views take precedence. No preceding body is compiled in this mode.
        from pycparser import c_parser, c_generator, c_ast
        context = re.sub(r'#pragma GLOBAL_ASM\([^\n]*\)', '', text[:match.start()])
        with tempfile.TemporaryDirectory(prefix='kig-screen-pp-') as directory:
            c = Path(directory) / 'context.c'
            c.write_text(context + '\nint t092_draft_boundary;\n' + candidate)
            processed = subprocess.check_output(['gcc', '-E', '-P', '-I' + str(ROOT / 'include'), str(c)], text=True, stderr=subprocess.DEVNULL)
        ast = c_parser.CParser().parse(processed)
        boundary = next(i for i, node in enumerate(ast.ext) if getattr(node, 'name', None) == 't092_draft_boundary')
        names = {getattr(node.decl if isinstance(node, c_ast.FuncDef) else node, 'name', None) for node in ast.ext[boundary + 1:]}
        generator = c_generator.CGenerator()
        retained = []
        for node in ast.ext[:boundary]:
            if isinstance(node, c_ast.FuncDef):
                node = node.decl
            if getattr(node, 'name', None) not in names:
                retained.append(generator.visit(node) + ';')
        source = '\n'.join(retained) + '\n' + processed.split('int t092_draft_boundary;', 1)[1]
    if source_output is not None:
        source_output.write_text(source)
    with tempfile.TemporaryDirectory(prefix='kig-screen-') as directory:
        c = Path(directory) / 'candidate.c'
        o = c.with_suffix('.o')
        c.write_text(source)
        command = [ROOT / '.venv/bin/python', ROOT / 'tools/ext/asm-processor/build.py', ROOT / 'tools/ext/ido/5.3/cc', '--', ROOT / 'tools/ext/binutils/bin/mips64-elf-as', '-EB', '-mips3', '-32', '-G', '0', '-I', 'include', '--', '-c', '-G', '0', '-non_shared', '-Xcpluscomm', '-Wab,-r4300_mul', '-O2', '-mips2', '-32', '-Iinclude', '-o', o, c]
        result = subprocess.run([str(x) for x in command], cwd=ROOT, capture_output=True, text=True)
        if result.returncode:
            raise RuntimeError(result.stderr[-12000:])
        code, masks, _ = elf.elf_function(o, function)
    originals = json.loads((ROOT / 'tools/progress/original-functions.json').read_text())
    row = next(r for r in originals.values() if r['function'] == function)
    base = {'main': 0x8000F960, 'ovl_7DF8': 0x801ABB20}[row['area']]
    offset = int(function[5:], 16) - base
    target = (ROOT / 'build/segments' / (row['area'] + '.bin')).read_bytes()[offset:offset + row['bytes']]
    a = struct.unpack('>' + 'I' * (len(code) // 4), code)
    b = struct.unpack('>' + 'I' * (len(target) // 4), target)
    words = sum((x & masks[i]) != (y & masks[i]) for i, (x, y) in enumerate(zip(a, b))) + abs(len(a) - len(b))
    return dict(function=function, draft=str(draft.relative_to(ROOT) if draft.is_relative_to(ROOT) else draft), tu=str(tu.relative_to(ROOT)), compiled=len(code), original=len(target), words=words, context='declarations' if declarations else ('prefix' if prefix else 'full'), error='')


def screen(item):
    function, draft = item
    errors = []
    for prefix, declarations in ((False, False), (True, False), (True, True)):
        try:
            result = measure(function, draft, prefix, declarations)
            result['full_error'] = errors[0] if errors else ''
            return result
        except Exception as error:
            errors.append(str(error))
    return dict(function=function, draft=str(draft.relative_to(ROOT) if draft.is_relative_to(ROOT) else draft), compiled=None, original=None, words=None, context='ERROR', error=errors[-1], full_error=errors[0])


def diagnostic(message):
    lines = message.splitlines()
    errors = [i for i, line in enumerate(lines) if 'Error:' in line or 'Fatal:' in line]
    if not errors:
        return message.strip()
    selected = sorted({j for i in errors for j in range(i, min(i + 3, len(lines)))})
    return '\n'.join(lines[i] for i in selected)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('-j', type=int, default=6)
    parser.add_argument('--output', type=Path, default=ROOT / 'tools/scratch/nonmatching/T-092/screen.md')
    parser.add_argument('--json', type=Path)
    parser.add_argument('--function', help='screen one function for diagnostics')
    args = parser.parse_args()
    status = list(csv.DictReader((ROOT / 'tools/progress/status.csv').open()))
    t2 = {r['name_or_vram'].split(':')[-1] for r in status if r['tier'] == 'T2'}
    items = []
    for draft in sorted((ROOT / 'tools/scratch/nonmatching').glob('T-0*/*.c')):
        fn = draft.stem
        if args.function and fn != args.function:
            continue
        if fn in t2 or ('0x' + fn.removeprefix('func_')) in t2:
            items.append((fn, draft))
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.j) as pool:
        results = list(pool.map(screen, items))
    results.sort(key=lambda r: (r['words'] is None, r['compiled'] != r['original'], r['words'] if r['words'] is not None else 10**9, r['function']))
    lines = ['# T-092 draft screen', '', 'IDO 5.3 -O2 -mips2 through asm-processor. Full owning TU first; prefix fallback removes other GLOBAL_ASM stubs and omits declarations after the target. Relocation masks come only from ELF REL entries. Size differences count as differing words. Declaration fallback keeps TU types/prototypes, omits preceding bodies, and gives explicit draft declarations precedence. Prefix/declaration scores require reconciliation before integration.', '', '| Function | Compiled B | Original B | Differing words | Context | Draft |', '|---|---:|---:|---:|---|---|']
    for r in results:
        lines.append(f"| {r['function']} | {r['compiled'] if r['compiled'] is not None else '—'} | {r['original'] if r['original'] is not None else '—'} | {r['words'] if r['words'] is not None else '—'} | {r['context']} | {r['draft']} |")
    lines += ['', '## Compilation diagnostics', '']
    for r in results:
        if r.get('full_error'):
            lines += [f"### {r['function']} ({r['context']})", '', '```text', diagnostic(r['full_error']), '```', '']
        if r['error'] and r['error'] != r.get('full_error'):
            lines += ['```text', diagnostic(r['error']), '```', '']
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text('\n'.join(lines) + '\n')
    if args.json:
        args.json.write_text(json.dumps(results, indent=2) + '\n')
    print(f'{len(results)} drafts; {sum(r["words"] is None for r in results)} errors; {args.output}')


if __name__ == '__main__':
    main()
