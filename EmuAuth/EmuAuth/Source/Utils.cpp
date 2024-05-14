#include "Global.h"

std::string Utils::GenerateHMAC(const std::string& key, const std::string& message)
{
    std::stringstream result;

#define SHA256_HASH_SIZE 32
    std::vector<uint8_t> out(SHA256_HASH_SIZE);

    hmac_sha256(key.data(), key.size(), message.data(), message.size(), out.data(), out.size());

    for (uint8_t x : out)
        result << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(x);

    return result.str();
}