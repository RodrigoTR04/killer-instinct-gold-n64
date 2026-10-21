"""Full-TU IDO check; run after make extract. Products remain in /tmp.
Imports the existing relocation-aware comparator; no production source edits.
"""
import sys, json
from pathlib import Path
sys.path.insert(0, 'tools/scratch/nonmatching/T-098')
from harness import compile, source, extent

def main():
    results = {}
    for suffix in '2EF4 310C 3324 353C 3754 396C'.split():
        fn = 'func_801B' + suffix
        result = compile(fn, source(fn), 'T-101-final', suffix == '2EF4')
        results[fn] = result
        print(fn, result.get('words'), result.get('bytes'), flush=True)
    Path('/tmp/kig-t101-recheck.json').write_text(json.dumps(results, indent=2) + '\n')

if __name__ == '__main__':
    main()
