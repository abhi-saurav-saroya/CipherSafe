#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include <vector>

struct MasterUser {
    std::string masterUsername;
    std::string salt;
    std::string hashedMasterKey;
};

class AuthManager {
private:
    std::vector<MasterUser> Masters;

public:
    bool masterExists(const std::string& master_username) const;
    bool createMaster(const std::string& master_username, const std::string& master_password);
    bool authenticateMaster(const std::string& master_username, const std::string& master_password);
    void loadFromFile();
    void saveToFile();
};


#endif