#include <iostream>
#include <string>

struct Node {
  std::string websiteUrl;
  Node *next;
  Node *prev;
  Node(std::string url) : websiteUrl(url), next(nullptr), prev(nullptr) {}
};

struct DoublyLinkedList {
private:
  Node *head;
  Node *tail;

public:
  std::string current = "home page";
  DoublyLinkedList() : head(nullptr), tail(nullptr) {}

  void push_back(std::string url) {
    Node *newNode = new Node(url);
    if (head == nullptr) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    current = newNode->websiteUrl;
  }

  void back() {
    Node *temp = head;
    while (temp->websiteUrl != current) {
      temp = temp->next;
    }
    current = temp->prev == nullptr ? temp->websiteUrl : temp->prev->websiteUrl;
  }

  void forward() {
    Node *temp = head;
    while (temp->websiteUrl != current) {
      temp = temp->next;
    }
    current = temp->next == nullptr ? temp->websiteUrl : temp->next->websiteUrl;
  }
};

void options() {
  std::cout << std::endl;
  std::cout << "===== Browser History Tracker =====" << std::endl;
  std::cout << "1. Visit New Website" << std::endl;
  std::cout << "2. Back" << std::endl;
  std::cout << "3. Forward" << std::endl;
  std::cout << "4. Show Current Page" << std::endl;
  std::cout << "5. Exit" << std::endl;
}

int main() {
  DoublyLinkedList history;
  while (true) {
    options();
    int option = 0;
    std::cout << "choose option: ";
    std::cin >> option;
    if (option == 1) {
      std::string url;
      std::cout << "Enter url: ";
      std::cin >> url;
      history.push_back(url);
      std::cout << "Visited: " << history.current << std::endl << std::endl;
    } else if (option == 2) {
      history.back();
      std::cout << "moved back to: " << history.current << std::endl;
    } else if (option == 3) {
      history.forward();
      std::cout << "move forward to: " << history.current << std::endl;
    } else if (option == 4) {
      std::cout << "current page: " << history.current << std::endl;
    } else if (option == 5) {
      std::cout << std::endl << "Exiting..." << std::endl;
      break;
    } else {
      std::cout << "please enter valid option number" << std::endl;
    }
  }
}