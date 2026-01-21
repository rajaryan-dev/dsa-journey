#include <bits/stdc++.h>
using namespace std;

/*
 LeetCode 84. Largest Rectangle in Histogram (HARD)

 Given an array heights[] where heights[i] represents the height
 of a histogram bar (width = 1), return the area of the largest rectangle.
*/

class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();

    vector<int> left(n), right(n);  // NSL & NSR arrays
    stack<int> st;                  // stores indices

    // -------------------------------
    // Nearest Smaller to Right (NSR)
    // -------------------------------
    for (int i = n - 1; i >= 0; i--) {
      // Remove all bars taller or equal to current
      while (!st.empty() && heights[st.top()] >= heights[i]) {
        st.pop();
      }

      // If none smaller on right, boundary = n
      right[i] = st.empty() ? n : st.top();

      st.push(i);
    }

    // Clear stack for reuse
    while (!st.empty()) st.pop();

    // -------------------------------
    // Nearest Smaller to Left (NSL)
    // -------------------------------
    for (int i = 0; i < n; i++) {
      // Remove all bars taller or equal to current
      while (!st.empty() && heights[st.top()] >= heights[i]) {
        st.pop();
      }

      // If none smaller on left, boundary = -1
      left[i] = st.empty() ? -1 : st.top();

      st.push(i);
    }

    // -------------------------------
    // Calculate Maximum Area
    // -------------------------------
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
      int width = right[i] - left[i] - 1;  // rectangle width
      int area = heights[i] * width;       // area using heights[i]
      maxArea = max(maxArea, area);
    }

    return maxArea;
  }
};

int main() {
  Solution sol;

  // Example from LeetCode
  vector<int> heights = {2, 1, 5, 6, 2, 3};

  cout << "Histogram heights: ";
  for (int h : heights) cout << h << " ";
  cout << endl;

  int result = sol.largestRectangleArea(heights);

  cout << "Largest Rectangle Area = " << result << endl;

  return 0;
}
