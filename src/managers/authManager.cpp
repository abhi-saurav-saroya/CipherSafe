#include "authManager.h"
#include "authUI.h"
#include "general_utils.h"
#include "crypto_utils.h"
#include "json.hpp"
using json = nlohmann::json;

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <limits>

bool AuthManager::masterExists(const std::string& master_username) const {
    for (const auto& M : Masters) {
        if (toLower(M.masterUsername) == toLower(master_username))
            return true;
    }
    return false;
}

bool AuthManager::createMaster(const std::string& master_username, const std::string& master_key){
    if(masterExists(master_username))
        return false;

    MasterUser m;
    m.masterUsername = master_username;
    m.salt = generateSalt(16);
    m.hashedMasterKey = hashPassword(master_key, m.salt, PASSWORD_HASH_ITERATIONS);
    Masters.push_back(m);
    return true;
}

bool AuthManager::authenticateMaster(const std::string& master_username, const std::string& master_key){
    for (const auto& M : Masters) {
        if (toLower(M.masterUsername) == toLower(master_username))
            loggedIn = true;
            currentMasterUsername = M.masterUsername;

            return verifyPassword(master_key, M.salt, M.hashedMasterKey, PASSWORD_HASH_ITERATIONS);
    }
    return false;
}

void AuthManager::loadFromFile() {
    Masters.clear();

    std::ifstream indexFile("data/masters/index.json");
    if (!indexFile.is_open()) {
        // First run: no users exist
        return;
    }

    json index;
    indexFile >> index;
    indexFile.close();

    if (!index.contains("masters") || !index["masters"].is_array())
        return;

    for (const auto& usernameJson : index["masters"]) {
        std::string username = usernameJson.get<std::string>();
        std::string authPath = "data/masters/" + username + "/auth.json";

        std::ifstream authFile(authPath);
        if (!authFile.is_open())
            continue; // corrupted user, skip safely

        json auth;
        authFile >> auth;
        authFile.close();

        MasterUser M;
        M.masterUsername = auth["username"].get<std::string>();
        M.salt = auth["salt"].get<std::string>();
        M.hashedMasterKey = auth["password_hash"].get<std::string>();

        Masters.push_back(M);
    }
}

void AuthManager::saveToFile() {
    if(Masters.empty())
        return;

    ensureDir("data");
    ensureDir("data/masters");

    /* ---------- index.json ---------- */
    json index;
    index["masters"] = json::array();

    for (const auto& M : Masters) {
        index["masters"].push_back(M.masterUsername);
    }

    std::ofstream indexFile("data/masters/index.json");
    indexFile << index.dump(4);
    indexFile.close();

    /* ---------- per-user auth.json ---------- */
    for (const auto& M : Masters) {
        std::string basePath = "data/masters/" + M.masterUsername;

        ensureDir(basePath);
        ensureDir(basePath + "/vault");

        json auth;
        auth["username"] = M.masterUsername;
        auth["salt"] = M.salt;
        auth["password_hash"] = M.hashedMasterKey;

        std::ofstream authFile(basePath + "/auth.json");
        authFile << auth.dump(4);
        authFile.close();
    }
}

bool AuthManager::isLoggedIn() const {
    return loggedIn;
}

std::string AuthManager::getCurrentMasterUsername() const {
    return currentMasterUsername;
}

void AuthManager::logout() {
    saveToFile();
    currentMasterUsername.clear();
    loggedIn = false;
}
