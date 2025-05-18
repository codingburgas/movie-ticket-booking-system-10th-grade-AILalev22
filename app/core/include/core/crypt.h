#pragma once
namespace Crypt
{
    // calculate a sha256 hash based on src
    void CalcHash(const std::string& src, std::string& dst);
}