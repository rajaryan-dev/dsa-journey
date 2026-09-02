/*
 * ============================================================
 *  TRIE (Prefix Tree) — Complete Reference
 * ============================================================
 *  A Trie is a tree where each node represents a character.
 *  Paths from root to a node spell out a prefix/word.
 *
 *  Node structure:
 *   children[26]  — for lowercase English letters
 *   isEnd         — marks end of a word
 *   count         — how many words pass through this node
 *
 *  Time complexity:
 *   Insert / Search / StartsWith : O(L)  where L = word length
 *  Space: O(alphabet * total chars)
 *
 *  Topics:
 *   1. Insert, Search, Starts With — LC 208
 *   2. Count words with given prefix
 *   3. Delete a word
 *   4. Longest Common Prefix — LC 14
 *   5. Word Search II (Trie + DFS on board) — LC 212
 *   6. Trie-based autocomplete system
 *   7. Maximum XOR of Two Numbers — LC 421 (Binary Trie)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  Trie Node
// ─────────────────────────────────────────────────────────────
struct TrieNode {
    TrieNode* children[26];
    bool isEnd;
    int count;       // number of words passing through this node
    string word;     // store word at leaf (for Word Search II)

    TrieNode() : isEnd(false), count(0), word("") {
        fill(children, children + 26, nullptr);
    }
};

// ─────────────────────────────────────────────────────────────
//  Trie Class — LC 208
// ─────────────────────────────────────────────────────────────
class Trie {
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* cur = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!cur->children[idx]) cur->children[idx] = new TrieNode();
            cur = cur->children[idx];
            cur->count++;
        }
        cur->isEnd = true;
        cur->word  = word;
    }

    bool search(const string& word) {
        TrieNode* cur = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return cur->isEnd;
    }

    bool startsWith(const string& prefix) {
        TrieNode* cur = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return true;
    }

    // Count words with given prefix
    int countWordsWithPrefix(const string& prefix) {
        TrieNode* cur = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!cur->children[idx]) return 0;
            cur = cur->children[idx];
        }
        return cur->count;
    }

    // Delete a word
    bool deleteWord(TrieNode* node, const string& word, int depth) {
        if (!node) return false;
        if (depth == (int)word.size()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return !hasChildren(node); // true if node can be deleted
        }
        int idx = word[depth] - 'a';
        if (deleteWord(node->children[idx], word, depth + 1)) {
            delete node->children[idx];
            node->children[idx] = nullptr;
            return !node->isEnd && !hasChildren(node);
        }
        return false;
    }

    void deleteWord(const string& word) { deleteWord(root, word, 0); }

    bool hasChildren(TrieNode* node) {
        for (int i = 0; i < 26; i++) if (node->children[i]) return true;
        return false;
    }

    TrieNode* getRoot() { return root; }
};

// ─────────────────────────────────────────────────────────────
//  Longest Common Prefix — LC 14
//  Insert all words, then traverse longest common path.
// ─────────────────────────────────────────────────────────────
string longestCommonPrefix(vector<string>& words) {
    if (words.empty()) return "";
    Trie trie;
    for (auto& w : words) trie.insert(w);

    string lcp = "";
    TrieNode* cur = trie.getRoot();
    // Traverse as long as single child and not end of word
    while (true) {
        int childCount = 0, childIdx = -1;
        for (int i = 0; i < 26; i++)
            if (cur->children[i]) { childCount++; childIdx = i; }
        if (childCount != 1 || cur->isEnd) break;
        lcp += (char)('a' + childIdx);
        cur = cur->children[childIdx];
    }
    return lcp;
}

// ─────────────────────────────────────────────────────────────
//  Word Search II — LC 212
//  Find all words from a list that exist in the board.
// ─────────────────────────────────────────────────────────────
void dfs(vector<vector<char>>& board, TrieNode* node, int r, int c,
         vector<string>& res) {
    if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[0].size()) return;
    char ch = board[r][c];
    if (ch == '#' || !node->children[ch - 'a']) return;

    node = node->children[ch - 'a'];
    if (!node->word.empty()) { res.push_back(node->word); node->word = ""; } // found

    board[r][c] = '#';
    dfs(board, node, r+1, c, res); dfs(board, node, r-1, c, res);
    dfs(board, node, r, c+1, res); dfs(board, node, r, c-1, res);
    board[r][c] = ch;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    Trie trie;
    for (auto& w : words) trie.insert(w);
    vector<string> res;
    for (int r = 0; r < (int)board.size(); r++)
        for (int c = 0; c < (int)board[0].size(); c++)
            dfs(board, trie.getRoot(), r, c, res);
    return res;
}

// ─────────────────────────────────────────────────────────────
//  Maximum XOR of Two Numbers — LC 421
//  Binary Trie: insert all numbers bit by bit from MSB.
//  For each number, greedily pick opposite bit.
// ─────────────────────────────────────────────────────────────
struct BitTrieNode {
    BitTrieNode* children[2];
    BitTrieNode() { children[0] = children[1] = nullptr; }
};

class BitTrie {
    BitTrieNode* root;
public:
    BitTrie() { root = new BitTrieNode(); }

    void insert(int num) {
        BitTrieNode* cur = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!cur->children[bit]) cur->children[bit] = new BitTrieNode();
            cur = cur->children[bit];
        }
    }

    int maxXOR(int num) {
        BitTrieNode* cur = root;
        int xorVal = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int want = 1 - bit; // opposite for max XOR
            if (cur->children[want]) { xorVal |= (1 << i); cur = cur->children[want]; }
            else                       cur = cur->children[bit];
        }
        return xorVal;
    }
};

int findMaximumXOR(vector<int>& nums) {
    BitTrie trie;
    for (int x : nums) trie.insert(x);
    int res = 0;
    for (int x : nums) res = max(res, trie.maxXOR(x));
    return res;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Trie (Prefix Tree) =====\n\n";

    // 1. Basic Trie
    Trie trie;
    for (auto& w : {"apple","app","apricot","banana","band","bandwidth"})
        trie.insert(w);

    cout << "1. Basic Trie (insert: apple, app, apricot, banana, band, bandwidth)\n";
    cout << "   search(\"apple\"):    " << (trie.search("apple")    ? "YES":"NO") << "\n"; // YES
    cout << "   search(\"ap\"):       " << (trie.search("ap")       ? "YES":"NO") << "\n"; // NO
    cout << "   startsWith(\"ap\"):   " << (trie.startsWith("ap")   ? "YES":"NO") << "\n"; // YES
    cout << "   startsWith(\"ban\"):  " << (trie.startsWith("ban")  ? "YES":"NO") << "\n"; // YES
    cout << "   startsWith(\"xyz\"):  " << (trie.startsWith("xyz")  ? "YES":"NO") << "\n"; // NO

    cout << "\n2. Count words with prefix:\n";
    cout << "   prefix \"ap\": " << trie.countWordsWithPrefix("ap") << " words\n"; // 3
    cout << "   prefix \"ban\": " << trie.countWordsWithPrefix("ban") << " words\n"; // 2

    cout << "\n3. Delete word \"app\":\n";
    trie.deleteWord("app");
    cout << "   search(\"app\") after delete: " << (trie.search("app") ? "YES":"NO") << "\n"; // NO
    cout << "   search(\"apple\") still:      " << (trie.search("apple") ? "YES":"NO") << "\n"; // YES

    cout << "\n4. Longest Common Prefix:\n";
    vector<string> words = {"flower","flow","flight"};
    cout << "   {\"flower\",\"flow\",\"flight\"}: \"" << longestCommonPrefix(words) << "\"\n"; // fl
    vector<string> words2 = {"dog","racecar","car"};
    cout << "   {\"dog\",\"racecar\",\"car\"}: \"" << longestCommonPrefix(words2) << "\"\n"; // ""

    cout << "\n5. Word Search II:\n";
    vector<vector<char>> board = {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}};
    vector<string> wordList = {"oath","pea","eat","rain"};
    auto found = findWords(board, wordList);
    cout << "   Found: ";
    for (auto& w : found) cout << w << " ";
    cout << "\n"; // eat oath

    cout << "\n6. Maximum XOR {3,10,5,25,2,8}:\n";
    vector<int> nums = {3,10,5,25,2,8};
    cout << "   Max XOR = " << findMaximumXOR(nums) << "\n"; // 28

    return 0;
}
