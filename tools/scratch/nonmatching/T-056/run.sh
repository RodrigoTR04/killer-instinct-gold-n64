#!/bin/bash
# usage: run.sh func file...
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-f41c5900
fn=$1; shift; S=tools/scratch/nonmatching/T-056
for f in "$@"; do .venv/bin/python - "$fn" "$S/$f" <<'P'
import sys;sys.path.insert(0,'tools/scratch/nonmatching/T-056');import probe,pathlib
print(sys.argv[2],probe.probe(sys.argv[1],pathlib.Path(sys.argv[2]).read_text(), bool(__import__("os").environ.get("SHOW"))))
P
done
