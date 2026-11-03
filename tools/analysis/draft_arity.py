#!/usr/bin/env python3
"""Audit T2 drafts for calls whose argument count disagrees with a callee that
already has a real C definition in src/ (T4 or compiled-in).  m2c guesses
arities; T-138 found that fixing a wrong arity took func_801B5DCC from 303 to
157 differing words.  Read-only; prints one line per mismatch."""
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DEF = re.compile(r'^(?:static\s+)?[A-Za-z_][\w\s\*]*?\b(func_[0-9A-F]{8})\s*\(([^)]*)\)\s*\{', re.M)


def nparams(text):
    text = text.strip()
    if text in ('', 'void'):
        return 0
    return text.count(',') + 1


def strip(text):
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    return re.sub(r'//[^\n]*', '', text)


def split_args(s):
    depth, n, seen = 0, 0, False
    for ch in s:
        if ch in '([{':
            depth += 1
        elif ch in ')]}':
            depth -= 1
        elif ch == ',' and depth == 0:
            n += 1
        if not ch.isspace():
            seen = True
    return n + 1 if seen else 0


def calls(text, name):
    for m in re.finditer(r'(?<![\w])' + name + r'\s*\(', text):
        i, depth = m.end(), 1
        while i < len(text) and depth:
            depth += {'(': 1, ')': -1}.get(text[i], 0)
            i += 1
        yield text.count('\n', 0, m.start()) + 1, split_args(text[m.end():i - 1])


def is_decl(text, name, line):
    src = text.splitlines()[line - 1]
    before = src[:src.find(name)]
    return bool(re.search(r'\b(extern|void|int|[us](?:8|16|32|64)|f32|f64)\b[\s\*]*$', before))


defs = {}
for f in (ROOT / 'src').glob('*/*.c'):
    t = strip(f.read_text())
    for m in DEF.finditer(t):
        defs[m.group(1)] = (nparams(m.group(2)), f.name)

bad = defaultdict(list)
for d in sorted((ROOT / 'tools/scratch/nonmatching').glob('T-*/func_*.c')):
    if d.stem.count('-'):
        continue
    t = strip(d.read_text())
    own = d.stem
    for name, (n, where) in defs.items():
        if name == own:
            continue
        if n == 0:
            continue  # `f()` is an unprototyped K&R definition: arity unknown
        for line, got in calls(t, name):
            if got != n and not is_decl(t, name, line):
                bad[d].append((name, n, got, line, where))

for d, items in bad.items():
    for name, n, got, line, where in items:
        print(f'{d.relative_to(ROOT)}:{line}: {name} defined with {n} param(s) in {where}, called with {got}')
print(f'# {sum(len(v) for v in bad.values())} mismatches in {len(bad)} drafts', file=sys.stderr)
