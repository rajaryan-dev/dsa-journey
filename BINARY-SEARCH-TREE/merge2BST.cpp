#include <iostream>
#include <vector>
using namespace std;

// Node Class representing a node in the Binary Search Tree
class Node {
 public:
  int val;
  Node* left;
  Node* right;

  Node(int data) {
    val = data;
    left = right = nullptr;
  }
};

// -------------------------------------------------------------
// Function to Insert a Node in a BST
// -------------------------------------------------------------
Node* insert(Node* root, int val) {
  if (root == nullptr) {
    return new Node(val);
  }

  if (root->val > val) {
    root->left = insert(root->left, val);
  } else {
    root->right = insert(root->right, val);
  }

  return root;
}

// -------------------------------------------------------------
// Helper to build a BST from a vector of values
// -------------------------------------------------------------
Node* buildBST(vector<int> arr) {
  Node* root = nullptr;
  for (int val : arr) {
    root = insert(root, val);
  }
  return root;
}

// -------------------------------------------------------------
// Step 1: Flatten the BST into a sorted sequence
// -------------------------------------------------------------
// Uses Inorder Traversal to store BST values in a sorted vector.
// Time Complexity: O(N) where N is the number of nodes
// Space Complexity: O(H) for recursion stack (H = Height of Tree)
void inorder(Node* root, vector<int>& arr) {
  if (root == nullptr) return;

  inorder(root->left, arr);
  arr.push_back(root->val);
  inorder(root->right, arr);
}

// -------------------------------------------------------------
// Step 3: Construct a Balanced BST from a Sorted Vector
// -------------------------------------------------------------
// Recursively builds the tree by picking the middle element as root.
// This ensures the resulting BST is height-balanced.
// Time Complexity: O(N)
// Space Complexity: O(log N) for recursion stack (since tree is balanced)
Node* buildBSTFromSorted(vector<int> arr, int st, int end) {
  if (st > end) return nullptr;

  int mid = st + (end - st) / 2;
  Node* root = new Node(arr[mid]);
  
  root->left = buildBSTFromSorted(arr, st, mid - 1);
  root->right = buildBSTFromSorted(arr, mid + 1, end);

  return root;
}

// -------------------------------------------------------------
// Main Function: Merge Two BSTs
// -------------------------------------------------------------
// Approach:
// 1. Convert BST1 -> Sorted Array 1 (via Inorder)
// 2. Convert BST2 -> Sorted Array 2 (via Inorder)
// 3. Merge two sorted arrays into one sorted array (Two Pointer approach)
// 4. Build a Balanced BST from the merged sorted array
//
// Overall Time Complexity: O(M + N)
// Overall Space Complexity: O(M + N) to store vectors
Node* merge2BST(Node* root1, Node* root2) {
  // Step 1: Flatten both BSTs
  vector<int> arr1, arr2;
  inorder(root1, arr1);  // O(M)
  inorder(root2, arr2);  // O(N)

  // Step 2: Merge two sorted vectors
  vector<int> temp;  // Stores final sorted elements
  int i = 0, j = 0;
  
  // Standard merge logic (similar to Merge Sort)
  while (i < arr1.size() && j < arr2.size()) {
    if (arr1[i] < arr2[j]) {
      temp.push_back(arr1[i++]);
    } else {
      temp.push_back(arr2[j++]);
    }
  }
  while (i < arr1.size()) {
    temp.push_back(arr1[i++]);
  }
  while (j < arr2.size()) {
    temp.push_back(arr2[j++]);
  }

  // Step 3: Build Balanced BST from merged sorted vector
  // TC: O(M+N)
  return buildBSTFromSorted(temp, 0, temp.size() - 1);  
}

int main() {
  // Example Input: Two sets of keys
  vector<int> arr1 = {8, 2, 1, 10};
  vector<int> arr2 = {5, 3, 0};

  // Build initial BSTs
  Node* root1 = buildBST(arr1);
  Node* root2 = buildBST(arr2);

  // Merge the BSTs
  Node* root = merge2BST(root1, root2);

  // Validate Output: Inorder traversal of merged BST should be sorted
  vector<int> seq;
  inorder(root, seq);
  
  cout << "Inorder Traversal of Merged BST: ";
  for (int v : seq) {
    cout << v << " ";
  }
  cout << endl;

  return 0;
}