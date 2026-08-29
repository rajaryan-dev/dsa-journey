#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    Problem: 75. Sort Colors
    Link: https://leetcode.com/problems/sort-colors/

    Given an array nums with n objects colored red, white, or blue
    (represented by integers 0, 1, and 2), sort them in-place so that
    objects of the same color are adjacent, in the order 0, 1, 2.

    Must solve WITHOUT using a library sort function, in one pass,
    using only constant extra space.

    Example:
    Input:  nums = [2,0,2,1,1,0]
    Output: [0,0,1,1,2,2]
*/

// ---------------------------------------------------------------------------
// Approach 1: Counting Sort -> O(n) time, O(1) space (two passes)
//
// Beginner intuition: since there are only 3 possible values (0,1,2),
// just count how many of each you have, then overwrite the array —
// first fill in all the 0s, then all the 1s, then all the 2s.
// Simple to understand, but takes 2 passes over the array and doesn't
// satisfy the "one pass" constraint some interviewers ask for.
// ---------------------------------------------------------------------------
void sortColorsCounting(vector<int>& nums) {
  int count0 = 0, count1 = 0, count2 = 0;

  for (int num : nums) {
    if (num == 0)
      count0++;
    else if (num == 1)
      count1++;
    else
      count2++;
  }

  int idx = 0;
  for (int i = 0; i < count0; i++) nums[idx++] = 0;
  for (int i = 0; i < count1; i++) nums[idx++] = 1;
  for (int i = 0; i < count2; i++) nums[idx++] = 2;
}

// ---------------------------------------------------------------------------
// Approach 2: Dutch National Flag Algorithm (Optimal) -> O(n) time, O(1) space,
// ONE pass
//
// Beginner intuition: use THREE pointers to partition the array into
// three zones as we scan:
//
//   lo  -> boundary for 0s: everything BEFORE lo is guaranteed 0
//   hi  -> boundary for 2s: everything AFTER hi is guaranteed 2
//   mid -> the current element being examined (the "unsorted" zone
//          is always between lo and hi)
//
// At each step, look at nums[mid]:
//   - if nums[mid] == 0: it belongs in the 0-zone, so swap it with
//     nums[lo], then advance BOTH lo and mid (since the element that
//     came from lo is guaranteed to be either 0 or 1, safe to move on)
//   - if nums[mid] == 1: it's already in the right zone, just move
//     mid forward
//   - if nums[mid] == 2: it belongs in the 2-zone, so swap it with
//     nums[hi], then move hi backward. Do NOT advance mid here —
//     the element swapped in from hi is unexamined, so we must
//     check it next
//
// Loop continues while mid <= hi (once mid crosses hi, everything is
// partitioned into three zones: [0...lo-1]=0s, [lo...hi]=1s, [hi+1...n-1]=2s)
// ---------------------------------------------------------------------------
void sortColorsDNF(vector<int>& nums) {
  int lo = 0, mid = 0, hi = nums.size() - 1;

  while (mid <= hi) {
    if (nums[mid] == 0) {
      swap(nums[lo], nums[mid]);
      lo++;
      mid++;
    } else if (nums[mid] == 1) {
      mid++;
    } else {  // nums[mid] == 2
      swap(nums[mid], nums[hi]);
      hi--;
      // mid NOT incremented — need to re-check swapped-in value
    }
  }
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<vector<int>> testCases = {
      {2, 0, 2, 1, 1, 0},  // expected [0,0,1,1,2,2]
      {2, 0, 1},           // expected [0,1,2]
      {0}                  // expected [0]
  };

  auto printVec = [](const string& label, vector<int>& v) {
    cout << label << ": [";
    for (int i = 0; i < (int)v.size(); i++) {
      cout << v[i];
      if (i < (int)v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
  };

  for (auto& nums : testCases) {
    vector<int> n1 = nums, n2 = nums;

    sortColorsCounting(n1);
    sortColorsDNF(n2);

    printVec("Counting Sort", n1);
    printVec("Dutch Nat. Flag", n2);
    cout << "-----------------------------------" << endl;
  }

  return 0;
}