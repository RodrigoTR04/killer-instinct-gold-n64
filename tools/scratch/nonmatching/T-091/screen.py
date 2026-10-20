import pathlib,re,subprocess
root=pathlib.Path('.')
protected={'8002AA98','8002AAEC','80017378','8002F45C','8002A900','801BF720','801BF914','801C4E38','801B6528','801B695C','801C5064','801C7998','801C6A80','8002F6F4','80015F6C','8001E0B4','8002E4A0','8002A4F0','800121C8','8001256C'}
tus=['main_1BE80','main_1E7F0','main_1EB40','main_27490','main_2B780','ovl_7DF8_2380','ovl_7DF8_3F60','ovl_7DF8_5ED0','ovl_7DF8_116E0','ovl_7DF8_13FF0','ovl_7DF8_17E70','ovl_7DF8_1B790','ovl_7DF8_1BD90']
for tu in tus:
 im='main' if tu.startswith('main') else 'ovl_7DF8'
 for fn in re.findall(r'/(func_[0-9A-F]+)\.s',pathlib.Path(f'src/{im}/{tu}.c').read_text()):
  if fn[5:] in protected or fn.startswith('func_801B20'):continue
  drafts=list(root.glob(f'tools/scratch/nonmatching/*/{fn}.c'))
  if not drafts:continue
  draft=drafts[0]
  p=subprocess.run(['.venv/bin/python','tools/scratch/nonmatching/T-055/ctx.py',fn,str(draft)],capture_output=True,text=True)
  print(tu,draft, p.stdout.strip(),p.stderr.strip()[-300:],flush=True)
