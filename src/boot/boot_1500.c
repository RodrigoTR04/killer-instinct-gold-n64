#include "boot.h"

/* Rare's 0x1172 wrapper replaces the gzip header; the body is raw DEFLATE. */
s32 boot_inflate(u8 *source, u8 *destination, huft *scratch) {
    inflate_input = source;
    inflate_output = destination;
    inflate_huft_pool = scratch;
    inflate_input += 2;
    wp = 0;
    inflate_inptr = 0;
    inflate();
    return wp;
}
