#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    Problem: 88. Merge Sorted Array
    Link: https://leetcode.com/problems/merge-sorted-array/

    Given two sorted arrays nums1 and nums2, with m and n elements
    respectively, merge nums2 into nums1 as one sorted array in-place.
    nums1 has length m+n (first m are real, last n are 0-padding).

    Example:
    Input:  nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
    Output: [1,2,2,3,5,6]
*/

// ---------------------------------------------------------------------------
// Approach 1: Merge + Sort (Brute Force) -> O((m+n) log(m+n)) time, O(1) extra
// space Idea: copy nums2 into the empty tail of nums1, then sort the whole
// thing.
//       Simple but ignores the fact both arrays are already sorted.
// ---------------------------------------------------------------------------
void mergeBrute(vector<int>& nums1, int m, vector<int>& nums2, int n) {
  for (int i = 0; i < n; i++) {
    nums1[m + i] = nums2[i];
  }
  sort(nums1.begin(), nums1.end());
}

// ---------------------------------------------------------------------------
// Approach 2: Two Pointer + Extra Array -> O(m+n) time, O(m+n) space
// Idea: merge nums1[0..m) and nums2[0..n) into a separate temp array
//       (classic merge-two-sorted-arrays), then copy back into nums1.
//       Correct and easy to reason about, but uses extra space unnecessarily.
// ---------------------------------------------------------------------------
void mergeExtraSpace(vector<int>& nums1, int m, vector<int>& nums2, int n) {
  vector<int> merged;
  merged.reserve(m + n);

  int i = 0, j = 0;

  while (i < m && j < n) {
    if (nums1[i] <= nums2[j])
      merged.push_back(nums1[i++]);
    else
      merged.push_back(nums2[j++]);
  }
  while (i < m) merged.push_back(nums1[i++]);
  while (j < n) merged.push_back(nums2[j++]);

  for (int k = 0; k < m + n; k++) {
    nums1[k] = merged[k];
  }
}

// ---------------------------------------------------------------------------
// Approach 3: Three Pointers from the Back (Optimal) -> O(m+n) time, O(1) space
// Idea: nums1 has empty slots at the END (index m to m+n-1), so instead of
//       merging from the front (which would overwrite unread values),
//       merge from the BACK — place the largest remaining element at the
//       last empty slot each time.
//
//       i = last real element of nums1 (m-1)
//       j = last element of nums2 (n-1)
//       k = last index of nums1 (m+n-1) -> where result gets placed
//
//       Whichever of nums1[i] / nums2[j] is bigger goes to nums1[k].
//       After i runs out, any remaining nums2 elements are copied directly
//       (remaining nums1 elements are already in correct position).
// ---------------------------------------------------------------------------
void mergeOptimal(vector<int>& nums1, int m, vector<int>& nums2, int n) {
  int i = m - 1;
  int j = n - 1;
  int k = m + n - 1;

  while (i >= 0 && j >= 0) {
    if (nums1[i] > nums2[j]) {
      nums1[k] = nums1[i];
      i--;
    } else {
      nums1[k] = nums2[j];
      j--;
    }
    k--;
  }

  // leftover nums2 elements (if any) still need to be placed
  while (j >= 0) {
    nums1[k] = nums2[j];
    j--;
    k--;
  }

  // leftover nums1 elements (if any) are already in correct position,
  // no copy needed
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<int> a1 = {1, 2, 3, 0, 0, 0}, b1 = {2, 5, 6};
  vector<int> a2 = {1, 2, 3, 0, 0, 0}, b2 = {2, 5, 6};
  vector<int> a3 = {1, 2, 3, 0, 0, 0}, b3 = {2, 5, 6};

  mergeBrute(a1, 3, b1, 3);
  mergeExtraSpace(a2, 3, b2, 3);
  mergeOptimal(a3, 3, b3, 3);

  auto printVec = [](const string& label, vector<int>& v) {
    cout << label << ": [";
    for (int i = 0; i < (int)v.size(); i++) {
      cout << v[i];
      if (i < (int)v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
  };

  printVec("Brute Force (merge+sort)", a1);
  printVec("Two Pointer (extra space)", a2);
  printVec("Three Pointer (optimal)", a3);

  return 0;
}