#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* mergeTwoLists(ListNode* head1, ListNode* head2) {
    if (!head1 || !head2) return head1 ? head1 : head2;

    if (head1->val <= head2->val) {
      head1->next = mergeTwoLists(head1->next, head2);
      return head1;
    } else {
      head2->next = mergeTwoLists(head1, head2->next);
      return head2;
    }
  }
};

// Helper function to build linked list from vector
ListNode* buildList(vector<int> arr) {
  if (arr.empty()) return nullptr;

  ListNode* head = new ListNode(arr[0]);
  ListNode* temp = head;
  for (int i = 1; i < arr.size(); i++) {
    temp->next = new ListNode(arr[i]);
    temp = temp->next;
  }
  return head;
}

// Helper function to print linked list
void printList(ListNode* head) {
  while (head) {
    cout << head->val;
    if (head->next) cout << " -> ";
    head = head->next;
  }
  cout << endl;
}

int main() {
  // Example input
  vector<int> a = {1, 2, 4};
  vector<int> b = {1, 3, 4};

  // Build lists
  ListNode* list1 = buildList(a);
  ListNode* list2 = buildList(b);

  // Merge lists
  Solution s;
  ListNode* merged = s.mergeTwoLists(list1, list2);

  // Print result
  cout << "Merged List: ";
  printList(merged);

  return 0;
}
