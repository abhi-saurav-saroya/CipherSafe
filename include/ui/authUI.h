#ifndef AUTHUI_H
#define AUTHUI_H

class AuthManager;

enum class AuthResult {
    LOGIN_SUCCESS,
    EXIT
};

class AuthUI {
    private:
        AuthManager& authManager;
        void newMasterSignUp();
        bool oldMasterSignIn();
    public:
        explicit AuthUI(AuthManager& manager);
        AuthResult authManagerMenu();
};

#endif