#include <iostream>
#include "LinkedList.hpp"

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

  list.print();
  std::cout << "Length of list: " << list.length() << std::endl;
}