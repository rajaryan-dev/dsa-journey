#include <iostream>
using namespace std;

/*
---------------------------------------------------------
 NODE STRUCTURE — Circular Singly Linked List
---------------------------------------------------------
Each node stores:
  - data : integer
  - next : pointer to next node

In circular linked list:
  - last node points back to head
---------------------------------------------------------
*/
class Node {
 public:
  int data;
  Node* next;

  Node(int val) {
    data = val;
    next = nullptr;
  }
};

/*
=========================================================
             CIRCULAR LINKED LIST CLASS
=========================================================
Maintains:
  - head → first node
  - tail → last node (tail->next always = head)
=========================================================
*/
class CircularList {
 private:
  Node* head;
  Node* tail;

 public:
  CircularList() { head = tail = nullptr; }

  /*
  -------------------------------------------------------
   INSERT AT HEAD (O(1))
  -------------------------------------------------------
   Steps:
    1. Create a new node
    2. If list empty → head = tail = newNode → tail->next = head
    3. Else:
       - newNode->next = head
       - head = newNode
       - tail->next = head
  -------------------------------------------------------
  */
  void insertAtHead(int val) {
    Node* newNode = new Node(val);

    if (head == nullptr) {  // empty list
      head = tail = newNode;
      tail->next = head;  // circular link
    } else {
      newNode->next = head;  // connect newNode → old head
      head = newNode;        // update head
      tail->next = head;     // restore circular connection
    }
  }

  /*
  -------------------------------------------------------
   INSERT AT TAIL (O(1))
  -------------------------------------------------------
   Steps:
    1. Create new node
    2. If list empty → head = tail = newNode
    3. Else:
        - newNode->next = head
        - tail->next = newNode
        - tail = newNode
  -------------------------------------------------------
  */
  void insertAtTail(int val) {
    Node* newNode = new Node(val);

    if (tail == nullptr) {  // empty list
      head = tail = newNode;
      tail->next = head;  // circular link
    } else {
      newNode->next = head;  // new node points to head
      tail->next = newNode;  // old tail points to newNode
      tail = newNode;        // update tail
    }
  }

  /*
  -------------------------------------------------------
   DELETE AT HEAD (O(1))
  -------------------------------------------------------
   Cases:
    1. Empty list → return
    2. Only one node → delete it
    3. More than one:
        - move head → head->next
        - tail->next = new head
        - delete old head
  -------------------------------------------------------
  */
  void deleteAtHead() {
    if (head == nullptr) {
      cout << "List is Empty\n";
      return;
    }

    if (head == tail) {  // only one node
      delete head;
      head = tail = nullptr;
    } else {
      Node* temp = head;
      head = head->next;  // move head forward
      tail->next = head;  // reconnect tail to new head
      temp->next = nullptr;
      delete temp;
    }
  }

  /*
  -------------------------------------------------------
   DELETE AT TAIL (O(n))
  -------------------------------------------------------
   Cases:
    1. Empty list → return
    2. Only one node → delete it
    3. More than one:
        - find second last node
        - make it new tail
        - tail->next = head
        - delete old tail
  -------------------------------------------------------
  */
  void deleteAtTail() {
    if (head == nullptr) {
      cout << "List is Empty\n";
      return;
    }

    if (head == tail) {  // only one node
      delete head;
      head = tail = nullptr;
    } else {
      Node* prev = head;

      // find node just before tail
      while (prev->next != tail) {
        prev = prev->next;
      }

      Node* temp = tail;
      tail = prev;        // update tail
      tail->next = head;  // maintain circular link
      temp->next = nullptr;
      delete temp;
    }
  }

  /*
  -------------------------------------------------------
   PRINT LIST (HEAD → BACK TO HEAD)
  -------------------------------------------------------
   Since it is circular, we stop when we reach head again.
  -------------------------------------------------------
  */
  void printList() {
    if (head == nullptr) {
      cout << "List is Empty\n";
      return;
    }

    cout << head->data << "=>";

    Node* temp = head->next;

    while (temp != head) {  // stop when loop completes
      cout << temp->data << "=>";
      temp = temp->next;
    }

    cout << "HEAD\n";  // indicates circular link
  }
};

/*
=========================================================
                  DRIVER CODE
=========================================================
*/
int main() {
  CircularList cl;

  cl.insertAtHead(1);
  cl.insertAtHead(2);
  cl.insertAtHead(3);
  cl.insertAtHead(4);
  cl.printList();

  cl.insertAtTail(5);
  cl.printList();

  cl.deleteAtHead();
  cl.printList();

  cl.deleteAtTail();
  cl.printList();

  return 0;
}
