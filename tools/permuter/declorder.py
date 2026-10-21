#!/usr/bin/env python3
"""Bounded IDO declaration-order / whitespace search, in screen.py TU context.

Only uninitialized leading declarations move. Executable token order stays fixed.
No source, draft or build input is overwritten; best.c and result.json are outputs.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import json
from pathlib import Path
import random
import re
import tempfile
import time

import screen

# Comments/literals are indivisible. Whitespace edits never touch their contents.
LEX = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|\d+(?:[\w.]*)|>>=|<<=|\+\+|--|->|&&|\|\||==|!=|<=|>=|<<|>>|\+=|-=|\*=|/=|%=|&=|\|=|\^=|[^\s]', re.S)


def tokens(source):
    return list(LEX.finditer(source))


def region(source, function):
    ts = tokens(source)
    opening = None
    for start, token in enumerate(ts[:-1]):
        if token.group() != function or ts[start + 1].group() != '(':
            continue
        depth = 0
        for i in range(start + 1, len(ts) - 1):
            depth += (ts[i].group() == '(') - (ts[i].group() == ')')
            if depth == 0:
                j = i + 1
                while j < len(ts) and ts[j].group().startswith(('/*', '//')):
                    j += 1
                if j < len(ts) and ts[j].group() == '{':
                    opening = j
                elif (j < len(ts) and re.fullmatch(r'[A-Za-z_]\w*', ts[j].group())
                      and all(re.fullmatch(r'[A-Za-z_]\w*|,', t.group()) for t in ts[start + 2:i])):
                    # K&R definitions put parameter declarations between the
                    # closing parenthesis and body. Do not rewrite that ABI.
                    k = j
                    while k < len(ts) and ts[k].group() not in ('{', '}', '=', '('):
                        k += 1
                    if k < len(ts) and ts[k].group() == '{':
                        opening = k
                break
        if opening is not None:
            break
    if opening is None:
        raise ValueError('function definition not found: ' + function)
    depth = 1
    for i in range(opening + 1, len(ts)):
        depth += (ts[i].group() == '{') - (ts[i].group() == '}')
        if not depth:
            return ts[opening].end(), ts[i].start()
    raise ValueError('unterminated function')


def declaration_plan(body):
    # Only simple, fixed-size declarators move. Initialized declarations and
    # comments stay anchored; later uninitialized declarations still participate.
    simple = re.compile(r'([A-Za-z_]\w*)\s+((?:\*\s*)*[A-Za-z_]\w*(?:\s*\[\s*\d+\s*\])?(?:\s*,\s*(?:\*\s*)*[A-Za-z_]\w*(?:\s*\[\s*\d+\s*\])?)*)\s*;\Z')
    excluded = {'return', 'break', 'continue', 'goto', 'extern', 'static', 'volatile', 'const', 'typedef', 'register'}
    result, plan, end = [], [], 0
    ts = tokens(body)
    i = 0
    while i < len(ts):
        if ts[i].group().startswith(('/*', '//')):
            plan.append(body[end:ts[i].end()] + ('\n' if ts[i].group().startswith('//') else ''))
            end = ts[i].end()
            i += 1
            continue
        start = ts[i].start()
        if not re.fullmatch(r'[A-Za-z_]\w*', ts[i].group()) or ts[i].group() in excluded:
            break
        depth = 0
        j = i
        while j < len(ts):
            value = ts[j].group()
            if value == ';' and depth == 0:
                break
            depth += (value in ('(', '[', '{')) - (value in (')', ']', '}'))
            j += 1
        if j == len(ts):
            break
        text = body[start:ts[j].end()]
        m = simple.fullmatch(text)
        if m:
            entries = [(m[1], x.strip()) for x in m[2].split(',')]
            result.extend(entries)
            plan.extend(entries)
        elif re.match(r'[A-Za-z_]\w*\s+(?:\*\s*)*[A-Za-z_]\w*\s*(?:\[[^]]*\]\s*)?=', text):
            # Keep initializer evaluation order and its complete source unchanged.
            plan.append(body[end:ts[j].end()])
        else:
            break
        end = ts[j].end()
        i = j + 1
    return result, end, plan


def declarations(body):
    ds, end, _ = declaration_plan(body)
    return ds, end


def render_declarations(ds, combined=False, plan=None):
    def render_group(group):
        groups = []
        for typ, name in group:
            if combined and groups and groups[-1][0] == typ:
                groups[-1][1].append(name)
            else:
                groups.append((typ, [name]))
        return '\n'.join('    ' + typ + ' ' + ', '.join(names) + ';' for typ, names in groups)
    if plan is None:
        return '\n' + render_group(ds) + '\n'
    # An initializer may refer to a local (or a shadowed outer name). Keep
    # declarations on their original side of such an initializer. Independent
    # initializers stay fixed but do not block unrelated uninitialized locals.
    names = {re.search(r'[A-Za-z_]\w*', name)[0] for _, name in ds}
    rank = {entry: i for i, entry in enumerate(ds)}
    parts, segment = [], []
    def flush():
        ordered = iter(sorted((x for x in segment if isinstance(x, tuple)), key=rank.__getitem__))
        group = []
        for entry in segment:
            if isinstance(entry, tuple):
                group.append(next(ordered))
            else:
                parts.extend([render_group(group), entry.strip()])
                group = []
        parts.append(render_group(group))
        segment.clear()
    for entry in plan:
        if isinstance(entry, str) and names.intersection(t.group() for t in tokens(entry) if not t.group().startswith(('/*', '//', '"', "'"))):
            flush()
            parts.append(entry.strip())
        else:
            segment.append(entry)
    flush()
    return '\n' + '\n'.join(p for p in parts if p) + '\n'


def boundaries(body):
    ts = tokens(body)
    parens = 0
    result = []
    for i, t in enumerate(ts[:-1]):
        value = t.group()
        parens += (value == '(') - (value == ')')
        nxt = ts[i + 1]
        gap = body[t.end():nxt.start()]
        if gap.strip() or value.startswith('//'):
            continue
        if (value == ';' and parens == 0) or value in ('{', '}') or nxt.group() in ('{', '}'):
            result.append((t.end(), nxt.start()))
    return result


def layout(body, rng=None, mode=None):
    edits = boundaries(body)
    if rng is not None:
        edits = rng.sample(edits, min(len(edits), rng.randint(1, 5)))
    for a, b in reversed(sorted(edits)):
        sep = ('\n    ' if mode == 'split' else ' ') if mode else ('\n    ' if '\n' not in body[a:b] else ' ')
        body = body[:a] + sep + body[b:]
    return body


def layout_source(source, function, rng=None, mode=None):
    a, b = region(source, function)
    start = next(t.start() for t in reversed(tokens(source[:a])) if t.group() == function)
    return source[:start] + layout(source[start:b + 1], rng, mode) + source[b + 1:]


def search(function, draft, output, seconds=600, jobs=2, seed=118, context='auto'):
    output.mkdir(parents=True, exist_ok=True)
    original = draft.read_text()
    a, b = region(original, function)
    body = original[a:b]
    ds, end, plan = declaration_plan(body)
    rng = random.Random(seed)
    started = time.monotonic()
    seen = set()
    counts = {'compiled': 0, 'errors': 0, 'duplicates': 0}
    errors = []
    with tempfile.TemporaryDirectory(prefix='kig-declorder-') as directory:
        def compile_one(item):
            label, candidate = item
            with tempfile.NamedTemporaryFile(mode='w', suffix='.c', dir=directory) as f:
                f.write(candidate)
                f.flush()
                try:
                    r = screen.measure(function, Path(f.name), prefix=selected != 'full', declarations=selected == 'declarations')
                    return label, candidate, r, None
                except Exception as exc:
                    return label, candidate, None, str(exc)

        # Select context once; never silently change it between variants.
        selected = context
        baseline = None
        for selected in (['full', 'prefix', 'declarations'] if context == 'auto' else [context]):
            _, _, baseline, error = compile_one(('baseline', original))
            if baseline is not None:
                break
            errors.append({'context': selected, 'error': error})
        if baseline is None:
            raise RuntimeError(json.dumps(errors))
        best, best_result, winner = original, baseline, 'baseline'
        history = []
        frontier = [original]
        def initial():
            yield 'split-all', layout_source(original, function, mode='split')
            yield 'join-all', layout_source(original, function, mode='join')
            orders = itertools.permutations(range(len(ds))) if len(ds) <= 6 else (rng.sample(range(len(ds)), len(ds)) for _ in range(400))
            for order in orders:
                for combined in (False, True):
                    newbody = render_declarations([ds[i] for i in order], combined, plan) + body[end:].lstrip('\n')
                    yield f'order={list(order)} combined={combined}', original[:a] + newbody + original[b:]
        initial_candidates = iter(initial())
        exhausted = False
        with ThreadPoolExecutor(max_workers=jobs) as pool:
            while time.monotonic() - started < seconds and best_result['words']:
                batch = []
                attempts = 0
                while len(batch) < jobs and attempts < jobs * 100:
                    attempts += 1
                    if not exhausted and (counts['compiled'] + counts['errors'] + len(batch)) % 4 != 3:
                        try:
                            label, candidate = next(initial_candidates)
                        except StopIteration:
                            exhausted = True
                            continue
                    else:
                        parent = rng.choice(frontier)
                        ba, bb = region(parent, function)
                        current = parent[ba:bb]
                        decls, stop, current_plan = declaration_plan(current)
                        if len(decls) > 1 and rng.random() < .35:
                            i, k = rng.sample(range(len(decls)), 2)
                            decls[i], decls[k] = decls[k], decls[i]
                            current = render_declarations(decls, rng.choice([True, False]), current_plan) + current[stop:].lstrip('\n')
                            candidate = parent[:ba] + current + parent[bb:]
                        else:
                            candidate = layout_source(parent, function, rng)
                        label = f'hill-{counts["compiled"] + counts["errors"] + len(batch)}'
                    if candidate in seen:
                        counts['duplicates'] += 1
                        continue
                    seen.add(candidate)
                    batch.append((label, candidate))
                if not batch:
                    break
                for label, candidate, result, error in pool.map(compile_one, batch):
                    if error:
                        counts['errors'] += 1
                        if len(errors) < 8:
                            errors.append({'label': label, 'error': error})
                        continue
                    counts['compiled'] += 1
                    score = (result['words'], abs(result['compiled'] - result['original']))
                    oldscore = (best_result['words'], abs(best_result['compiled'] - best_result['original']))
                    if score < oldscore:
                        best, best_result, winner = candidate, result, label
                        frontier = [candidate]
                        history.append({'label': label, 'words': result['words'], 'compiled': result['compiled']})
                        (output / 'best.c').write_text(best)
                        print(f'{function}: {baseline["words"]} -> {result["words"]} ({label})', flush=True)
                    elif score == oldscore:
                        if len(frontier) < 32:
                            frontier.append(candidate)
                        else:
                            frontier[rng.randrange(32)] = candidate
        (output / 'best.c').write_text(best)
        report = dict(function=function, draft=str(draft), context=selected, before=baseline, after=best_result, winner=winner, seconds=time.monotonic()-started, seed=seed, locals=len(ds), initial_exhausted=exhausted, **counts, history=history, diagnostics=errors)
        (output / 'result.json').write_text(json.dumps(report, indent=2) + '\n')
        return report


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('function')
    p.add_argument('draft', type=Path)
    p.add_argument('output', type=Path)
    p.add_argument('--seconds', type=float, default=600)
    p.add_argument('-j', type=int, default=2)
    p.add_argument('--seed', type=int, default=118)
    p.add_argument('--context', choices=['auto', 'full', 'prefix', 'declarations'], default='auto')
    args = p.parse_args()
    if args.seconds <= 0 or args.j < 1:
        p.error('seconds and workers must be positive')
    print(json.dumps(search(args.function, args.draft, args.output, args.seconds, args.j, args.seed, args.context), indent=2))


if __name__ == '__main__':
    main()
