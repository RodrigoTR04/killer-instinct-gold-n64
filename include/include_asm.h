#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H
/* IDO sources are processed by asm-processor before compilation. */
#ifndef _LANGUAGE_C
#define INCLUDE_ASM(path, name) __asm__(".include \"" path "/" #name ".s\"")
#endif
#endif
