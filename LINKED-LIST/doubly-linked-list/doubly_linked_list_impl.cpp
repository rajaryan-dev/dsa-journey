#include <iostream>
using namespace std;

/* ------------------------------------------------------
   NODE OF DOUBLY LINKED LIST
---------------------------------------------------------*/
class Node {
 public:
  int data;
  Node* next;
  Node* prev;

  Node(int val) {
    data = val;
    next = prev = NULL;
  }
};

/* ------------------------------------------------------
   DOUBLY LINKED LIST CLASS
---------------------------------------------------------*/
class DoublyList {
 private:
  Node* head;
  Node* tail;

 public:
  DoublyList() { head = tail = NULL; }

  /* ======================================================
     INSERT AT FRONT (O(1))
  =======================================================*/
  void push_front(int val) {
    Node* newNode = new Node(val);

    if (head == NULL) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
  }

  /* ======================================================
     INSERT AT BACK (O(1))
  =======================================================*/
  void push_back(int val) {
    Node* newNode = new Node(val);

    if (head == NULL) {
      head = tail = newNode;
    } else {
      newNode->prev = tail;
      tail->next = newNode;
      tail = newNode;
    }
  }

  /* ======================================================
     POP FRONT — DELETE FIRST NODE (O(1))
  =======================================================*/
  void pop_front() {
    if (head == NULL) {
      cout << "List is already empty\n";
      return;
    }

    Node* temp = head;

    if (head == tail) {
      // Only one node
      head = tail = NULL;
    } else {
      head = head->next;
      head->prev = NULL;
    }

    delete temp;
  }

  /* ======================================================
     POP BACK — DELETE LAST NODE (O(1))
  =======================================================*/
  void pop_back() {
    if (head == NULL) {
      cout << "List is empty\n";
      return;
    }

    Node* temp = tail;

    if (head == tail) {
      head = tail = NULL;
    } else {
      tail = tail->prev;
      tail->next = NULL;
    }

    delete temp;
  }

  /* ======================================================
     INSERT AT POSITION (1-based Index)
     Position 1 → push_front
     Position > length → push_back
  =======================================================*/
  void insert_at(int pos, int val) {
    if (pos == 1) {
      push_front(val);
      return;
    }

    Node* newNode = new Node(val);
    Node* temp = head;
    int count = 1;

    while (temp != NULL && count < pos - 1) {
      temp = temp->next;
      count++;
    }

    if (temp == NULL) {
      // Position is out of range → insert at end
      push_back(val);
      return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL)
      temp->next->prev = newNode;
    else
      tail = newNode;  // inserting at last

    temp->next = newNode;
  }

  /* ======================================================
     DELETE AT POSITION (1-based Index)
  =======================================================*/
  void delete_at(int pos) {
    if (head == NULL) {
      cout << "List is empty!\n";
      return;
    }

    if (pos == 1) {
      pop_front();
      return;
    }

    Node* temp = head;
    int count = 1;

    while (temp != NULL && count < pos) {
      temp = temp->next;
      count++;
    }

    if (temp == NULL) {
      cout << "Position out of range\n";
      return;
    }

    if (temp->next != NULL)
      temp->next->prev = temp->prev;
    else
      tail = temp->prev;  // deleting last node

    temp->prev->next = temp->next;

    delete temp;
  }

  /* ======================================================
     SEARCH VALUE — RETURN POSITION
  =======================================================*/
  int search(int key) {
    Node* temp = head;
    int pos = 1;

    while (temp != NULL) {
      if (temp->data == key) return pos;
      temp = temp->next;
      pos++;
    }

    return -1;  // not found
  }

  /* ======================================================
     REVERSE THE LIST (O(n))
     Swap next and prev pointers for every node.
  =======================================================*/
  void reverse() {
    Node* temp = NULL;
    Node* current = head;

    while (current != NULL) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;  // move using swapped pointer
    }

    if (temp != NULL) head = temp->prev;  // new head
  }

  /* ======================================================
     PRINT FORWARD (HEAD → TAIL)
  =======================================================*/
  void print() {
    Node* temp = head;
    while (temp != NULL) {
      cout << temp->data << "<=>";
      temp = temp->next;
    }
    cout << "NULL\n";
  }

  /* ======================================================
     PRINT REVERSE (TAIL → HEAD)
  =======================================================*/
  void print_reverse() {
    Node* temp = tail;
    while (temp != NULL) {
      cout << temp->data << "<=>";
      temp = temp->prev;
    }
    cout << "NULL\n";
  }
};

/* ======================================================
                DRIVER CODE FOR TESTING
=======================================================*/
int main() {
  DoublyList dll;

  dll.push_front(3);
  dll.push_front(2);
  dll.push_front(1);
  dll.print();

  dll.push_back(4);
  dll.push_back(5);
  dll.print();

  dll.pop_front();
  dll.print();

  dll.pop_back();
  dll.print();

  dll.insert_at(2, 10);
  dll.print();

  dll.delete_at(3);
  dll.print();

  cout << "Searching 10 at position: " << dll.search(10) << endl;

  dll.reverse();
  dll.print();

  cout << "Reverse print: ";
  dll.print_reverse();

  return 0;
}
