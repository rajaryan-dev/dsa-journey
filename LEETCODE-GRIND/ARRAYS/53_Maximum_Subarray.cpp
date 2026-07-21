#include <climits>
#include <iostream>
#include <vector>
using namespace std;

/*
    Problem: 53. Maximum Subarray
    Link: https://leetcode.com/problems/maximum-subarray/

    Given an integer array nums, find the subarray with the largest sum,
    and return its sum.

    Example:
    Input:  nums = [-2,1,-3,4,-1,2,1,-5,4]
    Output: 6
    Explanation: subarray [4,-1,2,1] has the largest sum = 6.
*/

// ---------------------------------------------------------------------------
// Approach 1: Brute Force -> O(n^2) time, O(1) space
// Idea: try every possible (start, end) pair, sum the subarray, track max.
// ---------------------------------------------------------------------------
int maxSubArrayBrute(vector<int>& nums) {
  int n = nums.size();
  int maxSum = INT_MIN;

  for (int st = 0; st < n; st++) {
    int currSum = 0;
    for (int end = st; end < n; end++) {
      currSum += nums[end];
      maxSum = max(maxSum, currSum);
    }
  }

  return maxSum;
}

// ---------------------------------------------------------------------------
// Approach 2: Kadane's Algorithm -> O(n) time, O(1) space
// Idea: at each index, decide -> extend the running subarray OR drop it
//       and start fresh from the current element.
//       currSum = max(nums[i], currSum + nums[i])
//       If currSum ever goes negative, it can only hurt future sums,
//       so reset it to 0.
// ---------------------------------------------------------------------------
int maxSubArrayKadane(vector<int>& nums) {
  int n = nums.size();
  int maxSum = INT_MIN;
  int currSum = 0;

  for (int i = 0; i < n; i++) {
    currSum += nums[i];
    maxSum = max(maxSum, currSum);

    if (currSum < 0) {
      currSum = 0;
    }
  }

  return maxSum;
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<vector<int>> testCases = {
      {-2, 1, -3, 4, -1, 2, 1, -5, 4},  // expected 6
      {1},                              // expected 1
      {5, 4, -1, 7, 8}                  // expected 23
  };

  for (auto& nums : testCases) {
    vector<int> numsCopy1 = nums;  // brute force takes its own copy
    vector<int> numsCopy2 = nums;  // kadane takes its own copy

    int bruteResult = maxSubArrayBrute(numsCopy1);
    int kadaneResult = maxSubArrayKadane(numsCopy2);

    cout << "Brute Force  -> Max Subarray Sum: " << bruteResult << endl;
    cout << "Kadane's Algo -> Max Subarray Sum: " << kadaneResult << endl;
    cout << "-----------------------------------" << endl;
  }

  return 0;
}