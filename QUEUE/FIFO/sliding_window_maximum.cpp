// sliding_window_maximum.cpp
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

/*
LeetCode 239. Sliding Window Maximum (Hard)

Approach:
- Use a monotonic deque to keep indices of useful elements
- Front of deque always stores index of maximum element for current window
*/

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // stores indices
    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
      // Remove indices out of current window
      if (!dq.empty() && dq.front() == i - k) {
        dq.pop_front();
      }

      // Remove smaller elements from the back
      while (!dq.empty() && nums[dq.back()] < nums[i]) {
        dq.pop_back();
      }

      // Add current index
      dq.push_back(i);

      // Store result once window size reaches k
      if (i >= k - 1) {
        result.push_back(nums[dq.front()]);
      }
    }

    return result;
  }
};

int main() {
  // Example (hardcoded – no user input)
  vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
  int k = 3;

  Solution sol;
  vector<int> ans = sol.maxSlidingWindow(nums, k);

  cout << "Sliding Window Maximums: ";
  for (int val : ans) {
    cout << val << " ";
  }
  cout << endl;

  return 0;
}
