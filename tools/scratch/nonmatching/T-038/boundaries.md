# Boot translation unit boundaries

49 boundaries follow an original inventory body end, 1–3 zero words and a 16-byte-aligned function start, using the definite-alignment criterion in docs/tu_boundaries.md. This is not proof of historical source provenance. The additional SDK boundary before handwritten bzero at ROM 0x3780 follows a 64-byte zero gap after osSetThreadPri; it is not a 1–3-word alignment candidate. The entry remains hasm at 0x1000–0x1050. ROM offsets below are physical cartridge offsets.

| Next ROM offset | Preceding function | Zero words |
|---|---|---:|
| 0x12B0 | func_800005EC | 3 |
| 0x1500 | boot_dma_chunked | 1 |
| 0x1560 | boot_inflate | 2 |
| 0x29F0 | func_80001D10 | 3 |
| 0x3190 | func_80002420 | 2 |
| 0x3510 | osCreateThread | 3 |
| 0x3780 | osSetThreadPri | 16 |
| 0x3820 | bzero | 1 |
| 0x38A0 | osInvalICache | 3 |
| 0x3950 | osInvalDCache | 1 |
| 0x3AD0 | osCreatePiManager | 1 |
| 0x3B00 | osCreateMesgQueue | 1 |
| 0x3C10 | osPiStartDma | 3 |
| 0x3D50 | osRecvMesg | 2 |
| 0x3DF0 | strchr | 3 |
| 0x4150 | viMgrMain | 3 |
| 0x41C0 | osSetEventMesg | 2 |
| 0x4230 | osViSetEvent | 1 |
| 0x4510 | osSpTaskStartGo | 1 |
| 0x4660 | osSendMesg | 1 |
| 0x4860 | osDpSetNextBuffer | 2 |
| 0x48D0 | osViSetMode | 2 |
| 0x48F0 | __osGetSR | 1 |
| 0x49A0 | __osSiRawWriteIo | 1 |
| 0x5290 | osWritebackDCache | 3 |
| 0x52F0 | osMapTLBRdb | 2 |
| 0x5350 | osPiRawReadIo | 3 |
| 0x5650 | __osRestoreInt | 1 |
| 0x5770 | osGetThreadPri | 2 |
| 0x59D0 | __osDevMgrMain | 3 |
| 0x5B50 | osPiGetCmdQueue | 2 |
| 0x6080 | __osViInit | 3 |
| 0x6090 | __osViGetCurrentContext | 1 |
| 0x63F0 | __osViSwapContext | 1 |
| 0x6400 | osGetCount | 1 |
| 0x6410 | __osSpSetStatus | 1 |
| 0x6720 | bcopy | 3 |
| 0x67A0 | osVirtualToPhysical | 1 |
| 0x67E0 | __osSpSetPc | 3 |
| 0x6870 | __osSpRawStartDma | 1 |
| 0x68A0 | __osSpDeviceBusy | 1 |
| 0x68B0 | __osSpGetStatus | 1 |
| 0x68E0 | __osDpDeviceBusy | 1 |
| 0x6910 | __osSiDeviceBusy | 1 |
| 0x6D90 | kdebugserver | 3 |
| 0x6EC0 | __osSyncPutChars | 3 |
| 0x7020 | osDestroyThread | 2 |
| 0x7030 | __osSetCompare | 1 |
| 0x70F0 | __osProbeTLB | 2 |
| 0x7100 | __osGetCause | 1 |
