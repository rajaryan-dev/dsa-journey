#include <bits/stdc++.h>
using namespace std;

/* ----------------------------------------------------
   PRINT NUMBERS FROM N TO 1
   Example: printNums(5) -> 5 4 3 2 1
-----------------------------------------------------*/
void printNums(int num) {
  if (num == 0) return;  // Base case
  cout << num << " ";
  printNums(num - 1);  // Recursive call
}

/* ----------------------------------------------------
   FACTORIAL USING RECURSION
   factorial(5) = 5 * 4 * 3 * 2 * 1 = 120
-----------------------------------------------------*/
int factorial(int n) {
  if (n == 0) return 1;  // Base case: 0! = 1
  return n * factorial(n - 1);
}

/* ----------------------------------------------------
   SUM OF FIRST N NATURAL NUMBERS
   calSum(5) = 1 + 2 + 3 + 4 + 5 = 15
-----------------------------------------------------*/
int calSum(int n) {
  if (n == 0) return 0;  // Base case
  return n + calSum(n - 1);
}

/* ----------------------------------------------------
   FIBONACCI — NORMAL RECURSION (NOT OPTIMIZED)
   Sequence: 0 1 1 2 3 5 8 13 ...
   Example: fib(8) = 21
-----------------------------------------------------*/
int fib(int n) {
  if (n == 0 || n == 1) return n;  // Base case
  return fib(n - 1) + fib(n - 2);  // Recursive formula
}

/* ----------------------------------------------------

   FIBONACCI WITH MEMOIZATION (Optimized O(n))
   Normal recursion → exponential and slow
   Optimized → store results to avoid recomputation
-----------------------------------------------------*/
vector<int> dp(1000, -1);  // Memo array (supports n ≤ 999)
int fib(int n) {
  if (n == 0 || n == 1) return n;  // Base case
  if (dp[n] != -1) return dp[n];   // Use stored result
  return dp[n] = fib(n - 1) + fib(n - 2);
}

/* ----------------------------------------------------
   CHECK IF ARRAY IS SORTED IN ASCENDING ORDER
   isSorted({1, 2, 3}, n) → true
-----------------------------------------------------*/
bool isSorted(const vector<int>& arr, int n) {
  if (n <= 1) return true;  // Base case
  if (arr[n - 1] < arr[n - 2]) return false;
  return isSorted(arr, n - 1);
}

/* ----------------------------------------------------
                      MAIN FUNCTION
   Example calls for all the above functions
-----------------------------------------------------*/
int main() {
  // 1️⃣ Print Numbers
  cout << "Print numbers from N to 1: ";
  printNums(5);
  cout << "\n";

  // 2️⃣ Factorial
  cout << "Factorial of 5: " << factorial(5) << "\n";

  // 3️⃣ Sum of Natural Numbers
  cout << "Sum of first 5 numbers: " << calSum(5) << "\n";

  // 4️⃣ Fibonacci
  cout << "Fibonacci of 8: " << fib(8) << "\n";

  // 5️⃣ Check Sorted
  vector<int> arr = {1, 2, 3, 6, 9};
  cout << "Is array sorted? " << (isSorted(arr, arr.size()) ? "Yes" : "No")
       << "\n";

  return 0;
}
