#include "general_utils.h"

#include <string>
#include <cctype>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& ch : result) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return result;
}

void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


bool ensureDir(const std::string& path) {
    try {
        if (fs::exists(path))
            return true;

        return fs::create_directories(path);
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "[FS ERROR] " << e.what() << std::endl;
        return false;
    }
}