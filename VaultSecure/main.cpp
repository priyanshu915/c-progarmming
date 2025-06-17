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
      file << db.dump(4); // Pretty print with 4 spaces
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

void authOption() {
  std::cout << "**Welcome to VaultSecure**\n";
  std::cout << "1. Create Account\n"
            << "2. Sign In\n"
            << "3. Exit\n";
}

void options() {
  std::cout << "1. Add Password\n"
            << "2. Remove Password\n"
            << "3. Get Passwords\n"
            << "4. Edit Passwords\n"
            << "5. Sign Out\n"
            << "6. Delete Account\n"
            << "7. Exit\n";
}

int main() {
  VaultSecure vault;
  int choice;
  std::string email, password, name, url, newPassword;

  while (true) {
    authOption();
    std::cout << std::endl << "Choose an option: ";
    std::cin >> choice;
    if(std::cin.fail()) {
      std::cin.clear(); // Clear the error flag
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
      std::cout << "Invalid input. Please enter a number.\n";
      continue;
    }
    if (choice == 1) {
      User newUser;
      std::cout << "Enter Email: ";
      std::cin >> newUser.email;
      std::cout << "Enter Password: ";
      std::cin >> newUser.password;
      std::cout << "Enter Name: ";
      std::cin >> newUser.name;
      vault.createAccount(newUser);
    } else if (choice == 2) {
      std::cout << "Enter Email: ";
      std::cin >> email;
      std::cout << "Enter Password: ";
      std::cin >> password;
      if (vault.signin(email, password)) {
        std::cout << "Sign In Successful!\n";
        while (true) {
          options();
          std::cout << "Choose an option: ";
          std::cin >> choice;
          if(std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
          }

          if (choice == 1) {
            App appData;
            std::cout << "Enter URL: ";
            std::cin >> appData.url;
            std::cout << "Enter Password: ";
            std::cin >> appData.password;
            vault.addPass(appData);
          } else if (choice == 2) {
            std::cout << "Enter URL to remove: ";
            std::cin >> url;
            vault.removePass(url);
          } else if (choice == 3) {
            std::cout << "Enter URL to get passwords: ";
            std::cin >> url;
            vault.getPasses(url);
          } else if (choice == 4) {
            std::cout << "Enter URL to edit: ";
            std::cin >> url;
            std::cout << "Enter current password: ";
            std::cin >> password;
            std::cout << "Enter new password: ";
            std::cin >> newPassword;
            vault.editPasses(url, password, newPassword);
          } else if (choice == 5) {
            vault.signout();
            break; // Exit to main menu
          } else if (choice == 6) {
            vault.deleteAccount();
            break; // Exit to main menu
          } else if (choice == 7) {
            return 0; // Exit program
          }
        }
      } else if( choice == 3) {
        return 0; // Exit program
      }
      else {
        std::cout << "Sign In Failed! Invalid email or password.\n";
      }
    }
  }
}