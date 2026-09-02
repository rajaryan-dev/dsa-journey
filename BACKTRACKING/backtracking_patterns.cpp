/*
 * ============================================================
 *  BACKTRACKING — Complete Reference
 * ============================================================
 *  Backtracking = Try all possibilities + undo on failure.
 *
 *  Template:
 *    void backtrack(state) {
 *        if (base case) { record result; return; }
 *        for each choice:
 *            make choice
 *            backtrack(new state)
 *            undo choice  ← KEY STEP
 *    }
 *
 *  Topics:
 *   1. Subsets — LC 78
 *   2. Subsets II (with duplicates) — LC 90
 *   3. Permutations — LC 46
 *   4. Permutations II (with duplicates) — LC 47
 *   5. Combination Sum I — LC 39 (items can repeat)
 *   6. Combination Sum II — LC 40 (each item once)
 *   7. Word Search — LC 79
 *   8. Word Break II — LC 140
 *   9. Palindrome Partitioning — LC 131
 *  10. Letter Combinations of Phone Number — LC 17
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  1. Subsets (no duplicates) — LC 78
// ─────────────────────────────────────────────────────────────
void subsets(vector<int>& nums, int start, vector<int>& cur, vector<vector<int>>& res) {
    res.push_back(cur);
    for (int i = start; i < (int)nums.size(); i++) {
        cur.push_back(nums[i]);
        subsets(nums, i + 1, cur, res);
        cur.pop_back();
    }
}

// ─────────────────────────────────────────────────────────────
//  2. Subsets II (with duplicates) — LC 90
// ─────────────────────────────────────────────────────────────
void subsetsWithDup(vector<int>& nums, int start, vector<int>& cur, vector<vector<int>>& res) {
    res.push_back(cur);
    for (int i = start; i < (int)nums.size(); i++) {
        if (i > start && nums[i] == nums[i-1]) continue; // skip duplicates at same level
        cur.push_back(nums[i]);
        subsetsWithDup(nums, i + 1, cur, res);
        cur.pop_back();
    }
}

// ─────────────────────────────────────────────────────────────
//  3. Permutations (no duplicates) — LC 46
// ─────────────────────────────────────────────────────────────
void permute(vector<int>& nums, int start, vector<vector<int>>& res) {
    if (start == (int)nums.size()) { res.push_back(nums); return; }
    for (int i = start; i < (int)nums.size(); i++) {
        swap(nums[start], nums[i]);
        permute(nums, start + 1, res);
        swap(nums[start], nums[i]); // undo
    }
}

// ─────────────────────────────────────────────────────────────
//  4. Permutations II (with duplicates) — LC 47
// ─────────────────────────────────────────────────────────────
void permuteUnique(vector<int>& nums, vector<bool>& used, vector<int>& cur, vector<vector<int>>& res) {
    if ((int)cur.size() == (int)nums.size()) { res.push_back(cur); return; }
    for (int i = 0; i < (int)nums.size(); i++) {
        if (used[i]) continue;
        // Skip duplicate: same value as previous but prev not used in this recursion path
        if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
        used[i] = true;
        cur.push_back(nums[i]);
        permuteUnique(nums, used, cur, res);
        cur.pop_back();
        used[i] = false;
    }
}

// ─────────────────────────────────────────────────────────────
//  5. Combination Sum I — LC 39 (same element can be reused)
// ─────────────────────────────────────────────────────────────
void combinationSum(vector<int>& candidates, int start, int target,
                    vector<int>& cur, vector<vector<int>>& res) {
    if (target == 0) { res.push_back(cur); return; }
    for (int i = start; i < (int)candidates.size(); i++) {
        if (candidates[i] > target) break;
        cur.push_back(candidates[i]);
        combinationSum(candidates, i, target - candidates[i], cur, res); // i not i+1 (reuse)
        cur.pop_back();
    }
}

// ─────────────────────────────────────────────────────────────
//  6. Combination Sum II — LC 40 (each element used once, no dup subsets)
// ─────────────────────────────────────────────────────────────
void combinationSum2(vector<int>& candidates, int start, int target,
                     vector<int>& cur, vector<vector<int>>& res) {
    if (target == 0) { res.push_back(cur); return; }
    for (int i = start; i < (int)candidates.size(); i++) {
        if (candidates[i] > target) break;
        if (i > start && candidates[i] == candidates[i-1]) continue; // skip dups
        cur.push_back(candidates[i]);
        combinationSum2(candidates, i + 1, target - candidates[i], cur, res);
        cur.pop_back();
    }
}

// ─────────────────────────────────────────────────────────────
//  7. Word Search — LC 79
//  DFS on grid, mark visited, backtrack
// ─────────────────────────────────────────────────────────────
bool wordSearch(vector<vector<char>>& board, string& word, int idx, int r, int c) {
    if (idx == (int)word.size()) return true;
    if (r < 0 || r >= (int)board.size() || c < 0 || c >= (int)board[0].size()) return false;
    if (board[r][c] != word[idx]) return false;

    char temp = board[r][c];
    board[r][c] = '#'; // mark visited
    bool found = wordSearch(board, word, idx+1, r+1, c) ||
                 wordSearch(board, word, idx+1, r-1, c) ||
                 wordSearch(board, word, idx+1, r, c+1) ||
                 wordSearch(board, word, idx+1, r, c-1);
    board[r][c] = temp; // restore (backtrack)
    return found;
}

bool exist(vector<vector<char>>& board, string word) {
    for (int r = 0; r < (int)board.size(); r++)
        for (int c = 0; c < (int)board[0].size(); c++)
            if (wordSearch(board, word, 0, r, c)) return true;
    return false;
}

// ─────────────────────────────────────────────────────────────
//  8. Palindrome Partitioning — LC 131
// ─────────────────────────────────────────────────────────────
bool isPalin(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}

void palindromePartition(const string& s, int start, vector<string>& cur, vector<vector<string>>& res) {
    if (start == (int)s.size()) { res.push_back(cur); return; }
    for (int end = start; end < (int)s.size(); end++) {
        if (isPalin(s, start, end)) {
            cur.push_back(s.substr(start, end - start + 1));
            palindromePartition(s, end + 1, cur, res);
            cur.pop_back();
        }
    }
}

// ─────────────────────────────────────────────────────────────
//  9. Letter Combinations of Phone Number — LC 17
// ─────────────────────────────────────────────────────────────
void letterCombinations(const string& digits, int idx, string& cur,
                        vector<string>& res, vector<string>& phone) {
    if (idx == (int)digits.size()) { res.push_back(cur); return; }
    for (char c : phone[digits[idx] - '0']) {
        cur += c;
        letterCombinations(digits, idx + 1, cur, res, phone);
        cur.pop_back();
    }
}

vector<string> letterCombinations(const string& digits) {
    if (digits.empty()) return {};
    vector<string> phone = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    string cur = "";
    letterCombinations(digits, 0, cur, res, phone);
    return res;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Backtracking =====\n\n";

    // 1. Subsets
    vector<int> s = {1, 2, 3};
    vector<vector<int>> res; vector<int> cur;
    subsets(s, 0, cur, res);
    cout << "1. Subsets of {1,2,3}: " << res.size() << " subsets\n"; // 8

    // 2. Subsets with duplicates
    vector<int> sd = {1, 2, 2}; sort(sd.begin(), sd.end()); res.clear();
    subsetsWithDup(sd, 0, cur, res);
    cout << "2. Subsets of {1,2,2}: " << res.size() << " unique subsets\n"; // 6

    // 3. Permutations
    vector<int> p = {1, 2, 3}; res.clear();
    permute(p, 0, res);
    cout << "3. Permutations of {1,2,3}: " << res.size() << "\n"; // 6

    // 4. Unique Permutations
    vector<int> pu = {1, 1, 2}; sort(pu.begin(), pu.end()); res.clear();
    vector<bool> used(3, false);
    permuteUnique(pu, used, cur, res);
    cout << "4. Unique perms of {1,1,2}: " << res.size() << "\n"; // 3

    // 5. Combination Sum I
    vector<int> cand = {2, 3, 6, 7}; sort(cand.begin(), cand.end()); res.clear();
    combinationSum(cand, 0, 7, cur, res);
    cout << "5. Combo Sum {2,3,6,7} target=7: " << res.size() << " combos\n"; // 2

    // 6. Combination Sum II
    vector<int> cand2 = {10,1,2,7,6,1,5}; sort(cand2.begin(), cand2.end()); res.clear();
    combinationSum2(cand2, 0, 8, cur, res);
    cout << "6. Combo Sum II target=8: " << res.size() << " unique combos\n"; // 4

    // 7. Word Search
    vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    string w1 = "ABCCED", w2 = "SEE", w3 = "ABCB";
    cout << "7. Word Search \"ABCCED\": " << (exist(board,w1)?"YES":"NO") << "\n"; // YES
    cout << "   Word Search \"ABCB\":   " << (exist(board,w3)?"YES":"NO") << "\n"; // NO

    // 8. Palindrome Partitioning
    vector<vector<string>> pres; vector<string> pcur;
    palindromePartition("aab", 0, pcur, pres);
    cout << "8. Palindrome partitions of \"aab\": " << pres.size() << "\n"; // 2

    // 9. Letter Combinations
    auto lc = letterCombinations("23");
    cout << "9. Letter combos of \"23\": ";
    for (auto& s : lc) cout << s << " ";
    cout << "\n"; // ad ae af bd be bf cd ce cf

    return 0;
}
