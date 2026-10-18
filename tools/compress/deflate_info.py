#!/usr/bin/env python3
"""Inspect raw DEFLATE blocks, code lengths and LZ tokens (stdlib only)."""
import argparse
import json
from pathlib import Path


class Bits:
    def __init__(self, data):
        self.data, self.pos = data, 0

    def read(self, n):
        value = 0
        for i in range(n):
            value |= ((self.data[self.pos // 8] >> (self.pos % 8)) & 1) << i
            self.pos += 1
        return value


def tree(lengths):
    counts = [lengths.count(i) for i in range(16)]
    counts[0] = 0
    code, table = 0, {}
    for size in range(1, 16):
        code = (code + counts[size - 1]) << 1
        next_code = code
        for symbol, length in enumerate(lengths):
            if length == size:
                table[size, next_code] = symbol
                next_code += 1
    return table


def symbol(bits, table):
    code = 0
    for size in range(1, 16):
        code = (code << 1) | bits.read(1)
        if (size, code) in table:
            return table[size, code]
    raise ValueError('invalid Huffman code')


LBASE = [3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258]
LEXTRA = [0]*8 + [1]*4 + [2]*4 + [3]*4 + [4]*4 + [5]*4 + [0]
DBASE = [1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577]
DEXTRA = [0]*4 + [i for i in range(1,14) for _ in range(2)]


def inspect(data):
    bits, output, blocks = Bits(data), 0, []
    while True:
        start, out_start = bits.pos, output
        final, kind = bits.read(1), bits.read(2)
        literals = matches = 0
        lengths = distances = []
        if kind == 0:
            bits.pos = (bits.pos + 7) & ~7
            length, inverse = bits.read(16), bits.read(16)
            assert length ^ inverse == 65535
            bits.pos += length * 8
            output += length
        elif kind in (1, 2):
            if kind == 1:
                lengths = [8]*144 + [9]*112 + [7]*24 + [8]*8
                distances = [5]*32
            else:
                nl, nd, nc = bits.read(5)+257, bits.read(5)+1, bits.read(4)+4
                order = [16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15]
                cl = [0]*19
                for i in range(nc):
                    cl[order[i]] = bits.read(3)
                codes, all_lengths = tree(cl), []
                while len(all_lengths) < nl+nd:
                    s = symbol(bits, codes)
                    if s < 16:
                        all_lengths.append(s)
                    else:
                        repeat = bits.read({16:2,17:3,18:7}[s]) + {16:3,17:3,18:11}[s]
                        all_lengths.extend([all_lengths[-1] if s == 16 else 0]*repeat)
                lengths, distances = all_lengths[:nl], all_lengths[nl:]
            lt, dt = tree(lengths), tree(distances)
            while True:
                s = symbol(bits, lt)
                if s == 256:
                    break
                if s < 256:
                    literals += 1
                    output += 1
                else:
                    i = s-257
                    length = LBASE[i] + bits.read(LEXTRA[i])
                    ds = symbol(bits, dt)
                    distance = DBASE[ds] + bits.read(DEXTRA[ds])
                    assert distance <= output
                    output += length
                    matches += 1
        else:
            raise ValueError('reserved block')
        blocks.append(dict(start_bit=start, end_bit=bits.pos, final=final, type=kind,
                           expanded_start=out_start, expanded_end=output,
                           literals=literals, matches=matches, tokens=literals+matches,
                           literal_code_lengths=lengths, distance_code_lengths=distances))
        if final:
            return blocks


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('raw_deflate', type=Path)
    args = parser.parse_args()
    print(json.dumps(inspect(args.raw_deflate.read_bytes()), indent=2))
