/*
 * ============================================================
 *  LONGEST INCREASING SUBSEQUENCE (LIS)
 * ============================================================
 *  Problem: Given array, find length of longest strictly
 *  increasing subsequence.
 *
 *  Approaches:
 *   1. DP         — O(n²)   — dp[i] = LIS ending at index i
 *   2. Binary Search (Patience Sorting) — O(n log n)
 *   3. Reconstruct the actual LIS sequence
 *
 *  Related: LDS, LNDS, Number of LIS (LC 673)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  Approach 1 : DP  O(n²)
//  dp[i] = length of LIS ending exactly at index i
//  Recurrence: dp[i] = max(dp[j]+1) for all j < i where arr[j] < arr[i]
// ─────────────────────────────────────────────────────────────
int LIS_DP(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);       // each element is LIS of length 1 alone
    int ans = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

// ─────────────────────────────────────────────────────────────
//  Approach 2 : Binary Search (Patience Sorting)  O(n log n)
//  Maintain a "tails" array where tails[i] = smallest tail
//  element of all increasing subsequences of length i+1.
// ─────────────────────────────────────────────────────────────
int LIS_BinarySearch(vector<int>& arr) {
    vector<int> tails;
    for (int x : arr) {
        // Find first element in tails >= x (lower_bound for strictly increasing)
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);  // extend
        else                   *it = x;              // replace
    }
    return tails.size();
}

// ─────────────────────────────────────────────────────────────
//  Approach 3 : Reconstruct actual LIS sequence  O(n²)
// ─────────────────────────────────────────────────────────────
vector<int> reconstruct_LIS(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1), parent(n, -1);
    int best = 1, bestIdx = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > best) { best = dp[i]; bestIdx = i; }
    }

    vector<int> lis;
    for (int i = bestIdx; i != -1; i = parent[i])
        lis.push_back(arr[i]);
    reverse(lis.begin(), lis.end());
    return lis;
}

// ─────────────────────────────────────────────────────────────
//  Bonus 1: Longest Non-Decreasing Subsequence (LNDS)
//  Same as LIS but allow equal elements — use upper_bound instead
// ─────────────────────────────────────────────────────────────
int LNDS(vector<int>& arr) {
    vector<int> tails;
    for (int x : arr) {
        auto it = upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else                   *it = x;
    }
    return tails.size();
}

// ─────────────────────────────────────────────────────────────
//  Bonus 2: Number of LIS sequences — LC 673  O(n²)
// ─────────────────────────────────────────────────────────────
int numberOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1), cnt(n, 1);
    int maxLen = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                } else if (dp[j] + 1 == dp[i]) {
                    cnt[i] += cnt[j];
                }
            }
        }
        maxLen = max(maxLen, dp[i]);
    }

    int result = 0;
    for (int i = 0; i < n; i++)
        if (dp[i] == maxLen) result += cnt[i];
    return result;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Longest Increasing Subsequence =====\n\n";

    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Array: {10,9,2,5,3,7,101,18}\n";
    cout << "LIS length (DP O(n²)):       " << LIS_DP(arr) << "\n";       // 4
    cout << "LIS length (BS O(n logn)):   " << LIS_BinarySearch(arr) << "\n"; // 4

    auto lis = reconstruct_LIS(arr);
    cout << "Actual LIS sequence: ";
    for (int x : lis) cout << x << " ";
    cout << "\n\n";

    vector<int> arr2 = {1, 3, 6, 7, 9, 4, 10, 5, 6};
    cout << "Array: {1,3,6,7,9,4,10,5,6}\n";
    cout << "LIS length: " << LIS_BinarySearch(arr2) << "\n"; // 6
    cout << "LNDS (non-decreasing): " << LNDS(arr2) << "\n";  // 6

    vector<int> arr3 = {1, 3, 5, 4, 7};
    cout << "\nArray: {1,3,5,4,7}\n";
    cout << "Number of LIS sequences: " << numberOfLIS(arr3) << "\n"; // 2

    return 0;
}
