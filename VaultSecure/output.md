
# 🔐 VaultSecure - Console Output Demo

A simple console-based password manager using **OOP + JSON + FileSystem** concepts in C++.  
This output simulates a typical user session.  

---

## 💻 C++ Code

```cpp
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <unordered_map>

using json = nlohmann::json;
namespace fs = std::filesystem;

struct User {
  std::string email;
  std::string password;
  std::string name;
};

struct App {
  std::string url;
  std::string password;
};

class VaultSecure {
private:
  json db;
  std::string fileName = "db.json";

  void loadData() {
    std::ifstream file(fileName);
    if (file.is_open()) {
      file >> db;
      file.close();
    } else {
      std::cerr << "Error opening file: " << fileName << std::endl;
    }
  }

  void updateDB() {
    for (auto it = db.begin(); it != db.end(); ++it) {
      if (user["email"] == (*it)["email"]) {
        *it = user;
      }
    }
    std::ofstream file(fileName);
    if (file.is_open()) {
      file << db.dump(4);
      file.close();
    } else {
      std::cerr << "Error opening file for writing: " << fileName << std::endl;
    }
  }

public:
  json user;

  VaultSecure() {
    if (!fs::exists(fileName)) {
      std::ofstream file(fileName);
      file << "[]";
      file.close();
    }
  }

  void createAccount(User newUser) {
    loadData();
    json user = {{"email", newUser.email},
                 {"password", newUser.password},
                 {"name", newUser.name}};
    db.push_back(user);
    updateDB();
  }

  bool signin(std::string email, std::string password) {
    loadData();
    for (auto it = db.begin(); it != db.end(); ++it) {
      if ((*it)["email"] == email && (*it)["password"] == password) {
        user = *it;
        return true;
      }
    }
    return false;
  }

  void signout() { user.clear(); }

  void deleteAccount() {
    loadData();
    for (auto it = db.begin(); it != db.end(); ++it) {
      if (user["email"] == (*it)["email"]) {
        db.erase(it);
        break;
      }
    }
    updateDB();
    user.clear();
  }

  void addPass(App appData) {
    loadData();
    json app = {{"url", appData.url},
                {"password", appData.password},
                {"email", user["email"]}};
    if (user.contains("apps")) {
      user["apps"].push_back(app);
    } else {
      user["apps"] = json::array({app});
    }
    updateDB();
  }

  void removePass(std::string url) {
    loadData();
    if (user.contains("apps")) {
      for (auto it = user["apps"].begin(); it != user["apps"].end(); ++it) {
        if ((*it)["url"] == url) {
          user["apps"].erase(it);
          break;
        }
      }
    }
    updateDB();
  }

  void getPasses(std::string url) {
    loadData();
    std::unordered_map<std::string, std::string> passes;
    bool found = false;
    if (user.contains("apps")) {
      for (const auto &app : user["apps"]) {
        if (app["url"] == url) {
          passes["url"] = app["url"];
          passes["password"] = app["password"];
          passes["email"] = app["email"];
          found = true;
          break;
        }
      }
    }
    if (found) {
      std::cout << "URL: " << passes["url"] << "\n"
                << "Password: " << passes["password"] << "\n"
                << "Email: " << passes["email"] << std::endl;
    } else {
      std::cout << "No password found for URL: " << url << std::endl;
    }
  }

  void editPasses(std::string url, std::string password,
                  std::string newPassword) {
    loadData();
    if (user.contains("apps")) {
      for (auto &app : user["apps"]) {
        if (app["url"] == url && app["password"] == password) {
          app["password"] = newPassword;
          break;
        }
      }
    }
    updateDB();
  }

  ~VaultSecure() {
    loadData();
    updateDB();
  }
};
```

---

## 🧪 Demo Session

### 👤 Creating a New Account

```text
**Welcome to VaultSecure**
1. Create Account
2. Sign In
3. Exit

Choose an option: 1
Enter Email: john@example.com
Enter Password: john123
Enter Name: John

✅ Account created successfully.
```

### 🔐 Signing In

```text
Choose an option: 2
Enter Email: john@example.com
Enter Password: john123

✅ Sign In Successful!
```

### ➕ Add a Password

```text
Choose an option: 1
Enter URL: github.com
Enter Password: gh@123

🔐 Password added for github.com
```

### 🔍 Get Password

```text
Choose an option: 3
Enter URL to get passwords: github.com

🌐 URL: github.com
🔑 Password: gh@123
📧 Email: john@example.com
```

### ✏️ Edit Password

```text
Choose an option: 4
Enter URL to edit: github.com
Enter current password: gh@123
Enter new password: newGH@123

✅ Password updated for github.com
```

### ❌ Remove Password

```text
Choose an option: 2
Enter URL to remove: github.com

🗑️ Password removed for github.com
```

### 🚪 Sign Out & Delete Account

```text
Choose an option: 5
👋 Signed out successfully.

--- or ---

Choose an option: 6
🗑️ Account deleted successfully.
```

### ❎ Exit

```text
Choose an option: 7

👋 Exiting...
```
