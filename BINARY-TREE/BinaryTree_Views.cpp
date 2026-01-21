#include <iostream>
#include <map>    // Required for storing horizontal distance mappings
#include <queue>  // Required for Level Order Traversal (BFS)
#include <vector>
using namespace std;

// ======================================================================================
// NODE STRUCTURE
// ======================================================================================
// A Binary Tree Node contains:
// 1. Data: The value stored in the node
// 2. Left Pointer: Address of the left child
// 3. Right Pointer: Address of the right child

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
// We build the tree using a 'Preorder' sequence (Root -> Left -> Right).
// The sequence includes '-1' to indicate where a NULL node exists.
//
// Algorithm:
// 1. Take the current value from the sequence using the static index
// 2. If the value is -1, return NULL (no node exists here)
// 3. Create a new Node with the current value
// 4. Recursively build the Left Subtree
// 5. Recursively build the Right Subtree
// 6. Return the created node
//
// Time Complexity: O(N) where N is the number of nodes
// Space Complexity: O(H) where H is the height (recursion stack)

static int idx =
    -1;  // Static variable to track current index in the preorder vector

Node* buildTree(const vector<int>& preorder) {
  idx++;  // Move to the next element in the sequence

  // Base Case: If we encounter -1, it means no node exists here
  if (preorder[idx] == -1) {
    return NULL;
  }

  // Create the new node with current value
  Node* root = new Node(preorder[idx]);

  // Recursively build the left and right subtrees
  root->left = buildTree(preorder);   // Build Left Subtree
  root->right = buildTree(preorder);  // Build Right Subtree

  return root;  // Return the created node
}

