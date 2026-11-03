#!/bin/bash
# usage: batch.sh fn file...   (env PREFIX=1 for prefix compile) -> "file exact masked"
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-b7e0fb3a
fn=$1; shift
toolbox run -c kig-build bash -c "for f in $*; do e=\$(COUNT=1 RONORM=1 PREFIX=${PREFIX:-} .venv/bin/python tools/scratch/nonmatching/T-155/cmp.py $fn \$f 2>&1 | tail -1); m=\$(COUNT=1 RONORM=1 REGMASK=1 PREFIX=${PREFIX:-} .venv/bin/python tools/scratch/nonmatching/T-155/cmp.py $fn \$f 2>&1 | tail -1); echo \"\$f | \$e | \$m\"; done"
