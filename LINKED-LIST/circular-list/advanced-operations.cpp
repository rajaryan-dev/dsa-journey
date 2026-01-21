#include <iostream>
using namespace std;

class Node {
 public:
  int data;
  Node* next;

  Node(int val) {
    data = val;
    next = nullptr;
  }
};

class CircularList {
 private:
  Node* head;
  Node* tail;

 public:
  CircularList() { head = tail = nullptr; }

  /* -------------------------------------------------------
                BASIC INSERT OPERATIONS
  ------------------------------------------------------- */
  void insertAtHead(int val) {
    Node* newNode = new Node(val);

    if (head == nullptr) {
      head = tail = newNode;
      tail->next = head;
    } else {
      newNode->next = head;
      head = newNode;
      tail->next = head;
    }
  }

  void insertAtTail(int val) {
    Node* newNode = new Node(val);

    if (head == nullptr) {
      head = tail = newNode;
      tail->next = head;
    } else {
      newNode->next = head;
      tail->next = newNode;
      tail = newNode;
    }
  }

  /* -------------------------------------------------------
                BASIC DELETE OPERATIONS
  ------------------------------------------------------- */
  void deleteAtHead() {
    if (head == nullptr) {
      cout << "List is Empty\n";
      return;
    }

    if (head == tail) {
      delete head;
      head = tail = nullptr;
    } else {
      Node* temp = head;
      head = head->next;
      tail->next = head;
      delete temp;
    }
  }

  void deleteAtTail() {
    if (head == nullptr) {
      cout << "List is Empty\n";
      return;
    }

    if (head == tail) {
      delete head;
      head = tail = nullptr;
    } else {
      Node* prev = head;

      while (prev->next != tail) prev = prev->next;

      Node* temp = tail;
      tail = prev;
      tail->next = head;
      delete temp;
    }
  }

  /* =======================================================
                ADVANCED FUNCTIONS
  ======================================================= */

  /* -------------------------------------------------------
      LENGTH OF CIRCULAR LIST (O(n))
  ------------------------------------------------------- */
  int length() {
    if (head == nullptr) return 0;

    int count = 1;
    Node* temp = head->next;

    while (temp != head) {
      count++;
      temp = temp->next;
    }
    return count;
  }

  /* -------------------------------------------------------
     SEARCH (returns 1-based index)
     If not found → returns -1
  ------------------------------------------------------- */
  int search(int val) {
    if (head == nullptr) return -1;

    Node* temp = head;
    int pos = 1;

    do {
      if (temp->data == val) return pos;
      temp = temp->next;
      pos++;
    } while (temp != head);

    return -1;
  }

  /* -------------------------------------------------------
     INSERT AT POSITION (1-based)
     Uses:
        pos == 1 → insertAtHead
        pos == len+1 → insertAtTail
        else → insert in middle
  ------------------------------------------------------- */
  void insertAtPosition(int pos, int val) {
    int len = length();

    if (pos < 1 || pos > len + 1) {
      cout << "Invalid position\n";
      return;
    }

    if (pos == 1) {
      insertAtHead(val);
      return;
    }

    if (pos == len + 1) {
      insertAtTail(val);
      return;
    }

    Node* newNode = new Node(val);
    Node* temp = head;
    int count = 1;

    while (count < pos - 1) {
      temp = temp->next;
      count++;
    }

    newNode->next = temp->next;
    temp->next = newNode;
  }

  /* -------------------------------------------------------
     DELETE AT POSITION (1-based)
  ------------------------------------------------------- */
  void deleteAtPosition(int pos) {
    int len = length();

    if (pos < 1 || pos > len) {
      cout << "Invalid position\n";
      return;
    }

    if (pos == 1) {
      deleteAtHead();
      return;
    }

    if (pos == len) {
      deleteAtTail();
      return;
    }

    Node* temp = head;
    int count = 1;

    while (count < pos - 1) {
      temp = temp->next;
      count++;
    }

    Node* toDelete = temp->next;
    temp->next = toDelete->next;

    delete toDelete;
  }

  /* -------------------------------------------------------
     VERIFY IF LIST IS CIRCULAR
     Always true for our implementation, but useful.
  ------------------------------------------------------- */
  bool isCircular() {
    if (head == nullptr) return true;  // empty list is circular

    Node* temp = head->next;

    while (temp != nullptr && temp != head) temp = temp->next;

    return (temp == head);
  }

  /* -------------------------------------------------------
     REVERSE THE CIRCULAR LIST (O(n))
  ------------------------------------------------------- */
  void reverse() {
    if (head == nullptr || head == tail) return;

    Node* prev = tail;
    Node* curr = head;
    Node* next = nullptr;

    do {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    } while (curr != head);

    // Update head & tail after full reversal
    tail = head;
    head = prev;
  }

  /* -------------------------------------------------------
     SPLIT INTO TWO CIRCULAR LISTS (TORTOISE-HARE APPROACH)
  ------------------------------------------------------- */
  void splitIntoTwo(CircularList& first, CircularList& second) {
    if (head == nullptr || head == tail) {
      cout << "Not enough nodes to split\n";
      return;
    }

    Node* slow = head;
    Node* fast = head;

    // Tortise-Hare to find mid
    while (fast->next != head && fast->next->next != head) {
      slow = slow->next;
      fast = fast->next->next;
    }

    // slow = end of first half
    first.head = head;
    first.tail = slow;
    first.tail->next = first.head;

    second.head = slow->next;
    second.tail = tail;
    second.tail->next = second.head;
  }

  /* -------------------------------------------------------
     PRINT LIST (HEAD → BACK TO HEAD)
  ------------------------------------------------------- */
  void printList() {
    if (head == nullptr) {
      cout << "List is Empty\n";
      return;
    }

    Node* temp = head;
    do {
      cout << temp->data << "=>";
      temp = temp->next;
    } while (temp != head);

    cout << "HEAD\n";
  }
};

/* ======================================================
                     DRIVER CODE
======================================================= */
int main() {
  CircularList cl;

  cl.insertAtHead(3);
  cl.insertAtHead(2);
  cl.insertAtHead(1);

  cl.insertAtTail(4);
  cl.insertAtTail(5);

  cout << "Original List: ";
  cl.printList();

  cout << "Length = " << cl.length() << endl;

  cout << "Search 4 at position: " << cl.search(4) << endl;

  cl.insertAtPosition(3, 99);
  cl.printList();

  cl.deleteAtPosition(3);
  cl.printList();

  cout << "Reversed: ";
  cl.reverse();
  cl.printList();

  cout << "Is Circular? " << (cl.isCircular() ? "Yes" : "No") << endl;

  CircularList first, second;
  cl.splitIntoTwo(first, second);

  cout << "\nFirst Half: ";
  first.printList();

  cout << "Second Half: ";
  second.printList();

  return 0;
}
