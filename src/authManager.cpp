#include "authManager.h"
#include "general_utils.h"

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
    m.masterKey = master_key;
    Masters.push_back(m);
    return true;
}

bool AuthManager::authenticateMaster(const std::string& master_username, const std::string& master_key){
    for (const auto& M : Masters) {
        if (toLower(M.masterUsername) == toLower(master_username) && M.masterKey == master_key)
            return true;
    }
    return false;
}

void AuthManager::loadFromFile(){
    std::cout << "Functionality under development" << std::endl;
}

void AuthManager::saveToFile(){
    std::cout << "Functionality under development" << std::endl;
}
