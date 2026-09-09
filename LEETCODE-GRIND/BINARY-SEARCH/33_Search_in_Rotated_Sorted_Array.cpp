#include <iostream>
#include <vector>
using namespace std;

/*
    Problem: 33. Search in Rotated Sorted Array
    Link: https://leetcode.com/problems/search-in-rotated-sorted-array/

    There is an integer array nums sorted in ascending order (with
    distinct values), but it has been rotated at an unknown pivot.
    Given the array after rotation and a target value, return its
    index if found, else -1.

    Must run in O(log n) time.

    Example:
    Input:  nums = [4,5,6,7,0,1,2], target = 0
    Output: 4

    Input:  nums = [4,5,6,7,0,1,2], target = 3
    Output: -1
*/

// ---------------------------------------------------------------------------
// Approach 1: Brute Force (Linear Scan) -> O(n) time, O(1) space
//
// Beginner intuition: just check every element one by one until you
// find the target. Correct but ignores the fact that the array IS
// still "sorted" in two halves — doesn't meet the O(log n) requirement.
// ---------------------------------------------------------------------------
int searchBrute(vector<int>& nums, int target) {
  for (int i = 0; i < (int)nums.size(); i++) {
    if (nums[i] == target) return i;
  }
  return -1;
}

// ---------------------------------------------------------------------------
// Approach 2: Modified Binary Search (Optimal) -> O(log n) time, O(1) space
//
// Beginner intuition: even though the array is rotated, at ANY point
// (lo, mid, hi), at least ONE half (left of mid, or right of mid) is
// still perfectly sorted. The trick is figuring out WHICH half is
// sorted, then checking if the target lies inside that sorted half.
//
// Step by step at each iteration:
//   1. Find mid = (lo + hi) / 2. If nums[mid] == target, done.
//   2. Check if the LEFT half (lo to mid) is sorted:
//        condition: nums[lo] <= nums[mid]
//      - If left half is sorted:
//          - if target lies within [nums[lo], nums[mid]) range,
//            search LEFT (hi = mid - 1)
//          - else search RIGHT (lo = mid + 1)
//   3. Otherwise, the RIGHT half (mid to hi) must be sorted instead:
//      - if target lies within (nums[mid], nums[hi]] range,
//        search RIGHT (lo = mid + 1)
//      - else search LEFT (hi = mid - 1)
//
// This way, every step eliminates half the array, just like normal
// binary search — just with an extra check to figure out which half
// is safe to reason about.
// ---------------------------------------------------------------------------
int searchOptimal(vector<int>& nums, int target) {
  int lo = 0, hi = nums.size() - 1;

  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;

    if (nums[mid] == target) return mid;

    // Left half [lo..mid] is sorted
    if (nums[lo] <= nums[mid]) {
      if (nums[lo] <= target && target < nums[mid]) {
        hi = mid - 1;  // target is inside the sorted left half
      } else {
        lo = mid + 1;  // target must be in the right half
      }
    }
    // Right half [mid..hi] is sorted
    else {
      if (nums[mid] < target && target <= nums[hi]) {
        lo = mid + 1;  // target is inside the sorted right half
      } else {
        hi = mid - 1;  // target must be in the left half
      }
    }
  }

  return -1;  // target not found
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<pair<vector<int>, int>> testCases = {
      {{4, 5, 6, 7, 0, 1, 2}, 0},  // expected 4
      {{4, 5, 6, 7, 0, 1, 2}, 3},  // expected -1
      {{1}, 0}                     // expected -1
  };

  for (auto& tc : testCases) {
    vector<int> nums = tc.first;
    int target = tc.second;

    cout << "Brute Force -> Index: " << searchBrute(nums, target) << endl;
    cout << "Optimal     -> Index: " << searchOptimal(nums, target) << endl;
    cout << "-----------------------------------" << endl;
  }

  return 0;
}