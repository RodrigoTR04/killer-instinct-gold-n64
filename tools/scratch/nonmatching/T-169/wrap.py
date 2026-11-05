#!/usr/bin/env python3
"""wrap.py FN DRAFT [--top N] [--json out]

Scans a draft for block boundaries and, one at a time, wraps real statements in
`do { ... } while (0);`.  IDO emits no code for the loop, but renumbers basic
blocks, which changes the schedule.  Every wrapped statement is real code from
the function, never an empty statement.

Reports the official full-TU word count for each variant, cheapest first.
"""
import argparse
import importlib.util
import json
import re
import sys
import concurrent.futures as cf
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)

OUT = Path('/tmp/wrap_variants')


def statements(body):
    """Yield (start_line, end_line, indent, text) for statement units, innermost.

    A unit is one simple statement (`;` terminated, brace-balanced) or one whole
    control statement (`if`/`for`/`while`/`do` including its block).
    """
    lines = body.split('\n')
    units = []
    i = 0
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()
        if not stripped or stripped in ('{', '}'):
            i += 1
            continue
        indent = len(line) - len(line.lstrip())
        start = i
        depth = line.count('{') - line.count('}')
        j = i
        # control statement with braces: consume until depth returns to 0
        if depth > 0:
            while j + 1 < len(lines) and depth > 0:
                j += 1
                depth += lines[j].count('{') - lines[j].count('}')
        else:
            # simple statement: consume until a line ends with ';' at depth 0
            while j < len(lines) and not lines[j].rstrip().endswith(';'):
                j += 1
                if j < len(lines):
                    depth += lines[j].count('{') - lines[j].count('}')
        text = '\n'.join(lines[start:j + 1])
        # never wrap a declaration: it must stay a declaration in the block
        is_decl = (re.match(r'^\s*(?:[A-Za-z_]\w*\s+)+\**\w+\s*(?:\[\w*\])?\s*(?:=|;)', text)
                   and '{' not in text)
        if not is_decl:
            units.append((start, j, indent, text))
        i = j + 1
    return units


def wrap(body, units, chosen):
    """Wrap each chosen unit (by index) in do { } while (0)."""
    lines = body.split('\n')
    # insert from the end so earlier indices stay valid
    for idx in sorted(chosen, reverse=True):
        start, end, indent, text = units[idx]
        pad = ' ' * indent
        inner = '\n'.join(('    ' + l) if l.strip() else l for l in text.split('\n'))
        new = f'{pad}do {{\n{inner}\n{pad}}} while (0);'
        lines[start:end + 1] = new.split('\n')
    return '\n'.join(lines)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function')
    ap.add_argument('draft')
    ap.add_argument('--combos', type=int, default=0, help='also try N random pairs')
    ap.add_argument('--json')
    args = ap.parse_args()

    fn = args.function
    src = Path(args.draft).read_text()
    m = re.search(r'\b' + re.escape(fn) + r'\([^)]*\)\s*\{\n', src)
    head_end = m.end()
    rest = src[head_end:]
    # matching close brace
    depth, end = 1, None
    for i, ch in enumerate(rest):
        if ch == '{':
            depth += 1
        elif ch == '}':
            depth -= 1
            if depth == 0:
                end = i
                break
    body, tail = rest[:end], rest[end:]
    units = statements(body)
    print(f'{fn}: {len(units)} statement units', flush=True)

    OUT.mkdir(exist_ok=True)
    cand = {}

    def build(chosen):
        return src[:head_end] + wrap(body, units, chosen) + tail

    def score(name, text):
        p = OUT / name
        p.write_text(text)
        try:
            r = dict(screen.measure(fn, p))
            return (r['words'], r['compiled'], name)
        except Exception:
            return (10 ** 6, 0, name)

    results = []
    tasks = []
    for i in range(len(units)):
        tasks.append((f'single_{i}.c', build([i])))
    if args.combos:
        import random
        random.seed(5)
        for k in range(args.combos):
            n = random.choice([2, 2, 3])
            chosen = tuple(sorted(random.sample(range(len(units)), min(n, len(units)))))
            tasks.append((f'combo_{k}_' + '_'.join(map(str, chosen)) + '.c', build(chosen)))
    with cf.ThreadPoolExecutor(8) as pool:
        results = list(pool.map(lambda t: score(*t), tasks))
    results.sort()
    base = score('base.c', src)
    print(f'baseline {base[0]}', flush=True)
    for w, b, n in results[:20]:
        if w < base[0]:
            print(f'BETTER {w} {b}B {n}', flush=True)
    print('--- top 8 ---')
    for w, b, n in results[:8]:
        print(w, b, n)
    if args.json:
        Path(args.json).write_text(json.dumps(results, indent=1))


main()
