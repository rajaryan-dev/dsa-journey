/*
 * ============================================================
 *  FILE      : derangement_of_balls_dp.cpp
 *  PROBLEM   : Disarrangement of Balls (Derangement)
 *  PLATFORM  : GeeksForGeeks
 *  LINK      :
 * https://www.geeksforgeeks.org/problems/dearrangement-of-balls0918/1 TOPIC :
 * Dynamic Programming PATTERN   : Fibonacci-style DP (Counting / Combinatorics)
 *  DATE      : 2025
 * ============================================================
 *
 *  PROBLEM STATEMENT:
 *  ------------------
 *  Given N balls numbered 1 to N, count the number of ways
 *  to arrange them such that NO ball ends up in its original
 *  position. This is called a DERANGEMENT.
 *
 *  Example:
 *    N = 1  →  0  (only arrangement is [1], which is original)
 *    N = 2  →  1  ([2,1] is the only derangement)
 *    N = 3  →  2  ([2,3,1] and [3,1,2])
 *    N = 4  →  9
 *
 *  RECURRENCE RELATION:
 *  --------------------
 *    D(1) = 0
 *    D(2) = 1
 *    D(n) = (n-1) * (D(n-1) + D(n-2))
 *
 *  INTUITION BEHIND THE FORMULA:
 *  ------------------------------
 *  Place ball `n`. It can go into any of (n-1) positions.
 *  Say ball `n` goes to position `k`. Now two sub-cases:
 *    Case 1: Ball `k` goes to position `n`  →  remaining (n-2) balls
 *            need to be deranged  →  D(n-2) ways
 *    Case 2: Ball `k` does NOT go to position `n`  →  treat position `n`
 *            as "forbidden" for ball `k`, effectively a derangement
 *            of (n-1) balls  →  D(n-1) ways
 *  Total: (n-1) * (D(n-1) + D(n-2))
 *
 *  COMPLEXITY SUMMARY:
 *  -------------------
 *  | Method          | Time   | Space        |
 *  |-----------------|--------|--------------|
 *  | Recursion       | O(2^n) | O(n) stack   |
 *  | Memoization     | O(n)   | O(n) dp+stack|
 *  | Tabulation      | O(n)   | O(n) dp      |
 *  | Space-Optimized | O(n)   | O(1)         |
 *
 * ============================================================
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  // =========================================================
  // METHOD 1: Pure Recursion
  // ---------------------------------------------------------
  // Directly applies the recurrence. No caching.
  // Time : O(2^n)  — overlapping subproblems recomputed
  // Space: O(n)    — recursion call stack depth
  // =========================================================
  int solveRec(int n) {
    // Base cases
    if (n == 1) return 0;
    if (n == 2) return 1;

    // Recurrence: (n-1) * (D(n-1) + D(n-2))
    return (n - 1) * (solveRec(n - 1) + solveRec(n - 2));
  }

  // =========================================================
  // METHOD 2: Memoization (Top-Down DP)
  // ---------------------------------------------------------
  // Recursion + cache. Each subproblem solved only once.
  // Time : O(n)
  // Space: O(n) dp array + O(n) stack
  // =========================================================
  int solveMem(int n, vector<int>& dp) {
    // Base cases
    if (n == 1) return 0;
    if (n == 2) return 1;

    // Return cached result if already computed
    if (dp[n] != -1) return dp[n];

    // Cache and return
    return dp[n] = (n - 1) * (solveMem(n - 1, dp) + solveMem(n - 2, dp));
  }

  // =========================================================
  // METHOD 3: Tabulation (Bottom-Up DP)
  // ---------------------------------------------------------
  // Fills dp table from base cases up to n. No recursion.
  // Time : O(n)
  // Space: O(n) dp array
  // =========================================================
  int solveTab(int n) {
    // Edge cases before indexing dp[2]
    if (n <= 1) return 0;
    if (n == 2) return 1;

    // dp[i] = number of derangements of i balls
    // Size n+1 so index n is valid
    vector<int> dp(n + 1, 0);
    dp[1] = 0;
    dp[2] = 1;

    for (int i = 3; i <= n; i++) {
      dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
    }

    return dp[n];
  }

  // =========================================================
  // METHOD 4: Space-Optimized (Optimal)
  // ---------------------------------------------------------
  // Only the last two values are ever needed, so drop the
  // full array and use two variables instead.
  // Time : O(n)
  // Space: O(1)
  // =========================================================
  int solveOptimized(int n) {
    // Edge cases
    if (n <= 1) return 0;
    if (n == 2) return 1;

    int prev2 = 0;  // D(1)
    int prev1 = 1;  // D(2)

    for (int i = 3; i <= n; i++) {
      int curr = (i - 1) * (prev1 + prev2);
      prev2 = prev1;
      prev1 = curr;
    }

    return prev1;  // D(n)
  }

  // =========================================================
  // DRIVER: countDer
  // Switch between methods by uncommenting one line.
  // =========================================================
  int countDer(int n) {
    // M-1: Pure Recursion
    // return solveRec(n);

    // M-2: Memoization
    // vector<int> dp(n + 1, -1);
    // return solveMem(n, dp);

    // M-3: Tabulation
    // return solveTab(n);

    // M-4: Space-Optimized (default)
    return solveOptimized(n);
  }
};

// ============================================================
//  MAIN — quick local test (no cin, hardcoded inputs)
// ============================================================
int main() {
  Solution sol;

  // Expected: D(1)=0, D(2)=1, D(3)=2, D(4)=9, D(5)=44
  int testCases[] = {1, 2, 3, 4, 5};

  for (int n : testCases) {
    cout << "D(" << n << ") = " << sol.countDer(n) << "\n";
  }

  return 0;
}

/*
 *  EXPECTED OUTPUT:
 *  ----------------
 *  D(1) = 0
 *  D(2) = 1
 *  D(3) = 2
 *  D(4) = 9
 *  D(5) = 44
 *
 *  KEY TAKEAWAY:
 *  -------------
 *  Derangement is a classic combinatorics problem solved with
 *  Fibonacci-style DP. The recurrence D(n) = (n-1)*(D(n-1)+D(n-2))
 *  is worth memorising — it appears in counting problems involving
 *  forbidden positions.
 */