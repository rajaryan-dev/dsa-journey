/*
 * ============================================================
 *  BST — Advanced Operations
 * ============================================================
 *  Topics:
 *   1. Floor and Ceil in BST
 *   2. Kth Smallest Element — LC 230
 *   3. Kth Largest Element
 *   4. LCA in BST — LC 235
 *   5. Convert BST to Sorted Doubly Linked List
 *   6. Two Sum in BST — LC 653
 *   7. Validate BST — LC 98
 *   8. BST Iterator — LC 173
 *   9. Count nodes in range [L, R] — LC 938
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Build BST by inserting values
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left  = insert(root->left,  val);
    else                  root->right = insert(root->right, val);
    return root;
}

// ─────────────────────────────────────────────────────────────
//  1. Floor in BST (largest value ≤ target)
//  Ceil  in BST (smallest value ≥ target)
// ─────────────────────────────────────────────────────────────
int floorBST(TreeNode* root, int target) {
    int floor = -1;
    while (root) {
        if (root->val == target) return root->val;
        if (root->val < target) { floor = root->val; root = root->right; }
        else                      root = root->left;
    }
    return floor;
}

int ceilBST(TreeNode* root, int target) {
    int ceil = -1;
    while (root) {
        if (root->val == target) return root->val;
        if (root->val > target) { ceil = root->val; root = root->left; }
        else                      root = root->right;
    }
    return ceil;
}

// ─────────────────────────────────────────────────────────────
//  2. Kth Smallest Element — LC 230
//  Use reverse inorder for Kth Largest
// ─────────────────────────────────────────────────────────────
int kthSmallest(TreeNode* root, int k) {
    int count = 0, result = -1;
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node || count >= k) return;
        inorder(node->left);
        if (++count == k) { result = node->val; return; }
        inorder(node->right);
    };
    inorder(root);
    return result;
}

int kthLargest(TreeNode* root, int k) {
    int count = 0, result = -1;
    function<void(TreeNode*)> reverseInorder = [&](TreeNode* node) {
        if (!node || count >= k) return;
        reverseInorder(node->right);
        if (++count == k) { result = node->val; return; }
        reverseInorder(node->left);
    };
    reverseInorder(root);
    return result;
}

// ─────────────────────────────────────────────────────────────
//  3. LCA in BST — LC 235  O(h) iterative
// ─────────────────────────────────────────────────────────────
int lcaBST(TreeNode* root, int p, int q) {
    while (root) {
        if (p < root->val && q < root->val)      root = root->left;
        else if (p > root->val && q > root->val) root = root->right;
        else return root->val;
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────
//  4. Convert BST to Sorted Doubly Linked List (in-place)
//  Use inorder traversal, thread prev→cur and cur→prev
// ─────────────────────────────────────────────────────────────
TreeNode* bstToDLL(TreeNode* root) {
    TreeNode *head = nullptr, *prev = nullptr;
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        node->left = prev;
        if (prev) prev->right = node;
        else head = node;
        prev = node;
        inorder(node->right);
    };
    inorder(root);
    return head;
}

// ─────────────────────────────────────────────────────────────
//  5. Two Sum in BST — LC 653
//  Use BST Iterator (inorder) + reverse iterator (reverse inorder)
//  Two-pointer approach: leftmost + rightmost
// ─────────────────────────────────────────────────────────────
bool findTargetInBST(TreeNode* root, int k) {
    // Collect inorder (sorted) then use two-pointer
    vector<int> arr;
    function<void(TreeNode*)> collect = [&](TreeNode* node) {
        if (!node) return;
        collect(node->left);
        arr.push_back(node->val);
        collect(node->right);
    };
    collect(root);
    int lo = 0, hi = arr.size() - 1;
    while (lo < hi) {
        if (arr[lo] + arr[hi] == k) return true;
        if (arr[lo] + arr[hi] <  k) lo++;
        else                         hi--;
    }
    return false;
}

// ─────────────────────────────────────────────────────────────
//  6. Validate BST — LC 98
//  Pass valid (min, max) range for each node
// ─────────────────────────────────────────────────────────────
bool isValidBST(TreeNode* node, long long mn = LLONG_MIN, long long mx = LLONG_MAX) {
    if (!node) return true;
    if (node->val <= mn || node->val >= mx) return false;
    return isValidBST(node->left,  mn,         node->val) &&
           isValidBST(node->right, node->val,  mx);
}

// ─────────────────────────────────────────────────────────────
//  7. Range Sum BST — LC 938
//  Sum of all values in [low, high]
// ─────────────────────────────────────────────────────────────
int rangeSumBST(TreeNode* root, int low, int high) {
    if (!root) return 0;
    int sum = 0;
    if (root->val >= low && root->val <= high) sum += root->val;
    if (root->val > low)  sum += rangeSumBST(root->left,  low, high);
    if (root->val < high) sum += rangeSumBST(root->right, low, high);
    return sum;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== BST Advanced Operations =====\n\n";

    //  BST:
    //        10
    //       /  \
    //      5   15
    //     / \    \
    //    3   7   20
    TreeNode* root = nullptr;
    for (int v : {10, 5, 15, 3, 7, 20})
        root = insert(root, v);

    cout << "BST values: {10,5,15,3,7,20}\n\n";

    cout << "1. Floor(6)  = " << floorBST(root, 6)  << "\n"; // 5
    cout << "   Ceil(6)   = " << ceilBST(root, 6)   << "\n"; // 7
    cout << "   Floor(15) = " << floorBST(root, 15) << "\n"; // 15
    cout << "   Ceil(16)  = " << ceilBST(root, 16)  << "\n"; // 20

    cout << "\n2. 1st Smallest: " << kthSmallest(root, 1) << "\n"; // 3
    cout << "   3rd Smallest: " << kthSmallest(root, 3) << "\n";   // 7
    cout << "   1st Largest:  " << kthLargest(root, 1)  << "\n";   // 20

    cout << "\n3. LCA(3, 7)  = " << lcaBST(root, 3, 7)   << "\n"; // 5
    cout << "   LCA(5, 20) = " << lcaBST(root, 5, 20)   << "\n"; // 10

    cout << "\n4. BST to DLL (inorder): ";
    // Clone BST manually for this demo
    TreeNode* root2 = nullptr;
    for (int v : {10, 5, 15, 3, 7, 20}) root2 = insert(root2, v);
    TreeNode* dll = bstToDLL(root2);
    for (TreeNode* cur = dll; cur; cur = cur->right)
        cout << cur->val << " ";
    cout << "\n";

    cout << "\n5. Two Sum in BST (target=15): "
         << (findTargetInBST(root, 15) ? "YES" : "NO") << "\n"; // YES (5+10)
    cout << "   Two Sum in BST (target=100): "
         << (findTargetInBST(root, 100) ? "YES" : "NO") << "\n"; // NO

    cout << "\n6. Is Valid BST: "
         << (isValidBST(root) ? "YES" : "NO") << "\n"; // YES
    // Create invalid BST
    TreeNode* inv = new TreeNode(5);
    inv->left  = new TreeNode(1);
    inv->right = new TreeNode(4);
    inv->right->left  = new TreeNode(3);
    inv->right->right = new TreeNode(6);
    cout << "   Invalid BST check: "
         << (isValidBST(inv) ? "YES" : "NO") << "\n"; // NO

    cout << "\n7. Range Sum [5,15]: " << rangeSumBST(root, 5, 15) << "\n"; // 32 (5+7+10+15)

    return 0;
}
