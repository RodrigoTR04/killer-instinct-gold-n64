"""Recompile the six installed scratch drafts in their complete owning TU.
Run after make extract. Compiler products and expanded sources remain in /tmp.
"""
from harness import *
rows = {}
for suffix in '2EF4 310C 3324 353C 3754 396C'.split():
    name = 'func_801B' + suffix
    result = compile(name, source(name), 'final', suffix == '2EF4')
    rows[name] = result
    print(name, result.get('words'), result.get('bytes'), flush=True)
(OUT / 'recheck.json').write_text(json.dumps(rows, indent=2) + '\n')
