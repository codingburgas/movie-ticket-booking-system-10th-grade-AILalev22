#pragma once
#include "type.h"
namespace Crypt
{
    // convert nibble to hex
    char ToHex(int n);
    // convert a byte into two hexes stored in hex
    void ByteToHex(char by, char* hex);
    // convert a hash of 32 bytes into a 65 byte str
    char* HashToStr(byte* hash);
    // calculate a hash based on a str
	char* CalcHash(void* src);
}