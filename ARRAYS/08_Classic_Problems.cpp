/*
 * ============================================================================
 * FILE: 08_Classic_Problems.cpp
 * ============================================================================
 *
 * CLASSIC ARRAY PROBLEMS (Interview Favourites)
 *
 * ┌──────────────────────────────────┬──────────┬───────┐
 * │ Problem                         │ Time     │ Space │
 * ├──────────────────────────────────┼──────────┼───────┤
 * │ Kadane's (Max Subarray Sum)     │ O(n)     │ O(1)  │
 * │ Dutch National Flag (0,1,2)     │ O(n)     │ O(1)  │
 * │ Merge Two Sorted Arrays         │ O(n + m) │ O(n+m)│
 * │ Subarray with Given Sum         │ O(n)     │ O(1)  │
 * │ Best Time to Buy/Sell Stock     │ O(n)     │ O(1)  │
 * │ Move Negatives to One Side      │ O(n)     │ O(1)  │
 * │ Trapping Rain Water             │ O(n)     │ O(1)  │
 * └──────────────────────────────────┴──────────┴───────┘
 *
 * ============================================================================
 */

#include <algorithm>   // std::swap, std::max, std::min
#include <climits>
#include <iostream>
#include <utility>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// UTILITY: Print Array
// ─────────────────────────────────────────────────────────────────────────────
void printArray(const int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// 1. KADANE'S ALGORITHM — Maximum Subarray Sum — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Idea: at each position, decide — extend the current subarray OR start
//   a fresh one from the current element.
//
//     currentMax = max(arr[i], currentMax + arr[i])
//     globalMax  = max(globalMax, currentMax)
//
//   Example: [-2, 1, -3, 4, -1, 2, 1, -5, 4]
//     Max subarray: [4, -1, 2, 1]  →  sum = 6
// ─────────────────────────────────────────────────────────────────────────────
int kadane(const int arr[], int size) {
    int curMax = arr[0], globalMax = arr[0];

    for (int i = 1; i < size; i++) {
        curMax = max(arr[i], curMax + arr[i]);
        globalMax = max(globalMax, curMax);
    }
    return globalMax;
}

// ─────────────────────────────────────────────────────────────────────────────
// 2. DUTCH NATIONAL FLAG — Sort 0s, 1s, 2s — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Three pointers: lo, mid, hi
//     lo  = boundary for 0s (everything < lo is 0)
//     hi  = boundary for 2s (everything > hi is 2)
//     mid = current element being examined
//
//     if arr[mid] == 0 → swap(arr[lo], arr[mid]),  lo++, mid++
//     if arr[mid] == 1 → mid++
//     if arr[mid] == 2 → swap(arr[mid], arr[hi]),  hi--
//
//   Before: [0, 1, 2, 0, 1, 2]  →  After: [0, 0, 1, 1, 2, 2]
// ─────────────────────────────────────────────────────────────────────────────
void dutchNationalFlag(int arr[], int size) {
    int lo = 0, mid = 0, hi = size - 1;

    while (mid <= hi) {
        if (arr[mid] == 0) {
            swap(arr[lo++], arr[mid++]);
        } else if (arr[mid] == 1) {
            mid++;
        } else {   // arr[mid] == 2
            swap(arr[mid], arr[hi--]);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 3. MERGE TWO SORTED ARRAYS — O(n + m)
// ─────────────────────────────────────────────────────────────────────────────
//   Two pointers (i for a[], j for b[]). Compare front elements, pick
//   the smaller one into result[].  Flush remaining elements at the end.
//
//   a = [1, 3, 5]   b = [2, 4, 6]  →  result = [1, 2, 3, 4, 5, 6]
// ─────────────────────────────────────────────────────────────────────────────
void mergeSorted(const int a[], int n, const int b[], int m,
                 int result[], int& resSize) {
    int i = 0, j = 0, k = 0;

    while (i < n && j < m) {
        if (a[i] <= b[j]) result[k++] = a[i++];
        else              result[k++] = b[j++];
    }
    while (i < n) result[k++] = a[i++];
    while (j < m) result[k++] = b[j++];

    resSize = k;
}

// ─────────────────────────────────────────────────────────────────────────────
// 4. SUBARRAY WITH GIVEN SUM (Non-negative) — Sliding Window — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Expand window (add right), shrink window (subtract left) until sum
//   equals target.
//
//   [1, 4, 20, 3, 10, 5]  target=33  →  subarray [20, 3, 10]  indices 2..4
// ─────────────────────────────────────────────────────────────────────────────
bool subarrayWithSum(const int arr[], int size, int target,
                     int& start, int& end) {
    int windowSum = 0;
    start = 0;

    for (int i = 0; i < size; i++) {
        windowSum += arr[i];

        while (windowSum > target && start <= i) {
            windowSum -= arr[start++];
        }
        if (windowSum == target) {
            end = i;
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// 5. BEST TIME TO BUY & SELL STOCK (Single Transaction) — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Track the minimum price seen so far. At each day, compute potential
//   profit if we sell today.  Keep the maximum of all potential profits.
//
//   prices = [7, 1, 5, 3, 6, 4]
//     Buy at 1, sell at 6 → profit = 5
// ─────────────────────────────────────────────────────────────────────────────
int maxStockProfit(const int prices[], int n) {
    if (n < 2) return 0;

    int minPrice = prices[0];
    int maxProfit = 0;

    for (int i = 1; i < n; i++) {
        maxProfit = max(maxProfit, prices[i] - minPrice);
        minPrice  = min(minPrice, prices[i]);
    }
    return maxProfit;
}

// ─────────────────────────────────────────────────────────────────────────────
// 6. MOVE NEGATIVES TO ONE SIDE — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Partition-style: keep a write pointer for negatives. Scan left to
//   right; whenever a negative is found, swap it to the write position.
//
//   [-1, 2, -3, 4, 5, -6]  →  [-1, -3, -6, 4, 5, 2]   (order may change)
// ─────────────────────────────────────────────────────────────────────────────
void moveNegatives(int arr[], int size) {
    int write = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            swap(arr[write++], arr[i]);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 7. TRAPPING RAIN WATER — O(n) time, O(1) space
// ─────────────────────────────────────────────────────────────────────────────
//   Two-pointer approach:
//     leftMax  = max height seen from left so far
//     rightMax = max height seen from right so far
//
//     At each step, process the side with the smaller max:
//       water trapped at position i = max(0, min(leftMax, rightMax) − height[i])
//
//   heights = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
//                 ■              ■
//             ■   ■ ■   ■   ■ ■ ■ ■   ■     trapped = 6 units
// ─────────────────────────────────────────────────────────────────────────────
int trapRainWater(const int height[], int n) {
    if (n < 3) return 0;                      // need at least 3 bars

    int lo = 0, hi = n - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;

    while (lo < hi) {
        if (height[lo] <= height[hi]) {
            if (height[lo] >= leftMax) leftMax = height[lo];
            else                       water += leftMax - height[lo];
            lo++;
        } else {
            if (height[hi] >= rightMax) rightMax = height[hi];
            else                        water += rightMax - height[hi];
            hi--;
        }
    }
    return water;
}

// ═════════════════════════════════════════════════════════════════════════════
// MAIN — Demonstrate All Classic Problems
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    cout << "============================================" << endl;
    cout << "   08 · CLASSIC ARRAY PROBLEMS" << endl;
    cout << "============================================" << endl;

    // ── 1. Kadane's Algorithm ────────────────────────────────────────────
    cout << "\n--- Kadane's Algorithm (Max Subarray Sum) ---" << endl;
    int k[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Array:  "; printArray(k, 9);
    cout << "Max subarray sum = " << kadane(k, 9) << endl;

    // ── 2. Dutch National Flag ───────────────────────────────────────────
    cout << "\n--- Dutch National Flag (Sort 0,1,2) ---" << endl;
    int dnf[] = {2, 0, 1, 2, 0, 1, 0, 2, 1};
    cout << "Before: "; printArray(dnf, 9);
    dutchNationalFlag(dnf, 9);
    cout << "After:  "; printArray(dnf, 9);

    // ── 3. Merge Two Sorted Arrays ───────────────────────────────────────
    cout << "\n--- Merge Two Sorted Arrays ---" << endl;
    int ma[] = {1, 3, 5, 7};
    int mb[] = {2, 4, 6, 8, 10};
    cout << "A: "; printArray(ma, 4);
    cout << "B: "; printArray(mb, 5);
    int merged[9]; int mSz;
    mergeSorted(ma, 4, mb, 5, merged, mSz);
    cout << "Merged: "; printArray(merged, mSz);

    // ── 4. Subarray with Given Sum ───────────────────────────────────────
    cout << "\n--- Subarray with Given Sum (33) ---" << endl;
    int sw[] = {1, 4, 20, 3, 10, 5};
    cout << "Array:  "; printArray(sw, 6);
    int s, e;
    if (subarrayWithSum(sw, 6, 33, s, e))
        cout << "Found! Indices " << s << " to " << e << endl;
    else
        cout << "Not found." << endl;

    // ── 5. Stock Buy & Sell ──────────────────────────────────────────────
    cout << "\n--- Best Time to Buy & Sell Stock ---" << endl;
    int prices[] = {7, 1, 5, 3, 6, 4};
    cout << "Prices: "; printArray(prices, 6);
    cout << "Max profit = " << maxStockProfit(prices, 6) << endl;

    // ── 6. Move Negatives ────────────────────────────────────────────────
    cout << "\n--- Move Negatives to One Side ---" << endl;
    int neg[] = {-1, 2, -3, 4, 5, -6, 7};
    cout << "Before: "; printArray(neg, 7);
    moveNegatives(neg, 7);
    cout << "After:  "; printArray(neg, 7);

    // ── 7. Trapping Rain Water ───────────────────────────────────────────
    cout << "\n--- Trapping Rain Water ---" << endl;
    int h[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Heights: "; printArray(h, 12);
    cout << "Water trapped = " << trapRainWater(h, 12) << " units" << endl;

    cout << "\n============================================" << endl;
    cout << "   Classic Problems Completed!" << endl;
    cout << "============================================" << endl;

    return 0;
}
