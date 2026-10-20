"""Recheck all final drafts through production asm-processor in their complete TUs."""
import json
from pathlib import Path
import probe
from reconcile import reconcile
here=Path(__file__).resolve().parent
results=json.loads((here/'results.json').read_text())
contexts=json.loads((here/'context_changes.json').read_text())
failed=False
for fn,row in results.items():
    d=(probe.ROOT/row['draft']).read_text()
    if row['retained']:
        changes=contexts[fn]
    else:
        d,changes=reconcile(fn,d)
    result=probe.check(fn,d,changes)
    ok=result is not None and list(result)==row['new']
    print(fn,result,'OK' if ok else 'FAIL',flush=True)
    failed|=not ok
raise SystemExit(failed)
