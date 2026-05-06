/*
=========================================================
File: 375_Guess_Number_Higher_or_Lower_II_DP.cpp
=========================================================

LeetCode 375. Guess Number Higher or Lower II

Approaches Included:
1. Pure Recursion
2. Memoization (Top Down DP)
3. Tabulation (Bottom Up DP)

---------------------------------------------------------

Problem:
You need to guess a number from 1 to n.

If you guess wrong:
- You pay the amount of the guessed number.
- Then continue searching in remaining range.

Return the minimum money required to guarantee a win.

---------------------------------------------------------

Core Idea:
Try every number as first guess.

For every guess:
    cost = currentGuess + worstCase(left, right)

Take minimum among all guesses.

---------------------------------------------------------

Complexities:

1. Pure Recursion
   TC = Exponential
   SC = O(n)

2. Memoization
   TC = O(n^3)
   SC = O(n^2)

3. Tabulation
   TC = O(n^3)
   SC = O(n^2)

=========================================================
*/

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  // =====================================================
  // 1. PURE RECURSION
  // =====================================================
  int solveRec(int start, int end) {
    // Base Case
    if (start >= end) {
      return 0;
    }

    int ans = INT_MAX;

    // Try every possible guess
    for (int i = start; i <= end; i++) {
      int leftCost = solveRec(start, i - 1);
      int rightCost = solveRec(i + 1, end);

      // Worst case cost
      int cost = i + max(leftCost, rightCost);

      ans = min(ans, cost);
    }

    return ans;
  }

  // =====================================================
  // 2. MEMOIZATION (TOP DOWN DP)
  // =====================================================
  int solveMem(int start, int end, vector<vector<int>>& dp) {
    // Base Case
    if (start >= end) {
      return 0;
    }

    // Already solved
    if (dp[start][end] != -1) {
      return dp[start][end];
    }

    int ans = INT_MAX;

    // Try every possible guess
    for (int i = start; i <= end; i++) {
      int leftCost = solveMem(start, i - 1, dp);
      int rightCost = solveMem(i + 1, end, dp);

      // Worst case cost
      int cost = i + max(leftCost, rightCost);

      ans = min(ans, cost);
    }

    return dp[start][end] = ans;
  }

  // =====================================================
  // 3. TABULATION (BOTTOM UP DP)
  // =====================================================
  int solveTab(int n) {
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    // Fill from smaller ranges to larger ranges
    for (int start = n; start >= 1; start--) {
      for (int end = start; end <= n; end++) {
        // Single element range
        if (start == end) {
          continue;
        }

        int ans = INT_MAX;

        // Try every possible guess
        for (int i = start; i <= end; i++) {
          int leftCost = dp[start][i - 1];
          int rightCost = dp[i + 1][end];

          // Worst case cost
          int cost = i + max(leftCost, rightCost);

          ans = min(ans, cost);
        }

        dp[start][end] = ans;
      }
    }

    return dp[1][n];
  }

  int getMoneyAmount(int n) {
    // =================================================
    // PURE RECURSION
    // =================================================
    // return solveRec(1, n);

    // =================================================
    // MEMOIZATION
    // =================================================
    // vector<vector<int>> dp(n + 1,
    //                        vector<int>(n + 1, -1));
    //
    // return solveMem(1, n, dp);

    // =================================================
    // TABULATION
    // =================================================
    return solveTab(n);
  }
};

// =========================================================
// MAIN FUNCTION
// =========================================================
int main() {
  Solution obj;

  int n = 10;

  int ans = obj.getMoneyAmount(n);

  cout << "Minimum money required: " << ans << endl;

  return 0;
}