#include "pch.h"
#include "crypt.h"
#include "type.h"
extern "C"
{
#include "sha256.h"
}
namespace Crypt
{
    void CalcHash(const std::string& src,std::string& dst)
    {
        if (src.empty()) return;
        SHA256_CTX ctx;
        byte hash[SHA256_BLOCK_SIZE];

        sha256_init(&ctx);
        sha256_update(&ctx, (byte*)src.c_str(), src.size());
        sha256_final(&ctx, hash);
        std::stringstream hstream;
        for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        {
            hstream << std::hex << std::setfill('0') << (int)hash[i];
        }
        dst = hstream.str();
    }
}