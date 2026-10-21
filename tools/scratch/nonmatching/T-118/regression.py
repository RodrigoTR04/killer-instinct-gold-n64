#!/usr/bin/env python3
"""Reproduce two known matches in isolated TU snapshots; run from repo root."""
import json
from pathlib import Path
import sys
import tempfile

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools/permuter'))
import declorder as search


def check(function, mutation, output):
    owners = []
    for tu in (ROOT / 'src/main').glob('*.c'):
        source = tu.read_text()
        try:
            a, b = search.region(source, function)
        except ValueError:
            continue
        owners.append((tu, source, a, b))
    assert len(owners) == 1, owners
    tu, source, a, b = owners[0]
    name = next(t.start() for t in reversed(search.tokens(source[:a])) if t.group() == function)
    start = source.rfind('\n', 0, name) + 1
    candidate = mutation(source[start:b + 1], function)
    with tempfile.TemporaryDirectory(prefix='kig-t118-regression-') as directory:
        snapshot = Path(directory)
        for path in ROOT.iterdir():
            if path.name != 'src':
                (snapshot / path.name).symlink_to(path, target_is_directory=path.is_dir())
        (snapshot / 'src/main').mkdir(parents=True)
        marker = '#pragma GLOBAL_ASM("unused/' + function + '.s")'
        (snapshot / 'src/main' / tu.name).write_text(source[:start] + marker + source[b + 1:])
        draft = snapshot / 'draft.c'
        draft.write_text(candidate)
        try:
            search.screen.ROOT = snapshot
            result = search.search(function, draft, output, seconds=90, jobs=2, context='full')
        finally:
            search.screen.ROOT = ROOT
    assert result['before']['words'] == 2, result
    assert result['after']['words'] == 0, result
    print(function, '2 -> 0', result['winner'])


def swap_key_step(source, _):
    return source.replace('ALKeyMap *key;', '__SWAP__').replace('s32 step;', 'ALKeyMap *key;').replace('__SWAP__', 's32 step;')


if __name__ == '__main__':
    check('func_8002B95C', lambda source, fn: search.layout_source(source, fn, mode='join'), Path('/tmp/kig-t118-layout-regression'))
    check('func_8002F6F4', swap_key_step, Path('/tmp/kig-t118-declaration-regression-replay'))
