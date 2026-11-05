#!/usr/bin/env python3
"""Combine a draft's declaration header with a function body extracted from a
permuter source.c, so the pair can be measured in the owning TU.

usage: combine.py FUNCTION DRAFT PERMUTER_SOURCE OUT
"""
import re, sys
from pathlib import Path

def extract(fn, source):
    lines = source.splitlines()
    for i, line in enumerate(lines):
        if re.match(r'^[A-Za-z_][\w \t*]*\b' + re.escape(fn) + r'\s*\(', line):
            depth, started, out = 0, False, []
            for j in range(i, len(lines)):
                l = lines[j]
                out.append(l)
                depth += l.count('{') - l.count('}')
                if '{' in l: started = True
                if started and depth == 0:
                    return '\n'.join(out) + '\n'
    return None

def head(fn, draft):
    lines = draft.splitlines()
    for i, line in enumerate(lines):
        if re.match(r'^[A-Za-z_][\w \t*]*\b' + re.escape(fn) + r'\s*\(', line):
            return '\n'.join(lines[:i]) + '\n'
    return draft

def main():
    fn, draft, src, dst = sys.argv[1], Path(sys.argv[2]), Path(sys.argv[3]), Path(sys.argv[4])
    body = extract(fn, src.read_text())
    if body is None:
        print(f'{fn} not found', file=sys.stderr); sys.exit(1)
    dst.write_text(head(fn, draft.read_text()) + body)

main()
