/*
 * ============================================================
 *  BINARY TREE — Root-to-Leaf Paths, Path Sum, LCA
 * ============================================================
 *  Topics:
 *   1. All root-to-leaf paths
 *   2. Path Sum (has path summing to target?) — LC 112
 *   3. Path Sum II (all paths with target sum) — LC 113
 *   4. Maximum Path Sum — LC 124
 *   5. Lowest Common Ancestor (LCA)            — LC 236
 *   6. LCA — LC 235 (in BST, simpler)
 *   7. Distance between two nodes
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Helper: build tree from level-order array (-1 = null)
TreeNode* buildTree(vector<int>& arr) {
    if (arr.empty() || arr[0] == -1) return nullptr;
    TreeNode* root = new TreeNode(arr[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < (int)arr.size()) {
        TreeNode* cur = q.front(); q.pop();
        if (arr[i] != -1) { cur->left = new TreeNode(arr[i]); q.push(cur->left); }
        i++;
        if (i < (int)arr.size() && arr[i] != -1) { cur->right = new TreeNode(arr[i]); q.push(cur->right); }
        i++;
    }
    return root;
}

// ─────────────────────────────────────────────────────────────
//  1. All Root-to-Leaf Paths
// ─────────────────────────────────────────────────────────────
void allPaths(TreeNode* node, string path, vector<string>& res) {
    if (!node) return;
    path += to_string(node->val);
    if (!node->left && !node->right) { res.push_back(path); return; }
    allPaths(node->left,  path + "->", res);
    allPaths(node->right, path + "->", res);
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res;
    allPaths(root, "", res);
    return res;
}

// ─────────────────────────────────────────────────────────────
//  2. Has Path Sum — LC 112
// ─────────────────────────────────────────────────────────────
bool hasPathSum(TreeNode* node, int target) {
    if (!node) return false;
    if (!node->left && !node->right) return node->val == target;
    return hasPathSum(node->left,  target - node->val) ||
           hasPathSum(node->right, target - node->val);
}

// ─────────────────────────────────────────────────────────────
//  3. All Paths with Target Sum — LC 113
// ─────────────────────────────────────────────────────────────
void pathSumII(TreeNode* node, int target, vector<int>& cur, vector<vector<int>>& res) {
    if (!node) return;
    cur.push_back(node->val);
    if (!node->left && !node->right && node->val == target) res.push_back(cur);
    pathSumII(node->left,  target - node->val, cur, res);
    pathSumII(node->right, target - node->val, cur, res);
    cur.pop_back(); // backtrack
}

vector<vector<int>> pathSum(TreeNode* root, int target) {
    vector<vector<int>> res;
    vector<int> cur;
    pathSumII(root, target, cur, res);
    return res;
}

// ─────────────────────────────────────────────────────────────
//  4. Maximum Path Sum — LC 124
//  A path can start and end at any node.
//  Key: at each node, max gain = max(0, left_gain, right_gain)
// ─────────────────────────────────────────────────────────────
int maxPathSumHelper(TreeNode* node, int& globalMax) {
    if (!node) return 0;
    int left  = max(0, maxPathSumHelper(node->left,  globalMax));
    int right = max(0, maxPathSumHelper(node->right, globalMax));
    // Update global max with path through this node
    globalMax = max(globalMax, node->val + left + right);
    // Return max single-branch gain upward
    return node->val + max(left, right);
}

int maxPathSum(TreeNode* root) {
    int res = INT_MIN;
    maxPathSumHelper(root, res);
    return res;
}

// ─────────────────────────────────────────────────────────────
//  5. Lowest Common Ancestor — LC 236 (General Binary Tree)
//  Idea: if current node == p or q, return it.
//        if both sides return non-null, current is LCA.
// ─────────────────────────────────────────────────────────────
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* left  = lowestCommonAncestor(root->left,  p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;  // p and q on different sides
    return left ? left : right;      // both on same side
}

// ─────────────────────────────────────────────────────────────
//  6. LCA in BST — LC 235
//  If both p and q are smaller → go left
//  If both larger              → go right
//  Else current is LCA
// ─────────────────────────────────────────────────────────────
TreeNode* lcaInBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val)
            root = root->left;
        else if (p->val > root->val && q->val > root->val)
            root = root->right;
        else
            return root;
    }
    return nullptr;
}

// ─────────────────────────────────────────────────────────────
//  7. Distance between two nodes
//  dist(p, q) = depth(p) + depth(q) - 2*depth(LCA)
// ─────────────────────────────────────────────────────────────
int depthFromNode(TreeNode* root, int val, int depth) {
    if (!root) return -1;
    if (root->val == val) return depth;
    int d = depthFromNode(root->left, val, depth + 1);
    return d != -1 ? d : depthFromNode(root->right, val, depth + 1);
}

int distBetweenNodes(TreeNode* root, int p, int q) {
    TreeNode* pNode = new TreeNode(p);
    TreeNode* qNode = new TreeNode(q);
    TreeNode* lca = lowestCommonAncestor(root, pNode, qNode);
    // Simplified: find depth from lca
    int dp = depthFromNode(lca, p, 0);
    int dq = depthFromNode(lca, q, 0);
    return dp + dq;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Binary Tree: Paths & LCA =====\n\n";

    //        5
    //       / \
    //      4   8
    //     /   / \
    //    11  13  4
    //   / \    \  \
    //  7   2    5  1
    vector<int> arr = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 5, -1, 1};
    TreeNode* root = buildTree(arr);

    cout << "1. All root-to-leaf paths:\n";
    for (auto& p : binaryTreePaths(root)) cout << "   " << p << "\n";

    cout << "\n2. Has path sum 22? "
         << (hasPathSum(root, 22) ? "YES" : "NO") << "\n"; // YES (5->4->11->2)

    cout << "\n3. All paths summing to 22:\n";
    for (auto& path : pathSum(root, 22)) {
        cout << "   ";
        for (int v : path) cout << v << " ";
        cout << "\n";
    }

    cout << "\n4. Maximum path sum: " << maxPathSum(root) << "\n"; // 48 (13+8+5+4+11+7)

    cout << "\n5. LCA of nodes 7 and 2 in general tree:\n";
    TreeNode* n7 = root->left->left->left;   // 7
    TreeNode* n2 = root->left->left->right;  // 2
    cout << "   LCA(7,2) = " << lowestCommonAncestor(root, n7, n2)->val << "\n"; // 11

    cout << "\n6. LCA(13, 5) in BST context = "
         << lowestCommonAncestor(root, root->right->left, root->right->right->left)->val
         << "\n"; // 8

    return 0;
}
