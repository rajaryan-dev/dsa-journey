#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
 * ============================================================
 * LC 983. Minimum Cost For Tickets
 * Difficulty: Medium
 * Topic: Dynamic Programming
 * ============================================================
 *
 * PROBLEM:
 * You have a list of travel days (1–365) for the year.
 * Three types of passes are available:
 *   - 1-day  pass: costs[0]
 *   - 7-day  pass: costs[1]
 *   - 30-day pass: costs[2]
 * A pass bought on day D covers D, D+1, ..., D+(duration-1).
 * Return the minimum cost to cover all travel days.
 *
 * APPROACH:
 * Index-based DP — track position in the `days` array, not the
 * calendar day. At each index, try all 3 passes and jump to
 * the next uncovered travel day.
 *
 * State:  dp[i] = min cost to cover all travel days from index i onward
 * Base:   dp[n] = 0  (no more travel days left)
 *
 * Transition (for index k):
 *   op1 = costs[0] + dp[k+1]          // 1-day pass covers just days[k]
 *   op2 = costs[1] + dp[i7]           // 7-day pass, i7 = first index not
 * covered op3 = costs[2] + dp[i30]          // 30-day pass, i30 = first index
 * not covered dp[k] = min(op1, op2, op3)
 *
 * Time:  O(n)   — each index processed once; inner while loops are O(n) total
 * Space: O(n)   — dp array of size n+1
 * ============================================================
 */

class Solution {
 public:
  // ============================================================
  // METHOD 1: RECURSION (Pure, no memoization)
  // ============================================================
  // Simple top-down recursion. At each index, try all 3 passes
  // and recurse to the next uncovered index.
  //
  // Problem: Overlapping subproblems are recomputed repeatedly.
  // Time: O(3^n) in worst case → TLE on large inputs.
  // Space: O(n) recursion stack
  // ============================================================

  int solveRec(int n, vector<int>& days, vector<int>& costs, int index) {
    // Base case: no travel days left to cover
    if (index >= n) return 0;

    // Option 1: Buy 1-day pass → move to next index
    int op1 = costs[0] + solveRec(n, days, costs, index + 1);

    // Option 2: Buy 7-day pass → skip all days covered by this pass
    int i7 = index;
    while (i7 < n && days[i7] < days[index] + 7) i7++;
    int op2 = costs[1] + solveRec(n, days, costs, i7);

    // Option 3: Buy 30-day pass → skip all days covered by this pass
    int i30 = index;
    while (i30 < n && days[i30] < days[index] + 30) i30++;
    int op3 = costs[2] + solveRec(n, days, costs, i30);

    return min({op1, op2, op3});
  }

  // ============================================================
  // METHOD 2: MEMOIZATION (Top-Down DP)
  // ============================================================
  // Same recursion as above, but cache results in dp[index].
  // Each index is computed at most once → eliminates redundant work.
  //
  // Time:  O(n)
  // Space: O(n) dp array + O(n) recursion stack
  // ============================================================

  int solveMem(int n, vector<int>& days, vector<int>& costs, int index,
               vector<int>& dp) {
    // Base case: no travel days left to cover
    if (index >= n) return 0;

    // Return cached result if already computed
    if (dp[index] != -1) return dp[index];

    // Option 1: Buy 1-day pass
    int op1 = costs[0] + solveMem(n, days, costs, index + 1, dp);

    // Option 2: Buy 7-day pass
    int i7 = index;
    while (i7 < n && days[i7] < days[index] + 7) i7++;
    int op2 = costs[1] + solveMem(n, days, costs, i7, dp);

    // Option 3: Buy 30-day pass
    int i30 = index;
    while (i30 < n && days[i30] < days[index] + 30) i30++;
    int op3 = costs[2] + solveMem(n, days, costs, i30, dp);

    dp[index] = min({op1, op2, op3});
    return dp[index];
  }

  // ============================================================
  // METHOD 3: TABULATION (Bottom-Up DP)  ← FINAL / BEST
  // ============================================================
  // Iterative. Fill dp[] from right to left (index n-1 down to 0).
  // No recursion stack. Cleanest for interviews.
  //
  // dp[k] = min cost to cover all travel days from index k onward
  // dp[n] = 0  (base case: nothing left to cover)
  //
  // Time:  O(n)
  // Space: O(n)
  // ============================================================

