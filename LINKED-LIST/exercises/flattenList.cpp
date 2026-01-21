/************************************************************
🔹 LeetCode Problem: 430. Flatten a Multilevel Doubly Linked List
🔹 Difficulty: Medium

You are given a doubly linked list that contains:
  • next pointer → points to the next node
  • prev pointer → points to the previous node
  • child pointer → may point to a separate doubly linked list

Goal:
Flatten the multilevel structure into a single-level doubly linked list
such that:
  • nodes of the child list appear AFTER curr
  • and BEFORE curr->next
  • all child pointers must be set to NULL in final flattened list

Example (Visualization):
1 — 2 — 3 — 4
        |
        7 — 8 — 9
            |
            11 — 12

Output after flattening:
1 — 2 — 3 — 7 — 8 — 9 — 11 — 12 — 4

🔹 Approach Used: Recursion (DFS style)
🔹 Time Complexity: O(n) — each node is visited once
🔹 Space Complexity: O(depth) — recursion stack
************************************************************/

#include <iostream>
using namespace std;

// 🔸 Definition for a Node (given by LeetCode)
class Node {
 public:
  int val;
  Node* prev;
  Node* next;
  Node* child;

  Node(int data) {
    val = data;
    prev = next = child = nullptr;
  }
};

class Solution {
 public:
  Node* flatten(Node* head) {
    // Base case: if list is empty, nothing to flatten
    if (head == nullptr) return nullptr;

    Node* curr = head;

    // Traverse the current level
    while (curr != nullptr) {
      // Case 1: No child → just move ahead
      if (curr->child == nullptr) {
        curr = curr->next;
        continue;
      }

      // Case 2: Current node has a child
      Node* nextNode = curr->next;             // Save the next pointer
      Node* childList = flatten(curr->child);  // Recursively flatten child list

      // Attach flattened child list just after current node
      curr->next = childList;
      childList->prev = curr;
      curr->child = nullptr;  // clear child pointer → VERY IMPORTANT

      // Move to the tail of the newly attached list to reconnect nextNode
      while (curr->next != nullptr) {
        curr = curr->next;
      }

      // Reconnect the original nextNode (curr -> next -> nextNode)
      if (nextNode != nullptr) {
        curr->next = nextNode;
        nextNode->prev = curr;
      }
    }

    return head;  // return head of the flattened list
  }
};

/***********************
🔹 Test in main() — for VS Code only
⚠ LeetCode ignores main()
***********************/
void printList(Node* head) {
  cout << "Flattened list: ";
  while (head != nullptr) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
}

int main() {
  /*
      Constructing below multilevel doubly linked list manually:

      1 — 2 — 3 — 4 — 5 — 6
              |
              7 — 8 — 9 — 10
                  |
                  11 — 12
  */

  // Level 1
  Node* n1 = new Node(1);
  Node* n2 = new Node(2);
  Node* n3 = new Node(3);
  Node* n4 = new Node(4);
  Node* n5 = new Node(5);
  Node* n6 = new Node(6);

  n1->next = n2;
  n2->prev = n1;
  n2->next = n3;
  n3->prev = n2;
  n3->next = n4;
  n4->prev = n3;
  n4->next = n5;
  n5->prev = n4;
  n5->next = n6;
  n6->prev = n5;

  // Level 2 (child of 3)
  Node* n7 = new Node(7);
  Node* n8 = new Node(8);
  Node* n9 = new Node(9);
  Node* n10 = new Node(10);

  n7->next = n8;
  n8->prev = n7;
  n8->next = n9;
  n9->prev = n8;
  n9->next = n10;
  n10->prev = n9;

  n3->child = n7;  // connect child

  // Level 3 (child of 8)
  Node* n11 = new Node(11);
  Node* n12 = new Node(12);
  n11->next = n12;
  n12->prev = n11;

  n8->child = n11;  // connect child

  // Call flatten
  Solution obj;
  Node* result = obj.flatten(n1);

  // Print final flattened list
  printList(result);  // output: Flattened list: 1 2 3 7 8 11 12 9 10 4 5 6

  return 0;
}
