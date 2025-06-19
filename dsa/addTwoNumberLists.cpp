#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(): val(0), next(nullptr) {};
  ListNode(int data): val(data), next(nullptr) {};
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode* temp1 = l1, *temp2 = l2;
        ListNode* dummy = new ListNode();
        ListNode* specialNode = new ListNode(0);
        ListNode* current = dummy;
        
        while(temp1 != nullptr || temp2 != nullptr) {
          if(temp1 == nullptr && temp2 != nullptr) temp1 = specialNode;
          if(temp1 != nullptr && temp2 == nullptr) temp2 = specialNode;
            int sum = temp1->val + temp2->val;
            if(carry > 0) {
                sum += carry;
                carry = 0;
            }

            if(sum > 9) {
                int tenth = sum / 10;
                carry = tenth;
                sum -= tenth * 10;
            }

            current->next = new ListNode(sum);
            current = current->next;

            temp1 = temp1->next;
            temp2 = temp2->next;

            if(carry > 0 && temp1 == nullptr && temp2 == nullptr) {
                current->next = new ListNode(carry);
            }
        }

        return dummy->next;
    }
};

int main() {
  Solution sol;
  ListNode* l1, *l2;
  l1 = new ListNode(2);
  l1->next = new ListNode(4);
  l1->next->next = new ListNode(3);
  l1->next->next->next = new ListNode(7);
  l1->next->next->next->next = nullptr;

  l2 = new ListNode(2);
  l2->next = new ListNode(4);
  l2->next->next = new ListNode(7);
  l2->next->next->next = nullptr;

  ListNode* temp1 = l1;
  ListNode* temp2 = l2;

  std::cout << ' ';

  while(temp1 != nullptr) {
    std::cout << temp1->val << " ";
    temp1 = temp1->next;
  }

  std::cout << std::endl << ' ';

  while(temp2!= nullptr ) {
    std::cout << temp2->val << " ";
    temp2 = temp2->next;
  }

  std::cout << std::endl << "--------" << std::endl;
  
  std::cout << ' ';
  
  ListNode* head = sol.addTwoNumbers(l1, l2);

  while(head != nullptr) {
    std::cout << head->val << " ";
    head = head->next;
  }
}