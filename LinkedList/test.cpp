#include <iostream>
#include <string>

template <typename T> class Node {
public:
  T data;
  Node *next;

  Node(T data) {
    this->data = data;
    next = nullptr;
  }
};

template <typename T> class List {
private:
  Node<T> *head;
  Node<T> *tail;
  std::string emptyMessage = "LinkedList is empty";

  void helperReverseOrder(Node<T> *node) {
    if (node == nullptr)
      return;
    helperReverseOrder(node->next);
    std::cout << node->data << "->";
  }

public:
  List() { head = tail = nullptr; }

  void push_front(T value) {
    Node<T> *newNode = new Node<T>(value);
    if (head == nullptr) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head = newNode;
    }
  }

  void pop_front() {
    if (head == nullptr) {
      std::cout << emptyMessage << std::endl;
      return;
    } else {
      Node<T> *temp = head;
      head = temp->next;
      delete temp;
    }
  }

  void push_back(T value) {
    Node<T> *newNode = new Node<T>(value);
    if (tail == nullptr) {
      head = tail = newNode;
    } else {
      Node<T> *temp = tail;
      tail = newNode;
      temp->next = tail;
    }
  }

  void pop_back() {
    if (tail == nullptr) {
      std::cout << emptyMessage << std::endl;
      return;
    } else {
      Node<T> *temp = head;
      while (temp->next != tail) {
        temp = temp->next;
      }
      tail = temp;
      tail->next = nullptr;
    }
  }

  void insert(T value, int pos) {
    if (pos < 0) {
      std::cout << "invalid position!" << std::endl;
      return;
    }

    if (pos == 0) {
      push_front(value);
      return;
    }

    Node<T> *temp = head;
    for (int i = 0; i < pos - 1; i++) {
      if (temp == nullptr) {
        std::cout << "invalid position!" << std::endl;
        return;
      }
      temp = temp->next;
    }

    Node<T> *newNode = new Node(value);
    newNode->next = temp->next;
    temp->next = newNode;
  }

  int search(T value) {
    Node<T> *temp = head;
    int index = 0;
    while (temp->data != value) {
      if (temp == nullptr) {
        std::cout << value << " not found!" << std::endl;
        return -1;
      }
      temp = temp->next;
      index++;
    }
    return index;
  }

  void print() {
    Node<T> *temp = head;
    while (temp != nullptr) {
      std::cout << temp->data << "->";
      temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
  }

  int length() {
    int length = 0;
    if (head == nullptr)
      return 0;
    Node<T> *temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
      length++;
    }
    return length + 1;
  }

  void reverseOrder() {
    helperReverseOrder(head);
    std::cout << "NULL" << std::endl;
  }

  void swap(int pos1, int pos2) {
    if (pos1 < 0 || pos2 < 0 || pos1 >= length() || pos2 >= length()) {
      std::cout << "Invalid position!" << std::endl;
      return;
    }

    if (pos1 == pos2) {
      std::cout << "Positions must not be the same!" << std::endl;
      return;
    }

    Node<T> *temp1 = head;
    for (int i = 0; i < pos1; i++) {
      temp1 = temp1->next;
    }

    Node<T> *temp2 = head;
    for (int i = 0; i < pos2; i++) {
      temp2 = temp2->next;
    }

    T data = temp1->data;
    temp1->data = temp2->data;
    temp2->data = data;
  }

  void reverse() {
    int i = 0, j = length() - 1;
    while (i < j) {
      swap(i, j);
      i++;
      j--;
    }
  }

  void erase(int n) {
    if (n < 0 || n >= length()) {
      std::cout << "invalid position" << std::endl;
      return;
    } else {
      Node<T> *temp = head;
      for (int i = 0; i < n - 1; i++) {
        temp = temp->next;
      }
      temp->next = temp->next->next;
    }
  }
};

int main() {
  List<int> nums;
  nums.push_front(3);
  nums.push_front(2);
  nums.push_front(1);

  nums.pop_front();

  nums.push_back(4);
  nums.push_back(5);

  nums.pop_back();

  nums.insert(10, 1);

  nums.print();

  std::cout << nums.search(10) << std::endl;

  std::cout << nums.length() << std::endl;

  nums.reverseOrder();

  nums.print();
  nums.swap(0, 3);
  nums.print();

  nums.reverse();
  std::cout << "after reverse" << std::endl;
  nums.print();

  nums.erase(2);
  nums.print();

  nums.pop_back();
  nums.pop_back();

  std::cout << "print after earse" << std::endl;
  nums.erase(0);
  nums.print();
  return 0;
}