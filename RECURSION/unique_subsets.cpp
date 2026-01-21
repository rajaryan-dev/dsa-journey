/*
🔵 LeetCode Problem 90: Subsets II

❗ Goal:
Given an integer array nums that may contain duplicates, return ALL possible
subsets (the power set). The result must NOT contain duplicate subsets.

Example:
Input:  [1, 2, 2]
Output: [[], [1], [2], [1,2], [2,2], [1,2,2]]
*/

#include <bits/stdc++.h>

#include <vector>

using namespace std;

class Solution {
 public:
  /**
   * Recursive function to generate unique subsets through backtracking.
   *
   * @param nums          - sorted input array
   * @param currentSubset - subset currently being built
   * @param index         - current index in nums
   * @param result        - stores all unique subsets
   */
  void generateSubsets(vector<int>& nums, vector<int>& currentSubset, int index,
                       vector<vector<int>>& result) {
    // Base case: reached end of nums → store the built subset
    if (index == nums.size()) {
      result.push_back(currentSubset);
      return;
    }

    /* ────────────────────────────────────────────
       OPTION 1: INCLUDE nums[index] in subset
    ──────────────────────────────────────────── */
    currentSubset.push_back(nums[index]);
    generateSubsets(nums, currentSubset, index + 1, result);

    // Backtrack → remove last element before exploring exclusion
    currentSubset.pop_back();

    /* ────────────────────────────────────────────
       OPTION 2: EXCLUDE nums[index]
       Skip all FOLLOWING identical values to avoid duplicate subsets
    ──────────────────────────────────────────── */
    int nextIndex = index + 1;
    while (nextIndex < nums.size() && nums[nextIndex] == nums[index])
      nextIndex++;

    generateSubsets(nums, currentSubset, nextIndex, result);
  }

  /**
   * Returns list of all UNIQUE subsets.
   */
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());  // Sorting required to detect duplicates
    vector<vector<int>> result;
    vector<int> currentSubset;

    generateSubsets(nums, currentSubset, 0, result);
    return result;
  }
};

/* -------------------------------------------------------
   🧪 TESTING in main() - Works in VS Code and C++ Compilers
-------------------------------------------------------- */
int main() {
  Solution obj;

  vector<int> nums = {1, 2, 2};  // ⬅ Change test case here

  vector<vector<int>> ans = obj.subsetsWithDup(nums);

  cout << "Unique subsets:" << endl;
  for (const auto& subset : ans) {
    cout << "[ ";
    for (int num : subset) cout << num << " ";
    cout << "]" << endl;
  }

  return 0;
}
