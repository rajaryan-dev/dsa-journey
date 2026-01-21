#include <iostream>
#include <vector>
using namespace std;

// Class definition for the Stack data structure
class Stack {
  // We use a vector to store the stack elements.
  // Vectors are dynamic arrays that handle memory management automatically.
  vector<int> v;

 public:
  // Function to add an element to the top of the stack (Push operation)
  // Time Complexity: O(1) in most cases (amortized)
  void push(int val) {
    // v.push_back() adds the element to the end of the vector,
    // which acts as the "top" of our stack.
    v.push_back(val);
  }

  // Function to remove the top element from the stack (Pop operation)
  // Time Complexity: O(1)
  void pop() {
    // First, we should check if the stack is not empty to avoid errors
    if (v.empty()) {
      cout << "Stack Underflow: The stack is empty!" << endl;
      return;
    }
    // v.pop_back() removes the last element from the vector,
    // effectively removing the "top" element of the stack.
    v.pop_back();
  }

  // Function to retrieve the top element without removing it (Peek/Top
  // operation) Time Complexity: O(1)
  int top() {
    if (v.empty()) {
      cout << "Stack is empty!" << endl;
      return -1;  // Return -1 or throw an error indicating empty stack
    }
    // v.back() returns the last element in the vector, which corresponds to the
    // top.
    return v.back();
  }

  // Function to check if the stack is empty
  // Time Complexity: O(1)
  bool empty() {
    // v.size() returns the number of elements. If it is 0, the stack is empty.
    // Alternatively, we can simply return v.empty().
    return v.size() == 0;
  }
};

int main() {
  Stack s;

  // Pushing elements onto the stack
  s.push(10);
  s.push(20);
  s.push(30);

  // Taking elements out (LIFO order: Last In, First Out)
  // We expect 30 to come out first, then 20, then 10.
  while (!s.empty()) {
    cout << s.top() << " ";  // Print the top element
    s.pop();                 // Remove the top element
  }

  cout << endl;
  return 0;
}
