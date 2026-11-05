#!/usr/bin/env python3
"""Extract a function definition (+ its local typedef/decls are left behind) from a permuter source.c."""
import re, sys
from pathlib import Path

def extract(fn, source):
    # find "funcname(" at column 0 definition
    lines = source.splitlines()
    for i, line in enumerate(lines):
        if re.match(r'^[A-Za-z_][\w \t*]*\b' + re.escape(fn) + r'\s*\(', line):
            # definition if the matching close brace ends the function
            depth = 0; started = False; out = []
            for j in range(i, len(lines)):
                l = lines[j]
                out.append(l)
                depth += l.count('{') - l.count('}')
                if '{' in l: started = True
                if started and depth == 0:
                    return '\n'.join(out) + '\n'
    return None

def main():
    fn, src, dst = sys.argv[1], Path(sys.argv[2]), Path(sys.argv[3])
    text = extract(fn, src.read_text())
    if text is None:
        print('not found', file=sys.stderr); sys.exit(1)
    dst.write_text(text)

main()
