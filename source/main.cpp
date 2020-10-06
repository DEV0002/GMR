#include <iostream>
#include "util/buffers.h"

int main()
{
    std::cout << "Hello World!" << std::endl;
    uint8_t   arr[2] = { 0xAA, 0xAA };
    Bitstream stream(arr, 2 * 8);
    printf("1: ");
    std::cout << stream.readBits(4);
    printf("\n2: ");
    std::cout << stream.readBits(8);
    printf("\n3: ");
    std::cout << stream.readBits(4);
    return 0;
}