#ifndef AUTHUI_H
#define AUTHUI_H

class AuthManager;

class AuthUI {
    private:
        AuthManager& authManager;
        void newMasterSignUp();
        void oldMasterSignIn();
    public:
        explicit AuthUI(AuthManager& manager);
        void authManagerMenu();
};

#endif