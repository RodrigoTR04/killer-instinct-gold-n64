#!/bin/bash
# usage: frame.sh fn file... -> frame size and exact/masked diff words
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-b7e0fb3a
fn=$1; shift
toolbox run -c kig-build bash -c "for f in $*; do fr=\$(PREFIX=${PREFIX:-} .venv/bin/python tools/scratch/nonmatching/T-155/asm.py $fn \$f 2>&1 | grep -m1 'addiu.sp,sp,-' | sed 's/.*sp,sp,//'); e=\$(COUNT=1 RONORM=1 PREFIX=${PREFIX:-} .venv/bin/python tools/scratch/nonmatching/T-155/cmp.py $fn \$f 2>&1 | tail -1 | sed 's/.*diffwords=//'); m=\$(COUNT=1 RONORM=1 REGMASK=1 PREFIX=${PREFIX:-} .venv/bin/python tools/scratch/nonmatching/T-155/cmp.py $fn \$f 2>&1 | tail -1| sed 's/.*diffwords=//'); echo \"\$f frame=\$fr exact=\$e masked=\$m\"; done"
