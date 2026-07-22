#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    Problem: 169. Majority Element
    Link: https://leetcode.com/problems/majority-element/

    Given an array nums of size n, return the majority element.
    The majority element is the element that appears MORE THAN n/2 times.

    Assume the majority element always exists in the array (guaranteed
    by problem constraints).

    Example:
    Input:  nums = [2,2,1,1,1,2,2]
    Output: 2
*/

// ---------------------------------------------------------------------------
// Approach 1: Brute Force -> O(n^2) time, O(1) space
// Idea: for each element, count its frequency by scanning the whole array.
//       If freq > n/2, that's the majority element.
// ---------------------------------------------------------------------------
int majorityElementBrute(vector<int>& nums) {
  int n = nums.size();

  for (int val : nums) {
    int freq = 0;
    for (int el : nums) {
      if (el == val) freq++;
    }
    if (freq > n / 2) return val;
  }

  return -1;  // unreachable if majority guaranteed
}

// ---------------------------------------------------------------------------
// Approach 2: Sorting -> O(n log n) time, O(1) space (ignoring sort space)
// Idea: if an element appears more than n/2 times, after sorting it MUST
//       occupy the middle index (n/2), since it's the most frequent.
// ---------------------------------------------------------------------------
int majorityElementSort(vector<int>& nums) {
  sort(nums.begin(), nums.end());
  return nums[nums.size() / 2];
}

// ---------------------------------------------------------------------------
// Approach 3: HashMap -> O(n) time, O(n) space
// Idea: count frequency of each element, return the one exceeding n/2.
// ---------------------------------------------------------------------------
int majorityElementHashMap(vector<int>& nums) {
  int n = nums.size();
  unordered_map<int, int> freq;

  for (int num : nums) {
    freq[num]++;
    if (freq[num] > n / 2) return num;
  }

  return -1;  // unreachable if majority guaranteed
}

// ---------------------------------------------------------------------------
// Approach 4: Boyer-Moore Voting Algorithm (Optimal) -> O(n) time, O(1) space
// Idea: maintain a candidate (ans) and a counter (freq).
//       - If freq == 0, pick current element as new candidate.
//       - If current element == candidate, freq++.
//       - Else, freq--.
//       Intuition: majority element "cancels out" every non-majority
//       element it's paired against, so it survives as the final candidate.
//       NOTE: this ONLY works because majority is guaranteed to exist here.
// ---------------------------------------------------------------------------
int majorityElementBoyerMoore(vector<int>& nums) {
  int freq = 0, ans = 0;

  for (int i = 0; i < (int)nums.size(); i++) {
    if (freq == 0) {
      ans = nums[i];
    }
    if (ans == nums[i]) {
      freq++;
    } else {
      freq--;
    }
  }

  return ans;
}

// ---------------------------------------------------------------------------
// VARIANT NOTE: What if majority element is NOT guaranteed to exist?
// (e.g. LeetCode 229 - Majority Element II style constraint, or a
//  modified version of this same problem)
//
// In that case, Boyer-Moore's candidate alone is NOT enough — the
// candidate it finds may not actually be a majority element.
// You MUST add a verification pass after finding the candidate:
//
//     int count = 0;
//     for (int val : nums) {
//         if (val == ans) count++;
//     }
//     if (count > n / 2) return ans;
//     else return -1; // no majority element exists
//
// This verification step is O(n) extra, but keeps total complexity O(n).
// Always add this check if the problem does NOT explicitly guarantee
// a majority element exists.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<vector<int>> testCases = {
      {2, 2, 1, 1, 1, 2, 2},  // expected 2
      {3, 2, 3},              // expected 3
      {1}                     // expected 1
  };

  for (auto& nums : testCases) {
    vector<int> c1 = nums, c2 = nums, c3 = nums, c4 = nums;

    cout << "Brute Force   -> Majority Element: " << majorityElementBrute(c1)
         << endl;
    cout << "Sort          -> Majority Element: " << majorityElementSort(c2)
         << endl;
    cout << "HashMap       -> Majority Element: " << majorityElementHashMap(c3)
         << endl;
    cout << "Boyer-Moore   -> Majority Element: "
         << majorityElementBoyerMoore(c4) << endl;
    cout << "-----------------------------------" << endl;
  }

  return 0;
}