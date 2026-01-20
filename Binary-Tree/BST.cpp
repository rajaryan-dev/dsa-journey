#include <iostream>
#include <vector>
using namespace std;

class Node {
 public:
  int data;
  Node* left;
  Node* right;

  Node(int val) {
    data = val;
    left = right = nullptr;
  }
};

Node* insert(Node* root, int val) {
  if (root == nullptr) {
    return new Node(val);
  }

  if (val < root->data) {
    root->left = insert(root->left, val);
  } else {
    root->right = insert(root->right, val);
  }

  return root;
}

Node* buildBST(vector<int> arr) {
  Node* root = nullptr;

  for (int val : arr) {
    root = insert(root, val);
  }

  return root;
}

void inorder(Node* root) {
  if (root == nullptr) {
    return;
  }

  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}

bool search(Node* root, int target) {  // Time_Complexity: O(height) or O(logn)
  if (root == nullptr) return false;
  if (root->data == target) return true;

  if (root->data > target) {
    return search(root->left, target);
  } else {
    return search(root->right, target);
  }
}

int main() {
  vector<int> arr = {3, 2, 1, 5, 6, 4};

  Node* root = buildBST(arr);
  inorder(root);
  cout << endl;
  search(root, 5) ? cout << "Found" : cout << "Not Found";

  return 0;
}