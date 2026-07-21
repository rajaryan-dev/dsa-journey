#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    Problem: 136. Single Number
    Link: https://leetcode.com/problems/single-number/

    Given a non-empty array of integers nums, every element appears twice
    except for one. Find that single one.

    Must implement a solution with linear runtime complexity and use
    only constant extra space (XOR approach satisfies this; others don't).

    Example:
    Input:  nums = [4,1,2,1,2]
    Output: 4
*/

// ---------------------------------------------------------------------------
// Approach 1: HashMap -> O(n) time, O(n) space
// Idea: count frequency of each number, return the one with count = 1.
// ---------------------------------------------------------------------------
int singleNumberHashMap(vector<int>& nums) {
  unordered_map<int, int> freq;

  for (int num : nums) {
    freq[num]++;
  }

  for (auto& entry : freq) {
    if (entry.second == 1) {
      return entry.first;
    }
  }

  return -1;  // unreachable per constraints
}

// ---------------------------------------------------------------------------
// Approach 2: Sorting -> O(n log n) time, O(1) space (ignoring sort space)
// Idea: after sorting, duplicates sit next to each other in pairs.
//       Walk in steps of 2, compare nums[i] with nums[i+1].
//       If they don't match, nums[i] is the single one.
//       If loop finishes without returning, the last element is the answer.
// ---------------------------------------------------------------------------
int singleNumberSort(vector<int>& nums) {
  sort(nums.begin(), nums.end());

  int n = nums.size();
  int i = 0;

  while (i < n - 1) {
    if (nums[i] == nums[i + 1]) {
      i += 2;
    } else {
      return nums[i];
    }
  }

  return nums[i];
}

// ---------------------------------------------------------------------------
// Approach 3: XOR (Optimal) -> O(n) time, O(1) space
// Idea: XOR of a number with itself is 0, XOR with 0 is the number itself.
//       a ^ a = 0
//       a ^ 0 = a
//       XOR-ing all elements cancels out every pair, leaving only the
//       single number that appears once.
//
//       Example: [4,1,2,1,2] -> 4^1^2^1^2 = 4^(1^1)^(2^2) = 4^0^0 = 4
// ---------------------------------------------------------------------------
int singleNumberXOR(vector<int>& nums) {
  int result = 0;

  for (int num : nums) {
    result ^= num;
  }

  return result;
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<vector<int>> testCases = {
      {2, 2, 1},        // expected 1
      {4, 1, 2, 1, 2},  // expected 4
      {1}               // expected 1
  };

  for (auto& nums : testCases) {
    vector<int> copy1 = nums;  // hashmap
    vector<int> copy2 = nums;  // sort (will get mutated by sort)
    vector<int> copy3 = nums;  // xor

    cout << "HashMap -> Single Number: " << singleNumberHashMap(copy1) << endl;
    cout << "Sort    -> Single Number: " << singleNumberSort(copy2) << endl;
    cout << "XOR     -> Single Number: " << singleNumberXOR(copy3) << endl;
    cout << "-----------------------------------" << endl;
  }

  return 0;
}