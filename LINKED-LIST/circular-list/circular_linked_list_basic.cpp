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
  Node* head;
  Node* tail;

 public:
  CircularList() { head = tail = nullptr; }

  void insertAtHead(int val) {
    Node* newNode = new Node(val);

    if (tail == nullptr) {  // here we can also use if(head == nullptr)
      head = tail = newNode;
      tail->next = head;

    } else {
      newNode->next = head;  // or newNode->next = tail->next;
      head = newNode;        // or tail->next = newNode;
      tail->next = head;
    }
  }

  void insertAtTail(int val) {
    Node* newNode = new Node(val);

    if (tail == nullptr) {  // here we can also use if(head == nullptr)
      head = tail = newNode;
      tail->next = head;

    } else {
      newNode->next = head;
      tail->next = newNode;
      tail = newNode;
    }
  }

  void deleteAtHead() {
    if (head == nullptr) {
      cout << "List is Empty" << endl;
      return;
    } else if (head == tail) {
      delete head;
      head = tail = nullptr;
    } else {
      Node* temp = head;
      head = head->next;
      tail->next = head;
      temp->next = nullptr;
      delete temp;
    }
  }

  void deleteAtTail() {
    if (head == nullptr) {
      cout << "List is Empty" << endl;
      return;
    } else if (head == tail) {
      delete head;
      head = tail = nullptr;
    } else {
      Node* temp = tail;
      Node* prev = head;

      while (prev->next != tail) {
        prev = prev->next;
      }

      tail = prev;
      tail->next = head;
      temp->next = nullptr;
      delete temp;
    }
  }

  void printList() {
    if (head == nullptr) return;

    cout << head->data << "=>";

    Node* temp;
    temp = head->next;
    while (temp != head) {
      cout << temp->data << "=>";
      temp = temp->next;
    }
    cout << temp->data << endl;
  }
};

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