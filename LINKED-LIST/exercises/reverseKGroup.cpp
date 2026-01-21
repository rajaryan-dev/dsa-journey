/************************************************************
 *  LeetCode 25: Reverse Nodes in k-Group
 *  Difficulty: Hard
 *
 *  Problem Link:
 *  https://leetcode.com/problems/reverse-nodes-in-k-group/
 *
 *  ---------------------------------------------------------
 *  QUESTION:
 *  ---------------------------------------------------------
 *  Given the head of a linked list, reverse the nodes of the
 *  list k at a time, and return the modified list.
 *
 *  - k is a positive integer.
 *  - If the number of nodes is not a multiple of k,
 *    leave the last remaining nodes as they are.
 *  - You may NOT alter the values inside the nodes,
 *    only the node pointers can be changed.
 *
 *  Example:
 *     Input:  head = [1,2,3,4,5],  k = 2
 *     Output: [2,1,4,3,5]
 *
 *  ---------------------------------------------------------
 *  INTUITION:
 *  ---------------------------------------------------------
 *  To reverse the list in chunks of size k:
 *
 *  1. Check if k nodes exist.
 *     - If not, do nothing and return current head.
 *
 *  2. Recursively reverse the remaining list first.
 *     - This gives us the head of the already reversed
 *       remaining portion (nextGroupHead).
 *
 *  3. Reverse the first k nodes.
 *
 *  4. Connect this reversed block → nextGroupHead.
 *
 *  Time Complexity:  O(n)
 *  Space Complexity: O(n/k) due to recursion depth
 *
 ************************************************************/

#include <iostream>
#include <vector>
using namespace std;

// ------------------------------
// Definition for singly-linked list
// ------------------------------
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// ----------------------------------------------------------
// Solution Class
// ----------------------------------------------------------
class Solution {
 public:
  /********************************************************
   * reverseKGroup(head, k)
   * ------------------------------------------------------
   * Main recursive approach:
   *   1. Ensure current segment has k nodes.
   *   2. Recursively reverse rest of the list.
   *   3. Reverse this group of k nodes.
   *   4. Return new head of this reversed group.
   ********************************************************/
  ListNode* reverseKGroup(ListNode* head, int k) {
    // Step 1: Verify if a full group of k nodes exists
    ListNode* checker = head;
    for (int i = 0; i < k; i++) {
      if (!checker) return head;  // not enough nodes → return as is
      checker = checker->next;
    }

    // Step 2: Recursively handle the remaining list
    ListNode* nextGroupHead = reverseKGroup(checker, k);

    // Step 3: Reverse this group of k nodes
    ListNode* curr = head;
    ListNode* prev = nextGroupHead;

    for (int i = 0; i < k; i++) {
      ListNode* nextNode = curr->next;  // store next node
      curr->next = prev;                // reverse pointer
      prev = curr;                      // move prev forward
      curr = nextNode;                  // move curr forward
    }

    // Step 4: prev is the new head of this reversed group
    return prev;
  }
};

// ----------------------------------------------------------
// Helper Functions for Testing in VS Code
// ----------------------------------------------------------

// Create linked list from vector
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

// Print linked list
void printList(ListNode* head) {
  while (head) {
    cout << head->val;
    if (head->next) cout << " -> ";
    head = head->next;
  }
  cout << endl;
}

// ----------------------------------------------------------
// MAIN FUNCTION for Local VS Code Testing
// ----------------------------------------------------------
int main() {
  vector<int> arr = {1, 2, 3, 4, 5};
  int k = 2;

  ListNode* head = createList(arr);

  cout << "Original List:\n";
  printList(head);

  Solution sol;
  ListNode* result = sol.reverseKGroup(head, k);

  cout << "\nList Reversed in Groups of " << k << ":\n";
  printList(result);

  return 0;
}
