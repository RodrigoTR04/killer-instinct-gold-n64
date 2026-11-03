#!/bin/bash
# usage: side.sh fn draft [from] [to] : side-by-side canonical asm (target left, draft right)
R=/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33
cd $R; mkdir -p /tmp/t157
toolbox run -c kig-build bash -c "DUMP=/tmp/t157/m.txt DUMPT=/tmp/t157/t.txt .venv/bin/python tools/scratch/nonmatching/T-157/cmp.py $1 $2 >/dev/null"
paste -d'|' <(sed -n "${3:-1},${4:-500}p" /tmp/t157/t.txt) <(sed -n "${3:-1},${4:-500}p" /tmp/t157/m.txt) | awk -F'|' '{printf "%-28s %s\n",$1,$2}'
