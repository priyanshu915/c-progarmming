#include <iostream>
#include <memory>

class Weapon {
public:
    Weapon(std::string name) : name(name) {
        std::cout << name << " is created\n";
    }
    ~Weapon() {
        std::cout << name << " is destroyed\n";
    }
    void use() {
        std::cout << "Using weapon: " << name << "\n";
    }
private:
    std::string name;
};

class Player {
public:
    std::unique_ptr<Weapon> weapon;

    void equipWeapon(std::unique_ptr<Weapon> w) {
        weapon = std::move(w);  // Transfer ownership
    }

    void attack() {
        if (weapon) weapon->use();
        else std::cout << "No weapon equipped!\n";
    }
};

int main() {
    Player p1, p2;

    std::unique_ptr<Weapon> sword = std::make_unique<Weapon>("Sword");

    p1.equipWeapon(std::move(sword)); // p1 owns the weapon now

    p1.attack(); //  Works
    std::cout << "p2" << std::endl;
    p2.attack(); //  No weapon

    // Weapon is auto deleted when p1 goes out of scope
}
