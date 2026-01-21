#include <iostream>
#include <unordered_map>
using namespace std;

/*
LeetCode 146. LRU Cache (Medium)

Design a data structure that follows the Least Recently Used (LRU) cache system.

LRUCache(int capacity)
    Initialize the LRU cache with positive size capacity.

int get(int key)
    Return the value of the key if the key exists, otherwise return -1.

void put(int key, int value)
    Update the value of the key if the key exists.
    Otherwise, insert the pair.
    When cache exceeds capacity → remove Least Recently Used element.

Both get() and put() must run in O(1).

Approach Used:
----------------------------------
Doubly Linked List + HashMap
    • DLL → maintains usage order
        Most Recently Used   → front (right after head)
        Least Recently Used  → back (just before tail)

    • HashMap → stores key -> node address for O(1) access
*/

class LRUCache {
 public:
  // Node for Doubly Linked List
  class Node {
   public:
    int key, val;
    Node* prev;
    Node* next;

    Node(int k, int v) {
      key = k;
      val = v;
      prev = next = nullptr;
    }
  };

  Node* head = new Node(-1, -1);  // dummy head
  Node* tail = new Node(-1, -1);  // dummy tail

  unordered_map<int, Node*> mp;  // maps key to node
  int cap;

  // Insert node right after head → Most Recently Used
  void addNode(Node* newNode) {
    Node* temp = head->next;

    head->next = newNode;
    newNode->prev = head;

    newNode->next = temp;
    temp->prev = newNode;
  }

  // Remove a node from DLL
  void deleteNode(Node* delNode) {
    Node* prevNode = delNode->prev;
    Node* nextNode = delNode->next;

    prevNode->next = nextNode;
    nextNode->prev = prevNode;
  }

  // Constructor
  LRUCache(int capacity) {
    cap = capacity;

    // Join head & tail initially
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (mp.find(key) == mp.end()) return -1;  // key not present

    Node* node = mp[key];
    int value = node->val;

    // Move node to front (MRU)
    mp.erase(key);
    deleteNode(node);
    addNode(node);
    mp[key] = node;

    return value;
  }

  void put(int key, int value) {
    // If key already exists → remove old
    if (mp.find(key) != mp.end()) {
      Node* existing = mp[key];
      mp.erase(key);
      deleteNode(existing);
    }

    // If cache full → remove LRU (before tail)
    if (mp.size() == cap) {
      Node* lru = tail->prev;
      mp.erase(lru->key);
      deleteNode(lru);
    }

    // Insert new node at MRU position
    Node* newNode = new Node(key, value);
    addNode(newNode);
    mp[key] = newNode;
  }
};

// ---------------------------------------------------------
// MAIN FUNCTION (FOR TESTING IN VS CODE)
// ---------------------------------------------------------
int main() {
  cout << "Testing LRU Cache Implementation\n\n";

  LRUCache cache(2);  // capacity = 2

  cache.put(1, 10);
  cache.put(2, 20);

  cout << "get(1) → " << cache.get(1) << endl;  // returns 10

  cache.put(3, 30);  // removes key 2

  cout << "get(2) → " << cache.get(2) << endl;  // returns -1 (removed)

  cache.put(4, 40);  // removes key 1

  cout << "get(1) → " << cache.get(1) << endl;  // returns -1
  cout << "get(3) → " << cache.get(3) << endl;  // returns 30
  cout << "get(4) → " << cache.get(4) << endl;  // returns 40

  return 0;
}
