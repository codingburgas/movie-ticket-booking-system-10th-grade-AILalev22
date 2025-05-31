#pragma once
#define SALT_BYTES 16
namespace Crypt
{
    // calculate a sha256 hash
    // salt can be skipped by passing null for srcSalt and dwLenSalt
    void CalcHash(const std::string& src, byte srcSalt[], DWORD dwLenSalt, std::string& dst);

    // fill a buffer with random bytes
    void GenSalt(byte dst[], DWORD dwLen);

    void ByteToHex(const byte src[], DWORD dwLenSrc, std::string& hex);
    void HexToByte(const std::string& src, DWORD dwLenDst, byte dst[]);
}