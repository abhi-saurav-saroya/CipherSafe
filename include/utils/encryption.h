#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

static bool xorProcessFile(const std::string& inputPath, const std::string& outputPath, const std::string& key);
bool xorEncryptFile(const std::string& inputPath, const std::string& outputPath, const std::string& key);
bool xorDecryptFile(const std::string& inputPath, const std::string& outputPath, const std::string& key);

#endif
