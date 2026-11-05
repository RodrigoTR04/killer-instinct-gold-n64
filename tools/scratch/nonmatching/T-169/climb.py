#!/usr/bin/env python3
"""Hill-climb a draft against the OFFICIAL screen.measure word count.

Mutates: order of top-level statements in the function body, the order of the
operands of a two-term && condition, and the order of leading declarations.
Always re-measures with `screen.measure` on the full owning TU, so the objective
is exactly the number the lead reads off docs/t2_drafts.md.
"""
import importlib.util
import random
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)

TMP = Path('/tmp/climb_candidate.c')


def score(fn, text):
    TMP.write_text(text)
    try:
        return dict(screen.measure(fn, TMP))['words']
    except Exception:
        return 10 ** 6


def split_body(src, fn):
    """Return (head, [statements], tail) where statements are top-level stmts."""
    m = re.search(r'\b' + re.escape(fn) + r'\s*\([^)]*\)\s*\{\n', src)
    head = src[:m.end()]
    rest = src[m.end():]
    # find matching close brace of the function
    depth = 1
    end = None
    for i, ch in enumerate(rest):
        if ch == '{':
            depth += 1
        elif ch == '}':
            depth -= 1
            if depth == 0:
                end = i
                break
    body = rest[:end]
    tail = rest[end:]
    # group into statements at depth 0
    stmts, buf, depth = [], '', 0
    for line in body.split('\n'):
        if not line.strip() and not buf:
            continue
        buf += line + '\n'
        depth += line.count('{') - line.count('}')
        if depth == 0 and buf.rstrip().endswith((';', '}')):
            stmts.append(buf)
            buf = ''
    if buf.strip():
        stmts.append(buf)
    return head, stmts, tail


def decl_end(stmts):
    """Number of leading statement groups that are declarations."""
    n = 0
    for s in stmts:
        if re.match(r'^\s*(?:[A-Za-z_]\w*\s+)+\**\w+', s.strip()) and s.rstrip().endswith(';') and '{' not in s:
            n += 1
        else:
            break
    return n


def main():
    fn, draft = sys.argv[1], Path(sys.argv[2])
    out = Path(sys.argv[3])
    budget = int(sys.argv[4]) if len(sys.argv) > 4 else 600
    random.seed(int(sys.argv[5]) if len(sys.argv) > 5 else 1)
    src = draft.read_text()
    head, stmts, tail = split_body(src, fn)
    n = len(stmts)
    nd = decl_end(stmts)
    print(f'{fn}: {n} top-level groups, {nd} declarations', flush=True)

    def build(order):
        return head + ''.join(order) + tail

    best = score(fn, build(stmts))
    best_o = list(stmts)
    print('start', best, flush=True)
    if best == 0:
        out.write_text(build(best_o))
        return
    tried = 0
    while tried < budget:
        o = best_o[:]
        kind = random.choice(['swap_decl', 'swap_stmt', 'cond_and', 'cond_and'])
        if kind == 'swap_decl' and nd > 1:
            i, j = random.sample(range(nd), 2)
            o[i], o[j] = o[j], o[i]
        elif kind == 'swap_stmt' and n > nd + 1:
            i, j = random.sample(range(nd, n), 2)
            o[i], o[j] = o[j], o[i]
        else:
            idx = random.randrange(n)
            m = re.search(r'\(\s*([^()]+?)\s*\)\s*&&\s*\(\s*([^()]+?)\s*\)', o[idx])
            if not m:
                continue
            a, b = m.group(1), m.group(2)
            o[idx] = o[idx][:m.start()] + f'({b}) && ({a})' + o[idx][m.end():]
        tried += 1
        s = score(fn, build(o))
        if s < best:
            best, best_o = s, o
            out.write_text(build(best_o))
            print(f'improved {best} ({kind}) after {tried}', flush=True)
            if best == 0:
                break
    print('final', best, 'tried', tried, flush=True)
    out.write_text(build(best_o))


main()