// ======================================================================================
// LEVEL ORDER TRAVERSAL (Breadth First Search - BFS)
// ======================================================================================
// Traverse the tree level by level, visiting all nodes at current depth before
// moving to the next depth. This is implemented using a QUEUE data structure.
//
// Algorithm:
// 1. Push the Root node into the Queue
// 2. Push NULL into the Queue to mark the end of the first level
// 3. While the Queue is not empty:
//    a. Pop a Node from the front
//    b. If the Node is NULL:
//       - We have finished traversing a level. Print a newline
//       - If the Queue is still not empty, push another NULL to mark end of
//       next level
//    c. If the Node is NOT NULL:
//       - Print its data
//       - If it has a Left Child, push it to the Queue
//       - If it has a Right Child, push it to the Queue
//
// Time Complexity: O(N) where N is the number of nodes
// Space Complexity: O(W) where W is the maximum width of the tree

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
      // If queue is empty, we are done. If not, push NULL for the next level
      if (!q.empty()) {
        q.push(NULL);
      }
    } else {
      cout << curr->data << " ";

      // Add left and right children to the queue if they exist
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
// TOP VIEW OF A BINARY TREE
// ======================================================================================
// The Top View of a binary tree is the set of nodes visible when the tree is
// viewed from the top. We see only the topmost node at each horizontal
// distance.
//
// CONCEPT: Horizontal Distance (HD)
// - Root node has HD = 0
// - Left child has HD = parent's HD - 1
// - Right child has HD = parent's HD + 1
//
// Algorithm:
// 1. Use a Queue to perform level order traversal, storing pairs of (Node, HD)
// 2. Use a Map to store the first node encountered at each horizontal distance
//    - Key: Horizontal Distance (HD)
//    - Value: Node's data value
// 3. For each node:
//    a. If this HD is NOT in the map, add it (first node at this HD from top)
//    b. Add left child with HD-1 to queue
//    c. Add right child with HD+1 to queue
// 4. Print all values from the map in sorted order of HD (left to right)
//
// Example Tree:
//        1
//       / \
//      2   3
//         / \
//        4   5
//
// HD:   -1   0   1   2
// Top:   2   1   3   5
//
// Time Complexity: O(N log N) due to map operations
// Space Complexity: O(N) for queue and map

void topView(Node* root) {
  // Edge case: empty tree
  if (root == NULL) {
    return;
  }

  // Queue stores pairs of [Node, Horizontal_Distance]
  queue<pair<Node*, int>> q;

  // Map stores [Horizontal_Distance -> Node's data value]
  // Using map (not unordered_map) to maintain sorted order of HD
  map<int, int> m;

  // Start with root at horizontal distance 0
  q.emplace(root, 0);  // emplace() creates the pair in-place (more efficient)

  while (!q.empty()) {
    // Extract the front node and its horizontal distance
    Node* curr = q.front().first;
    int currHD = q.front().second;
    q.pop();

    // If this horizontal distance is seen for the first time,
    // this is the topmost node at this HD (store it)
    if (m.find(currHD) == m.end()) {
      m[currHD] = curr->data;
    }

    // Add left child with HD-1 (moving left decreases HD)
    if (curr->left != NULL) {
      q.emplace(curr->left, currHD - 1);
    }

    // Add right child with HD+1 (moving right increases HD)
    if (curr->right != NULL) {
      q.emplace(curr->right, currHD + 1);
    }
  }

  // Print the top view from left to right (map is sorted by key/HD)
  for (auto it : m) {
    cout << it.second << " ";
  }
  cout << endl;
}

// ======================================================================================
// BOTTOM VIEW OF A BINARY TREE
// ======================================================================================
// The Bottom View of a binary tree is the set of nodes visible when the tree is
// viewed from the bottom. We see only the bottommost node at each horizontal
// distance.
//
// CONCEPT: Similar to Top View, but we keep UPDATING the map
// - Instead of storing only the first node at each HD, we store the LAST node
// - This is achieved by continuously overwriting the map value for each HD
//
// Algorithm:
// 1. Use a Queue to perform level order traversal, storing pairs of (Node, HD)
// 2. Use a Map to store the last node encountered at each horizontal distance
//    - Key: Horizontal Distance (HD)
//    - Value: Node's data value
// 3. For each node:
//    a. ALWAYS update the map at this HD (overwrite previous value)
//    b. Add left child with HD-1 to queue
//    c. Add right child with HD+1 to queue
// 4. Print all values from the map in sorted order of HD (left to right)
//
// Example Tree:
//        1
//       / \
//      2   3
//         / \
//        4   5
//
// HD:      -1   0   1   2
// Bottom:   2   4   3   5
//
// Time Complexity: O(N log N) due to map operations
// Space Complexity: O(N) for queue and map

void bottomView(Node* root) {
  // Edge case: empty tree
  if (root == NULL) {
    return;
  }

  // Queue stores pairs of [Node, Horizontal_Distance]
  queue<pair<Node*, int>> q;

  // Map stores [Horizontal_Distance -> Node's data value]
  map<int, int> m;

  // Start with root at horizontal distance 0
  q.emplace(root, 0);

  while (!q.empty()) {
    // Extract the front node and its horizontal distance
    Node* curr = q.front().first;
    int currHD = q.front().second;
    q.pop();

    // ALWAYS update the map at this HD (this ensures we keep the bottommost
    // node) Unlike top view, we don't check if HD exists - we overwrite it
    m[currHD] = curr->data;

    // Add left child with HD-1
    if (curr->left != NULL) {
      q.emplace(curr->left, currHD - 1);
    }

    // Add right child with HD+1
    if (curr->right != NULL) {
      q.emplace(curr->right, currHD + 1);
    }
  }

  // Print the bottom view from left to right
  for (auto it : m) {
    cout << it.second << " ";
  }
  cout << endl;
}

// ======================================================================================
// KTH LEVEL OF A BINARY TREE
// ======================================================================================
// Print all nodes at the Kth level of the binary tree.
// Level numbering starts from 1 (root is at level 1).
//
// CONCEPT: Use recursion to traverse down the tree
// - At each recursive call, decrease K by 1
// - When K becomes 1, we've reached the target level - print the node
//
// Algorithm:
// 1. Base Case: If root is NULL, return
// 2. If K == 1, we are at the target level - print current node's data
// 3. Otherwise, recursively call for left and right subtrees with K-1
//
// Example Tree:
//        1         (Level 1)
//       / \
//      2   3       (Level 2)
//         / \
//        4   5     (Level 3)
//
// kthLevel(root, 2) will print: 2 3
// kthLevel(root, 3) will print: 4 5
//
// Time Complexity: O(N) in worst case (visiting all nodes)
// Space Complexity: O(H) where H is height (recursion stack)

void kthLevel(Node* root, int K) {
  // Base Case: If node is NULL, return
  if (root == NULL) {
    return;
  }

  // If K is 1, we are at the target level - print this node
  if (K == 1) {
    cout << root->data << " ";
    return;
  }

  // Recursively traverse left and right subtrees with K-1
  // This effectively moves down one level in the tree
  kthLevel(root->left, K - 1);
  kthLevel(root->right, K - 1);
}

// Transform to Sum Tree
int sumTree(Node* root) {
  if (root == NULL) {
    return 0;
  }

  int leftSumTree = sumTree(root->left);
  int rightSumTree = sumTree(root->right);

  root->data = leftSumTree + rightSumTree + root->data;
  return root->data;
}

// ======================================================================================
// MAIN FUNCTION
// ======================================================================================
int main() {
  // Preorder sequence to build the tree
  // Sequence: 1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1
  // This creates the following tree:
  //        1
  //       / \
  //      2   3
  //         / \
  //        4   5
  //
  // Explanation of sequence:
  // - 1: Root node
  // - 2: Left child of 1
  //   - -1: No left child of 2
  //   - -1: No right child of 2
  // - 3: Right child of 1
  //   - 4: Left child of 3
  //     - -1: No left child of 4
  //     - -1: No right child of 4
  //   - 5: Right child of 3
  //     - -1: No left child of 5
  //     - -1: No right child of 5

  vector<int> preorder = {1, 2, -1, -1, 3, 4, -1, -1, 5, -1, -1};

  cout << "Building Binary Tree from Preorder Sequence..." << endl;
  Node* root = buildTree(preorder);

  cout << "\n========================================" << endl;
  cout << "TREE STRUCTURE:" << endl;
  cout << "========================================" << endl;
  cout << "       1       " << endl;
  cout << "      / \\      " << endl;
  cout << "     2   3     " << endl;
  cout << "        / \\    " << endl;
  cout << "       4   5   " << endl;
  cout << "========================================" << endl;

  // Display Level Order Traversal for reference
  cout << "\nLevel Order Traversal (for reference):" << endl;
  levelOrder(root);

  // Test Top View
  cout << "\n========================================" << endl;
  cout << "TOP VIEW:" << endl;
  cout << "========================================" << endl;
  cout << "Nodes visible from top: ";
  topView(root);
  cout << "(Expected: 2 1 3 5)" << endl;

  // Test Bottom View
  cout << "\n========================================" << endl;
  cout << "BOTTOM VIEW:" << endl;
  cout << "========================================" << endl;
  cout << "Nodes visible from bottom: ";
  bottomView(root);
  cout << "(Expected: 2 4 3 5)" << endl;

  // Test Kth Level
  cout << "\n========================================" << endl;
  cout << "KTH LEVEL NODES:" << endl;
  cout << "========================================" << endl;

  int level = 1;
  cout << "Nodes at Level " << level << ": ";
  kthLevel(root, level);
  cout << "(Expected: 1)" << endl;

  level = 2;
  cout << "Nodes at Level " << level << ": ";
  kthLevel(root, level);
  cout << "(Expected: 2 3)" << endl;

  level = 3;
  cout << "Nodes at Level " << level << ": ";
  kthLevel(root, level);
  cout << "(Expected: 4 5)" << endl;

  cout << "\n========================================" << endl;

  // Test Sum Tree

  cout << "Sum Tree: " << sumTree(root) << endl;

  return 0;
}
