/* DRAFT. Remaining diff: 2 differing words; 56/56 bytes */
typedef struct { u8 initialized; u8 pad[3]; void *used; void *buffer; } T024DmaState;
extern T024DmaState D_80068158;
extern u8 D_80067ED8[];
extern void func_8002B22C(void);
void (*func_8002B3A8(T024DmaState **state))(void) {
 if (!D_80068158.initialized) { D_80068158.used=0; D_80068158.buffer=D_80067ED8; D_80068158.initialized=1; }
 *state=&D_80068158; return func_8002B22C;
}
