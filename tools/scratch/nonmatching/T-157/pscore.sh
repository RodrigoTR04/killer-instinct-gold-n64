#!/bin/bash
# usage: pscore.sh fn draft.c  -> permuter's base score (weighted diff, stack-diffs)
R=/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33
cd $R
d=/tmp/ps157_$$
toolbox run -c kig-build bash -c "rm -rf $d; .venv/bin/python tools/permuter/import_fn.py $1 $d --draft $2 >/dev/null 2>&1; timeout 40 .venv/bin/python tools/ext/decomp-permuter/permuter.py $d --stack-diffs -j 1 --stop-on-zero 2>&1 | tr '\r' '\n' | grep -a -m1 'iteration 1,\|base score\|score' ; rm -rf $d"
