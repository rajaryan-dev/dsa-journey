#include <iostream>

using namespace std;

// Node class representing each element in the linked list
class Node {
   public:
    int data;       // Data stored in the node
    Node *next;     // Pointer to the next node

    // Constructor to initialize a node with data
    Node(int d) {
        data = d;
        next = NULL;
    }
};

// Queue class implementation using Linked List
class Queue {
    Node *front;    // Points to the first element (head)
    Node *rear;     // Points to the last element (tail)

   public:
    // Constructor to initialize an empty queue
    Queue() {
        front = NULL;
        rear = NULL;
    }

    // Function to add an element to the queue (enqueue)
    void push(int x) {
        Node *temp = new Node(x);
        
        // If queue is empty, both front and rear point to the new node
        if (front == NULL) {
            front = temp;
            rear = temp;
            return;
        }
        
        // Link the new node to the end of the list and update rear
        rear->next = temp;
        rear = temp;
    }

    // Function to remove an element from the queue (dequeue)
    void pop() {
        if (front == NULL) {
            cout << "Queue is empty" << endl;
            return;
        }
        
        // Store the current front to delete it later
        Node *temp = front;
        // Move front to the next node
        front = front->next;
        
        // Delete the old front node to free memory
        delete temp;

        // If queue becomes empty after deletion, update rear to NULL
        if (front == NULL) {
            rear = NULL;
        }
    }

    // Function to get the front element of the queue
    int peek() {
        if (front == NULL) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return front->data;
    }

    // Function to check if the queue is empty
    bool empty() {
        return front == NULL;
    }
};

int main() {
    Queue q;
    
    // Adding elements to the queue
    q.push(10);
    q.push(20);
    q.push(30);

    cout << "Front element: " << q.peek() << endl;

    // Removing an element
    q.pop();
    cout << "Front element after pop: " << q.peek() << endl;

    // Removing remaining elements
    q.pop();
    q.pop();
    q.pop();  // Should print "Queue is empty"

    // Checking if queue is empty
    cout << "Is empty? " << (q.empty() ? "Yes" : "No") << endl;

    return 0;
}
