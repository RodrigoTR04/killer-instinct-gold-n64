#!/bin/bash
# usage: s.sh fn draft  -> writes /tmp/t157/t.txt /tmp/t157/m.txt (canonical, unmasked); prints reg-masked and exact counts
R=/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33
cd $R; mkdir -p /tmp/t157
toolbox run -c kig-build bash -c "DUMP=/tmp/t157/m.txt DUMPT=/tmp/t157/t.txt COUNT=1 REGMASK=1 .venv/bin/python tools/scratch/nonmatching/T-157/cmp.py $1 $2 | tail -1; COUNT=1 .venv/bin/python tools/scratch/nonmatching/T-157/cmp.py $1 $2 | tail -1"
