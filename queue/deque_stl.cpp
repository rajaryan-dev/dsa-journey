#include <iostream>
#include <deque>

using namespace std;

int main() {
    // Declare a deque of integers
    deque<int> dq;

    cout << "Pushing elements: 5 (front), 10 (back), 15 (back), 2 (front)..." << endl;
    // push_front(): Insert at the beginning
    dq.push_front(5);
    // push_back(): Insert at the end
    dq.push_back(10);
    dq.push_back(15);
    dq.push_front(2);
    
    // Current deque: 2, 5, 10, 15

    // Access elements
    cout << "Front element: " << dq.front() << endl; // Should be 2
    cout << "Back element: " << dq.back() << endl;   // Should be 15
    cout << "Element at index 1: " << dq.at(1) << endl; // Should be 5

    // Pop elements
    cout << "Popping front..." << endl;
    dq.pop_front(); // Removes 2
    cout << "New Front: " << dq.front() << endl; // Should be 5

    cout << "Popping back..." << endl;
    dq.pop_back(); // Removes 15
    cout << "New Back: " << dq.back() << endl; // Should be 10

    // Size and Empty check
    cout << "Size: " << dq.size() << endl;
    cout << "Is empty? " << (dq.empty() ? "Yes" : "No") << endl;

    // Traversal
    cout << "Deque elements: ";
    for (int x : dq) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
