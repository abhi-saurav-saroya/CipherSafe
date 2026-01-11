#include "authUI.h"
#include "authManager.h"
#include "utils.h"

#include <iostream>
using namespace std;

int main() {
    cout << "-------- Welcome to CipherSafe - Secure File Locker --------" << endl << endl;

    AuthManager manager;

    AuthUI ui(manager);
    ui.authManagerMenu();

    return 0;
}