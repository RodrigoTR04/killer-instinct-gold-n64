#!/usr/bin/env python3
"""Recheck retained T-111 drafts in the complete production TU after extraction."""
from pathlib import Path
import sys
ROOT = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(ROOT / 'tools/permuter'))
import screen
for task, function in [('T-023', 'func_801BADEC'), ('T-023', 'func_801BB258'),
                       ('T-029', 'func_801B5650'), ('T-029', 'func_801B5DCC')]:
    print(screen.measure(function, ROOT / 'tools/scratch/nonmatching' / task / (function + '.c')), flush=True)
