"""Parallel measure of variant bodies against a function. usage: import and call sweep()"""
import importlib.util, sys, tempfile, concurrent.futures as cf, os
from pathlib import Path
ROOT=Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-a52eff74')
spec=importlib.util.spec_from_file_location('screen',ROOT/'tools/permuter/screen.py')
screen=importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
def measure(fn,text,tag):
    d=Path('/tmp/msweep'); d.mkdir(exist_ok=True)
    p=d/f'{fn}_{tag}.c'; p.write_text(text)
    try:
        r=screen.measure(fn,p)
        return r['words'] if not r['error'] else 9999, r['compiled']
    except Exception as e:
        return 9999,0
def sweep(fn,variants,jobs=6):
    out={}
    with cf.ThreadPoolExecutor(jobs) as ex:
        futs={ex.submit(measure,fn,t,k):k for k,t in variants.items()}
        for f in cf.as_completed(futs): out[futs[f]]=f.result()
    return out
