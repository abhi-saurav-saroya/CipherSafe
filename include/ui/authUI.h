#ifndef AUTHUI_H
#define AUTHUI_H

class AuthManager;

class AuthUI {
    private:
        AuthManager& authManager;
    public:
        AuthUI(AuthManager& manager);
        void authManagerMenu();
        void newMasterSignUp();
        void oldMasterSignIn();
};

#endif