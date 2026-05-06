#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

class Solution {
 public:
  // ── Method 1: Pure Recursion ─────────────────────────────────────────
  int solveRec(vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    if (amount < 0) return INT_MAX;

    int mini = INT_MAX;
    for (int i = 0; i < coins.size(); i++) {
      int ans = solveRec(coins, amount - coins[i]);
      if (ans != INT_MAX) mini = min(mini, 1 + ans);
    }
    return mini;
  }

  // ── Method 2: Top-Down (Memoization) ─────────────────────────────────
  int solveMem(vector<int>& coins, int amount, vector<int>& dp) {
    if (amount == 0) return 0;
    if (amount < 0) return INT_MAX;
    if (dp[amount] != -1) return dp[amount];

    int mini = INT_MAX;
    for (int i = 0; i < coins.size(); i++) {
      int ans = solveMem(coins, amount - coins[i], dp);
      if (ans != INT_MAX) mini = min(mini, 1 + ans);
    }
    dp[amount] = mini;
    return dp[amount];
  }

  // ── Method 3: Bottom-Up (Tabulation) ─────────────────────────────────
  int solveTab(vector<int>& coins, int amount) {
    // dp[i] = min coins needed to make amount i
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
      for (int j = 0; j < coins.size(); j++) {
        if (coins[j] <= i && dp[i - coins[j]] != INT_MAX)
          dp[i] = min(dp[i], 1 + dp[i - coins[j]]);
      }
    }
    return dp[amount];
  }

  // ── Method 4: Space Optimized ─────────────────────────────────────────
  // Tabulation itself is already O(amount) space.
  // No further optimization possible since all previous
  // states are needed (not just last row/col). Same as Method 3.

  // ─────────────────────────────────────────────────────────────────────
  int coinChange(vector<int>& coins, int amount) {
    // Method 1: Pure Recursion  →  TLE for large inputs
    // int ans = solveRec(coins, amount);

    // Method 2: Top-Down
    // vector<int> dp(amount + 1, -1);
    // int ans = solveMem(coins, amount, dp);

    // Method 3 & 4: Bottom-Up (optimal)
    int ans = solveTab(coins, amount);

    return (ans != INT_MAX) ? ans : -1;
  }
};