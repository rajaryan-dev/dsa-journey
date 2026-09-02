/*
 * ============================================================
 *  BINARY SEARCH — Rotated Array & Peak Element
 * ============================================================
 *  Topics:
 *   1. Search in Rotated Sorted Array       (LC 33)
 *   2. Search in Rotated Sorted Array II    (LC 81, with dups)
 *   3. Find Minimum in Rotated Sorted Array (LC 153)
 *   4. Find Peak Element                    (LC 162)
 *   5. Kth Element of Two Sorted Arrays
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  1. Search in Rotated Sorted Array (no duplicates) — LC 33
//  Key: one of the two halves is always sorted.
// ─────────────────────────────────────────────────────────────
int searchRotated(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;

        // Left half is sorted
        if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid])
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        // Right half is sorted
        else {
            if (nums[mid] < target && target <= nums[hi])
                lo = mid + 1;
            else
                hi = mid - 1;
        }
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────
//  2. Search in Rotated Sorted Array II (with duplicates) — LC 81
//  Trick: when nums[lo]==nums[mid]==nums[hi], shrink both ends
// ─────────────────────────────────────────────────────────────
bool searchRotatedII(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return true;

        // Can't determine sorted half
        if (nums[lo] == nums[mid] && nums[mid] == nums[hi]) {
            lo++; hi--;
        }
        else if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid])
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        else {
            if (nums[mid] < target && target <= nums[hi])
                lo = mid + 1;
            else
                hi = mid - 1;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────
//  3. Find Minimum in Rotated Sorted Array — LC 153
//  Minimum is always in the unsorted (rotated) half.
// ─────────────────────────────────────────────────────────────
int findMin(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;  // min in right half
        else                      hi = mid;        // min in left half (or mid itself)
    }
    return nums[lo];
}

// ─────────────────────────────────────────────────────────────
//  4. Find Peak Element — LC 162
//  A peak is where nums[i] > nums[i-1] && nums[i] > nums[i+1]
//  Always move towards the rising side.
// ─────────────────────────────────────────────────────────────
int findPeakElement(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[mid + 1]) hi = mid;      // peak is on left (or mid)
        else                           lo = mid + 1;   // peak is on right
    }
    return lo;
}

// ─────────────────────────────────────────────────────────────
//  5. Kth Smallest Element in Two Sorted Arrays — LC 4 variant
//  O(log(min(m,n))) — binary search on smaller array partition
// ─────────────────────────────────────────────────────────────
double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
    if (A.size() > B.size()) return findMedianSortedArrays(B, A);
    int m = A.size(), n = B.size();
    int lo = 0, hi = m;
    while (lo <= hi) {
        int px = lo + (hi - lo) / 2;
        int py = (m + n + 1) / 2 - px;

        int maxLeftA  = (px == 0) ? INT_MIN : A[px - 1];
        int minRightA = (px == m) ? INT_MAX : A[px];
        int maxLeftB  = (py == 0) ? INT_MIN : B[py - 1];
        int minRightB = (py == n) ? INT_MAX : B[py];

        if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
            if ((m + n) % 2 == 0)
                return (max(maxLeftA, maxLeftB) + min(minRightA, minRightB)) / 2.0;
            else
                return max(maxLeftA, maxLeftB);
        }
        else if (maxLeftA > minRightB) hi = px - 1;
        else                           lo = px + 1;
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Binary Search: Rotated Array & Peak =====\n\n";

    // 1. Rotated search
    vector<int> r1 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Search 0 in {4,5,6,7,0,1,2}: index = "
         << searchRotated(r1, 0) << "\n"; // 4
    cout << "Search 3 in {4,5,6,7,0,1,2}: index = "
         << searchRotated(r1, 3) << "\n"; // -1

    // 2. With duplicates
    vector<int> r2 = {2, 5, 6, 0, 0, 1, 2};
    cout << "\nSearch 0 in {2,5,6,0,0,1,2} (dups): "
         << (searchRotatedII(r2, 0) ? "found" : "not found") << "\n"; // found
    cout << "Search 3 in {2,5,6,0,0,1,2} (dups): "
         << (searchRotatedII(r2, 3) ? "found" : "not found") << "\n"; // not found

    // 3. Find min
    vector<int> r3 = {3, 4, 5, 1, 2};
    cout << "\nMin of {3,4,5,1,2}: " << findMin(r3) << "\n"; // 1

    // 4. Find peak
    vector<int> r4 = {1, 2, 3, 1};
    cout << "\nPeak index in {1,2,3,1}: " << findPeakElement(r4)
         << " (value=" << r4[findPeakElement(r4)] << ")\n"; // index 2, value 3

    // 5. Median
    vector<int> A = {1, 3}, B = {2};
    cout << "\nMedian of {1,3} and {2}: "
         << findMedianSortedArrays(A, B) << "\n"; // 2.0
    vector<int> C = {1, 2}, D = {3, 4};
    cout << "Median of {1,2} and {3,4}: "
         << findMedianSortedArrays(C, D) << "\n"; // 2.5

    return 0;
}
