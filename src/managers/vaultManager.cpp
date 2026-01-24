#include "vaultManager.h"
#include "general_utils.h"
#include "encryption.h"
#include "json.hpp"

using json = nlohmann::json;

#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

VaultManager::VaultManager(const std::string& username, const std::string& rootPath)
    : masterUsername(username), vaultRootPath(rootPath)
{
    ensureDir(vaultRootPath);
    ensureDir(vaultRootPath + "/objects");
    ensureDir(vaultRootPath + "/temp");

    loadVaultIndex();
}

/* ---------- Utility helpers ---------- */

std::string VaultManager::generateFileId() const {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }

    static const char charset[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::string id;
    for (int i = 0; i < 12; ++i)
        id += charset[std::rand() % (sizeof(charset) - 1)];

    return id;
}

std::string VaultManager::currentTimestamp() const {
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(t, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

VaultFile* VaultManager::findFileById(const std::string& id) {
    for (auto& f : files)
        if (f.id == id)
            return &f;
    return nullptr;
}

VaultFile* VaultManager::findFileByName(const std::string& name) {
    for (auto& f : files)
        if (toLower(f.originalName) == toLower(name))
            return &f;
    return nullptr;
}

/* ---------- Index handling ---------- */

void VaultManager::loadVaultIndex() {
    files.clear();

    std::string indexPath = vaultRootPath + "/vault_index.json";
    if (!fs::exists(indexPath))
        return;

    std::ifstream in(indexPath);
    json j;
    in >> j;

    for (const auto& item : j) {
        VaultFile vf;
        vf.id = item["id"];
        vf.originalName = item["originalName"];
        vf.createdAt = item["createdAt"];
        vf.location = (item["location"] == "objects")
                          ? FileLocation::Objects
                          : FileLocation::Temp;

        files.push_back(vf);
    }
}

void VaultManager::saveVaultIndex() {
    json j = json::array();

    for (const auto& f : files) {
        j.push_back({
            {"id", f.id},
            {"originalName", f.originalName},
            {"createdAt", f.createdAt},
            {"location", f.location == FileLocation::Objects ? "objects" : "temp"}
        });
    }

    std::ofstream out(vaultRootPath + "/vault_index.json");
    out << j.dump(4);
}

void VaultManager::saveFileMetadata(const VaultFile& f) {
    std::string base =
        vaultRootPath +
        (f.location == FileLocation::Objects ? "/objects/" : "/temp/") +
        f.id;

    ensureDir(base);

    json meta;
    meta["id"] = f.id;
    meta["originalName"] = f.originalName;
    meta["createdAt"] = f.createdAt;

    std::ofstream out(base + "/metadata.json");
    out << meta.dump(4);
}

/* ---------- Core actions ---------- */

bool VaultManager::importAndEncryptFile(const std::string& sourcePath, const std::string& displayName) {
    if (!fs::exists(sourcePath))
        return false;

    VaultFile f;
    f.id = generateFileId();
    f.originalName = displayName;
    f.createdAt = currentTimestamp();
    f.location = FileLocation::Objects;

    std::string destDir = vaultRootPath + "/objects/" + f.id;
    ensureDir(destDir);

    std::string encryptedPath = destDir + "/data.enc";

    // 🔐 XOR encrypt directly using file paths
    if (!xorEncryptFile(sourcePath, encryptedPath, masterUsername))
        return false;

    saveFileMetadata(f);
    files.push_back(f);
    saveVaultIndex();

    return true;
}

bool VaultManager::decryptFile(const std::string& fileId,
                               const std::string& outputPath)
{
    VaultFile* f = findFileById(fileId);
    if (!f || f->location != FileLocation::Objects)
        return false;

    std::string src =
        vaultRootPath + "/objects/" + f->id + "/data.enc";

    if (!fs::exists(src))
        return false;

    fs::path outPath(outputPath);

    bool treatAsDirectory =
        fs::exists(outPath)
            ? fs::is_directory(outPath)
            : !outPath.has_extension();

    std::string finalOutputPath;

    if (treatAsDirectory) {
        ensureDir(outPath.string());
        finalOutputPath = (outPath / f->originalName).string();
    } else {
        finalOutputPath = outPath.string();
        if (outPath.has_parent_path())
            ensureDir(outPath.parent_path().string());
    }

    return xorDecryptFile(src, finalOutputPath, masterUsername);
}

void VaultManager::listFiles() const {
    if (files.empty()) {
        std::cout << "Vault is empty.\n";
        return;
    }

    for (const auto& f : files) {
        std::cout << "- ID: " << f.id
                  << " | Name: " << f.originalName
                  << " | Stored: "
                  << (f.location == FileLocation::Objects ? "objects" : "temp")
                  << "\n";
    }
}

bool VaultManager::deleteFile(const std::string& fileId) {
    VaultFile* f = findFileById(fileId);
    if (!f || f->location == FileLocation::Temp)
        return false;

    std::string from = vaultRootPath + "/objects/" + f->id;
    std::string to   = vaultRootPath + "/temp/" + f->id;

    fs::rename(from, to);
    f->location = FileLocation::Temp;

    saveVaultIndex();
    return true;
}

bool VaultManager::recoverFile(const std::string& fileId) {
    VaultFile* f = findFileById(fileId);
    if (!f || f->location == FileLocation::Objects)
        return false;

    std::string from = vaultRootPath + "/temp/" + f->id;
    std::string to   = vaultRootPath + "/objects/" + f->id;

    fs::rename(from, to);
    f->location = FileLocation::Objects;

    saveVaultIndex();
    return true;
}

bool VaultManager::purgeFile(const std::string& fileId) {
    for (auto it = files.begin(); it != files.end(); ++it) {
        if (it->id == fileId) {
            std::string dir =
                vaultRootPath +
                (it->location == FileLocation::Objects ? "/objects/" : "/temp/") +
                it->id;

            fs::remove_all(dir);
            files.erase(it);
            saveVaultIndex();
            return true;
        }
    }
    return false;
}

/* ---------- Info ---------- */

const std::string& VaultManager::getMasterUsername() const {
    return masterUsername;
}