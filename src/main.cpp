#include "authUI.h"
#include "authManager.h"

#include <iostream>
using namespace std;

int main() {
    cout << "-------- Welcome to CipherSafe - Secure File Locker --------" << endl << endl;

    AuthManager manager;
    manager.loadFromFile();

    AuthUI ui(manager);
    ui.authManagerMenu();

    manager.saveToFile();
    return 0;
}
