/************************************************************
 *  LeetCode 24: Swap Nodes in Pairs
 *
 *  Problem Link:
 *  https://leetcode.com/problems/swap-nodes-in-pairs/
 *
 *  QUESTION:
 *  ---------------------------------------------------------
 *  Given a linked list, swap every two adjacent nodes and
 *  return the head. You MUST swap actual nodes (not values).
 *
 *  Example:
 *     Input:  1 -> 2 -> 3 -> 4
 *     Output: 2 -> 1 -> 4 -> 3
 *
 *  ---------------------------------------------------------
 *  INTUITION:
 *  ---------------------------------------------------------
 *  For every two nodes:
 *
 *       first --> second --> third
 *
 *  After swapping:
 *
 *       second --> first --> third
 *
 *  We maintain:
 *      - first  : first node of pair
 *      - second : second node of pair
 *      - prev   : last node of previous swapped pair
 *
 *  TIME COMPLEXITY:  O(n)
 *  SPACE COMPLEXITY: O(1)
 *
 ************************************************************/

#include <iostream>
#include <vector>
using namespace std;

// ListNode Definition
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

// ----------------------------------------------------------
// Swap Pairs Function
// ----------------------------------------------------------
class Solution {
 public:
  ListNode* swapPairs(ListNode* head) {
    if (!head || !head->next) return head;  // nothing to swap

    ListNode* first = head;
    ListNode* sec = head->next;
    ListNode* prev = nullptr;

    while (first && sec) {
      ListNode* third = sec->next;  // start of next pair

      // swap nodes
      sec->next = first;
      first->next = third;

      // connect previous pair
      if (prev)
        prev->next = sec;
      else
        head = sec;  // first swap updates head

      // move forward
      prev = first;
      first = third;

      sec = (third ? third->next : nullptr);
    }

    return head;
  }
};

// ----------------------------------------------------------
// Helper Functions
// ----------------------------------------------------------
ListNode* createList(const vector<int>& arr) {
  if (arr.empty()) return nullptr;

  ListNode* head = new ListNode(arr[0]);
  ListNode* curr = head;

  for (int i = 1; i < arr.size(); i++) {
    curr->next = new ListNode(arr[i]);
    curr = curr->next;
  }
  return head;
}

void printList(ListNode* head) {
  while (head) {
    cout << head->val;
    if (head->next) cout << " -> ";
    head = head->next;
  }
  cout << endl;
}

// ----------------------------------------------------------
// MAIN for VS Code Testing
// ----------------------------------------------------------
int main() {
  vector<int> arr = {1, 2, 3, 4};
  ListNode* head = createList(arr);

  cout << "Original List:\n";
  printList(head);

  Solution sol;
  ListNode* result = sol.swapPairs(head);

  cout << "\nList After Swapping Pairs:\n";
  printList(result);

  return 0;
}
