#include <bits/stdc++.h>
using namespace std;

// LeetCode 225. Implement Stack using Queues
// Using TWO queues
class MyStack {
 public:
  queue<int> q1;  // main queue which behaves like stack
  queue<int> q2;  // helper queue

  MyStack() {}

  // Push element x onto stack.
  void push(int x) {
    // Step 1: Push new element into q2
    q2.push(x);

    // Step 2: Move all elements from q1 -> q2
    while (!q1.empty()) {
      q2.push(q1.front());
      q1.pop();
    }

    // Step 3: Swap q1 and q2
    swap(q1, q2);
  }

  // Removes the element on top of the stack and returns it.
  int pop() {
    int val = q1.front();
    q1.pop();
    return val;
  }

  // Get the top element.
  int top() { return q1.front(); }

  // Returns whether the stack is empty.
  bool empty() { return q1.empty(); }
};

// =========================
//      DRIVER CODE
// =========================
int main() {
  MyStack st;

  cout << "Pushing 1\n";
  st.push(1);

  cout << "Pushing 2\n";
  st.push(2);

  cout << "Current Top: " << st.top() << endl;  // should print 2

  cout << "Popping: " << st.pop() << endl;  // should print 2

  cout << "Is Empty? " << (st.empty() ? "Yes" : "No") << endl;

  cout << "Pushing 5\n";
  st.push(5);

  cout << "Top Now: " << st.top() << endl;  // should print 5

  return 0;
}
