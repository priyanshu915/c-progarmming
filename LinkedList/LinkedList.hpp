#include <iostream>

template <typename T> struct Node {
  T data;
  Node *next;
  Node() : data(0), next(nullptr) {};
  Node(T value) : data(value), next(nullptr) {};
  Node(T value, Node *nextNode) : data(value), next(nextNode) {};
};

template <typename T> struct List {
private:
  Node<T> *head;
  Node<T> *tail;

public:
  List() : head(nullptr), tail(nullptr) {};

  int length() {
    int length = 0;
    Node<T> *temp = head;
    while (temp != nullptr) {
      temp = temp->next;
      length++;
    }
    return length > 0 ? length++ : length;
  }

  void push_front(T value) {
    Node<T> *newNode = new Node<T>(value);
    if (head == nullptr)
      head = tail = newNode;
    else {
      newNode->next = head;
      head = newNode;
    }
  }

  void push_back(T value) {
    Node<T> *newNode = new Node<T>(value);
    if (tail == nullptr)
      head = tail = newNode;
    else {
      Node<T> *temp = tail;
      tail = newNode;
      temp->next = tail;
    }
  }

  void pop_front() {
    if (head == nullptr) {
      std::cout << "Linked list is empty" << std::endl;
      return;
    }
    Node<T> *temp = head;
    head = temp->next;
    delete temp;
  }

  void pop_back() {
    if (tail == nullptr) {
      std::cout << "Linked List is empty" << std::endl;
      return;
    }
    Node<T> *temp = head;
    while (temp->next != tail) {
      temp = temp->next;
    }
    tail = temp;
    tail->next = nullptr;
  }

  int search(T data) {
    int index = 0;
    Node<T> *temp = head;
    while (temp->data != data) {
      temp = temp->next;
      index++;
    }
    return index;
  }

  void insert(T value, int pos) {
    if (pos < 0 || pos >= length()) {
      std::cout << "invalid position" << std::endl;
      return;
    }
    if (pos == 0) {
      push_front(value);
      return;
    }

    Node<T> *newNode = new Node<T>(value);
    Node<T> *temp = head;
    for (int i = 0; i < pos - 1; i++) {
      temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
  }

  void remove(T value) {
    if (head->data == value) {
      head = head->next;
      return;
    } else {
      Node<T> *temp = head;
      while (temp->next->data != value) {
        temp = temp->next;
      }
      // delete temp;
      temp->next = temp->next->next;
    }
  }

  void clear() {
    head = tail = nullptr;
  }

  void print() {
    Node<T> *temp = head;
    while (temp != nullptr) {
      std::cout << temp->data << "->";
      temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
  }
};

