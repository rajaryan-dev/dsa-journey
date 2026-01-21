#include <iostream>

using namespace std;

// Node class for Doubly Linked List
class Node {
   public:
    int data;
    Node *next;
    Node *prev;

    Node(int d) {
        data = d;
        next = NULL;
        prev = NULL;
    }
};

class Deque {
    Node *front;
    Node *rear;

   public:
    Deque() {
        front = rear = NULL;
    }

    // Insert element at front
    void pushFront(int x) {
        Node *temp = new Node(x);
        if (front == NULL) {
            front = rear = temp;
        } else {
            temp->next = front;
            front->prev = temp;
            front = temp;
        }
    }

    // Insert element at rear
    void pushRear(int x) {
        Node *temp = new Node(x);
        if (rear == NULL) {
            front = rear = temp;
        } else {
            rear->next = temp;
            temp->prev = rear;
            rear = temp;
        }
    }

    // Delete element from front
    void popFront() {
        if (front == NULL) {
            cout << "Deque is empty" << endl;
            return;
        }
        Node *temp = front;
        front = front->next;

        if (front == NULL) {
            rear = NULL;
        } else {
            front->prev = NULL;
        }
        delete temp;
    }

    // Delete element from rear
    void popRear() {
        if (rear == NULL) {
            cout << "Deque is empty" << endl;
            return;
        }
        Node *temp = rear;
        rear = rear->prev;

        if (rear == NULL) {
            front = NULL;
        } else {
            rear->next = NULL;
        }
        delete temp;
    }

    // Get front element
    int getFront() {
        if (front == NULL) {
            return -1;
        }
        return front->data;
    }

    // Get rear element
    int getRear() {
        if (rear == NULL) {
            return -1;
        }
        return rear->data;
    }

    // Check if empty
    bool isEmpty() {
        return front == NULL;
    }
};

int main() {
    Deque dq;
    
    cout << "Pushing 10 at front, 20 at rear, 5 at front..." << endl;
    dq.pushFront(10);
    dq.pushRear(20);
    dq.pushFront(5); // Queue: 5, 10, 20

    cout << "Front: " << dq.getFront() << endl; // Should be 5
    cout << "Rear: " << dq.getRear() << endl;   // Should be 20

    cout << "Popping front..." << endl;
    dq.popFront(); // Queue: 10, 20
    cout << "Front after popFront: " << dq.getFront() << endl; // Should be 10

    cout << "Popping rear..." << endl;
    dq.popRear(); // Queue: 10
    cout << "Rear after popRear: " << dq.getRear() << endl; // Should be 10

    return 0;
}
