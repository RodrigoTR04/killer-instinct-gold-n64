/* Minimal US SDK declarations/macros from pinned SM64; T-080.
 * Isolated from the game headers. See docs/libultra_rebuild.md. */
#ifndef KIG_SDK_LIBULTRA_H
#define KIG_SDK_LIBULTRA_H
float sinf(float);

float cosf(float);

float sqrtf(float);
typedef signed char s8;

typedef unsigned char u8;

typedef unsigned short int u16;

typedef signed int s32;

typedef unsigned int u32;

typedef unsigned long long int u64;

typedef volatile u32 vu32;

typedef float f32;

typedef u32 size_t;

typedef u32 uintptr_t;

typedef u32 OSIntMask;

void osInitialize(void);

u32 osGetCount(void);

uintptr_t osVirtualToPhysical(void *);

typedef s32 OSPri;

typedef s32 OSId;

typedef union
{
    struct {f32 f_odd; f32 f_even;} f;
} __OSfp;

typedef struct
{
              u64 at, v0, v1, a0, a1, a2, a3;
              u64 t0, t1, t2, t3, t4, t5, t6, t7;
              u64 s0, s1, s2, s3, s4, s5, s6, s7;
              u64 t8, t9, gp, sp, s8, ra;
              u64 lo, hi;
              u32 sr, pc, cause, badvaddr, rcp;
              u32 fpcsr;
    __OSfp fp0, fp2, fp4, fp6, fp8, fp10, fp12, fp14;
    __OSfp fp16, fp18, fp20, fp22, fp24, fp26, fp28, fp30;
} __OSThreadContext;

typedef struct
{
    u32 flag;
    u32 count;
    u64 time;
} __OSThreadprofile_s;

typedef struct OSThread_s
{
             struct OSThread_s *next;
             OSPri priority;
             struct OSThread_s **queue;
             struct OSThread_s *tlnext;
             u16 state;
             u16 flags;
             OSId id;
             int fp;
             __OSThreadprofile_s *thprof;
             __OSThreadContext context;
} OSThread;

void osCreateThread(OSThread *thread, OSId id, void (*entry)(void *),
    void *arg, void *sp, OSPri pri);

OSPri osGetThreadPri(OSThread *thread);

void osSetThreadPri(OSThread *thread, OSPri pri);

void osStartThread(OSThread *thread);

typedef u32 OSEvent;

typedef void * OSMesg;

typedef struct OSMesgQueue_s {
 OSThread *mtqueue;
 OSThread *fullqueue;
 s32 validCount;
 s32 first;
 s32 msgCount;
 OSMesg *msg;
} OSMesgQueue;

extern void osCreateMesgQueue(OSMesgQueue *, OSMesg *, s32);

extern s32 osSendMesg(OSMesgQueue *, OSMesg, s32);

extern s32 osJamMesg(OSMesgQueue *, OSMesg, s32);

extern s32 osRecvMesg(OSMesgQueue *, OSMesg *, s32);

extern void osSetEventMesg(OSEvent, OSMesgQueue *, OSMesg);

typedef struct OSTimer_str
{
    struct OSTimer_str *next;
    struct OSTimer_str *prev;
    u64 interval;
    u64 remaining;
    OSMesgQueue *mq;
    OSMesg msg;
} OSTimer;

typedef u64 OSTime;

OSTime osGetTime(void);

u32 osSetTimer(OSTimer *, OSTime, OSTime, OSMesgQueue *, OSMesg);

typedef struct
{
             u32 type;
             u32 flags;
             u64 *ucode_boot;
             u32 ucode_boot_size;
             u64 *ucode;
             u32 ucode_size;
             u64 *ucode_data;
             u32 ucode_data_size;
             u64 *dram_stack;
             u32 dram_stack_size;
             u64 *output_buff;
             u64 *output_buff_size;
             u64 *data_ptr;
             u32 data_size;
             u64 *yield_data_ptr;
             u32 yield_data_size;
} OSTask_t;

