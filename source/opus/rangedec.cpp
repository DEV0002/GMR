#include "rangedec.h"

#include "fastmath.h"
#include "assert.h"
#include "util/buffers.h"

namespace Opus
{
    RangeDecoder::RangeDecoder(uint8_t *data, size_t length) : buffer(data, length * 8), data(data)
    {
        rng = 128;
        val = 127 - this->buffer.readBits(7);
        normalize();
    }

    // Decoding functions
    uint32_t RangeDecoder::decodeUInt(uint32_t ft)
    {
        uint16_t ftb = ilog2(ft - 1);
        uint16_t temp;
        if (ftb <= 8)
        {
            ftb -= 8;
            temp = ((ft - 1) >> ftb) + 1;
        }
        else
            temp = ft;
        uint16_t t = temp - min((uint16_t)(val / (rng / temp) + 1), temp);
        decodeSymbol(t, t + 1, temp);

        // Read raw bits if needed
        if (ilog2(ft - 1) > 8) t = (t << ftb) | readRawBits(ftb);

        if (t >= ft) std::cerr << "RANGE::DEC::UINT::ERROR\n";
        return t;
    }

    uint16_t RangeDecoder::decodeSymbol(uint16_t fl, uint16_t fh, uint16_t ft)
    {
        uint16_t fs = ft - min((uint16_t)(val / (rng / ft) + 1), ft);
        assert(fl <= fs && fs < fh);

        // Update State
        val -= (rng / ft) * (ft - fh);
        if (fl > 0)
            rng = (rng / ft) * (fh - fl);
        else
            rng -= (rng / ft) * (ft - fh);

        normalize();
        return fs;
    }

    uint32_t RangeDecoder::tell() { return nend - ilog2(rng); }

    // Shamelessly pulled from the Reference implementation cause I do not understand what RFC is
    // telling me
    uint32_t RangeDecoder::tellFrac()
    {
        uint32_t correction[8] = { 35733, 38967, 42495, 46340, 50535, 55109, 60097, 65535 };
        uint32_t nbits, r, b;
        int      l;
        nbits = nend << 3;
        l     = ilog2(rng);
        r     = rng >> (l - 16);
        b     = (r >> 12) - 8;
        b += r > correction[b];
        l = (l << 3) + b;
        return nbits - l;
    }

    // Private functions
    uint32_t RangeDecoder::readRawBits(uint32_t bits)
    {
        uint32_t read      = window;
        uint32_t avaliable = nend;
        do
        {
            read |= *(data + length - (avaliable / 8) - 1) << avaliable;
            avaliable += 8;
        } while (avaliable <= sizeof(uint32_t) * 8 - 8);
        uint32_t t = read & (((uint32_t) 1 << bits) - 1U);

        // Update Private Variables
        read >>= bits;
        avaliable -= bits;
        nend   = avaliable;
        window = read;

        return t;
    }

    void RangeDecoder::normalize()
    {
        while (rng <= 8388608)
        {
            nend += 8;
            rng <<= 8;
            val = ((val << 8) + (255 - buffer.readBits(8))) & 0x7FFFFFFF;
        }
    }

}    // namespace Opus