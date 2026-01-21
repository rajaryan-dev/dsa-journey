/*
---------------------------------------------------------
 LeetCode Question:
 2596. Check Knight Tour Configuration  (Medium)

 A knight starts at (0,0) and must visit each cell exactly
 once. grid[r][c] contains the order of visit (0-indexed).
 Return true if the configuration is valid, otherwise false.

 Link: https://leetcode.com/problems/check-knight-tour-configuration/
---------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Recursive function to validate knight moves
bool isValid(vector<vector<int>>& grid, int r, int c, int n, int expVal) {
  // Out of bounds OR cell doesn't match expected number
  if (r < 0 || c < 0 || r >= n || c >= n) return false;
  if (grid[r][c] != expVal) return false;

  // If last required value reached, tour is valid
  if (expVal == n * n - 1) return true;

  // Try all 8 possible knight moves
  bool m1 = isValid(grid, r - 2, c + 1, n, expVal + 1);
  bool m2 = isValid(grid, r - 1, c + 2, n, expVal + 1);
  bool m3 = isValid(grid, r + 1, c + 2, n, expVal + 1);
  bool m4 = isValid(grid, r + 2, c + 1, n, expVal + 1);
  bool m5 = isValid(grid, r + 2, c - 1, n, expVal + 1);
  bool m6 = isValid(grid, r + 1, c - 2, n, expVal + 1);
  bool m7 = isValid(grid, r - 1, c - 2, n, expVal + 1);
  bool m8 = isValid(grid, r - 2, c - 1, n, expVal + 1);

  return m1 || m2 || m3 || m4 || m5 || m6 || m7 || m8;
}

bool checkValidGrid(vector<vector<int>>& grid) {
  int n = grid.size();

  // Knight must start at top-left with value 0
  if (grid[0][0] != 0) return false;

  return isValid(grid, 0, 0, n, 0);
}

int main() {
  // Example predefined grid (valid knight tour)
  vector<vector<int>> grid = {{0, 11, 16, 5, 20},
                              {17, 4, 19, 10, 15},
                              {12, 1, 8, 21, 6},
                              {3, 18, 23, 14, 9},
                              {24, 13, 2, 7, 22}};

  cout << "Checking the following grid:\n\n";
  for (auto& row : grid) {
    for (auto& x : row) {
      cout << setw(3) << x << " ";
    }
    cout << endl;
  }

  bool result = checkValidGrid(grid);

  cout << "\nKnight Tour Configuration: ";
  if (result)
    cout << "VALID" << endl;
  else
    cout << "INVALID" << endl;

  return 0;
}
