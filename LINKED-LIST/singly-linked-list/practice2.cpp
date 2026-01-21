#include <iostream>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
 public:
  ListNode* detectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) break;
    }

    if (!fast || !fast->next) return nullptr;

    slow = head;
    while (slow != fast) {
      slow = slow->next;
      fast = fast->next;
    }

    return slow;
  }
};

int main() {
  // Creating nodes manually for VS Code testing
  ListNode* n1 = new ListNode(3);
  ListNode* n2 = new ListNode(2);
  ListNode* n3 = new ListNode(0);
  ListNode* n4 = new ListNode(-4);

  n1->next = n2;
  n2->next = n3;
  n3->next = n4;
  n4->next = n2;  // create cycle here

  Solution s;
  ListNode* cycleStart = s.detectCycle(n1);

  if (cycleStart)
    cout << "Cycle starts at node with value: " << cycleStart->val << endl;
  else
    cout << "No cycle detected" << endl;

  return 0;
}
