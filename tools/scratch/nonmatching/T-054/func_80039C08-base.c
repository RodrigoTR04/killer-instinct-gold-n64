
/* DRAFT. Remaining diff: 160 differing instruction words; emitted 608 / original 648 bytes (positional comparison). */
typedef struct T026AudioClient { struct T026AudioClient *next; s32 pad; s32 (*handler)(void *); s32 pad1; s32 samples; } T026AudioClient;
typedef struct T026AudioBus { s32 pad; u32 *(*pull)(void *, s16 *, s32, s32, u32 *); void (*param)(void *, s32, s32); } T026AudioBus;
typedef struct { T026AudioClient *clients; u8 pad[0x18]; s32 nextTime, time; u8 pad1[0x14]; T026AudioBus *bus; u8 pad2[8]; s32 rate, maxSamples; } T026Synth;
extern T026Synth *D_80048440;
extern f64 D_80049348;
extern void _collectPVoices(void *);
u32 *func_80039C08(u32 *commands, s32 *commandCount, s32 output, s32 samples) {
    T026Synth *synth = D_80048440;
    T026AudioClient *client, *earliest = 0;
    u32 *out = commands;
    s16 count = 0;
    s32 distance = 0x7FFFFFFF;
    if (synth->clients == 0) { *commandCount = 0; return commands; }
    for (client = synth->clients; client != 0; client = client->next) {
        if (client->samples - synth->time < distance) { earliest = client; distance = client->samples - synth->time; }
    }
    synth->nextTime = earliest->samples;
    while (synth->nextTime - synth->time < samples) {
        synth->nextTime &= ~15;
        earliest->samples += (s32)(f32)(((f64)((f32)earliest->handler(earliest) * (f32)synth->rate) / D_80049348) + 0.5);
        earliest = 0; distance = 0x7FFFFFFF;
        for (client = synth->clients; client != 0; client = client->next) {
            if (client->samples - synth->time < distance) { earliest = client; distance = client->samples - synth->time; }
        }
        synth->nextTime = earliest->samples;
    }
    while (samples > 0) {
        s32 n = samples;
        T026AudioBus *bus;
        if (synth->maxSamples < samples) n = synth->maxSamples;
        out[0] = 0x07000000; out[1] = 0;
        bus = synth->bus;
        bus->param(bus, 6, output);
        samples -= n;
        out = bus->pull(bus, &count, n, synth->time, out+2);
        output += n*4;
        synth->time += n;
    }
    *commandCount = ((u8 *)out-(u8 *)commands) >> 3;
    _collectPVoices(synth);
    return out;
}
