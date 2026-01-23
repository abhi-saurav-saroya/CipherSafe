#include "encryption.h"

#include <fstream>
#include <vector>
#include <iostream>

static bool xorProcessFile(const std::string& inputPath, const std::string& outputPath, const std::string& key) {
    if (key.empty()) {
        std::cerr << "[ENCRYPTION ERROR] Key cannot be empty.\n";
        return false;
    }

    std::ifstream inFile(inputPath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "[ENCRYPTION ERROR] Failed to open input file.\n";
        return false;
    }

    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "[ENCRYPTION ERROR] Failed to open output file.\n";
        return false;
    }

    const size_t keyLen = key.size();
    size_t keyIndex = 0;

    char byte;
    while (inFile.get(byte)) {
        byte ^= key[keyIndex];
        outFile.put(byte);

        keyIndex = (keyIndex + 1) % keyLen;
    }

    inFile.close();
    outFile.close();
    return true;
}

bool xorEncryptFile(const std::string& inputPath, const std::string& outputPath, const std::string& key) {
    return xorProcessFile(inputPath, outputPath, key);
}

bool xorDecryptFile(const std::string& inputPath,const std::string& outputPath,const std::string& key) {
    return xorProcessFile(inputPath, outputPath, key);
}
