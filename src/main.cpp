#include "authManager.h"
#include "authUI.h"
#include "dashboardUI.h"
#include "vaultManager.h"

#include <iostream>
#include <string>

int main() {
    AuthManager authManager;
    authManager.loadFromFile();

    while (true) {
        AuthUI authUI(authManager);

        AuthResult result = authUI.authManagerMenu();

        if (result == AuthResult::EXIT)
            break;

        // -------- DASHBOARD --------
        std::string username = authManager.getCurrentMasterUsername();
        std::string vaultPath = "data/masters/" + username + "/vault";

        VaultManager vaultManager(username, vaultPath);
        DashboardUI dashboardUI(authManager, vaultManager);

        dashboardUI.dashboardMenu();

        authManager.logout();
    }

    return 0;
}