  int solveTab(int n, vector<int>& days, vector<int>& costs) {
    // Initialize all to 0; dp[n] = 0 is the base case naturally
    vector<int> dp(n + 1, 0);

    // Fill from last travel day index backwards
    for (int k = n - 1; k >= 0; k--) {
      // Option 1: 1-day pass → next index is k+1
      int op1 = costs[0] + dp[k + 1];

      // Option 2: 7-day pass → find first index not covered
      int i7 = k;
      while (i7 < n && days[i7] < days[k] + 7) i7++;
      int op2 = costs[1] + dp[i7];

      // Option 3: 30-day pass → find first index not covered
      int i30 = k;
      while (i30 < n && days[i30] < days[k] + 30) i30++;
      int op3 = costs[2] + dp[i30];

      dp[k] = min({op1, op2, op3});
    }

    // dp[0] = min cost to cover all travel days
    return dp[0];
  }
  // Space-Optimized:

  int Optimized(int n, vector<int>& days, vector<int>& cost) {
    int ans = 0;

    // Each queue stores {travel_day, cumulative_cost_if_pass_bought_then}
    // Acts as a sliding window of active passes
    queue<pair<int, int>> week;   // active 7-day passes
    queue<pair<int, int>> month;  // active 30-day passes

    for (int day : days) {
      // Step 1: Expire passes that no longer cover current day
      while (!month.empty() && month.front().first + 30 <= day) month.pop();
      while (!week.empty() && week.front().first + 7 <= day) week.pop();

      // Step 2: Push this day with cost if we were to buy a pass here
      week.push({day, ans + cost[1]});
      month.push({day, ans + cost[2]});

      // Step 3: Pick cheapest option
      ans = min({ans + cost[0],           // 1-day pass today
                 week.front().second,     // best active 7-day pass
                 month.front().second});  // best active 30-day pass
    }

    return ans;
  }

  // ============================================================
  // DRIVER
  // ============================================================

  int mincostTickets(vector<int>& days, vector<int>& costs) {
    int n = days.size();

    // --- Recursion ---
    // return solveRec(n, days, costs, 0);

    // --- Memoization ---
    // vector<int> dp(n + 1, -1);
    // return solveMem(n, days, costs, 0, dp);

    // --- Tabulation (active) ---
    return solveTab(n, days, costs);
  }
};

/*
 * ============================================================
 * DRY RUN — Example 1
 * days = [1,4,6,7,8,20], costs = [2,7,15]
 * n = 6
 *
 * Tabulation (right to left):
 *
 * dp[6] = 0
 *
 * k=5 (day 20):
 *   op1 = 2 + dp[6] = 2
 *   i7:  days[5]=20, 20 < 20+7=27 → i7=6  → op2 = 7 + dp[6] = 7
 *   i30: days[5]=20, 20 < 20+30=50 → i30=6 → op3 = 15 + dp[6] = 15
 *   dp[5] = min(2,7,15) = 2
 *
 * k=4 (day 8):
 *   op1 = 2 + dp[5] = 4
 *   i7:  days[4]=8, 8<15 → i7=5; days[5]=20, 20>=15 → stop, i7=5
 *        op2 = 7 + dp[5] = 9
 *   i30: days[4]=8, 8<38 → ... → i30=6 → op3 = 15 + 0 = 15
 *   dp[4] = min(4,9,15) = 4
 *
 * k=3 (day 7):
 *   op1 = 2 + dp[4] = 6
 *   i7:  days[3]=7, 7<14 → i7=4; days[4]=8, 8<14 → i7=5; days[5]=20 ≥14 → stop
 *        op2 = 7 + dp[5] = 9
 *   i30: → i30=6 → op3 = 15
 *   dp[3] = min(6,9,15) = 6
 *
 * k=2 (day 6):
 *   op1 = 2 + dp[3] = 8
 *   i7:  6 < 13 → i7 moves past days 6,7,8 → i7=5; 20≥13 stop
 *        op2 = 7 + dp[5] = 9
 *   i30: → i30=6 → op3=15
 *   dp[2] = min(8,9,15) = 8
 *
 * k=1 (day 4):
 *   op1 = 2 + dp[2] = 10
 *   i7:  4 < 11 → moves past 4,6,7,8 → i7=5; 20≥11 stop
 *        op2 = 7 + dp[5] = 9
 *   i30: → i30=6 → op3=15
 *   dp[1] = min(10,9,15) = 9
 *
 * k=0 (day 1):
 *   op1 = 2 + dp[1] = 11
 *   i7:  1 < 8 → moves past 1,4,6,7 → i7=4; 8≥8 stop
 *        op2 = 7 + dp[4] = 11
 *   i30: → i30=6 → op3=15
 *   dp[0] = min(11,11,15) = 11  ✓
 *
 * Answer: 11
 * ============================================================
 */