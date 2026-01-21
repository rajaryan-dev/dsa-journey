#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------
LeetCode Question:
503. Next Greater Element II

Difficulty: Medium
Topics: Stack, Monotonic Stack, Array

Problem Statement (Short):
Given a circular integer array nums, return the next
greater number for every element. If no greater
element exists, return -1.

Approach:
- Use a monotonic decreasing stack
- Traverse the array twice to simulate circular behavior

Time Complexity: O(n)
Space Complexity: O(n)
------------------------------------------------------
*/

// Function implementing LeetCode 503
vector<int> nextGreaterElements(vector<int>& nums) {
  int n = nums.size();

  // Result array initialized with -1
  vector<int> ans(n, -1);

  // Stack to store indices (monotonic decreasing stack)
  stack<int> st;

  // Traverse from right to left twice (circular simulation)
  for (int i = 2 * n - 1; i >= 0; i--) {
    int idx = i % n;  // circular index

    // Remove elements smaller or equal to current element
    while (!st.empty() && nums[st.top()] <= nums[idx]) {
      st.pop();
    }

    // Top of stack is the next greater element
    if (!st.empty()) {
      ans[idx] = nums[st.top()];
    }

    // Push current index to stack
    st.push(idx);
  }

  return ans;
}

// ------------------------------------------------------
// main() - VS Code Execution
// ------------------------------------------------------
int main() {
  // Sample input (hardcoded for testing)
  vector<int> nums = {1, 2, 1};

  // Call function
  vector<int> result = nextGreaterElements(nums);

  // Print input array
  cout << "Input Array: ";
  for (int x : nums) {
    cout << x << " ";
  }
  cout << endl;

  // Print result array
  cout << "Next Greater Elements (Circular): ";
  for (int x : result) {
    cout << x << " ";
  }
  cout << endl;

    return 0;
}
