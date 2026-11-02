#!/bin/bash
# usage: cb.sh fn file1 file2 ... -> reg-masked diffwords and exact for each
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-b5eddd10
fn=$1; shift
toolbox run -c kig-build bash -c "for f in $*; do echo -n \"\$f \"; COUNT=1 PREFIX=${PREFIX:-} REGMASK=1 .venv/bin/python tools/scratch/nonmatching/T-154/cmp.py $fn \$f 2>&1 | tail -1 | sed 's/.*lines//'; done"
