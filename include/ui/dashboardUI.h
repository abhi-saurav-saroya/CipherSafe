#ifndef DASHBOARDUI_H
#define DASHBOARDUI_H

class AuthManager;
class VaultManager;

class DashboardUI {
    private:
        VaultManager& vaultManager;
        AuthManager& authManager;
        void uploadFile();          
        void decryptFile();      
        void listFiles();    
        void deleteFile(); 
        void recoverFile();  
        void deletePermanent();

    public:
        explicit DashboardUI(AuthManager& authMgr, VaultManager& vaultMgr);
        void dashboardMenu();

};

#endif