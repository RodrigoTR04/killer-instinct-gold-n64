/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

#ifdef VERSION_CN

char *main_strchr(const char *str, s32 ch) {
    char c = ch;
    while (*str != c) {
        if (*str == 0) {
            return NULL;
        }
        str++;
    }
    return (char *) str;
}

size_t main_strlen(const char *str) {
    const char *ptr = str;
    while (*ptr) {
        ptr++;
    }
    return ptr - str;
}

#endif

void *main_memcpy(void *dst, const void *src, size_t size) {
    u8 *_dst = dst;
    const u8 *_src = src;
    while (size > 0) {
        *_dst++ = *_src++;
        size--;
    }
    return dst;
}

#ifndef VERSION_CN

size_t main_strlen(const char *str) {
    const u8 *ptr = (const u8 *) str;
    while (*ptr) {
        ptr++;
    }
    return (const char *) ptr - str;
}

char *main_strchr(const char *str, s32 ch) {
    u8 c = ch;
    while (*(u8 *)str != c) {
        if (*(u8 *)str == 0) {
            return NULL;
        }
        str++;
    }
    return (char *) str;
}

#endif
