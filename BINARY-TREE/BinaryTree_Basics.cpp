#include <iostream>
#include <queue>  // Required for Level Order Traversal (BFS)
#include <vector>
using namespace std;

// ======================================================================================
// CONCEPT: TREES
// ======================================================================================
// A Tree is a non-linear hierarchical data structure.
// Unlike Arrays, Linked Lists, Stacks, and Queues, which are linear data
// structures, trees organize data hierarchically.
//
// Key Terminologies:
// 1. **Root**: The top-most node of the tree.
// 2. **Node**: An entity that contains a key or value and pointers to its child
// nodes.
// 3. **Parent**: The node which is a predecessor of a node.
// 4. **Child**: The node which is the immediate successor of a node.
// 5. **Leaf**: A node that has no children (both left and right are NULL).
// 6. **Subtree**: A tree consisting of a node and all of its descendants.

// ======================================================================================
// CONCEPT: BINARY TREE
// ======================================================================================
// A Binary Tree is a specific type of tree where each node has at most TWO
// children. These children are typically referred to as the 'Left Child' and
// the 'Right Child'.
//
// Each Node in a Binary Tree consists of three parts:
// 1. **Data**: The value stored in the node.
// 2. **Left Pointer**: Address of the left child.
// 3. **Right Pointer**: Address of the right child.

class Node {
 public:
  int data;     // Data value stored in the node
  Node* left;   // Pointer to the left child node
  Node* right;  // Pointer to the right child node

  // Constructor to initialize a new node
  Node(int val) {
    data = val;
    left = NULL;  // Initially, a new node has no children
    right = NULL;
  }
};

// ======================================================================================
// BUILDING A BINARY TREE (from Preorder Sequence)
// ======================================================================================
// We will build the tree using a 'Preorder' sequence (Root -> Left -> Right).
// The sequence includes '-1' (or NULL) to indicate where a leaf node ends.
//
// Algorithm:
// 1. Take the current value from the sequence.
// 2. If the value is -1, return NULL (base case for recursion).
// 3. Create a new Node with the current value.
// 4. Recursively build the Left Subtree.
// 5. Recursively build the Right Subtree.
// 6. Return the current Node.

static int idx =
    -1;  // Static variable to keep track of the current index in the vector

Node* buildTree(const vector<int>& preorder) {
  idx++;  // Move to the next element in the sequence

  // Base Case: If we encounter -1, it means no node exists here.
  if (preorder[idx] == -1) {
    return NULL;
  }

  // Create the new node
  Node* root = new Node(preorder[idx]);

  // Recursively build the left and right subtrees
  root->left = buildTree(preorder);   // Build Left
  root->right = buildTree(preorder);  // Build Right

  return root;  // Return the created node
}

// ======================================================================================
// TRAVERSALS
// ======================================================================================
// Traversing a tree means visiting every node in the tree exactly once.
// There are three main depth-first traversal methods:

// 1. PREORDER Traversal (Root -> Left -> Right)
//    - Process the Root.
//    - Traverse the Left subtree.
//    - Traverse the Right subtree.
void preOrder(Node* root) {
  if (root == NULL) {  // Base case: If node is NULL, return
    return;
  }

  cout << root->data << " ";  // Print Root
  preOrder(root->left);       // Visit Left
  preOrder(root->right);      // Visit Right
}

// 2. INORDER Traversal (Left -> Root -> Right)
//    - Traverse the Left subtree.
//    - Process the Root.
//    - Traverse the Right subtree.
void inOrder(Node* root) {
  if (root == NULL) {
    return;
  }

  inOrder(root->left);        // Visit Left
  cout << root->data << " ";  // Print Root
  inOrder(root->right);       // Visit Right
}

// 3. POSTORDER Traversal (Left -> Right -> Root)
//    - Traverse the Left subtree.
//    - Traverse the Right subtree.
//    - Process the Root.
void postOrder(Node* root) {
  if (root == NULL) {
    return;
  }

  postOrder(root->left);      // Visit Left
  postOrder(root->right);     // Visit Right
  cout << root->data << " ";  // Print Root
}

// 4. LEVEL ORDER Traversal (Breadth First Search - BFS)
//    - Traverse the tree level by level.
//    - Visit all nodes at current depth before moving to the next depth.
//    - This is typically implemented using a QUEUE data structure.
//
// Algorithm:
// 1. Push the Root node into the Queue.
// 2. Push NULL into the Queue to mark the end of the first level.
// 3. While the Queue is not empty:
//    a. Pop a Node from the front.
//    b. If the Node is NULL:
//       - We have finished traversing a level. Print a newline.
//       - If the Queue is still not empty, push another NULL to mark end of
//       next level.
//    c. If the Node is NOT NULL:
//       - Print its data.
//       - If it has a Left Child, push it to the Queue.
//       - If it has a Right Child, push it to the Queue.

