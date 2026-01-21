#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
------------------------------------------------------------
LeetCode: 42. Trapping Rain Water
Difficulty: Hard
Link: https://leetcode.com/problems/trapping-rain-water/

Approach:
- Prefix & Suffix Maximum (Left Max / Right Max)
- For each index i:
  water[i] = min(leftMax[i], rightMax[i]) - height[i]

Time Complexity:  O(n)
Space Complexity: O(n)
------------------------------------------------------------
*/

// Function to calculate trapped rain water
int trapRainWater(vector<int>& height) {
  int n = height.size();

  // Less than 3 bars cannot trap water
  if (n < 3) return 0;

  vector<int> lmax(n), rmax(n);

  // Build left maximum array
  lmax[0] = height[0];
  for (int i = 1; i < n; i++) {
    lmax[i] = max(lmax[i - 1], height[i]);
  }

  // Build right maximum array
  rmax[n - 1] = height[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    rmax[i] = max(rmax[i + 1], height[i]);
  }

  // Calculate trapped water
  int totalWater = 0;
  for (int i = 0; i < n; i++) {
    totalWater += min(lmax[i], rmax[i]) - height[i];
  }

  return totalWater;
}

int main() {
  // Example input (same as LeetCode example)
  vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

  cout << "Elevation Map: ";
  for (int h : height) cout << h << " ";
  cout << endl;

  cout << "Trapped Rain Water = " << trapRainWater(height) << endl;

  return 0;
}
