#ifndef VAULTMANAGER_H
#define VAULTMANAGER_H

#include <string>
#include <vector>

enum class FileLocation {
    Objects,
    Temp
};

// metadata of a single stored file
struct VaultFile {
    std::string id;
    std::string originalName;
    std::string createdAt;
    FileLocation location;
};



class VaultManager {
    private:
        std::string masterUsername;
        std::string vaultRootPath;

        std::vector<VaultFile> files;

        // ---------- Internal helpers (no UI access) ----------
        void loadVaultIndex();                 // load metadata from disk
        void saveVaultIndex();                 // writes entire vector to disk
        
        void saveFileMetadata(const VaultFile& file);

        VaultFile* findFileById(const std::string& id);
        VaultFile* findFileByName(const std::string& originalName);


        std::string generateFileId() const;
        std::string currentTimestamp() const;

    public:
        // ---------- Lifecycle ----------
        explicit VaultManager(const std::string& masterUsername, const std::string& vaultRootPath);

        // ---------- Core vault actions ----------
        bool importAndEncryptFile(const std::string& sourcePath, const std::string& displayName);
        bool decryptFile(const std::string& fileId, const std::string& outputPath);
        void listFiles() const;
        bool deleteFile(const std::string& fileId);                 // soft delete
        bool recoverFile(const std::string& fileId);
        bool purgeFile(const std::string& fileId);                  // permanent delete

        // ---------- Info ----------
        const std::string& getMasterUsername() const;
};

#endif