void levelOrder(Node* root) {
  if (root == NULL) {
    return;
  }

  queue<Node*> q;
  q.push(root);
  q.push(NULL);  // Mark end of level 0

  while (!q.empty()) {
    Node* curr = q.front();
    q.pop();

    if (curr == NULL) {
      cout << endl;  // Newline for next level
      // If queue is empty, we are done. If not, push NULL for the next level.
      if (!q.empty()) {
        q.push(NULL);
      }
    } else {
      cout << curr->data << " ";

      if (curr->left != NULL) {
        q.push(curr->left);
      }
      if (curr->right != NULL) {
        q.push(curr->right);
      }
    }
  }
}

// ======================================================================================
// CONCEPT: HEIGHT OF A TREE
// ======================================================================================
// The height of a tree is the number of nodes along the longest path from the
// root to the farthest leaf. Formula: Height = 1 + max(Height(Left),
// Height(Right)) Time Complexity: O(N)
int height(Node* root) {
  if (root == NULL) {
    return 0;
  }

  int leftHt = height(root->left);
  int rightHt = height(root->right);

  return max(leftHt, rightHt) + 1;
}

// ======================================================================================
// CONCEPT: COUNT OF NODES
// ======================================================================================
// Total number of nodes in the tree.
// Formula: Count = 1 (Root) + Count(Left) + Count(Right)
// Time Complexity: O(N)
int countNode(Node* root) {
  if (root == NULL) {
    return 0;
  }

  int leftCount = countNode(root->left);
  int rightCount = countNode(root->right);

  return leftCount + rightCount + 1;
}

// ======================================================================================
// CONCEPT: SUM OF NODES
// ======================================================================================
// Sum of all data values in the tree.
// Formula: Sum = Root.data + Sum(Left) + Sum(Right)
// Time Complexity: O(N)
int sum(Node* root) {
  if (root == NULL) {
    return 0;
  }

  int leftSum = sum(root->left);
  int rightSum = sum(root->right);

  return leftSum + rightSum + root->data;
}

// ======================================================================================
// MAIN FUNCTION
// ======================================================================================
int main() {
  // Input sequence for building the tree.
  // Sequence: 1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1
  // (Note: The previous sequence in code.cpp was a bit different, I'm using the
  // one that matches the structure:
  //      1
  //     / \
  //    2   3
  //   / \   \
  //  4   5   6
  // But let's stick to the user's original array elements to preserve their
  // intended tree if possible, or use a clear example. User's original: {1, 2,
  // -1, -1, 3, 4, -1, -1, 5, -1, -1} Let's analyze User's Tree again: Root: 1
  // Left Child: 2
  //    Left of 2: -1 (NULL)
  //    Right of 2: -1 (NULL)
  // Right Child: 3
  //    Left of 3: 4
  //       Left of 4: -1
  //       Right of 4: -1
  //    Right of 3: 5
  //       Left of 5: -1
  //       Right of 5: -1
  // Resulting Tree:
  //      1
  //     / \
  //    2   3
  //       / \
  //      4   5

  vector<int> preorder = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

  cout << "Building Tree from Preorder Sequence..." << endl;
  Node* root = buildTree(preorder);

  cout << "\n--------------------------------------------------" << endl;
  cout << "Preorder Traversal (Root -> Left -> Right): ";
  preOrder(root);
  cout << "\n(Expected: 1 2 3 4 5)" << endl;

  cout << "\n--------------------------------------------------" << endl;
  cout << "Inorder Traversal (Left -> Root -> Right):  ";
  inOrder(root);
  cout << "\n(Expected: 2 1 4 3 5)" << endl;

  cout << "\n--------------------------------------------------" << endl;
  cout << "Postorder Traversal (Left -> Right -> Root): ";
  postOrder(root);
  cout << "\n(Expected: 2 4 5 3 1)" << endl;

  cout << "\n--------------------------------------------------" << endl;
  cout << "Level Order Traversal (BFS):" << endl;
  levelOrder(root);
  cout << "(Expected:\n1\n2 3\n4 5)" << endl;

  cout << "--------------------------------------------------" << endl;

  cout << "\n--------------------------------------------------" << endl;
  cout << "Tree Properties Analysis:" << endl;
  cout << "1. Height of Tree : " << height(root) << endl;
  cout << "2. Total Nodes    : " << countNode(root) << endl;
  cout << "3. Sum of Nodes   : " << sum(root) << endl;
  cout << "--------------------------------------------------" << endl;

  return 0;
}
