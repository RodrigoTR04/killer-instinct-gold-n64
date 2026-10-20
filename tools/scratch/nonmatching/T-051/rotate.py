from probe import *
import itertools
s=Path('tools/scratch/nonmatching/T-033/func_80015450.c').read_text();pre=s[:s.index('void func_80015450')];rows=[];best=(68,s)
for valtype,cache,reload,initial in itertools.product(['s32','u8'],[0,1],[0,1],[0,1]):
 body='''void func_80015450(s32 arg0) {
 T033RotatingObject *obj;
 T033Rotation *rotation;
 VALTYPE value;
 obj=D_801D3430;
 do {
  value=obj->kind;
  if(value==0x3B) {
   rotation=&((T033Rotation *)&D_8004A9D8)[obj->index];
   rotation->yaw = rotation->yaw + obj->speed / 50.0;
   RELOAD
   while(rotation->yaw >= 360.0f) {
    rotation->yaw -= 360.0f;
    LOOPRELOAD
   }
   value=obj->active;
   if(value != 0 && rotation->pitch < 90.0f) rotation->pitch+=2.0f;
   if(obj->active != 0) {
    if(arg0 > obj->x) obj->x=arg0;
    else if(obj->x > arg0) obj->x-=128;
   }
  }
  obj++;
 }while(obj!=D_801D5C30);
}
'''.replace('VALTYPE',valtype).replace('RELOAD','rotation=&((T033Rotation *)&D_8004A9D8)[obj->index];' if reload else '').replace('LOOP' + ('rotation=&((T033Rotation *)&D_8004A9D8)[obj->index];' if reload else ''),'rotation=&((T033Rotation *)&D_8004A9D8)[obj->index];' if cache else '')
 # Restore original order for the x comparison
 body=body.replace('if(arg0 > obj->x) obj->x=arg0;\n    else if(obj->x > arg0) obj->x-=128;', 'if(arg0 < obj->x) obj->x-=128;\n    else if(obj->x < arg0) obj->x=arg0;')
 if initial:body=body.replace('rotation->yaw = rotation->yaw + obj->speed / 50.0;', '((T033Rotation *)&D_8004A9D8)[obj->index].yaw = ((T033Rotation *)&D_8004A9D8)[obj->index].yaw + obj->speed / 50.0;')
 v=pre+body;r=probe(v,'func_80015450','rotate%d'%len(rows));rows.append(r)
 if r.get('words',999)<best[0]:best=(r['words'],v);print('best',len(rows),r)
(ROOT/'rotate.json').write_text(json.dumps(rows,indent=2)+'\n');(ROOT/'15450-best.c').write_text(best[1])
