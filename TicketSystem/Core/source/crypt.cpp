#include "crypt.h"
extern "C"
{
#include "sha256.h"
}
#include "memory.h"
#include "string.hpp"
namespace Crypt
{
    char* CalcHash(const void* src)
    {
        return CalcHash((void*)src);
    }
    char* CalcHash(void* src)
    {
        if (!src) return 0;
        SHA256_CTX ctx;
        byte hash[SHA256_BLOCK_SIZE];

        sha256_init(&ctx);
        sha256_update(&ctx, (byte*)src, Str::Len((char*)src));
        sha256_final(&ctx, hash);

        return HashToStr(hash);
    }
    char* HashToStr(byte* hash)
    {
        char* ret = (char*)Mem::Alloc(2 * SHA256_BLOCK_SIZE + 1);
        int j = 0;
        for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        {
            char hex[2];
            ByteToHex(hash[i], hex);
            ret[j++] = hex[0];
            ret[j++] = hex[1];
        }
        ret[j] = 0;
        return ret;
    }
    void ByteToHex(char by, char* hex)
    {
        hex[0] = ToHex((by >> 4) & 0xf);
        hex[1] = ToHex(by & 0xf);
    }
    char ToHex(int n)
    {
        if (n >= 0 && n <= 9) return n + '0';
        return 'a' + n - 10;
    }
}