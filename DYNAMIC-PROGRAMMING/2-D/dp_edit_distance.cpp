/*
 * ============================================================
 *  EDIT DISTANCE & String DP Variants
 * ============================================================
 *  Problem: Given two strings word1, word2 — find minimum
 *  operations (Insert, Delete, Replace) to convert word1 → word2.
 *  Also known as Levenshtein Distance.
 *
 *  Recurrence:
 *    if word1[i-1] == word2[j-1] : dp[i][j] = dp[i-1][j-1]
 *    else : dp[i][j] = 1 + min(dp[i-1][j],    // delete
 *                               dp[i][j-1],    // insert
 *                               dp[i-1][j-1])  // replace
 *
 *  Variants:
 *   1. Edit Distance (Levenshtein)  — LC 72
 *   2. Wildcard Matching            — LC 44
 *   3. Regular Expression Matching  — LC 10
 *   4. Palindrome DP (Min insertions to make palindrome) — LC 1312
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  1. Edit Distance — LC 72  O(m*n)
// ─────────────────────────────────────────────────────────────
int editDistance(const string& w1, const string& w2) {
    int m = w1.size(), n = w2.size();
    // dp[i][j] = min ops to convert w1[0..i-1] → w2[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i; // delete all of w1
    for (int j = 0; j <= n; j++) dp[0][j] = j; // insert all of w2

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (w1[i-1] == w2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j],    // delete
                                    dp[i][j-1],      // insert
                                    dp[i-1][j-1]});  // replace
        }
    }
    return dp[m][n];
}

// ─────────────────────────────────────────────────────────────
//  2. Wildcard Matching — LC 44
//  '?' matches any single char, '*' matches any sequence (incl empty)
// ─────────────────────────────────────────────────────────────
bool isMatchWildcard(const string& s, const string& p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    // '*' can match empty — initialise first row
    for (int j = 1; j <= n; j++)
        dp[0][j] = dp[0][j-1] && p[j-1] == '*';

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*')
                // '*' matches empty (dp[i][j-1]) OR matches s[i-1] (dp[i-1][j])
                dp[i][j] = dp[i][j-1] || dp[i-1][j];
            else if (p[j-1] == '?' || s[i-1] == p[j-1])
                dp[i][j] = dp[i-1][j-1];
        }
    }
    return dp[m][n];
}

// ─────────────────────────────────────────────────────────────
//  3. Regular Expression Matching — LC 10
//  '.' matches any single char, '*' matches 0+ of preceding
// ─────────────────────────────────────────────────────────────
bool isMatchRegex(const string& s, const string& p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    // Handle patterns like a*, a*b*, a*b*c* that can match empty string
    for (int j = 2; j <= n; j += 2)
        if (p[j-1] == '*') dp[0][j] = dp[0][j-2];

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*') {
                // Use 0 occurrences of preceding char
                dp[i][j] = dp[i][j-2];
                // Use 1+ occurrences if preceding matches
                if (p[j-2] == '.' || p[j-2] == s[i-1])
                    dp[i][j] = dp[i][j] || dp[i-1][j];
            } else if (p[j-1] == '.' || p[j-1] == s[i-1]) {
                dp[i][j] = dp[i-1][j-1];
            }
        }
    }
    return dp[m][n];
}

// ─────────────────────────────────────────────────────────────
//  4. Min Insertions to Make Palindrome — LC 1312
//  Key insight: min insertions = n - LPS(s)
//  where LPS = Longest Palindromic Subsequence
//            = LCS(s, reverse(s))
// ─────────────────────────────────────────────────────────────
int longestPalindromicSubseq(const string& s) {
    string rev = string(s.rbegin(), s.rend());
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (s[i-1] == rev[j-1])
                      ? dp[i-1][j-1] + 1
                      : max(dp[i-1][j], dp[i][j-1]);
    return dp[n][n];
}

int minInsertionsToPalindrome(const string& s) {
    return s.size() - longestPalindromicSubseq(s);
}

// ─────────────────────────────────────────────────────────────
//  5. Distinct Subsequences — LC 115
//  Count how many times t appears as a subsequence in s
// ─────────────────────────────────────────────────────────────
long long distinctSubsequences(const string& s, const string& t) {
    int m = s.size(), n = t.size();
    vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i <= m; i++) dp[i][0] = 1; // empty t is always a subseq

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i-1][j]; // skip s[i-1]
            if (s[i-1] == t[j-1])
                dp[i][j] += dp[i-1][j-1]; // use s[i-1]
        }
    return dp[m][n];
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Edit Distance & String DP =====\n\n";

    cout << "1. Edit Distance\n";
    cout << "   \"horse\" → \"ros\"   = " << editDistance("horse", "ros") << "\n";   // 3
    cout << "   \"intention\" → \"execution\" = "
         << editDistance("intention", "execution") << "\n"; // 5
    cout << "   \"\" → \"abc\"       = " << editDistance("", "abc") << "\n";         // 3

    cout << "\n2. Wildcard Matching\n";
    cout << "   s=\"aa\" p=\"a\":    " << (isMatchWildcard("aa","a")   ? "true":"false") << "\n"; // false
    cout << "   s=\"aa\" p=\"*\":    " << (isMatchWildcard("aa","*")   ? "true":"false") << "\n"; // true
    cout << "   s=\"cb\" p=\"?a\":   " << (isMatchWildcard("cb","?a")  ? "true":"false") << "\n"; // false
    cout << "   s=\"adceb\" p=\"*a*b\": " << (isMatchWildcard("adceb","*a*b") ? "true":"false") << "\n"; // true

    cout << "\n3. Regex Matching\n";
    cout << "   s=\"aa\" p=\"a\":    " << (isMatchRegex("aa","a")   ? "true":"false") << "\n"; // false
    cout << "   s=\"aa\" p=\"a*\":   " << (isMatchRegex("aa","a*")  ? "true":"false") << "\n"; // true
    cout << "   s=\"ab\" p=\".*\":   " << (isMatchRegex("ab",".*")  ? "true":"false") << "\n"; // true
    cout << "   s=\"aab\" p=\"c*a*b\": " << (isMatchRegex("aab","c*a*b") ? "true":"false") << "\n"; // true

    cout << "\n4. Min Insertions to Make Palindrome\n";
    cout << "   \"zzazz\"   → " << minInsertionsToPalindrome("zzazz")   << "\n"; // 0
    cout << "   \"mbadm\"   → " << minInsertionsToPalindrome("mbadm")   << "\n"; // 2
    cout << "   \"leetcode\" → " << minInsertionsToPalindrome("leetcode") << "\n"; // 5

    cout << "\n5. Distinct Subsequences\n";
    cout << "   s=\"rabbbit\" t=\"rabbit\": " << distinctSubsequences("rabbbit","rabbit") << "\n"; // 3
    cout << "   s=\"babgbag\" t=\"bag\":     " << distinctSubsequences("babgbag","bag")   << "\n"; // 5

    return 0;
}