typedef union {
    OSTask_t t;
    long long int force_structure_alignment;
} OSTask;

typedef u32 OSYieldResult;

void osSpTaskLoad(OSTask *task);

void osSpTaskStartGo(OSTask *task);

void osSpTaskYield(void);

OSYieldResult osSpTaskYielded(OSTask *task);

extern void osInvalDCache(void *, size_t);

extern void osInvalICache(void *, size_t);

extern void osWritebackDCache(void *, size_t);

typedef struct {
    u32 ctrl;
    u32 width;
    u32 burst;
    u32 vSync;
    u32 hSync;
    u32 leap;
    u32 hStart;
    u32 xScale;
    u32 vCurrent;
} OSViCommonRegs;

typedef struct {
    u32 origin;
    u32 yScale;
    u32 vStart;
    u32 vBurst;
    u32 vIntr;
} OSViFieldRegs;

typedef struct {
    u8 type;
    OSViCommonRegs comRegs;
    OSViFieldRegs fldRegs[2];
} OSViMode;

typedef struct {
               u16 unk00;
               u16 retraceCount;
               void* buffer;
               OSViMode *modep;
               u32 features;
               OSMesgQueue *mq;
               OSMesg *msg;
               u32 unk18;
               u32 unk1c;
               u32 unk20;
               f32 unk24;
               u16 unk28;
               u32 unk2c;
} OSViContext;

void osCreateViManager(OSPri pri);

void osViSetMode(OSViMode *mode);

void osViSetEvent(OSMesgQueue *mq, OSMesg msg, u32 retraceCount);

void osViBlack(u8 active);

void osViSetSpecialFeatures(u32 func);

void osViSwapBuffer(void *vaddr);

typedef struct {
    u32 errStatus;
    void *dramAddr;
    void *C2Addr;
    u32 sectorSize;
    u32 C1ErrNum;
    u32 C1ErrSector[4];
} __OSBlockInfo;

typedef struct {
    u32 cmdType;
    u16 transferMode;
    u16 blockNum;
    s32 sectorNum;
    uintptr_t devAddr;
    u32 bmCtlShadow;
    u32 seqCtlShadow;
    __OSBlockInfo block[2];
} __OSTranxInfo;

typedef struct OSPiHandle_s {
    struct OSPiHandle_s *next;
    u8 type;
    u8 latency;
    u8 pageSize;
    u8 relDuration;
    u8 pulse;
    u8 domain;
    u32 baseAddress;
    u32 speed;
    __OSTranxInfo transferInfo;
} OSPiHandle;

typedef struct {
    u16 type;
    u8 pri;
    u8 status;
    OSMesgQueue *retQueue;
} OSIoMesgHdr;

typedef struct {
             OSIoMesgHdr hdr;
             void *dramAddr;
             uintptr_t devAddr;
             size_t size;
} OSIoMesg;

s32 osPiStartDma(OSIoMesg *mb, s32 priority, s32 direction, uintptr_t devAddr, void *vAddr,
                 size_t nbytes, OSMesgQueue *mq);

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt);

OSMesgQueue *osPiGetCmdQueue(void);

s32 osPiRawStartDma(s32 dir, u32 cart_addr, void *dram_addr, size_t size);

extern void bcopy(const void *, void *, size_t);

extern void bzero(void *, size_t);

extern u32 osTvType;

extern u32 osRomBase;

extern u32 osResetType;

extern u8 osAppNmiBuffer[64];

typedef struct {
 u16 type;
 u8 status;
 u8 errnum;
}OSContStatus;

typedef struct {
 u16 button;
 s8 stick_x;
 s8 stick_y;
 u8 errnum;
} OSContPad;

extern s32 osContInit(OSMesgQueue *, u8 *, OSContStatus *);

extern s32 osContStartReadData(OSMesgQueue *);

extern void osContGetReadData(OSContPad *);

extern s32 osEepromProbe(OSMesgQueue *);

