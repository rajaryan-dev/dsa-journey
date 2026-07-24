#include <iostream>
#include <vector>
using namespace std;

/*
    Problem: 2965. Find Missing and Repeated Values
    Link: https://leetcode.com/problems/find-missing-and-repeated-values/

    Given a 0-indexed n x n grid with values in range [1, n^2], every
    integer appears exactly once except 'a' (appears twice) and 'b'
    (missing). Return [a, b].

    Example:
    Input:  grid = [[1,3],[2,2]]
    Output: [2,4]
    Explanation: 2 is repeated, 4 is missing.
*/

// ---------------------------------------------------------------------------
// Approach 1: Frequency Array -> O(n^2) time, O(n^2) space
// Idea: flatten the grid conceptually, count occurrence of every number
//       from 1 to n*n. The number with freq=2 is repeated,
//       the number with freq=0 is missing.
// ---------------------------------------------------------------------------
vector<int> findMissingAndRepeatedFreq(vector<vector<int>>& grid) {
  int n = grid.size();
  int total = n * n;

  vector<int> freq(total + 1, 0);

  for (auto& row : grid) {
    for (int num : row) {
      freq[num]++;
    }
  }

  int repeated = -1, missing = -1;

  for (int i = 1; i <= total; i++) {
    if (freq[i] == 2)
      repeated = i;
    else if (freq[i] == 0)
      missing = i;
  }

  return {repeated, missing};
}

// ---------------------------------------------------------------------------
// Approach 2: Math (Sum + Sum of Squares) -> O(n^2) time, O(1) space
// Idea: let 'a' = repeated, 'b' = missing.
//       actualSum - expectedSum = a - b               ... (1)
//       actualSumSq - expectedSumSq = a^2 - b^2 = (a-b)(a+b)  ... (2)
//       From (1): a - b = diff1
//       From (2)/(1): a + b = diff2 / diff1
//       Solve the two linear equations for a and b.
//
//       expectedSum   = n*(n+1)/2   where n here = total (n*n original grid)
//       expectedSumSq = n*(n+1)*(2n+1)/6
//
//       Avoids extra array space, but risk of overflow with large n*n,
//       so use long long for sums.
// ---------------------------------------------------------------------------
vector<int> findMissingAndRepeatedMath(vector<vector<int>>& grid) {
  int n = grid.size();
  long long total = (long long)n * n;

  long long actualSum = 0, actualSumSq = 0;

  for (auto& row : grid) {
    for (int num : row) {
      actualSum += num;
      actualSumSq += (long long)num * num;
    }
  }

  long long expectedSum = total * (total + 1) / 2;
  long long expectedSumSq = total * (total + 1) * (2 * total + 1) / 6;

  long long diff1 = actualSum - expectedSum;                // a - b
  long long diff2 = (actualSumSq - expectedSumSq) / diff1;  // a + b

  long long a = (diff1 + diff2) / 2;  // repeated
  long long b = diff2 - a;            // missing

  return {(int)a, (int)b};
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<vector<vector<int>>> testCases = {
      {{1, 3}, {2, 2}},                  // expected [2,4]
      {{9, 1, 7}, {8, 9, 2}, {3, 4, 6}}  // expected [9,5]
  };

  for (auto& grid : testCases) {
    vector<vector<int>> g1 = grid, g2 = grid;

    vector<int> res1 = findMissingAndRepeatedFreq(g1);
    vector<int> res2 = findMissingAndRepeatedMath(g2);

    cout << "Frequency Array -> [repeated, missing]: [" << res1[0] << ", "
         << res1[1] << "]" << endl;
    cout << "Math Approach   -> [repeated, missing]: [" << res2[0] << ", "
         << res2[1] << "]" << endl;
    cout << "-----------------------------------" << endl;
  }

  return 0;
}