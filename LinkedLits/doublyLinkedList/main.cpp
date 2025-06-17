#include <iostream>

struct Node {
  int data;
  Node* next;
  Node* prev;
  Node(): data(0), next(nullptr), prev(nullptr) {};
  Node(int data): data(data), next(nullptr), prev(nullptr) {};
  Node(int data, Node* next): data(data), next(next), prev(nullptr) {};
  Node(int data, Node* next, Node* prev): data(data), next(next), prev(prev) {};
};

struct DoublyList {
  private:
  Node* head;
  Node* tail;

  public:
  DoublyList(): head(nullptr), tail(nullptr) {};

  void push_front(int data) {
    Node* newNode = new Node(data);
    if(head == nullptr) {
      head = tail = newNode;
    } else {
      head->prev = newNode;
      newNode->next = head;
      head = newNode;
    }
  }

  void push_back(int data) {
    Node* newNode = new Node(data);
    if(tail==nullptr) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
      tail->next = nullptr;
    }
  }

  void pop_front() {
    if(head==nullptr) {
      std::cout << "Linked list is emtpy" << std::endl;
      return;
    }
    Node* temp = head;
    head = temp->next;
    delete temp;
  }

  void pop_back() {
    if(tail==nullptr) {
      std::cout << "Linked list is empty" << std::endl;
      return;
    }
    Node* temp = tail;
    tail = temp->prev;
    tail->next = nullptr;
    delete temp;
  }

  int serach(int value) {
    Node* temp = head;
    int i = 0;
    while(temp->data != value) {
      temp = temp->next;
      i++;
    }
    return i;
  }

  Node* middle() {
    Node* slow = head;
    Node* fast = head;
    while(fast!=nullptr && fast->next!=nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }

  

  void print(Node* newHead = nullptr) {
    if(newHead==nullptr) newHead = head;
    std::cout << "NULL->";
    Node* temp = newHead;
    while(temp!=nullptr) {
      std::cout << temp->data << "->";
      temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
  }
};

int main() {
  DoublyList list;
  list.push_front(2);
  list.push_front(3);
  list.push_front(1);

  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  list.print();

  list.pop_front();
  list.pop_back();

  list.print();

  // list.print(list.middle());

  return 0;
}