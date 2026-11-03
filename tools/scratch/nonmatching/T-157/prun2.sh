#!/bin/bash
# usage: prun.sh fn draft.c outdir seconds [jobs]  -- restricted-weight permuter (no dummy-construct passes)
R=/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e98bbe33
cd $R
toolbox run -c kig-build bash -c "rm -rf $3; .venv/bin/python tools/permuter/import_fn.py $1 $3 --draft $2 >/dev/null 2>&1
cat >> $3/settings.toml <<'EOT'

[weight_overrides]
perm_ins_block = 0
perm_empty_stmt = 0
perm_condition = 0
perm_dummy_comma_expr = 0
perm_add_self_assignment = 0
perm_xor_zero = 0
perm_mult_zero = 0
perm_var_cond_block = 0
perm_duplicate_assignment = 0
perm_alias_array = 0
perm_inline = 0
perm_refer_to_var = 0
perm_remove_ast = 0
perm_pad_var_decl = 0
perm_add_sub = 0
perm_chain_assignment = 0
perm_long_chain_assignment = 0
perm_struct_ref = 0
perm_remove_var = 0
perm_temp_for_expr = 60
EOT
timeout --signal=INT --kill-after=15s $4 .venv/bin/python tools/ext/decomp-permuter/permuter.py $3 --stack-diffs --best-only -j ${5:-6} > $3/log.txt 2>&1"
