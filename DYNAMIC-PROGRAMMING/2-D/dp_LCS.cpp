/*
 * ============================================================
 *  LONGEST COMMON SUBSEQUENCE (LCS) & Variants
 * ============================================================
 *  Core Problem: Given two strings s1 and s2, find the length
 *  of the longest subsequence present in both.
 *
 *  Recurrence:
 *    if s1[i-1] == s2[j-1] : dp[i][j] = dp[i-1][j-1] + 1
 *    else                   : dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *
 *  Variants covered:
 *   1. LCS length (2D DP)
 *   2. LCS reconstruction (backtrack)
 *   3. Shortest Common Supersequence (SCS)
 *   4. Longest Common Substring (consecutive)
 *   5. Minimum Insertions/Deletions to make s1 == s2
 *   6. Is subsequence check
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  Build the LCS DP table — reused by all variants
// ─────────────────────────────────────────────────────────────
vector<vector<int>> buildLCS(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (s1[i-1] == s2[j-1])
                      ? dp[i-1][j-1] + 1
                      : max(dp[i-1][j], dp[i][j-1]);
    return dp;
}

// ─────────────────────────────────────────────────────────────
//  1. LCS Length
// ─────────────────────────────────────────────────────────────
int lcsLength(const string& s1, const string& s2) {
    auto dp = buildLCS(s1, s2);
    return dp[s1.size()][s2.size()];
}

// ─────────────────────────────────────────────────────────────
//  2. Reconstruct LCS string (backtrack the DP table)
// ─────────────────────────────────────────────────────────────
string reconstructLCS(const string& s1, const string& s2) {
    auto dp = buildLCS(s1, s2);
    string lcs = "";
    int i = s1.size(), j = s2.size();
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            lcs += s1[i-1];
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) i--;
        else                                  j--;
    }
    reverse(lcs.begin(), lcs.end());
    return lcs;
}

// ─────────────────────────────────────────────────────────────
//  3. Shortest Common Supersequence — LC 1092
//  SCS length = |s1| + |s2| - LCS(s1,s2)
//  Reconstruct: greedily include characters from both strings
// ─────────────────────────────────────────────────────────────
string shortestCommonSupersequence(const string& s1, const string& s2) {
    auto dp = buildLCS(s1, s2);
    string scs = "";
    int i = s1.size(), j = s2.size();
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            scs += s1[i-1]; i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            scs += s1[i-1]; i--;
        } else {
            scs += s2[j-1]; j--;
        }
    }
    while (i > 0) { scs += s1[i-1]; i--; }
    while (j > 0) { scs += s2[j-1]; j--; }
    reverse(scs.begin(), scs.end());
    return scs;
}

// ─────────────────────────────────────────────────────────────
//  4. Longest Common Substring (CONSECUTIVE chars) — different from LCS!
//  dp[i][j] = length of common substring ending at s1[i-1], s2[j-1]
// ─────────────────────────────────────────────────────────────
int longestCommonSubstring(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size(), best = 0;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            dp[i][j] = (s1[i-1] == s2[j-1]) ? dp[i-1][j-1] + 1 : 0;
            best = max(best, dp[i][j]);
        }
    return best;
}

// ─────────────────────────────────────────────────────────────
//  5. Min Insertions + Deletions to convert s1 → s2 — LC 583
//  Deletions from s1 = |s1| - LCS
//  Insertions into s1 = |s2| - LCS
// ─────────────────────────────────────────────────────────────
pair<int,int> minOpsToConvert(const string& s1, const string& s2) {
    int lcs = lcsLength(s1, s2);
    return { (int)s1.size() - lcs, (int)s2.size() - lcs };
}

// ─────────────────────────────────────────────────────────────
//  6. Is Subsequence — LC 392  O(m+n)
// ─────────────────────────────────────────────────────────────
bool isSubsequence(const string& s, const string& t) {
    int i = 0, j = 0;
    while (i < (int)s.size() && j < (int)t.size()) {
        if (s[i] == t[j]) i++;
        j++;
    }
    return i == (int)s.size();
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Longest Common Subsequence & Variants =====\n\n";

    string s1 = "AGGTAB", s2 = "GXTXAYB";
    cout << "s1 = \"" << s1 << "\"\n";
    cout << "s2 = \"" << s2 << "\"\n\n";

    cout << "1. LCS length:       " << lcsLength(s1, s2) << "\n"; // 4
    cout << "2. LCS string:       " << reconstructLCS(s1, s2) << "\n"; // GTAB
    cout << "3. SCS string:       " << shortestCommonSupersequence(s1, s2) << "\n";
    cout << "   SCS length:       " << shortestCommonSupersequence(s1, s2).size() << "\n";

    string s3 = "ABCBDAB", s4 = "BDCAB";
    cout << "\ns3 = \"" << s3 << "\", s4 = \"" << s4 << "\"\n";
    cout << "LCS: " << reconstructLCS(s3, s4) << " (len=" << lcsLength(s3, s4) << ")\n"; // BCAB or BDAB

    string t1 = "abcde", t2 = "acdfe";
    cout << "\n4. Longest common SUBSTRING(\"abcde\",\"acdfe\"): "
         << longestCommonSubstring(t1, t2) << "\n"; // 2 (cd)

    auto [del, ins] = minOpsToConvert(string("sea"), string("eat"));
    cout << "\n5. Convert \"sea\" to \"eat\": "
         << del << " deletions, " << ins << " insertions\n"; // 2 ops total

    cout << "\n6. isSubsequence(\"ace\", \"abcde\"): "
         << (isSubsequence("ace", "abcde") ? "YES" : "NO") << "\n"; // YES
    cout << "   isSubsequence(\"aec\", \"abcde\"): "
         << (isSubsequence("aec", "abcde") ? "YES" : "NO") << "\n"; // NO

    return 0;
}
