#include "pch.h"
#include "crypt.h"
#include "type.h"
#include <windows.h>

namespace Crypt
{
    void CalcHash(const std::string& src, std::string& dst)
    {
        if (src.empty()) return;
        HCRYPTPROV prov; // crypt context
        HCRYPTHASH hash;
        
        byte buf[32]; // hash buffer
        DWORD len = sizeof(buf); // buff size

        if (!CryptAcquireContextA(&prov, 0, 0, PROV_RSA_AES, CRYPT_VERIFYCONTEXT) || !CryptCreateHash(prov, CALG_SHA_256, 0, 0, &hash))
        {
            Utils::DbgMsg("error CryptAcuqireContextA()");
            return;
        }
        if (!CryptHashData(hash, (byte*)src.c_str(), src.size(), 0) || !CryptGetHashParam(hash, HP_HASHVAL, buf, &len, 0))
        {
            Utils::DbgMsg("error CryptHashData()");

            CryptReleaseContext(prov, 0);
            CryptDestroyHash(hash);
            return;
        }

        char strHash[65];
        for (int i = 0; i < len; i++)
        {
            sprintf_s(strHash + i * 2, sizeof(strHash) - i * 2, "%02x", buf[i]); // print bytes to hex str representation
        }
        strHash[sizeof(strHash) - 1] = 0;

        dst = strHash;
        CryptDestroyHash(hash);
        CryptReleaseContext(prov, 0);

        Utils::DbgMsg("CalcHash() is ok");
    }
}