#!/usr/bin/env python3
"""Measure retained drafts in their full owning TUs after extraction."""
from pathlib import Path
import json
import sys
ROOT = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(ROOT / 'tools/permuter'))
import screen
rows = []
for task, name in [('T-022', 'func_8001B134'), ('T-025', 'func_801B3B84'), ('T-023', 'func_801BADEC')]:
    row = screen.measure(name, ROOT / 'tools/scratch/nonmatching' / task / (name + '.c'))
    rows.append(row)
    print(row, flush=True)
(Path(__file__).parent / 'results.json').write_text(json.dumps(rows, indent=2) + '\n')
