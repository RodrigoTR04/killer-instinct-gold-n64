import sys, itertools, difflib
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import bbl
GB = '''    if (i < 72) do
    {
        green = i - 40;
        i++;
        *palette++ = ((green << 6) & 0x7C0) | 0xF801;
    }
    while (i < 72);
    if (i < 128) do
    {
        *palette++ = (i - 72) | 0xFFC1; i++;
    }
    while (i < 128);
'''
def region(ls):
    a = next((k for k, l in enumerate(ls) if l == 'slti at,v1,40'), None)
    b = next((k for k, l in enumerate(ls) if l == 'slti at,v1,72'), None)
    return ls[a:b] if a is not None and b is not None else []
TR = region(bbl.TGT)
def rscore(ls):
    r = region(ls)
    sm = difflib.SequenceMatcher(None, TR, r, autojunk=False)
    return sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
