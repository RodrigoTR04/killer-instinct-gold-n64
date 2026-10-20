#include "boot.h"

extern void osCreateViManager(s32);
extern void osSetEventMesg(s32, void *, s32);
extern void osViSetEvent(void *, s32, u8);
extern void osSpTaskLoad(u8 *), osSpTaskStartGo(u8 *);
extern s32 osViGetCurrentFramebuffer(void), osViGetNextFramebuffer(void);
/* This boot copy passes the byte count as an o32 64-bit argument (a2/a3). */
extern s32 osDpSetNextBuffer(s32, u64);
extern void osSpTaskYield(void), osViSwapBuffer(s32);
extern u32 osSpTaskYielded(u8 *);
extern s32 osSendMesg(s32, void *, s32);
extern s32 boot_next_framebuffer;
extern s32 D_8000666C, D_80006670, D_80006674;
extern s32 D_8000C3A0, boot_graphics_queue, boot_audio_queue, boot_scheduler_queue;
extern s32 D_8000CF98, D_8000CFA8, D_8000CFB8, D_8000CFD0;
extern u8 D_8000CFCC, boot_retrace_subscriber_count;
extern u8 boot_audio_running, boot_graphics_state, boot_dp_state;
extern u8 boot_graphics_sp_active, boot_swap_ready, boot_graphics_resume_count;
extern s32 boot_retrace_subscribers[];

/* Main installs the resident retrace/SP/DP scheduler after decompression. */
void boot_init_scheduler(void) {
    D_8000CFCC = 1;
    osCreateViManager(0xFE);
    osCreateMesgQueue(&boot_graphics_queue, &D_8000CF98, 3);
    osCreateMesgQueue(&boot_audio_queue, &D_8000CFA8, 3);
    osCreateMesgQueue(&boot_scheduler_queue, &D_8000CFB8, 5);
    osSetEventMesg(9, &boot_scheduler_queue, D_80006670);
    osSetEventMesg(4, &boot_scheduler_queue, D_80006674);
    osViSetEvent(&boot_scheduler_queue, D_8000666C, D_8000CFCC);
    boot_retrace_subscriber_count = 0;
    osCreateThread(&D_8000CFD0, 0x14, boot_scheduler_thread, 0, &D_8000C3A0, 0xD);
    osStartThread(&D_8000CFD0);
}

void boot_subscribe_retrace(void *unused, void *queue) {
    if ((s32) boot_retrace_subscriber_count < 3) {
        boot_retrace_subscribers[boot_retrace_subscriber_count++] = (s32)queue;
    }
}

/* Graphics states: 0 idle, 1 running, 2 framebuffer wait,
 * 3 yield requested, 4 yielded, 5 dequeued. DP: 0 idle, 1 active, 2 waiting. */
