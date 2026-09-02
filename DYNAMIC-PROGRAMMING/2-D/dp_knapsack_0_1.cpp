/*
 * ============================================================
 *  0/1 KNAPSACK & VARIANTS
 * ============================================================
 *  Problem: Given n items with weight[] and value[], and a
 *  capacity W — pick items to MAXIMISE value without exceeding W.
 *  Each item can be taken at most ONCE (0/1).
 *
 *  Variants covered:
 *   1. 0/1 Knapsack (2D DP, 1D optimized)
 *   2. Unbounded Knapsack (items can repeat)
 *   3. Subset Sum — does a subset with sum S exist?
 *   4. Partition Equal Subset Sum — LC 416
 *   5. Target Sum — LC 494 (count ways)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  1a. 0/1 Knapsack — 2D DP  O(n*W)
//  dp[i][w] = max value using first i items with capacity w
// ─────────────────────────────────────────────────────────────
int knapsack_2D(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            // Don't take item i
            dp[i][w] = dp[i-1][w];
            // Take item i (if it fits)
            if (wt[i-1] <= w)
                dp[i][w] = max(dp[i][w], dp[i-1][w - wt[i-1]] + val[i-1]);
        }
    }
    return dp[n][W];
}

// ─────────────────────────────────────────────────────────────
//  1b. 0/1 Knapsack — 1D (Space Optimized)  O(W) space
//  Process w from W down to wt[i] to avoid re-using same item
// ─────────────────────────────────────────────────────────────
int knapsack_1D(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < n; i++)
        for (int w = W; w >= wt[i]; w--)     // ← RIGHT TO LEFT (key!)
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

// ─────────────────────────────────────────────────────────────
//  2. Unbounded Knapsack — Items can be used unlimited times
//  Process w from LEFT TO RIGHT (allows reuse)
// ─────────────────────────────────────────────────────────────
int unboundedKnapsack(vector<int>& wt, vector<int>& val, int W) {
    vector<int> dp(W + 1, 0);
    for (int w = 1; w <= W; w++)
        for (int i = 0; i < (int)wt.size(); i++)
            if (wt[i] <= w)
                dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
    return dp[W];
}

// ─────────────────────────────────────────────────────────────
//  3. Subset Sum — Does any subset sum to target?  O(n*target)
// ─────────────────────────────────────────────────────────────
bool subsetSum(vector<int>& nums, int target) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    for (int x : nums)
        for (int t = target; t >= x; t--)
            dp[t] = dp[t] || dp[t - x];
    return dp[target];
}

// ─────────────────────────────────────────────────────────────
//  4. Partition Equal Subset Sum — LC 416
//  Split array into two subsets with equal sum.
//  Key: total sum must be even; find subset with sum/2.
// ─────────────────────────────────────────────────────────────
bool canPartition(vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2 != 0) return false;
    return subsetSum(nums, total / 2);
}

// ─────────────────────────────────────────────────────────────
//  5. Target Sum — LC 494
//  Assign + or - to each num, count ways to reach target.
//  Math reduction: let P = sum of + group, N = sum of - group
//    P + N = total,  P - N = target  →  P = (total + target) / 2
//  Count subsets with sum P using DP (count DP variant)
// ─────────────────────────────────────────────────────────────
int findTargetSumWays(vector<int>& nums, int target) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (abs(target) > total || (total + target) % 2 != 0) return 0;
    int S = (total + target) / 2;

    vector<int> dp(S + 1, 0);
    dp[0] = 1;
    for (int x : nums)
        for (int j = S; j >= x; j--)
            dp[j] += dp[j - x];
    return dp[S];
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== 0/1 Knapsack & Variants =====\n\n";

    vector<int> wt  = {1, 3, 4, 5};
    vector<int> val = {1, 4, 5, 7};
    int W = 7;
    cout << "Items: wt={1,3,4,5}  val={1,4,5,7}  Capacity=7\n";
    cout << "0/1 Knapsack (2D): " << knapsack_2D(wt, val, W) << "\n"; // 9
    cout << "0/1 Knapsack (1D): " << knapsack_1D(wt, val, W) << "\n"; // 9

    cout << "\nUnbounded Knapsack (same items, reuse allowed): "
         << unboundedKnapsack(wt, val, W) << "\n"; // 11

    cout << "\n--- Subset Sum ---\n";
    vector<int> nums = {3, 34, 4, 12, 5, 2};
    cout << "Nums={3,34,4,12,5,2}  Target=9:  "
         << (subsetSum(nums, 9) ? "YES" : "NO") << "\n"; // YES
    cout << "Nums={3,34,4,12,5,2}  Target=30: "
         << (subsetSum(nums, 30) ? "YES" : "NO") << "\n"; // NO

    cout << "\n--- Partition Equal Subset Sum ---\n";
    vector<int> p1 = {1, 5, 11, 5};
    vector<int> p2 = {1, 2, 3, 5};
    cout << "{1,5,11,5} can partition: "
         << (canPartition(p1) ? "YES" : "NO") << "\n"; // YES
    cout << "{1,2,3,5}  can partition: "
         << (canPartition(p2) ? "YES" : "NO") << "\n"; // NO

    cout << "\n--- Target Sum ---\n";
    vector<int> ts = {1, 1, 1, 1, 1};
    cout << "{1,1,1,1,1} target=3, ways: "
         << findTargetSumWays(ts, 3) << "\n"; // 5

    return 0;
}
