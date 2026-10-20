from attempts import *
p=Path('src/main/main_2FF0.c');s=p.read_text()
a=(ROOT/'func_80016910-inline_divisor_0.c').read_text()
for name,lit in [('D_80048838','3.14159'),('D_80048840','180.0'),('D_80048848','3.14159'),('D_80048850','180.0')]:
 a=re.sub(r'\b'+name+r'\b','('+lit+')',a[a.index('void func_80016910'):]) if False else a
 # Keep declarations intact for standalone diagnostic, substitute body only.
 head,body=a.split('void func_80016910',1);body=re.sub(r'\b'+name+r'\b',lit,body);a=head+'void func_80016910'+body
assert probe(a,'func_80016910')['words']==0
# Install only its function body and needed new extern declarations, retaining TU declarations.
a=a[a.index('void func_80016910'):].replace('    f32 x;\n','')
b=(ROOT/'func_8001B620-stage_address_expression.c').read_text();b=b[b.index('void func_8001B620'):]
# Local declarations coexist with the old non-prototype function used by existing callers.
for fn,body,decl in [('func_80016910',a,'''extern f32 sinf(f32), cosf(f32);
extern void func_8002DBDC(f32, f32 *), func_8002DC48(f32 *);
extern u32 func_800326F0(void);
extern f32 D_8004A988, D_8004A98C, D_8004A990, D_8004A994;
extern s16 D_8004A986;
extern f32 D_80061CC8[], D_80061CD0;
extern u8 D_801D3430;
'''),('func_8001B620',b,'''extern f32 D_800695CC;
''')]:
 pragma=next(line for line in s.splitlines() if line.startswith('#pragma') and '/'+fn+'.s"' in line)
 s=s.replace(pragma,decl+'\n'+body)
p.write_text(s)
p=Path('symbol_addrs.main.us.txt');s=p.read_text().replace('function_owner:func_8001B620','function_owner:func_8001B134');p.write_text(s)
