#include <iostream>
#include <memory>

class Test {
  private:
  std::string key;
  public:
  Test(std::string key): key(key) { std::cout << key << " constructor!" << std::endl; }
  void print(std::string text) { std::cout << key << ": " << text << std::endl; }
  ~Test() {std::cout << key << " destructor!" << std::endl; }
};

int main() {
  std::shared_ptr<Test> ptr1 = std::make_shared<Test>("ptr1");
  ptr1->print("hello world");

  (*ptr1.get()).print("hello");
  std::shared_ptr<Test>ptr2 = ptr1;
  ptr2->print("how are you");
  return 0;
}