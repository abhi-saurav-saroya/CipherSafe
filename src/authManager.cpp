#include "authManager.h"
#include "general_utils.h"
#include "crypto_utils.h"

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
            return verifyPassword(master_key, M.salt, M.hashedMasterKey, PASSWORD_HASH_ITERATIONS);
    }
    return false;
}

void AuthManager::loadFromFile(){
    std::cout << "Functionality under development" << std::endl;
}

void AuthManager::saveToFile(){
    std::cout << "Functionality under development" << std::endl;
}
