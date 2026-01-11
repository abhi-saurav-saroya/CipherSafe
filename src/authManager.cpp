#include "authManager.h"

#include <fstream>
#include <string>
#include <iostream>
#include <limits>

bool AuthManager::masterExists(const std::string& master_username) const {
    std::cout << "Functionality under development" << std::endl;
    return false;
}

bool AuthManager::createMaster(const std::string& master_username, const std::string& master_key){
    std::cout << "Functionality under development" << std::endl;
    return false;
}

bool AuthManager::authenticateMaster(const std::string& master_username, const std::string& master_password){
    std::cout << "Functionality under development" << std::endl;
    return false;
}

void AuthManager::loadFromFile(){
    std::cout << "Functionality under development" << std::endl;
}

void AuthManager::saveToFile(){
    std::cout << "Functionality under development" << std::endl;
}
