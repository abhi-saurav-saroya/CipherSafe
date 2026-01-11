#include "utils.h"

#include <string>
#include <cctype>
#include <filesystem>
namespace fs = std::filesystem;

std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& ch : result) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return result;
}

bool ensureDir(const std::string& s) {
    try {
        return fs::create_directories("data/" + s);
    } catch (const fs::filesystem_error&) {
        return false;
    }
}