extern s32 osEepromRead(OSMesgQueue *, u8, u8 *);

extern s32 osEepromWrite(OSMesgQueue *, u8, u8 *);

extern s32 osEepromLongRead(OSMesgQueue *, u8, u8 *, int);

extern s32 osEepromLongWrite(OSMesgQueue *, u8, u8 *, int);

extern s32 osAiSetNextBuffer(void *, u32);

typedef struct {
        s32 active;
    OSThread *thread;
        OSMesgQueue *cmdQueue;
        OSMesgQueue *evtQueue;
        OSMesgQueue *acsQueue;
        s32 (*dma)(s32, u32, void *, u32);
        s32 (*edma)(OSPiHandle *, s32, u32, void *, u32);
} OSDevMgr;

extern u64 osClockRate;

extern OSViMode osViModePalLan1;

extern OSViMode osViModeMpalLan1;

extern void osCreateThread(OSThread *, OSId, void (*)(void *),
                       void *, void *, OSPri);

extern void osDestroyThread(OSThread *);

extern void osStartThread(OSThread *);

extern void osSetThreadPri(OSThread *, OSPri);

extern OSPri osGetThreadPri(OSThread *);

extern void osMapTLBRdb(void);

extern u32 osVirtualToPhysical(void *);

extern s32 osPiRawReadIo(u32, u32 *);

extern s32 osPiRawStartDma(s32, u32, void *, u32);

extern s32 osPiStartDma(OSIoMesg *, s32, s32, u32, void *, u32,
                     OSMesgQueue *);

extern void osCreatePiManager(OSPri, OSMesgQueue *, OSMesg *, s32);

extern void osViSetSpecialFeatures(u32);

extern void osViSetMode(OSViMode *);

extern void osViSetEvent(OSMesgQueue *, OSMesg, u32);

extern void osViSwapBuffer(void *);

extern void osViBlack(u8);

extern void osCreateViManager(OSPri);

extern OSTime osGetTime(void);

extern u32 osSetTimer(OSTimer *, OSTime, OSTime,
                   OSMesgQueue *, OSMesg);

extern void osInitialize(void);

extern u32 osGetCount(void);

typedef s32 Mtx_t[4][4];

typedef union { Mtx_t m; long long int force_structure_alignment; } Mtx;

typedef struct { unsigned char col[3]; char pad1; unsigned char colc[3]; char pad2; signed char dir[3]; char pad3; } Light_t;

typedef union { Light_t l; long long int force_structure_alignment[2]; } Light;

typedef struct { Light l[2]; } LookAt;

extern OSThread *__osThreadTail;

extern u32 D_80334894;

extern OSThread *__osRunQueue;

extern OSThread *__osActiveQueue;

extern OSThread *__osRunningThread;

typedef struct {
    u32 initialized;
    OSThread *mgrThread;
    OSMesgQueue *cmdQueue;
    OSMesgQueue *eventQueue;
    OSMesgQueue *accessQueue;
    s32 (*dma_func)(s32, u32, void *, size_t);
    u64 force_align;
} OSMgrArgs;

s32 __osDisableInt(void);

void __osRestoreInt(s32);

void __osEnqueueAndYield(OSThread **);

void __osDequeueThread(OSThread **, OSThread *);

void __osEnqueueThread(OSThread **, OSThread *);

OSThread *__osPopThread(OSThread **);

s32 __osSiRawStartDma(s32, void *);

void __osSiCreateAccessQueue(void);

void __osSiGetAccess(void);

void __osSiRelAccess(void);

u32 __osProbeTLB(void *);

void __osPiCreateAccessQueue(void);

void __osPiGetAccess(void);

void __osSetSR(u32);

u32 __osGetSR(void);

void __osSetFpcCsr(u32);

s32 __osSiRawReadIo(u32, u32 *);

s32 __osSiRawWriteIo(u32, u32);

s32 osPiRawReadIo(u32, u32 *);

void __osSpSetStatus(u32);

