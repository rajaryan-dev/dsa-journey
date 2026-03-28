// Fibonacci using Top-Down DP (Memoization), Bottom-Up DP (Tabulation) & Space Optimization

#include <iostream>
#include <vector>
using namespace std;

// Recursive function with memoization
// Time: O(n) | Space: O(n)
int fib(int n, vector<int>& dp) {
  // Base case: fib(0) = 0, fib(1) = 1
  if (n <= 1) return n;
  if (dp[n] != -1) return dp[n];

  // Store result in dp array to avoid recomputation
  dp[n] = fib(n - 1, dp) + fib(n - 2, dp);
  return dp[n];
}

// Bottom-Up DP (Tabulation) - Iterative approach
// Time: O(n) | Space: O(n)
int fibTabulation(int n) {
  // Create dp table and set base cases
  vector<int> dp(n + 1);
  dp[0] = 0;
  dp[1] = 1;

  // Fill table from 2 to n using previously computed values
  for (int i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n];
}

// Space Optimized - Only keep track of previous two values
// Time: O(n) | Space: O(1)
int fibOptimized(int n) {
  if (n <= 1) return n;

  int prev2 = 0; // fib(i-2)
  int prev1 = 1; // fib(i-1)

  for (int i = 2; i <= n; i++) {
    int curr = prev1 + prev2;
    prev2 = prev1;
    prev1 = curr;
  }

  return prev1;
}

int main() {
  int n = 6;

  // Top-Down approach
  vector<int> dp(n + 1, -1);
  cout << "Top-Down : " << fib(n, dp) << endl;    // Output: 8

  // Bottom-Up approach
  cout << "Bottom-Up: " << fibTabulation(n) << endl; // Output: 8

  // Space Optimized approach
  cout << "Optimized: " << fibOptimized(n) << endl;   // Output: 8

  return 0;
}