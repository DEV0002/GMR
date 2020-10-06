#pragma once

#include <stdint.h>
#include <iostream>
#include "util/buffers.h"

namespace Opus
{
    class RangeDecoder
    {
    public:
        RangeDecoder(uint8_t *data, size_t length);

        uint32_t decodeUInt(uint32_t ft);
        uint16_t decodeSymbol(uint16_t f, uint16_t k, uint16_t n);

        uint32_t tell();
        uint32_t tellFrac();

    private:
        // Raw Bits
        uint8_t *data;
        size_t   length;
        uint32_t window, nend;

        // Symbol decoding
        uint32_t  val, rng;
        Bitstream buffer;

        // Functions
        void     normalize();
        uint32_t readRawBits(uint32_t bits);
    };
}    // namespace Opus