u32 __osSpGetStatus(void);

s32 __osSpSetPc(void *);

s32 __osSpDeviceBusy(void);

s32 __osSiDeviceBusy(void);

s32 __osSpRawStartDma(u32 dir, void *sp_ptr, void *dram_ptr, size_t size);

void __osViInit(void);

OSViContext *__osViGetCurrentContext(void);

void __osViSwapContext(void);

void __osSetTimerIntr(u64);

u64 __osInsertTimer(OSTimer *);

void __osSetCompare(u32);

s32 __osAiDeviceBusy(void);

void __osDispatchThread(void);

u32 __osGetCause(void);

s32 __osAtomicDec(u32 *);

extern OSDevMgr __osPiDevMgr;

void __osDevMgrMain(void *);

void __osPiRelAccess(void);

typedef struct __OSEventState
{
    OSMesgQueue *messageQueue;
    OSMesg message;
} __OSEventState;

extern void __osEnqueueAndYield(OSThread **);

extern void __osDequeueThread(OSThread **, OSThread *);

extern void __osEnqueueThread(OSThread **, OSThread *);

extern OSThread *__osPopThread(OSThread **);

extern void __osDispatchThread(void);

extern void __osSetTimerIntr(OSTime);

extern OSTime __osInsertTimer(OSTimer *);

extern void __osTimerInterrupt(void);

extern u32 __osProbeTLB(void *);

extern int __osSpDeviceBusy(void);

extern OSThread *__osFaultedThread;

extern OSTimer *__osTimerList;

extern OSTimer __osBaseTimer;

extern OSTime __osCurrentTime;

extern u32 __osBaseCounter;

extern u32 __osViIntrCount;

extern u32 __osTimerCounter;

extern __OSEventState __osEventStateTab[15];

extern u32 osViClock;

extern u32 __osShutdown;

extern void __osTimerServicesInit(void);

extern s32 __osAiDeviceBusy(void);

typedef struct {
 unsigned type : 2;
    unsigned pad : 4;
 unsigned length : 2;
 unsigned char buf[3];
} rdbPacket;

extern unsigned int __osRdbWriteOK;

extern unsigned int __osRdbSendMessage;

extern u32 __osBbEepromSize;

extern u32 __osBbIsBb;

void *memcpy(void *dst, const void *src, size_t size);

size_t strlen(const char *str);

char *strchr(const char *str, s32 ch);

typedef struct
{
    u8 padOrEnd;
    u8 txLen;
    u8 rxLen;
    u8 command;
    u16 button;
    s8 rawStickX;
    s8 rawStickY;
} OSContPackedRead;

typedef struct
{
    u8 padOrEnd;
    u8 txLen;
    u8 rxLen;
    u8 command;
    u8 data1;
    u8 data2;
    u8 data3;
    u8 data4;
} OSContPackedRequest;

typedef struct {
               u32 ramarray[15];
               u32 pifstatus;
} OSPifRam;

typedef struct {
              u8 dummy;
              u8 txsize;
              u8 rxsize;
              u8 cmd;
              u8 typeh;
              u8 typel;
              u8 status;
              u8 dummy1;
} __OSContRequesFormat;

typedef struct {
              u8 txsize;
              u8 rxsize;
              u8 cmd;
              u8 address;
              u8 data[8];
} __OSContEepromFormat;

extern s32 __osEepStatus(OSMesgQueue *, OSContStatus *);

void __osContGetInitData(u8 *pattern, OSContStatus *data);

void __osPackRequestData(u8 cmd);

u8 __osContAddressCrc(u16 addr);

u8 __osContDataCrc(u8 *data);

extern u8 __osContLastCmd;

extern OSTimer __osEepromTimer;

extern OSMesg __osEepromTimerMsg[4];

extern OSMesgQueue __osEepromTimerQ;

extern OSPifRam __osEepPifRam;

extern OSPifRam __osContPifRam;

extern u8 __osMaxControllers;

