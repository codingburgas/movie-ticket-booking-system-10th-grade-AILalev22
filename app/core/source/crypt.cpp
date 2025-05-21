#include "pch.h"
#include "crypt.h"
#include "type.h"

namespace Crypt
{
    void Close(const HCRYPTPROV& prov,const HCRYPTHASH& hash)
    {
        CryptReleaseContext(prov, 0);
        CryptDestroyHash(hash);
    }
    void CalcHash(const std::string& src, std::string& dst)
    {
        if (src.empty()) return;
        HCRYPTPROV prov; //crypt context
        HCRYPTHASH hash;
        
        byte buf[32]; // hash buffer
        DWORD len = sizeof(buf); // buff sz

        if (!CryptAcquireContextA(&prov, 0, 0, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
        {
            DbgMsg("error CryptAcuqireContextA()");
            return;
        }
        if (!CryptCreateHash(prov, CALG_SHA_256, 0, 0, &hash))
        {
            DbgMsg("error CryptCreateHash()");
            return;
        }
        if (!CryptHashData(hash, (byte*)src.c_str(), src.size(), 0))
        {
            DbgMsg("error CryptHashData()");

            Close(prov, hash);
            return;
        }
        if (!CryptGetHashParam(hash, HP_HASHVAL, buf, &len, 0))
        {
            DbgMsg("error CryptGetHashParam()");
            Close(prov, hash);
            return;
        }
        char strHash[65];
        for (DWORD i = 0; i < len; i++)
        {
            sprintf_s(strHash + i * 2, sizeof(strHash) - i * 2, "%02x", buf[i]); // print bytes to hex str representation
        }
        strHash[sizeof(strHash) - 1] = 0;

        dst = strHash;
        Close(prov, hash);
    }
}