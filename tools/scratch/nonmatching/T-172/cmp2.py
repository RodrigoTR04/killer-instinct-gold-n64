"""cmp.py variant that honours BASEREV-independent TU text (works after edits)."""
import importlib.util, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmp155', ROOT / 'tools/scratch/nonmatching/T-155/cmp.py')
cmp = importlib.util.module_from_spec(spec); spec.loader.exec_module(cmp)
import os, difflib, re
def main():
    fn, draft = sys.argv[1], Path(sys.argv[2])
    if not draft.is_absolute(): draft = ROOT / draft
    ctx = 1
    if '--context' in sys.argv:
        ctx = int(sys.argv[sys.argv.index('--context') + 1])
    source, tu = cmp.build_source(fn, draft)
    import tempfile
    with tempfile.TemporaryDirectory() as d:
        o = cmp.compile_source(source, Path(d) / 'c.c')
        pairs = cmp.draft_raw(o, fn)
    mask = bool(os.environ.get('REGMASK'))
    def M(x):
        return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x) if mask else x
    mine = [M(cmp.canon(cmp.apply_relocs(i, r))) for _, i, r in pairs]
    theirs = [M(cmp.canon(t)) for t in cmp.target_raw(fn)]
    theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
    print(f'# {fn}  target {len(theirs)} instr / draft {len(mine)} instr  ({tu.relative_to(ROOT)})')
    if os.environ.get('COUNT'):
        sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
        bad = sum(max(i2-i1, j2-j1) for t,i1,i2,j1,j2 in sm.get_opcodes() if t != 'equal')
        print(f'diffwords={bad} unmasked')
        return
    d = list(difflib.unified_diff(theirs, mine, 'target', 'draft', lineterm='', n=ctx))
    print('\n'.join(d) if d else 'IDENTICAL')
main()
