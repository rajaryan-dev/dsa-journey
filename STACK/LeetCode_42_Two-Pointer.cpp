#include <iostream>
#include <vector>
using namespace std;

/*
------------------------------------------------------------
LeetCode: 42. Trapping Rain Water
Difficulty: Hard
Link: https://leetcode.com/problems/trapping-rain-water/

Approach:
- Two Pointer Technique (Optimized)
- Use left and right pointers
- Maintain leftMax and rightMax

Time Complexity:  O(n)
Space Complexity: O(1)
------------------------------------------------------------
*/

int trapRainWater(vector<int>& height) {
  int n = height.size();
  if (n < 3) return 0;

  int left = 0;
  int right = n - 1;

  int leftMax = 0;
  int rightMax = 0;

  int totalWater = 0;

  // Process until pointers meet
  while (left < right) {
    // If left bar is smaller, process left side
    if (height[left] <= height[right]) {
      // Update leftMax or collect water
      if (height[left] >= leftMax) {
        leftMax = height[left];
      } else {
        totalWater += leftMax - height[left];
      }
      left++;

    }
    // Otherwise process right side
    else {
      // Update rightMax or collect water
      if (height[right] >= rightMax) {
        rightMax = height[right];
      } else {
        totalWater += rightMax - height[right];
      }
      right--;
    }
  }

  return totalWater;
}

int main() {
  // Example from LeetCode
  vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

  cout << "Elevation Map: ";
  for (int h : height) cout << h << " ";
  cout << endl;

  cout << "Trapped Rain Water = " << trapRainWater(height) << endl;

  return 0;
}