void boot_scheduler_thread(s32 unused) {
    s32 initial_message;
    u8 *event;
    s16 retrace_message[16];
    s32 *subscriber;
    s32 subscriber_index;

    boot_audio_running = 0;
    boot_graphics_state = 0;
    boot_dp_state = 0;
    boot_swap_ready = 1;
    event = (u8 *)&initial_message;
    boot_graphics_sp_active = 0;
    retrace_message[0] = 1;
    while(1) {
        osRecvMesg(&boot_scheduler_queue, &event, 1);
        /* 0: VI retrace, 1: DP completion, 2: SP completion. */
        switch (*event) {
        case 0:
            if (boot_audio_running == 0) {
                if (osRecvMesg(&boot_audio_queue, &boot_audio_task, 0) == 0) {
                    if (boot_graphics_sp_active != 0) {
                        osSpTaskYield();
                        boot_graphics_state = 3;
                    } else {
                        osSpTaskLoad(boot_audio_task->task);
                        osSpTaskStartGo(boot_audio_task->task);
                        boot_audio_running = 1;
                        if (boot_swap_ready == 1) {
                            boot_schedule_graphics();
                        }
                    }
                } else if ((boot_graphics_state == 0) || (boot_dp_state == 2)) {
                    boot_schedule_graphics();
                } else {
                    boot_start_graphics_task();
                }
            }
            subscriber_index = 0, subscriber = boot_retrace_subscribers;
            if ((s32) boot_retrace_subscriber_count > 0) {
                do {
                    osSendMesg(*subscriber, retrace_message, 0);
                    subscriber_index += 1;
                    subscriber += 1;
                } while (subscriber_index < (s32) boot_retrace_subscriber_count);
            }
            break;
        case 2:
            if (boot_graphics_state == 3) {
                if (osSpTaskYielded(boot_graphics_task->task) == 1) {
                    osSpTaskLoad(boot_audio_task->task);
                    osSpTaskStartGo(boot_audio_task->task);
                    boot_audio_running = 1;
                    boot_graphics_state = 4;
                } else {
                    boot_graphics_state = 1;
                    osSpTaskLoad(boot_audio_task->task);
                    osSpTaskStartGo(boot_audio_task->task);
                    boot_audio_running = 1;
                    boot_graphics_sp_active = 0;
                }
            } else if (boot_audio_running != 0) {
                osSendMesg(boot_audio_task->completion_queue, boot_audio_task->completion_message, 1);
                boot_audio_running = 0;
                if (boot_dp_state == 0) {
                    boot_start_graphics_task();
                }
            } else {
                boot_graphics_sp_active = 0;
                if (boot_swap_ready == 1) {
                    osViSwapBuffer(boot_next_framebuffer = boot_graphics_task->framebuffer);
                    boot_graphics_state = 0;
                    osSendMesg(boot_graphics_task->completion_queue, boot_graphics_task->completion_message, 1);
                }
            }
            break;
        case 1:
            if (boot_dp_state == 1) {
                boot_dp_state = 0;
                if (boot_audio_running == 0) {
                    boot_start_graphics_task();
                }
                continue;
            }
            boot_swap_ready = 1;
            if (boot_graphics_sp_active != 0) {
                continue;
            }
            osViSwapBuffer(boot_next_framebuffer = boot_graphics_task->framebuffer);
            boot_graphics_state = 0;
            osSendMesg(boot_graphics_task->completion_queue, boot_graphics_task->completion_message, 1);
            break;
        }
        continue;
    }
}

void boot_start_graphics_task(void) {
    if (boot_graphics_state == 4) {
        osSpTaskLoad(boot_graphics_task->task);
        osSpTaskStartGo(boot_graphics_task->task);
        boot_graphics_state = 1;
        boot_graphics_resume_count += 1;
        return;
    }
    if (boot_graphics_state == 2) {
        osSpTaskLoad(boot_graphics_task->task);
        osSpTaskStartGo(boot_graphics_task->task);
        boot_graphics_sp_active = 1;
        boot_swap_ready = 0;
        boot_graphics_resume_count = 0;
        boot_graphics_state = 1;
        return;
    }
    if ((boot_graphics_state == 5) && (boot_graphics_task != 0)) {
        if ((osViGetCurrentFramebuffer() != boot_graphics_task->framebuffer) && (osViGetNextFramebuffer() != boot_graphics_task->framebuffer)) {
            osSpTaskLoad(boot_graphics_task->task);
            osSpTaskStartGo(boot_graphics_task->task);
            boot_graphics_sp_active = 1;
            boot_swap_ready = 0;
            boot_graphics_resume_count = 0;
            boot_graphics_state = 1;
            return;
        }
        boot_graphics_state = 2;
    }
}

void boot_schedule_graphics(void) {
    if ((boot_graphics_state == 0) || (boot_graphics_state == 5)) {
        if (boot_dp_state == 2) {
            if ((osViGetCurrentFramebuffer() != boot_graphics_task->framebuffer) && (osViGetNextFramebuffer() != boot_graphics_task->framebuffer) && (osDpSetNextBuffer(boot_graphics_task->dp_buffer, (u32)boot_graphics_task->dp_size) != -1)) {
                boot_dp_state = 1;
            }
        } else if ((boot_graphics_state == 0) && (osRecvMesg(&boot_graphics_queue, &boot_graphics_task, 0) == 0)) {
            boot_graphics_state = 5;
            if (boot_graphics_task->dp_buffer != 0) {
                if ((osViGetCurrentFramebuffer() != boot_graphics_task->framebuffer) && (osViGetNextFramebuffer() != boot_graphics_task->framebuffer)) {
                    if (osDpSetNextBuffer(boot_graphics_task->dp_buffer, (u32)boot_graphics_task->dp_size) != -1) {
                        boot_dp_state = 1;
                    }
                } else {
                    boot_dp_state = 2;
                }
            } else if (boot_audio_running == 0) {
                boot_start_graphics_task();
            }
        }
    }
}
