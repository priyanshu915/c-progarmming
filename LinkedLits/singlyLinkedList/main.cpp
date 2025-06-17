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

  void reverse() {
    Node<T>* prev = nullptr;
    Node<T>* curr = head;
    Node<T>* next = nullptr;
    while(curr!=nullptr){
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    head = prev;
    tail = (head != nullptr? nullptr: tail);
  }

  void middle() {
    Node<T>* slow = head;
    Node<T>* fast = head;
    while(fast!=nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }
    head = slow;
  }

  void createCycle(int pos) {
    if(head == nullptr || tail == nullptr) {
      std::cout << "Linked list is empty" << std::endl;
      return;
    }
    if(head->next == nullptr) {
      std::cout << "Linked list should consist at least 2 element" << std::endl;
      return;
    }
    
    Node<T>* temp = head;
    for(int i = 0; i < pos; i++){
      temp = temp->next;
    }
    tail->next = temp;
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

int main() {
  List<int> list;

  // push_front
  list.push_front(6); // 6->NULL
  list.push_front(7); // 7->6->NULL

  // push_back
  list.push_back(4); // 7->6->4->NULL
  list.push_back(5); // 7->6->4->5->NULL

  // pop_front
  list.pop_front(); // 6->4->5->NULL

  // pop_back
  list.pop_back(); // 6->4->NULL

  // search
  std::cout << list.search(4) << std::endl;

  // insert
  list.insert(5, 1); // 6->5->4->NULL

  // remove
  list.remove(4); // 6->5->NULL
  list.remove(6); // 5->NULL

  // clear
  list.clear(); // NUL;

  list.push_front(0);
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  list.createCycle(3);

  list.print();
  std::cout << "Length of list: " << list.length() << std::endl;
}