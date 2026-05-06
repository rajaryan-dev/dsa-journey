#include <climits>
#include <vector>
using namespace std;

/*
===========================================================
🟢 1824. Minimum Sideway Jumps (LeetCode - Medium)

📌 Problem Summary:
- There are 3 lanes and positions from 0 to n.
- A frog starts at lane 2, position 0.
- obstacles[i] tells which lane has obstacle at position i:
    0 = no obstacle
    1,2,3 = obstacle in that lane

🎯 Goal:
Reach position n with minimum side jumps.

⚙️ Rules:
1. Move forward (pos → pos+1) if no obstacle → cost = 0
2. If blocked → can jump to another lane at SAME position → cost = +1

🧠 DP Insight:
State → (lane, position)

Transition:
- If forward possible → move forward
- Else → try other 2 lanes (+1 cost)

⚡ Key Trick:
Always check obstacle at (pos + 1), NOT pos

===========================================================
*/

class Solution {
 public:
  // =========================
  // 1. PURE RECURSION (TLE)
  // =========================
  /*
  int solveRec(vector<int>& obs, int lane, int pos) {
      int n = obs.size() - 1;
      if (pos == n) return 0;

      if (obs[pos + 1] != lane) {
          return solveRec(obs, lane, pos + 1);
      }

      int ans = INT_MAX;
      for (int i = 1; i <= 3; i++) {
          if (i != lane && obs[pos] != i) {
              ans = min(ans, 1 + solveRec(obs, i, pos));
          }
      }
      return ans;
  }
  */

  // =========================
  // 2. MEMOIZATION
  // =========================
  /*
  int solveMem(vector<int>& obs, int lane, int pos, vector<vector<int>>& dp) {
      int n = obs.size() - 1;
      if (pos == n) return 0;

      if (dp[lane][pos] != -1) return dp[lane][pos];

      if (obs[pos + 1] != lane) {
          return dp[lane][pos] = solveMem(obs, lane, pos + 1, dp);
      }

      int ans = INT_MAX;
      for (int i = 1; i <= 3; i++) {
          if (i != lane && obs[pos] != i) {
              ans = min(ans, 1 + solveMem(obs, i, pos, dp));
          }
      }

      return dp[lane][pos] = ans;
  }
  */

  // =========================
  // 3. TABULATION
  // =========================
  /*
  int solveTab(vector<int>& obs) {
      int n = obs.size();
      vector<vector<int>> dp(4, vector<int>(n, 1e9));

      for (int lane = 1; lane <= 3; lane++) {
          dp[lane][n - 1] = 0;
      }

      for (int pos = n - 2; pos >= 0; pos--) {
          for (int lane = 1; lane <= 3; lane++) {

              if (obs[pos + 1] != lane) {
                  dp[lane][pos] = dp[lane][pos + 1];
              } else {
                  int ans = 1e9;

                  for (int i = 1; i <= 3; i++) {
                      if (i != lane && obs[pos] != i) {
                          ans = min(ans, 1 + dp[i][pos]);
                      }
                  }
                  dp[lane][pos] = ans;
              }
          }
      }

      return dp[2][0];
  }
  */

  // =========================
  // 4. SPACE OPTIMIZED (BEST)
  // =========================
  int solveSpace(vector<int>& obs) {
    int n = obs.size();

    vector<int> curr(4, 1e9), next(4, 0);

    for (int pos = n - 2; pos >= 0; pos--) {
      for (int lane = 1; lane <= 3; lane++) {
        if (obs[pos + 1] != lane) {
          curr[lane] = next[lane];
        } else {
          int ans = 1e9;

          for (int i = 1; i <= 3; i++) {
            if (i != lane && obs[pos] != i) {
              ans = min(ans, 1 + next[i]);
            }
          }
          curr[lane] = ans;
        }
      }
      next = curr;
    }

    return next[2];
  }

  // =========================
  // MAIN FUNCTION
  // =========================
  int minSideJumps(vector<int>& obstacles) {
    // Recursion
    // return solveRec(obstacles, 2, 0);

    // Memoization
    /*
    int n = obstacles.size();
    vector<vector<int>> dp(4, vector<int>(n, -1));
    return solveMem(obstacles, 2, 0, dp);
    */

    // Tabulation
    // return solveTab(obstacles);

    // Space Optimized (ACTIVE ✅)
    return solveSpace(obstacles);
  }
};