#include "dashboardUI.h"
#include "authManager.h"
#include "vaultManager.h"
#include "general_utils.h"

#include <iostream>
#include <string>

DashboardUI::DashboardUI(AuthManager& authMgr, VaultManager& vaultMgr)
    : authManager(authMgr), vaultManager(vaultMgr) {}

void DashboardUI::dashboardMenu() {
    while(true) {
        std::cout << std::endl;
        std::cout << "\t1. Import and Encrypt new File." << std::endl;
        std::cout << "\t2. Decrypt a Locked File." << std::endl;
        std::cout << "\t3. List all Files." << std::endl;
        std::cout << "\t4. Delete a File." << std::endl;
        std::cout << "\t5. Recover a File." << std::endl;
        std::cout << "\t6. Delete a File Permanently." << std::endl;
        std::cout << "\t7. Log Out." << std::endl;
        std::cout << "Enter the Choice: ";

        int dashboardChoice;

        std::cin >> dashboardChoice;

        if(!std::cin || dashboardChoice < 1 || dashboardChoice > 7) {
            clearInput();
            std::cout << "Enter a valid option between 1 and 7." << std::endl;
            continue;
        }

        switch(dashboardChoice) {
            case 1:
                uploadFile();
                break;
            case 2:
                decryptFile();
                break;
            case 3:
                listFiles();
                break;
            case 4:
                deleteFile();
                break;
            case 5:
                recoverFile();
                break;
            case 6:
                deletePermanent();
                break;
            case 7:
                std::cout << "Logging out...\n";
                return;
        }
    }
}

void DashboardUI::uploadFile() {
    clearInput();

    std::string sourcePath, displayName;
    std::cout << "Enter full path of file: ";
    std::getline(std::cin, sourcePath);

    std::cout << "Enter the display name for the file: ";
    std::getline(std::cin, displayName);

    if (vaultManager.importAndEncryptFile(sourcePath, displayName))
        std::cout << "File stored securely.\n";
    else
        std::cout << "Import failed.\n";
}

void DashboardUI::decryptFile() {
    clearInput();

    std::string fileId;
    std::cout << "Enter file ID to decrypt: ";
    std::getline(std::cin, fileId);

    std::string outputPath;
    std::cout << "Enter output path: ";
    std::getline(std::cin, outputPath);

    if (vaultManager.decryptFile(fileId, outputPath))
        std::cout << "Decryption successful.\n";
    else
        std::cout << "Decryption failed.\n";
}

void DashboardUI::listFiles() {
    vaultManager.listFiles();
}

void DashboardUI::deleteFile() {
    clearInput();

    std::string fileId;
    std::cout << "Enter file ID to delete: ";
    std::getline(std::cin, fileId);

    if (vaultManager.deleteFile(fileId))
        std::cout << "File moved to temp.\n";
    else
        std::cout << "Delete failed.\n";
}

void DashboardUI::recoverFile() {
    clearInput();

    std::string fileId;
    std::cout << "Enter file name or ID to recover: ";
    std::getline(std::cin, fileId);

    if (vaultManager.recoverFile(fileId))
        std::cout << "File recovered successfully.\n";
    else
        std::cout << "Recovery failed.\n";
}

void DashboardUI::deletePermanent() {
    clearInput();

    std::string fileId;
    std::cout << "Enter file ID to permanently delete: ";
    std::getline(std::cin, fileId);

    char confirm;
    std::cout << "This cannot be undone. Confirm (y): ";
    std::cin >> confirm;
    clearInput();

    if (confirm == 'y' || confirm == 'Y') {
        if (vaultManager.purgeFile(fileId))
            std::cout << "File permanently removed.\n";
        else
            std::cout << "Purge failed.\n";
    } else {
        std::cout << "Cancelled.\n";
    }
}