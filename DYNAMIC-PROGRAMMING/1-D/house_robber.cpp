#include <algorithm>
#include <vector>
using namespace std;

class Solution {
 public:
  // ==========================================
  // 1. RECURSION (Top-Down, No Memoization)
  // TC: O(2^n) | SC: O(n) recursion stack
  // ==========================================
  int solveRec(vector<int>& nums, int n) {
    // Base cases
    if (n < 0) return 0;
    if (n == 0) return nums[0];

    int incl = solveRec(nums, n - 2) + nums[n];  // rob current house
    int excl = solveRec(nums, n - 1);            // skip current house

    return max(incl, excl);
  }

  // ==========================================
  // 2. MEMOIZATION (Top-Down + Cache)
  // TC: O(n) | SC: O(n) dp + O(n) recursion stack
  // ==========================================
  int solveMemo(vector<int>& nums, int n, vector<int>& dp) {
    // Base cases
    if (n < 0) return 0;
    if (n == 0) return nums[0];

    // Return cached result if already computed
    if (dp[n] != -1) return dp[n];

    int incl = solveMemo(nums, n - 2, dp) + nums[n];  // rob current house
    int excl = solveMemo(nums, n - 1, dp);            // skip current house

    dp[n] = max(incl, excl);
    return dp[n];
  }

  // ==========================================
  // 3. TABULATION (Bottom-Up)
  // TC: O(n) | SC: O(n)
  // ==========================================
  int solveTab(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 0);

    dp[0] = nums[0];  // only one house, rob it
    if (n == 1) return dp[0];
    dp[1] = max(nums[0], nums[1]);  // two houses, rob the better one

    // For each house, decide: rob it (skip one back) or skip it (take prev
    // best)
    for (int i = 2; i < n; i++) {
      int incl = dp[i - 2] + nums[i];  // rob current house
      int excl = dp[i - 1];            // skip current house
      dp[i] = max(incl, excl);
    }

    return dp[n - 1];
  }

  // ==========================================
  // 4. SPACE OPTIMIZED
  // TC: O(n) | SC: O(1)
  // ==========================================
  int solveOptimized(vector<int>& nums) {
    int n = nums.size();

    int prev2 = nums[0];  // dp[i-2]: best up to two houses back
    if (n == 1) return prev2;
    int prev1 = max(nums[0], nums[1]);  // dp[i-1]: best up to previous house

    for (int i = 2; i < n; i++) {
      int incl = prev2 + nums[i];  // rob current house
      int excl = prev1;            // skip current house
      int curr = max(incl, excl);  // best up to current house
      prev2 = prev1;               // slide window forward
      prev1 = curr;
    }

    return prev1;  // holds the final answer
  }

  // ==========================================
  // MAIN FUNCTION
  // ==========================================
  int rob(vector<int>& nums) {
    // --- Recursion ---
    // return solveRec(nums, nums.size() - 1);

    // --- Memoization ---
    // int n = nums.size();
    // vector<int> dp(n, -1);
    // return solveMemo(nums, n - 1, dp);

    // --- Tabulation ---
    // return solveTab(nums);

    // --- Space Optimized ---
    return solveOptimized(nums);
  }
};