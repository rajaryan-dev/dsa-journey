#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    Problem: 11. Container With Most Water
    Link: https://leetcode.com/problems/container-with-most-water/

    Given n non-negative integers height[i], each representing a vertical
    line at position i, find two lines that together with the x-axis
    form a container that holds the most water.

    Return the maximum amount of water a container can store.
    (Container area = min(height[l], height[r]) * (r - l))

    Example:
    Input:  height = [1,8,6,2,5,4,8,3,7]
    Output: 49
    Explanation: lines at index 1 (height 8) and index 8 (height 7)
                 form the max area = min(8,7) * (8-1) = 7*7 = 49
*/

// ---------------------------------------------------------------------------
// Approach 1: Brute Force -> O(n^2) time, O(1) space
// Idea: try every pair (i, j), compute area, track max.
//       area = min(height[i], height[j]) * (j - i)
// ---------------------------------------------------------------------------
int maxAreaBrute(vector<int>& height) {
  int n = height.size();
  int maxArea = 0;

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      int area = min(height[i], height[j]) * (j - i);
      maxArea = max(maxArea, area);
    }
  }

  return maxArea;
}

// ---------------------------------------------------------------------------
// Approach 2: Two Pointer (Optimal) -> O(n) time, O(1) space
// Idea: start with widest container (l=0, r=n-1). Width can only shrink
//       as pointers move inward, so to have any chance of a bigger area,
//       the NEXT container must have a taller limiting height.
//
//       At each step, move the pointer with the SMALLER height inward —
//       moving the taller one can never improve the area (width shrinks,
//       and the limiting height stays same or gets worse), but moving the
//       shorter one might find a taller line that increases the area.
//
//       Track max area at every step before moving.
// ---------------------------------------------------------------------------
int maxAreaOptimal(vector<int>& height) {
  int l = 0, r = height.size() - 1;
  int maxArea = 0;

  while (l < r) {
    int area = min(height[l], height[r]) * (r - l);
    maxArea = max(maxArea, area);

    if (height[l] < height[r]) {
      l++;
    } else {
      r--;
    }
  }

  return maxArea;
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<vector<int>> testCases = {
      {1, 8, 6, 2, 5, 4, 8, 3, 7},  // expected 49
      {1, 1},                       // expected 1
      {4, 3, 2, 1, 4}               // expected 16
  };

  for (auto& height : testCases) {
    vector<int> h1 = height, h2 = height;

    cout << "Brute Force   -> Max Area: " << maxAreaBrute(h1) << endl;
    cout << "Two Pointer   -> Max Area: " << maxAreaOptimal(h2) << endl;
    cout << "-----------------------------------" << endl;
  }

  return 0;
}