#!/bin/bash
# usage: permfull.sh fn draft seconds jobs  -> decomp-permuter with ALL default mutations (exploratory; results need honesty review)
cd /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-67556935
fn=$1; draft=$2; secs=${3:-480}; jobs=${4:-6}
dir=/tmp/pmfull_$fn
rm -rf $dir
toolbox run -c kig-build bash -c ".venv/bin/python tools/permuter/import_fn.py $fn $dir --draft $draft" >/dev/null 2>&1
timeout --signal=INT --kill-after=15s ${secs}s toolbox run -c kig-build bash -c ".venv/bin/python tools/ext/decomp-permuter/permuter.py $dir --stack-diffs --best-only --better-only --stop-on-zero -j $jobs" > $dir.log 2>&1
tr '\r' '\n' < $dir.log | grep -a "base score\|new best" | tail -3
