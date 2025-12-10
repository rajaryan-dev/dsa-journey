#include <iostream>
#include <queue> // Include the queue library

using namespace std;

int main() {
    // Declare a queue of integers using std::queue
    queue<int> q;

    // push(value): Adds 'value' to the end of the queue
    cout << "Pushing elements 10, 20, 30, 40..." << endl;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    
    // front(): Returns the element at the front
    cout << "Front element: " << q.front() << endl;

    // back(): Returns the element at the back
    cout << "Back element: " << q.back() << endl;

    // pop(): Removes the element from the front
    cout << "Popping one element..." << endl;
    q.pop();
    
    cout << "Front element after pop: " << q.front() << endl;

    // size(): Returns the number of elements in the queue
    cout << "Current size: " << q.size() << endl;

    // empty(): Returns true if the queue is empty
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl;

    cout << "\nTraversing the remaining queue elements:" << endl;
    // Note: To traverse a std::queue, we effectively empty it because we must pop to see the next element.
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    
    cout << "\nSize after traversal: " << q.size() << endl;

    return 0;
}
