#include "crypto_utils.h"

#include <sstream>
#include <iomanip>
#include <random>

std::string sha256(const std::string& input) {
    std::hash<std::string> hasher;
    size_t hash = hasher(input);

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

std::string generateSalt(size_t length) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(charset) - 2);

    std::string salt;
    for(size_t i = 0; i < length; ++i)
        salt += charset[dis(gen)];

    return salt;
}

std::string hashPassword( const std::string& password,const std::string& salt,int iterations) {
    std::string hash = password + salt;

    for(int i = 0; i < iterations; ++i) {
        hash = sha256(hash);
    }

    return hash;
}

bool verifyPassword(const std::string& password, const std::string& salt, const std::string& storedHash, int iterations) {
    return hashPassword(password, salt, iterations) == storedHash;
}
