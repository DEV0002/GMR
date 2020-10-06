#include "buffers.h"
#include "assert.h"
#include <iostream>

Bitstream::Bitstream(uint8_t *buffer, uint8_t bitLength) : buffer(buffer), bitLength(bitLength)
{
    index = offset = 0;
}

uint32_t Bitstream::readBits(uint8_t bits)
{
    assert(bits <= (sizeof(uint32_t) * 8));
    uint8_t noffset = (offset + bits);
    size_t  nindex  = index + (noffset >> 3);
    noffset &= 7;
    if ((nindex * 8 + noffset) > bitLength) return 0;
    bool increment = index != nindex && noffset != 0;

    // Read offset bits
    uint32_t read = *(buffer + index) >> offset;
    index++;
    if ((8 - offset) >= bits)
    {
        read >>= (8 - offset) - bits;
        index = nindex;
    }
    offset = noffset;

    // Read Bytes & remaining bits
    for (; index < nindex; index++) read = (read << 8) | *(buffer + index);
    if (increment) read |= (read << (8 - offset)) | *(buffer + index) >> offset;

    return read;
}