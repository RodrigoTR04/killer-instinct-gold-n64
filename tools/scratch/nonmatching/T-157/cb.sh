#!/bin/bash
# usage: cb.sh fn file1 file2 ... -> reg-masked and exact diffwords for each
R=/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33
cd $R
fn=$1; shift
toolbox run -c kig-build bash -c "for f in $*; do echo -n \"\$f \"; r=\$(COUNT=1 PREFIX=${PREFIX:-} REGMASK=1 .venv/bin/python tools/scratch/nonmatching/T-157/cmp.py $fn \$f 2>&1 | tail -1 | sed 's/.*lines//'); e=\$(COUNT=1 PREFIX=${PREFIX:-} .venv/bin/python tools/scratch/nonmatching/T-157/cmp.py $fn \$f 2>&1 | tail -1 | sed 's/.*diffwords=//'); echo \"\$r exact=\$e\"; done"
