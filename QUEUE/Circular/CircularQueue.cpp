#include <iostream>
using namespace std;

class CircularQueue {
    int *arr;
    int size;
    int front;
    int rear;

public:
    // Constructor to initialize the queue
    CircularQueue(int n) {
        size = n;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    // Function to add an element to the queue (Enqueue)
    void push(int data) {
        // Check if the queue is full
        // It is full if the next position of rear is front
        if ((rear + 1) % size == front) {
            cout << "Queue is Full (Overflow)\n";
            return;
        }

        // If queue is empty, initialize front and rear to 0
        if (front == -1) {
            front = 0;
            rear = 0;
        } else {
            // Circularly increment rear
            // If rear is at the last index, (rear + 1) % size becomes 0
            rear = (rear + 1) % size;
        }
        
        arr[rear] = data;
        cout << data << " pushed into queue\n";
    }

    // Function to remove an element from the queue (Dequeue)
    void pop() {
        // Check if queue is empty
        if (front == -1) {
            cout << "Queue is Empty (Underflow)\n";
            return;
        }

        int poppedData = arr[front];
        cout << poppedData << " popped from queue\n";

        // If there was only one element, reset the queue to empty state
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            // Circularly increment front
            // If front is at the last index, (front + 1) % size becomes 0
            front = (front + 1) % size;
        }
    }

    // Function to get the front element
    void peek() {
        if (front == -1) {
            cout << "Queue is Empty\n";
            return;
        }
        cout << "Front element: " << arr[front] << endl;
    }

    // Function to check if queue is empty
    bool isEmpty() {
        return front == -1;
    }
};

int main() {
    CircularQueue q(5);

    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    // Try pushing into a full queue
    q.push(60); 

    q.peek();
    q.pop();
    q.peek();
    q.pop();

    // Now we have space, so we can push again (demonstrating circular nature)
    q.push(60);
    q.peek();

    return 0;
}
