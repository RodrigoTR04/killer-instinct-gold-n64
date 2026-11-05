#!/bin/bash
# measure one function against several drafts
fn=$1; shift
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-c6fa874a
for d in "$@"; do
  .venv/bin/python tools/scratch/nonmatching/T-158/measure.py "$fn" "$d" 2>&1 | tail -2
done
