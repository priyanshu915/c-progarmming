#include <iostream>
#include <stdexcept>

int main() {
    int balance = 1000;
    try {
        int n;
        std::cout << "Enter the amount: ";
        std::cin >> n;

        if(n <= 0 && n > balance) {
            throw std::runtime_error("not enough money");
        }

        std::cout << "withdraw succesfull: " << balance << std::endl;
        std::cout << "remaning balance: " << balance - n << std::endl;
    } catch (const std::runtime_error& error) {
        std::cout << error.what() << std::endl;
    }
    return 0;
}