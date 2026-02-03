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
    left = nullptr;
    right = nullptr;
  }
};

Node* rightMostInLeftSubtree(Node* root) {
  Node* ans;
  while (root != nullptr) {
    ans = root;
    root = root->right;
  }
  return ans;
};

Node* leftMostInRightSubtree(Node* root) {
  Node* ans;
  while (root != nullptr) {
    ans = root;
    root = root->left;
  }
  return ans;
};

vector<int> getPredSucc(Node* root, int key) {
  Node* curr = root;
  Node* pred = nullptr;
  Node* succ = nullptr;

  while (curr != nullptr) {
    if (key < curr->val) {
      succ = curr;
      curr = curr->left;
    } else if (key > curr->val) {
      pred = curr;
      curr = curr->right;
    } else {
      if (curr->left != nullptr) {
        pred = rightMostInLeftSubtree(curr->left);
      }

      if (curr->right != nullptr) {
        succ = leftMostInRightSubtree(curr->right);
      }

      break;
    }
  }
  return {pred->val, succ->val};
};

int main() {
  Node* root = new Node(6);
  root->left = new Node(4);
  root->right = new Node(8);
  root->left->left = new Node(1);
  root->left->right = new Node(5);
  root->right->left = new Node(7);
  root->right->right = new Node(9);

  int key = 7;
  vector<int> ans = getPredSucc(root, key);
  cout << "predecessor: " << ans[0] << endl;
  cout << "successor: " << ans[1] << endl;

  return 0;
}