void guPerspectiveF(float mf[4][4], u16 *perspNorm, float fovy, float aspect,
                    float near, float far, float scale);

void guPerspective(Mtx *m, u16 *perspNorm, float fovy, float aspect, float near,
                   float far, float scale);

void guOrtho(Mtx *m, float left, float right, float bottom, float top,
             float near, float far, float scale);

void guTranslate(Mtx *m, float x, float y, float z);

void guRotate(Mtx *m, float a, float x, float y, float z);

void guScale(Mtx *m, float x, float y, float z);

void guMtxF2L(float mf[4][4], Mtx *m);

void guMtxIdent(Mtx *m);

void guMtxIdentF(float mf[4][4]);

void guMtxL2F(float mf[4][4], Mtx *m);

void guNormalize(float *, float *, float *);

void guLookAtReflect (Mtx *m, LookAt *l, float xEye, float yEye, float zEye,
                    float xAt, float yAt, float zAt,
                    float xUp, float yUp, float zUp);

#define ALIGNED8
#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define UNUSED
#define FORCE_BSS
#define EEPROM_TYPE_16K 0x02
#define OS_VI_GAMMA_DITHER_ON 0x0004
#define OS_MESG_PRI_HIGH 1
#define OS_EVENT_COUNTER 3
#define TRUE 1
#define OS_VI_DITHER_FILTER_OFF 0x0080
#define CHNL_ERR(format) ((format.rxsize & CHNL_ERR_MASK) >> 4)
#define VI_V_SYNC_REG (VI_BASE_REG+0x18)
#define IS_KSEG0(x) ((u32)(x) >= K0BASE && (u32)(x) < K1BASE)
#define PI_RD_LEN_REG (PI_BASE_REG+0x08)
#define IS_KSEG1(x) ((u32)(x) >= K1BASE && (u32)(x) < K2BASE)
#define VI_ORIGIN_REG (VI_BASE_REG+0x04)
#define SPSTATUS_CLEAR_SSTEP 0x00000020
#define CONT_CMD_WRITE_EEPROM_TX 10
#define MQ_GET_COUNT(mq) ((mq)->validCount)
#define MAXCONTROLLERS 4
#define VI_MPAL_CLOCK 48628316
#define GU_PI 3.1415926
#define VI_PAL_CLOCK 49656530
#define MQ_IS_FULL(mq) (MQ_GET_COUNT(mq) >= (mq)->msgCount)
#define RCP_IMASKSHIFT 16
#define PI_BSD_DOM1_RLS_REG (PI_BASE_REG+0x20)
#define EEPROM_TYPE_4K 0x01
#define AI_DRAM_ADDR_REG (AI_BASE_REG+0x00)
#define PI_BSD_DOM1_LAT_REG (PI_BASE_REG+0x14)
#define XUT_VEC (K0BASE+0x80)
#define PI_BSD_DOM2_PWD_REG (PI_BASE_REG+0x28)
#define SP_WR_LEN_REG (SP_BASE_REG+0x0C)
#define VI_CURRENT_REG (VI_BASE_REG+0x10)
#define CONT_EEPROM_BUSY 0x80
#define PI_BSD_DOM2_PGS_REG (PI_BASE_REG+0x2C)
#define VI_H_START_REG (VI_BASE_REG+0x24)
#define VI_INTR_REG (VI_BASE_REG+0x0C)
#define AI_DACRATE_REG (AI_BASE_REG+0x10)
#define PIF_RAM_END 0x1FC007FF
#define E_VEC (K0BASE+0x180)
#define OS_VI_DIVOT_ON 0x0010
#define VI_NTSC_CLOCK 48681812
#define TV_TYPE_MPAL 2
#define OS_VI_DITHER_FILTER 0x10000
#define RCP_IMASK 0x003f0000
#define OS_CLOCK_RATE 62500000LL
#define SP_IMEM_START 0x04001000
#define AI_LEN_REG (AI_BASE_REG+0x04)
#define OS_VI_GAMMA_ON 0x0001
#define CONT_CMD_NOP 0xff
#define FPCSR_FS 0x01000000
#define AI_STATUS_FIFO_FULL 0x80000000
#define SP_PC_REG 0x04080000
#define DEVICE_TYPE_INIT 7
#define VI_V_START_REG (VI_BASE_REG+0x28)
#define SPSTATUS_DMA_FULL 0x0008
#define PI_STATUS_DMA_BUSY 0x01
#define K1_TO_PHYS(x) ((u32)(x)&0x1FFFFFFF)
#define SI_STATUS_REG (SI_BASE_REG+0x18)
#define LEO_STATUS (LEO_BASE_REG + 0x508)
#define RDB_READ_INTR_REG (RDB_BASE_REG + 0xc)
#define CONT_CMD_WRITE_EEPROM_RX 1
#define TV_TYPE_PAL 0
#define VI_STATE_BLACK 0x20
#define SPSTATUS_SET_INTR_ON_BREAK 0x00000100
#define ECC_VEC (K0BASE+0x100)
#define SI_STATUS_RD_BUSY 0x0002
#define VI_X_SCALE_REG (VI_BASE_REG+0x30)
#define WAIT_ON_IO_BUSY(stat) stat = IO_READ(PI_STATUS_REG); while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) stat = IO_READ(PI_STATUS_REG);
#define EEPROM_BLOCK_SIZE 8
#define OS_VI_GAMMA_OFF 0x0002
#define M_TASK_FLAG0 1
#define M_TASK_FLAG1 2
#define PI_STATUS_CLR_INTR 0x02
#define VI_Y_SCALE_REG (VI_BASE_REG+0x34)
#define OS_IM_ALL 0x003fff01
#define UT_VEC K0BASE
#define CONT_CMD_REQUEST_STATUS_RX 3
#define CONT_CMD_REQUEST_STATUS_TX 1
#define CONT_CMD_REQUEST_STATUS 0
#define OS_VI_GAMMA_DITHER 0x04
#define CONT_CMD_READ_BUTTON 1
#define SP_RD_LEN_REG (SP_BASE_REG+0x08)
#define RDB_BASE_REG 0xc0000000
#define OS_READ 0
#define PI_BSD_DOM1_PWD_REG (PI_BASE_REG+0x18)
#define SPSTATUS_CLEAR_HALT 0x00000001
#define RESET_TYPE_COLD_RESET 0
#define SI_DRAM_ADDR_REG (SI_BASE_REG+0x00)
#define PI_MISC_REG (PI_BASE_REG+0x60)
#define VI_BURST_REG (VI_BASE_REG+0x14)
#define SPSTATUS_SIGNAL1_SET 0x0100
#define MI_BASE_REG 0x04300000
#define SI_PIF_ADDR_RD64B_REG (SI_BASE_REG+0x04)
#define OS_NUM_EVENTS 15
#define CONT_EEPROM 0x8000
#define IO_WRITE(addr,data) (*(vu32 *)PHYS_TO_K1(addr)=(u32)(data))
#define CONT_CMD_WRITE_EEPROM 5
#define VI_V_CURRENT_LINE_REG VI_CURRENT_REG
#define K0BASE 0x80000000
#define SPSTATUS_SET_SIGNAL0 0x00000400
#define OS_WRITE 1
#define CHNL_ERR_MASK 0xC0
#define SPSTATUS_SIGNAL0_SET 0x0080
#define VI_LEAP_REG (VI_BASE_REG+0x20)
#define OS_MESG_BLOCK 1
#define AI_BITRATE_REG (AI_BASE_REG+0x14)
#define IO_READ(addr) (*(vu32 *)PHYS_TO_K1(addr))
#define PI_DRAM_ADDR_REG (PI_BASE_REG+0x00)
#define OS_MESG_NOBLOCK 0
#define SP_DRAM_ADDR_REG (SP_BASE_REG+0x04)
#define PI_STATUS_REG (PI_BASE_REG+0x10)
#define OS_VI_DIVOT 0x10
#define CONT_CMD_RESET 0xff
#define SPSTATUS_CLEAR_SIGNAL0 0x00000200
#define SPSTATUS_CLEAR_SIGNAL1 0x00000800
#define SPSTATUS_CLEAR_SIGNAL2 0x00002000
#define LEO_STATUS_PRESENCE_MASK 0xFFFF
#define SPSTATUS_CLEAR_BROKE 0x00000004
#define OS_VI_DITHER_FILTER_ON 0x0040
#define DEVICE_TYPE_CART 0
#define SI_STATUS_DMA_BUSY 0x0001
#define CAUSE_IP6 0x00002000
#define OS_STATE_WAITING 8
#define VI_STATUS_REG (VI_BASE_REG+0x00)
#define MI_HW_INTR_MASK_REG (MI_BASE_REG+0x3C)
#define PI_BASE_REG 0x04600000
#define CONT_CMD_END 0xfe
#define PI_CART_ADDR_REG (PI_BASE_REG+0x04)
#define FPCSR_EV 0x00000800
#define NULL (void *)0
#define OS_EVENT_PRENMI 14
#define AI_CONTROL_REG (AI_BASE_REG+0x08)
#define VI_CONTROL_REG VI_STATUS_REG
#define SI_PIF_ADDR_WR64B_REG (SI_BASE_REG+0x10)
#define OS_STATE_STOPPED 1
#define CONT_NO_RESPONSE_ERROR 0x8
#define OS_VI_UNK100 0x100
#define FALSE 0
#define TV_TYPE_NTSC 1
#define OS_VI_GAMMA 0x08
#define PI_BSD_DOM1_PGS_REG (PI_BASE_REG+0x1C)
#define AI_BASE_REG 0x04500000
#define OS_IM_PI 0x00100401
#define PI_WR_LEN_REG (PI_BASE_REG+0x0C)
#define SP_STATUS_REG (SP_BASE_REG+0x10)
#define SPSTATUS_IO_FULL 0x0010
#define SI_BASE_REG 0x04800000
#define CONT_CMD_EXE 1
#define OS_VI_GAMMA_DITHER_OFF 0x0008
#define SP_BASE_REG 0x04040000
#define SR_CU1 0x20000000
#define PI_STATUS_IO_BUSY 0x02
#define K2BASE 0xC0000000
#define VI_V_BURST_REG (VI_BASE_REG+0x2C)
#define AI_STATUS_REG (AI_BASE_REG+0x0C)
#define K0_TO_PHYS(x) ((u32)(x)&0x1FFFFFFF)
#define LEO_BASE_REG 0x05000000
#define PI_BSD_DOM2_LAT_REG (PI_BASE_REG+0x24)
#define OS_STATE_RUNNABLE 2
#define PHYS_TO_K1(x) ((u32)(x)|0xA0000000)
#define OS_VI_DIVOT_OFF 0x0020
#define CONT_CMD_READ_EEPROM_RX 8
#define VI_WIDTH_REG (VI_BASE_REG+0x08)
#define CONT_CMD_READ_EEPROM_TX 2
#define CONT_CMD_READ_EEPROM 4
#define OS_EVENT_PI 8
#define EEPROM_MAXBLOCKS 64
#define SR_EXL 0x00000002
#define K1BASE 0xA0000000
#define SPSTATUS_HALT 0x0001
#define OS_EVENT_VI 7
#define OS_IM_CPU 0x0000ff01
#define SP_MEM_ADDR_REG (SP_BASE_REG+0x00)
#define VI_BASE_REG 0x04400000
#define SPSTATUS_DMA_BUSY 0x0004
#define PI_BSD_DOM2_RLS_REG (PI_BASE_REG+0x30)
#define VI_H_SYNC_REG (VI_BASE_REG+0x1C)
#define OS_VI_UNK200 0x200
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
