<h1 align="center">
  <img 
    src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=32&pause=1000&color=ffffff&center=true&vCenter=true&width=650&lines=CipherSafe - Secure File Locker"
    alt="First Come First Serve (FCFS) CPU Scheduling"
  />
</h1>

CipherSafe is a **console-based secure file vault application** built in **C++**, designed to simulate how encrypted file storage systems work internally.  
The project focuses on **core backend concepts** such as authentication, encryption, file system design, metadata management, and clean architecture — without relying on any GUI frameworks.

> Note: This project is built for **learning and demonstration purposes**. Encryption used is XOR-based and **not intended for production security**.

<p align="center">
  <img src="https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++"/>
</p>
<p align="center">
  <img src="https://img.shields.io/badge/Hashing-SHA256-0ea5e9?style=for-the-badge" alt="SHA256"/>
  <img src="https://img.shields.io/badge/Encryption-XOR_Based-22c55e?style=for-the-badge" alt="XOR"/>
  <img src="https://img.shields.io/badge/Domain-Cryptography-f97316?style=for-the-badge" alt="Cryptography"/>
</p>
<p align="center">
  <a href="https://github.com/nlohmann/json" target="_blank">
    <img src="https://img.shields.io/badge/Library-nlohmann%2Fjson-1f2937?style=for-the-badge&logo=github&logoColor=white" alt="nlohmann/json"/>
  </a>
</p>
<p align="center">
  <img src="https://img.shields.io/badge/License-MIT-success?style=for-the-badge" alt="License"/>
</p>

## Features

1. ### Authentication System
    - Master user **sign-up & sign-in**
    - Secure password hashing with salt
    - Persistent user storage (JSON-based)
    - Session-based login tracking

2. ### Vault Management
    - Import & encrypt files into a secure vault
    - Per-file metadata management
    - Unique ID-based file tracking
    - Automatic directory creation per file

3. ### File Lifecycle
    - Soft delete (move to `temp/`)
    - Recover deleted files
    - Permanent purge (irreversible)
    - Encrypted files stored at rest

4. ### Encryption
    - XOR-based encryption & decryption
    - Binary-safe (works for text, images, etc.)
    - Key derived from logged-in master user

## Project Architecture
<p align="center">
  <img src="assets\screenshots\project-structure.png" alt = "Project Dir" width="250" height = "600">
</p>

## Data Directory Structure
<p align="center">
  <img src="assets\screenshots\data-dir-structure.png" alt = "Data Dir" width="250" height = "700">
</p>

## Tech Stack

| Component | Technology |
|---------|------------|
| Language | C++ (C++20) |
| Build Tool | g++ (MinGW on Windows) |
| Storage | File System + JSON |
| Encryption | XOR-based (custom) |
| Libraries | STL, `<filesystem>`, `nlohmann/json` |


## Libraries Used

1. ### STL (Standard Template Library)
    - `std::vector`
    - `std::string`
    - `std::filesystem`
    - `std::fstream`
    - `std::ctime`

2. ### nlohmann/json
    - Used for persistent storage of:
        - User credentials
        - Vault index
        - File metadata

3. ### Header-only JSON library.

## Acknowledgements

- **nlohmann/json** — Header-only JSON library for C++  
  Created by **Niels Lohmann**  
  Used for structured and persistent data storage (`auth.json`, vault index, metadata).  
  GitHub: https://github.com/nlohmann/json


## Data Structures Used

| Structure | Purpose |
|------------|-----------|
| `vector<VaultFile>` | Tracks all vault files |
| `struct VaultFile` | Stores file metadata |
| `enum class FileLocation` | Objects vs Temp |
| JSON Arrays | Persistent indexing |


## System Design Overview

1. ### AuthManager
    - Handles master users
    - Password hashing & verification
    - Login session tracking
    - Persistent storage in `auth.json`

2. ### VaultManager
    - Manages encrypted files
    - Handles file lifecycle
    - Maintains `vault_index.json`
    - No UI responsibility (logic-only)

3. ### UI Layer
    - `AuthUI` → Authentication menu
    - `DashboardUI` → Vault operations
    - Input validation & flow control


## Application Workflow

1. ### Application Start
    - Load existing master users
    - Display authentication menu
    
2. ### Authentication Phase
    - User signs up OR signs in
    - Password is verified via hashing
    - Session is established

3. ### Dashboard Phase
    User can:
    - Import & encrypt files
    - List stored files
    - Decrypt files
    - Soft delete / recover

4. ### Logout
    - Session cleared
    - Vault state saved
    - Return to auth menu


## Encryption Design (XOR)

### How it works:
- File bytes are XOR-ed with a repeating key
- Same function used for encryption & decryption
- Binary-safe implementation


## Build & Run Instructions

### Requirements
- g++ (C++17 or later)
- MinGW (Windows) or GCC (Linux)

### Compile
```bash
g++ src/main/*.cpp src/ui/*.cpp src/utils/*.cpp src/managers/*.cpp -Iinclude/utils/ -Iinclude/ui/ -Iinclude/libs/ -Iinclude/managers/ -o CipherSafe
```
### Run (cmd)
```bash
CipherSafe.exe
```
### Run (powershell)
```bash
.\CipherSafe
```
---
<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&height=100&section=footer" alt="Footer"/>

<i>Built for fun, engineered for learning, encrypted for practice. 💾</i>
<i>Because your secrets deserve CipherSafe. 🛡️</i>

---

**© 2026 Open Source Project | CipherSafe - Secure File Locker | MIT License**