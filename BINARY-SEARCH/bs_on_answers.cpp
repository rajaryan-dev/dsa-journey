/*
 * ============================================================
 *  BINARY SEARCH ON ANSWER SPACE
 * ============================================================
 *  Key Insight:
 *    Instead of searching for a value IN an array, we search
 *    for the ANSWER within a range [lo, hi], and check
 *    feasibility of each mid via a helper predicate.
 *
 *  Template:
 *    lo = min_possible_answer
 *    hi = max_possible_answer
 *    while (lo < hi) {
 *        mid = lo + (hi - lo) / 2;
 *        if (feasible(mid)) hi = mid;   // or lo = mid + 1
 *        else               lo = mid + 1; // depends on direction
 *    }
 *    return lo;
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  Problem 1: Koko Eating Bananas (LC 875)
//  Piles of bananas, h hours, find minimum eating speed k.
// ─────────────────────────────────────────────────────────────
bool canFinish(vector<int>& piles, int k, int h) {
    long long hours = 0;
    for (int p : piles)
        hours += (p + k - 1) / k;  // ceil(p/k)
    return hours <= h;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int lo = 1, hi = *max_element(piles.begin(), piles.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canFinish(piles, mid, h)) hi = mid;
        else                          lo = mid + 1;
    }
    return lo;
}

// ─────────────────────────────────────────────────────────────
//  Problem 2: Minimum Days to Make m Bouquets (LC 1482)
//  Each bouquet needs k adjacent bloomed flowers.
// ─────────────────────────────────────────────────────────────
bool canMakeBouquets(vector<int>& bloom, int m, int k, int day) {
    int bouquets = 0, consecutive = 0;
    for (int b : bloom) {
        if (b <= day) {
            consecutive++;
            if (consecutive == k) { bouquets++; consecutive = 0; }
        } else {
            consecutive = 0;
        }
    }
    return bouquets >= m;
}

int minDays(vector<int>& bloomDay, int m, int k) {
    if ((long long)m * k > bloomDay.size()) return -1;
    int lo = 1, hi = *max_element(bloomDay.begin(), bloomDay.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canMakeBouquets(bloomDay, m, k, mid)) hi = mid;
        else                                       lo = mid + 1;
    }
    return lo;
}

// ─────────────────────────────────────────────────────────────
//  Problem 3: Split Array Largest Sum (LC 410)
//  Split array into m subarrays, minimise the largest sum.
// ─────────────────────────────────────────────────────────────
bool canSplit(vector<int>& nums, int m, int maxSum) {
    int parts = 1, curSum = 0;
    for (int n : nums) {
        if (n > maxSum) return false;
        if (curSum + n > maxSum) { parts++; curSum = n; }
        else                       curSum += n;
    }
    return parts <= m;
}

int splitArray(vector<int>& nums, int m) {
    int lo = *max_element(nums.begin(), nums.end());
    int hi = accumulate(nums.begin(), nums.end(), 0);
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canSplit(nums, m, mid)) hi = mid;
        else                        lo = mid + 1;
    }
    return lo;
}

// ─────────────────────────────────────────────────────────────
//  Problem 4: Find Square Root (integer, floor) — classic
// ─────────────────────────────────────────────────────────────
int mySqrt(int x) {
    if (x < 2) return x;
    long long lo = 1, hi = x / 2;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (mid * mid == x) return mid;
        if (mid * mid < x)  lo = mid + 1;
        else                hi = mid - 1;
    }
    return hi;
}

// ─────────────────────────────────────────────────────────────
//  Problem 5: Capacity to Ship Packages in D Days (LC 1011)
// ─────────────────────────────────────────────────────────────
bool feasible(vector<int>& weights, int capacity, int days) {
    int d = 1, load = 0;
    for (int w : weights) {
        if (load + w > capacity) { d++; load = 0; }
        load += w;
    }
    return d <= days;
}

int shipWithinDays(vector<int>& weights, int days) {
    int lo = *max_element(weights.begin(), weights.end());
    int hi = accumulate(weights.begin(), weights.end(), 0);
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (feasible(weights, mid, days)) hi = mid;
        else                              lo = mid + 1;
    }
    return lo;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Binary Search on Answer Space =====\n\n";

    // Koko
    vector<int> piles = {3, 6, 7, 11};
    cout << "Koko eating bananas (piles={3,6,7,11}, h=8): "
         << minEatingSpeed(piles, 8) << "\n"; // 4

    // Bouquets
    vector<int> bloom = {1, 10, 3, 10, 2};
    cout << "Min days for 3 bouquets of size 1: "
         << minDays(bloom, 3, 1) << "\n"; // 3

    // Split array
    vector<int> nums = {7, 2, 5, 10, 8};
    cout << "Split {7,2,5,10,8} into 2 parts, min largest sum: "
         << splitArray(nums, 2) << "\n"; // 18

    // Sqrt
    cout << "floor(sqrt(8)) = " << mySqrt(8) << "\n"; // 2
    cout << "floor(sqrt(16)) = " << mySqrt(16) << "\n"; // 4

    // Ship packages
    vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Min ship capacity (D=5 days): "
         << shipWithinDays(weights, 5) << "\n"; // 15

    return 0;
}
