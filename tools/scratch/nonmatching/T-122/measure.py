"""Measure the sixteen T-122 drafts; compiler products remain temporary."""
import concurrent.futures
import json
from pathlib import Path
import probe

if __name__ == '__main__':
    items = [('func_' + name, probe.draft('func_' + name)) for name in probe.FUNCTIONS]
    with concurrent.futures.ThreadPoolExecutor(max_workers=5) as pool:
        rows = list(pool.map(probe.screen.screen, items))
    for row in rows:
        print(row['function'], row['words'], row['compiled'], row['context'])
    Path('/tmp/kig-t122/final.json').write_text(json.dumps(rows, indent=2) + '\n')
