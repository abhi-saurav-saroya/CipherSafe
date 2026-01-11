#include "authUI.h"
#include "authManager.h"
#include "utils.h"

#include <iostream>
#include <limits>

AuthUI::AuthUI(AuthManager& manager)
    : authManager(manager) {}


void AuthUI::authManagerMenu() {
    while(true) {
        std::cout << std::endl;
        std::cout << "\t1. Sign Up.";
        std::cout << "\t2. Sign In.";
        std::cout << "\t3. Exit.";

        int authManagerMenuChoice;

        std::cin >> authManagerMenuChoice;

        if(!std::cin || authManagerMenuChoice < 1 || authManagerMenuChoice > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid option between 1 and 3." << std::endl;
            continue;
        }

        switch(authManagerMenuChoice) {
            case 1:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                newMasterSignUp();
                break;
            case 2:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                oldMasterSignIn();
                break;
            case 3:
                return;
        }
    }
}

void AuthUI::newMasterSignUp() {
    std::string master_username, master_key, master_key_confirm;
    std::cout << "Enter username (case-insensitive): ";
    getline(std::cin, master_username);

    if(authManager.masterExists(toLower(master_username))) {
        std::cout << "Master with this username already exists." << std::endl;
        std::cout << "Try signing up again. Returning to the main menu." << std::endl;
        return;
    }

    while(true) {
        std::cout << "Enter Master Key (8 characters length at minimum or 'quit' to return): ";
        getline(std::cin, master_key);
    
        if(toLower(master_key) == "quit") {
            std::cout << "Returning to the main menu." << std::endl;
            return;
        }

        if(master_key.length() < 8) {
            std::cout << "The length of the password cannot be less than eight characters." << std::endl;
            continue;
        }

        break;
    }

    while(true) {
        std::cout << "Confirm Master Key (or 'quit' to return): ";
        getline(std::cin, master_key_confirm);
    
        if(toLower(master_key_confirm) == "quit") {
            std::cout << "Returning to the main menu." << std::endl;
            return;
        }

        if(master_key != master_key_confirm) {
            std::cout << "The master keys didnt match." << std::endl;
            continue;
        }

        break;
    }

    authManager.createMaster(toLower(master_username), master_key);
}

void AuthUI::oldMasterSignIn(){
    std::string master_username, master_key;
    std::cout << "Enter username (case-insensitive): ";
    getline(std::cin, master_username);

    if(!authManager.masterExists(toLower(master_username))) {
        std::cout << "Master with this username does not exist." << std::endl;
        std::cout << "Try signing up first. Returning to the main menu." << std::endl;
        return;
    }

    while(true) {
        std::cout << "Enter Master Key (8 characters length at minimum or 'quit' to return): ";
        getline(std::cin, master_key);
    
        if(toLower(master_key) == "quit") {
            std::cout << "Returning to the main menu." << std::endl;
            return;
        }

        if(authManager.authenticateMaster(toLower(master_username), master_key)) {
            break;
        }
    }
}
