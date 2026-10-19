/* DRAFT. Remaining diff: 20 differing words; 324/324 bytes */
extern float D_80048138;
extern float sinf(float),cosf(float);
extern void guMtxIdentF(void *);
void func_8002A004(float m[4][4],float x,float y,float z) { float sx,cx,sy,cy,sz,cz,a,b; x*=D_80048138; y*=D_80048138; z*=D_80048138; sx=sinf(x); cx=cosf(x); sy=sinf(y); cy=cosf(y); sz=sinf(z); cz=cosf(z); guMtxIdentF(m); a=sx*sy; m[1][2]=sx; m[0][0]=cy*cz-a*sz; m[0][1]=cy*sz+a*cz; m[0][2]=-sy*cx; b=sx*cy; m[1][0]=-cx*sz; m[1][1]=cx*cz; m[2][0]=sy*cz+b*sz; m[2][2]=cx*cy; m[2][1]=sy*sz-b*cz; }
