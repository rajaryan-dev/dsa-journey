#include <iostream>
#include <vector>
using namespace std;

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

// Insert a Node in a BST
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

Node* buildBST(vector<int> arr) {
  Node* root = nullptr;

  for (int val : arr) {
    root = insert(root, val);
  }

  return root;
}

void inorder(Node* root, vector<int>& arr) {
  if (root == nullptr) return;

  inorder(root->left, arr);
  arr.push_back(root->val);
  inorder(root->right, arr);
}

Node* buildBSTFromSorted(vector<int> arr, int st, int end) {
  if (st > end) return nullptr;

  int mid = st + (end - st) / 2;
  Node* root = new Node(arr[mid]);
  root->left = buildBSTFromSorted(arr, st, mid - 1);
  root->right = buildBSTFromSorted(arr, mid + 1, end);

  return root;
}

Node* merge2BST(Node* root1, Node* root2) {  // TC: O(m+n)
  vector<int> arr1, arr2;
  inorder(root1, arr1);  // O(m)
  inorder(root2, arr2);  // O(n)

  vector<int> temp;  // final BST inorder : sorted

  // TC: O(m+n)
  int i = 0, j = 0;
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
  // TC: O(m+n)
  return buildBSTFromSorted(temp, 0, temp.size() - 1);  // sorted array, st, end
}

int main() {
  vector<int> arr1 = {8, 2, 1, 10};
  vector<int> arr2 = {5, 3, 0};

  Node* root1 = buildBST(arr1);
  Node* root2 = buildBST(arr2);

  Node* root = merge2BST(root1, root2);
  vector<int> seq;
  inorder(root, seq);
  for (int v : seq) {
    cout << v << " ";
  }
  cout << endl;

  return 0;
}