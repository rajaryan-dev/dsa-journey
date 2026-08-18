#include <iostream>
using namespace std;

/*
    Problem: 50. Pow(x, n)
    Link: https://leetcode.com/problems/powx-n/

    Implement pow(x, n), which calculates x raised to the power n
    (i.e., x^n).

    Constraints include negative n (x^-n = 1 / x^n) and n can be as
    low as INT_MIN, so int overflow on negation must be handled
    (use long long for n).

    Example:
    Input:  x = 2.00000, n = 10
    Output: 1024.00000

    Input:  x = 2.00000, n = -2
    Output: 0.25000
    Explanation: 2^-2 = 1/2^2 = 1/4 = 0.25
*/

// ---------------------------------------------------------------------------
// Approach 1: Brute Force (Linear Multiplication) -> O(n) time, O(1) space
// Idea: multiply x by itself |n| times. If n is negative, take reciprocal
//       at the end. Works but too slow for large n (TLE on LeetCode,
//       since n can be up to 2^31 - 1).
// ---------------------------------------------------------------------------
double myPowBrute(double x, int n) {
  long long N = n;
  bool isNegative = (N < 0);
  if (isNegative) N = -N;

  double result = 1.0;
  for (long long i = 0; i < N; i++) {
    result *= x;
  }

  return isNegative ? 1.0 / result : result;
}

// ---------------------------------------------------------------------------
// Approach 2: Fast Power / Binary Exponentiation (Optimal) -> O(log n) time,
// O(1) space (iterative) Idea: instead of multiplying n times, use the fact
// that:
//       x^n = (x^2)^(n/2)          if n is even
//       x^n = x * (x^2)^((n-1)/2)  if n is odd
//
//       Each step halves n and squares x, so total steps = log2(n).
//       Iterative version avoids recursion call-stack overhead.
//
//       Handle negative n by converting to positive exponent and taking
//       reciprocal at the end. Use long long for N to safely negate
//       INT_MIN (since -INT_MIN overflows a plain int).
// ---------------------------------------------------------------------------
double myPowOptimal(double x, int n) {
  long long N = n;
  bool isNegative = (N < 0);
  if (isNegative) N = -N;

  double result = 1.0;
  double base = x;

  while (N > 0) {
    if (N % 2 == 1) {
      result *= base;  // odd -> take one extra factor of base
    }
    base *= base;  // square the base
    N /= 2;        // halve the exponent
  }

  return isNegative ? 1.0 / result : result;
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  cout << "Brute Force -> 2.0^10  = " << myPowBrute(2.0, 10) << endl;
  cout << "Optimal     -> 2.0^10  = " << myPowOptimal(2.0, 10) << endl;
  cout << "-----------------------------------" << endl;

  cout << "Brute Force -> 2.0^-2  = " << myPowBrute(2.0, -2) << endl;
  cout << "Optimal     -> 2.0^-2  = " << myPowOptimal(2.0, -2) << endl;
  cout << "-----------------------------------" << endl;

  cout << "Brute Force -> 2.1^3   = " << myPowBrute(2.1, 3) << endl;
  cout << "Optimal     -> 2.1^3   = " << myPowOptimal(2.1, 3) << endl;

  return 0;
}