/**
 * @file BinarySearchTree_Basics.cpp
 * @brief Implementation of Basic Binary Search Tree (BST) operations.
 *
 * A Binary Search Tree is a binary tree where for every node:
 * 1. The left child's value is less than the node's value.
 * 2. The right child's value is greater than the node's value.
 *
 * This property enables efficient searching, insertion, and deletion operations,
 * typically taking O(log N) time on average.
 */

#include <iostream>
#include <vector>
using namespace std;

// Node structure definition for the BST
class Node {
 public:
  int data;
  Node* left;
  Node* right;

  // Constructor to initialize a new node
  Node(int val) {
    data = val;
    left = right = nullptr;
  }
};

/**
 * @brief Inserts a value into the BST maintaining the BST property.
 *
 * @param root Current root of the subtree.
 * @param val Value to insert.
 * @return Node* Pointer to the (potentially new) root of the subtree.
 *
 * Time Complexity: O(H) where H is the height of the tree.
 * Space Complexity: O(H) for recursion stack.
 */
Node* insert(Node* root, int val) {
  // Base Case: If the tree/subtree is empty, create a new node.
  if (root == nullptr) {
    return new Node(val);
  }

  // Recursive Step: Decide whether to go left or right.
  if (val < root->data) {
    // If value is smaller, it belongs in the left subtree.
    root->left = insert(root->left, val);
  } else {
    // If value is larger (or equal), it belongs in the right subtree.
    root->right = insert(root->right, val);
  }

  return root;
}

/**
 * @brief Builds a BST from a vector of integers.
 *
 * @param arr Vector containing elements to insert.
 * @return Node* Root of the constructed BST.
 */
Node* buildBST(const vector<int>& arr) {
  Node* root = nullptr;
  for (int val : arr) {
    root = insert(root, val);
  }
  return root;
}

/**
 * @brief Performs Inorder Traversal (Left -> Root -> Right).
 *
 * property: Inorder traversal of a BST always yields sorted values.
 *
 * @param root Root of the tree/subtree.
 */
void inorder(Node* root) {
  if (root == nullptr) {
    return;
  }

  inorder(root->left);        // Visit Left Subtree
  cout << root->data << " ";  // Visit Root
  inorder(root->right);       // Visit Right Subtree
}

/**
 * @brief Searches for a target value in the BST.
 *
 * @param root Root of the tree/subtree.
 * @param target Value to search for.
 * @return true if found, false otherwise.
 *
 * Time Complexity: O(H) - Efficiently eliminates half the tree at each step.
 */
bool search(Node* root, int target) {
  // Base Cases:
  // 1. Root is null (value not found).
  // 2. Root's data matches target (value found).
  if (root == nullptr) return false;
  if (root->data == target) return true;

  // Recursive Step: Navigate based on BST property.
  if (root->data > target) {
    // Target is smaller, search in left subtree.
    return search(root->left, target);
  } else {
    // Target is larger, search in right subtree.
    return search(root->right, target);
  }
}

int main() {
  // Input data for the BST
  vector<int> arr = {3, 2, 1, 5, 6, 4};

  cout << "Building BST from elements: ";
  for (int x : arr) cout << x << " ";
  cout << endl;

  // 1. Build the BST
  Node* root = buildBST(arr);

  // 2. Display Inorder Traversal (Should be sorted)
  cout << "Inorder Traversal (Sorted): ";
  inorder(root);
  cout << endl;

  // 3. Search Operation
  int target = 5;
  cout << "Searching for " << target << ": ";
  if (search(root, target)) {
    cout << "Found" << endl;
  } else {
    cout << "Not Found" << endl;
  }

  target = 10;
  cout << "Searching for " << target << ": ";
  if (search(root, target)) {
    cout << "Found" << endl;
  } else {
    cout << "Not Found" << endl;
  }

  return 0;
}
