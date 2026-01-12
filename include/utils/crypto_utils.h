#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <string>

std::string sha256(const std::string& input);
std::string generateSalt(size_t length = 16);
std::string hashPassword(const std::string& password, const std::string& salt, int iterations = 100000);
bool verifyPassword(const std::string& password, const std::string& salt, const std::string& storedHash, int iterations = 100000);

#endif
