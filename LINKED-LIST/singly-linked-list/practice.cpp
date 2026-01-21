#include <iostream>
using namespace std;

// 🧩 Problem: Reverse a Singly Linked List
// Given the head of a singly linked list, reverse the list,
// and return the reversed list.

// 🔹 Definition for singly-linked list
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 🔹 Solution Class
class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;  // previous pointer (initially null)
    ListNode* curr = head;     // current pointer starts from head
    ListNode* next = nullptr;  // next pointer to store next node

    // Traverse the list and reverse the links
    while (curr != nullptr) {
      next = curr->next;  // store next node
      curr->next = prev;  // reverse current node's link
      prev = curr;        // move prev one step forward
      curr = next;        // move curr one step forward
    }

    // After loop, prev will be the new head
    return prev;
  }
};

// 🔹 Helper Functions for Testing
void printList(ListNode* head) {
  while (head != nullptr) {
    cout << head->val;
    if (head->next) cout << " -> ";
    head = head->next;
  }
  cout << endl;
}

ListNode* createList(int arr[], int n) {
  if (n == 0) return nullptr;
  ListNode* head = new ListNode(arr[0]);
  ListNode* current = head;
  for (int i = 1; i < n; i++) {
    current->next = new ListNode(arr[i]);
    current = current->next;
  }
  return head;
}

// 🔹 Main Function for Local Testing
int main() {
  int arr[] = {1, 2, 3, 4, 5};
  int n = sizeof(arr) / sizeof(arr[0]);

  // Create linked list: 1 -> 2 -> 3 -> 4 -> 5
  ListNode* head = createList(arr, n);
  cout << "Original List: ";
  printList(head);

  // Reverse the list using Solution class
  Solution sol;
  ListNode* reversedHead = sol.reverseList(head);

  // Print reversed list
  cout << "Reversed List: ";
  printList(reversedHead);

  return 0;
}
