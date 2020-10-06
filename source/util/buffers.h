#pragma once

#include "stdint.h"

class Bitstream
{
private:
    uint8_t *buffer, offset;
    size_t   index, bitLength;

public:
    Bitstream(uint8_t *buffer, uint8_t bitLength);

    uint32_t readBits(uint8_t bits);
};