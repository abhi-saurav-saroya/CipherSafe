#include "authUI.h"
#include "authManager.h"
#include "general_utils.h"

#include <iostream>
#include <limits>

AuthUI::AuthUI(AuthManager& manager)
    : authManager(manager) {}


void AuthUI::authManagerMenu() {
    while(true) {
        std::cout << std::endl;
        std::cout << "\t1. Sign Up." << std::endl;
        std::cout << "\t2. Sign In." << std::endl;
        std::cout << "\t3. Exit." << std::endl;
        std::cout << "Enter the Choice: ";

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

    if(authManager.createMaster(toLower(master_username), master_key)) {
        std::cout << "New Master <" << master_username << "> created." << std::endl;
        std::cout << "Sign In now to get the access to dashboard." << std::endl;
        return;
    }

    std::cout << "Error creating new user. Returning to home page." << std::endl;
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
        std::cout << "Enter Master Key (or 'quit' to return): ";
        getline(std::cin, master_key);
    
        if(toLower(master_key) == "quit") {
            std::cout << "Returning to the main menu." << std::endl;
            return;
        }

        if(authManager.authenticateMaster(toLower(master_username), master_key)) {
            break;
        }
    }

    std::cout << "Signed In successfully." << std::endl;
}
