#include <iostream>
using namespace std;

/*
----------------------------------------------
    Singly Linked List Implementation
    Author: Raj Aryan
    Description: Basic operations on Linked List
----------------------------------------------
*/

// 🔹 Node class — represents a single element in the list
class Node {
 public:
  int data;    // Data part
  Node* next;  // Pointer to the next node

  // Constructor initializes a node with a given value
  Node(int val) {
    data = val;
    next = NULL;
  }
};

// 🔹 Linked List Class — manages head, tail, and operations
class List {
  Node* head;
  Node* tail;

 public:
  // Constructor initializes an empty list
  List() { head = tail = NULL; }

  /*
  ----------------------------------------------
  Function: push_front(int val)
  Description: Insert a new node at the beginning
  Time Complexity: O(1)
  Space Complexity: O(1)
  ----------------------------------------------
  */
  void push_front(int val) {
    Node* newNode = new Node(val);
    if (head == NULL) {
      head = tail = newNode;  // First node in the list
      return;
    }
    newNode->next = head;  // Link new node before head
    head = newNode;        // Update head
  }

  /*
  ----------------------------------------------
  Function: push_back(int val)
  Description: Insert a new node at the end
  Time Complexity: O(1)
  Space Complexity: O(1)
  ----------------------------------------------
  */
  void push_back(int val) {
    Node* newNode = new Node(val);
    if (head == NULL) {
      head = tail = newNode;
      return;
    }
    tail->next = newNode;  // Link last node to new node
    tail = newNode;        // Update tail
  }

  /*
  ----------------------------------------------
  Function: pop_front()
  Description: Remove a node from the front
  Time Complexity: O(1)
  Space Complexity: O(1)
  ----------------------------------------------
  */
  void pop_front() {
    if (head == NULL) {
      cout << "List is empty\n";
      return;
    }
    Node* temp = head;
    head = head->next;
    temp->next = NULL;
    delete temp;

    if (head == NULL) tail = NULL;  // If list becomes empty
  }

  /*
  ----------------------------------------------
  Function: pop_back()
  Description: Remove a node from the end
  Time Complexity: O(n)  // traversal needed to reach second-last node
  Space Complexity: O(1)
  ----------------------------------------------
  */
  void pop_back() {
    if (head == NULL) {
      cout << "List is empty\n";
      return;
    }

    if (head == tail) {  // Only one element
      delete head;
      head = tail = NULL;
      return;
    }

    Node* temp = head;
    while (temp->next != tail) {
      temp = temp->next;
    }

    delete tail;
    tail = temp;
    tail->next = NULL;
  }

  /*
  ----------------------------------------------
  Function: insert(int val, int pos)
  Description: Insert at a given position (0-based)
  Time Complexity: O(n)
  Space Complexity: O(1)
  ----------------------------------------------
  */
  void insert(int val, int pos) {
    if (pos < 0) {
      cout << "Invalid position\n";
      return;
    }

    if (pos == 0) {  // Insert at head
      push_front(val);
      return;
    }

    Node* temp = head;
    for (int i = 0; i < pos - 1 && temp != NULL; i++) {
      temp = temp->next;
    }

    if (temp == NULL) {
      cout << "Invalid position\n";
      return;
    }

    Node* newNode = new Node(val);
    newNode->next = temp->next;
    temp->next = newNode;

    if (newNode->next == NULL)
      tail = newNode;  // Update tail if inserted at end
  }

  /*
  ----------------------------------------------
  Function: search(int key)
  Description: Search for a key and return its index
  Time Complexity: O(n)
  Space Complexity: O(1)
  ----------------------------------------------
  */
  int search(int key) {
    Node* temp = head;
    int index = 0;
    while (temp != NULL) {
      if (temp->data == key) {
        return index;
      }
      temp = temp->next;
      index++;
    }
    return -1;  // Not found
  }

  /*
  ----------------------------------------------
  Function: PrintLL()
  Description: Print all nodes in the list
  Time Complexity: O(n)
  Space Complexity: O(1)
  ----------------------------------------------
  */
  void PrintLL() {
    Node* temp = head;
    if (head == NULL) {
      cout << "List is empty\n";
      return;
    }

    while (temp != NULL) {
      cout << temp->data << " -> ";
      temp = temp->next;
    }
    cout << "NULL" << endl;
  }

  /*
  ----------------------------------------------
  Destructor: Frees all dynamically allocated nodes
  Time Complexity: O(n)
  ----------------------------------------------
  */
  ~List() {
    Node* temp = head;
    while (temp != NULL) {
      Node* nextNode = temp->next;
      delete temp;
      temp = nextNode;
    }
    head = tail = NULL;
  }
};

// ---------------- MAIN FUNCTION ----------------
int main() {
  List ll;

  cout << "Initial Linked List:\n";
  ll.PrintLL();

  cout << "\nPush Front:\n";
  ll.push_front(1);
  ll.push_front(2);
  ll.push_front(3);
  ll.PrintLL();  // 3 -> 2 -> 1 -> NULL

  cout << "\nPush Back:\n";
  ll.push_back(4);
  ll.PrintLL();  // 3 -> 2 -> 1 -> 4 -> NULL

  cout << "\nPop Front:\n";
  ll.pop_front();
  ll.PrintLL();  // 2 -> 1 -> 4 -> NULL

  cout << "\nPop Back:\n";
  ll.pop_back();
  ll.PrintLL();  // 2 -> 1 -> NULL

  cout << "\nInsert at Position 2 (value = 5):\n";
  ll.insert(5, 2);
  ll.PrintLL();  // 2 -> 1 -> 5 -> NULL

  cout << "\nInvalid Position Insert:\n";
  ll.insert(10, 9);

  cout << "\nSearch Tests:\n";
  cout << "Position of 5: " << ll.search(5) << endl;
  cout << "Position of 7: " << ll.search(7) << endl;

  return 0;
}
