#include <iostream>
#include <list>
#include <vector>
using namespace std;

// Implementation of a Stack using the STL list (Doubly Linked List)
class Stack {
  // Underlying container: std::list is a doubly linked list.
  // We use the front of the list as the "top" of the stack.
  list<int> ll;

 public:
  // Pushes an element onto the stack.
  // Uses push_front to insert at the beginning of the list (O(1) operation).
  void push(int val) { ll.push_front(val); }

  // Removes the top element from the stack.
  // Uses pop_front to remove from the beginning of the list (O(1) operation).
  void pop() { ll.pop_front(); }

  // Returns the top element of the stack.
  // Uses front() to access the first element of the list (O(1) operation).
  int top() { return ll.front(); }

  // Checks if the stack is empty.
  bool empty() { return ll.size() == 0; }
};

int main() {
  Stack s;

  // Push elements onto the stack
  // Stack follows LIFO (Last In, First Out) principle
  s.push(10);
  s.push(20);
  s.push(30);

  // Print and remove elements from the stack
  // Expected output: 30 20 10 (Reverse order of insertion)
  while (!s.empty()) {
    cout << s.top() << " "; // Print the current top
    s.pop();                // Remove the current top
  }
  cout << endl;

  return 0;
}