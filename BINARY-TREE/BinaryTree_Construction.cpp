/*
 * ============================================================
 *  BINARY TREE — Construction from Traversals
 * ============================================================
 *  Topics:
 *   1. Build from Inorder + Preorder — LC 105
 *   2. Build from Inorder + Postorder — LC 106
 *   3. Serialize and Deserialize Binary Tree — LC 297
 *   4. Flatten Binary Tree to Linked List — LC 114
 *   5. Morris Inorder Traversal (O(1) space)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// ─────────────────────────────────────────────────────────────
//  Helper: print inorder
// ─────────────────────────────────────────────────────────────
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

// ─────────────────────────────────────────────────────────────
//  1. Build Tree from Inorder + Preorder — LC 105
//  Key: preorder[0] is always the ROOT.
//       Find root in inorder → left and right subtree sizes.
// ─────────────────────────────────────────────────────────────
TreeNode* buildFromPreIn(vector<int>& pre, int preStart, int preEnd,
                         vector<int>& in,  int inStart,  int inEnd,
                         unordered_map<int,int>& inMap) {
    if (preStart > preEnd || inStart > inEnd) return nullptr;
    int rootVal = pre[preStart];
    TreeNode* root = new TreeNode(rootVal);
    int inRoot = inMap[rootVal];
    int leftSize = inRoot - inStart;

    root->left  = buildFromPreIn(pre, preStart + 1, preStart + leftSize,
                                 in,  inStart,       inRoot - 1,  inMap);
    root->right = buildFromPreIn(pre, preStart + leftSize + 1, preEnd,
                                 in,  inRoot + 1,    inEnd,       inMap);
    return root;
}

TreeNode* buildTreePreIn(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int,int> inMap;
    for (int i = 0; i < (int)inorder.size(); i++) inMap[inorder[i]] = i;
    return buildFromPreIn(preorder, 0, preorder.size()-1,
                          inorder,  0, inorder.size()-1, inMap);
}

// ─────────────────────────────────────────────────────────────
//  2. Build Tree from Inorder + Postorder — LC 106
//  Key: postorder.back() is always the ROOT.
// ─────────────────────────────────────────────────────────────
TreeNode* buildFromPostIn(vector<int>& post, int postStart, int postEnd,
                          vector<int>& in,   int inStart,   int inEnd,
                          unordered_map<int,int>& inMap) {
    if (postStart > postEnd || inStart > inEnd) return nullptr;
    int rootVal = post[postEnd];
    TreeNode* root = new TreeNode(rootVal);
    int inRoot = inMap[rootVal];
    int leftSize = inRoot - inStart;

    root->left  = buildFromPostIn(post, postStart,            postStart + leftSize - 1,
                                  in,   inStart,              inRoot - 1, inMap);
    root->right = buildFromPostIn(post, postStart + leftSize, postEnd - 1,
                                  in,   inRoot + 1,           inEnd,      inMap);
    return root;
}

TreeNode* buildTreePostIn(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int,int> inMap;
    for (int i = 0; i < (int)inorder.size(); i++) inMap[inorder[i]] = i;
    return buildFromPostIn(postorder, 0, postorder.size()-1,
                           inorder,   0, inorder.size()-1, inMap);
}

// ─────────────────────────────────────────────────────────────
//  3. Serialize & Deserialize — LC 297
//  Use level-order (BFS) with "null" markers
// ─────────────────────────────────────────────────────────────
string serialize(TreeNode* root) {
    if (!root) return "";
    string res = "";
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        if (cur) {
            res += to_string(cur->val) + ",";
            q.push(cur->left);
            q.push(cur->right);
        } else {
            res += "null,";
        }
    }
    return res;
}

TreeNode* deserialize(const string& data) {
    if (data.empty()) return nullptr;
    stringstream ss(data);
    string token;
    getline(ss, token, ',');
    TreeNode* root = new TreeNode(stoi(token));
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        if (getline(ss, token, ',') && token != "null") {
            cur->left = new TreeNode(stoi(token));
            q.push(cur->left);
        }
        if (getline(ss, token, ',') && token != "null") {
            cur->right = new TreeNode(stoi(token));
            q.push(cur->right);
        }
    }
    return root;
}

// ─────────────────────────────────────────────────────────────
//  4. Flatten Binary Tree to Linked List — LC 114
//  Modify in-place: right pointers form a linked list (preorder)
//  Use reverse postorder: right → left → root
// ─────────────────────────────────────────────────────────────
void flatten(TreeNode* root) {
    TreeNode* prev = nullptr;
    function<void(TreeNode*)> dfs = [&](TreeNode* node) {
        if (!node) return;
        dfs(node->right);
        dfs(node->left);
        node->right = prev;
        node->left = nullptr;
        prev = node;
    };
    dfs(root);
}

// ─────────────────────────────────────────────────────────────
//  5. Morris Inorder Traversal — O(n) time, O(1) space
//  Temporarily threads right pointers to predecessors.
// ─────────────────────────────────────────────────────────────
vector<int> morrisInorder(TreeNode* root) {
    vector<int> res;
    TreeNode* cur = root;
    while (cur) {
        if (!cur->left) {
            res.push_back(cur->val);
            cur = cur->right;
        } else {
            // Find inorder predecessor
            TreeNode* pred = cur->left;
            while (pred->right && pred->right != cur)
                pred = pred->right;

            if (!pred->right) {
                pred->right = cur;  // Thread
                cur = cur->left;
            } else {
                pred->right = nullptr; // Unthread
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
    }
    return res;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Binary Tree Construction & Advanced Traversal =====\n\n";

    // Tree:
    //       3
    //      / \
    //     9  20
    //       /  \
    //      15   7
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder  = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};

    cout << "1. Build from Preorder+Inorder:\n";
    TreeNode* t1 = buildTreePreIn(preorder, inorder);
    cout << "   Inorder: "; printInorder(t1); cout << "\n";

    cout << "\n2. Build from Inorder+Postorder:\n";
    TreeNode* t2 = buildTreePostIn(inorder, postorder);
    cout << "   Inorder: "; printInorder(t2); cout << "\n";

    cout << "\n3. Serialize:\n";
    string s = serialize(t1);
    cout << "   \"" << s << "\"\n";
    cout << "   Deserialize → Inorder: ";
    printInorder(deserialize(s)); cout << "\n";

    cout << "\n4. Flatten to linked list (right pointers):\n   ";
    flatten(t1);
    TreeNode* cur = t1;
    while (cur) { cout << cur->val << " "; cur = cur->right; }
    cout << "\n";

    cout << "\n5. Morris Inorder Traversal (O(1) space):\n   ";
    // Rebuild tree since t1 is flattened
    t1 = buildTreePreIn(preorder, inorder);
    for (int v : morrisInorder(t1)) cout << v << " ";
    cout << "\n";

    return 0;
}
