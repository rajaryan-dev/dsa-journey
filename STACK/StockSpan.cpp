#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
  // ---------------- STOCK PRICES INPUT ----------------
  vector<int> price = {100, 80, 60, 70, 60, 75, 85};

  int n = price.size();
  vector<int> ans(n);  // store stock span result → must have size n
  stack<int> s;        // will store **indices** of prices

  // ---------------- MAIN LOGIC ----------------
  for (int i = 0; i < n; i++) {
    // Remove indices from stack while current day's price is **greater**
    // than or equal to price at stack top → monotonic decreasing stack
    while (!s.empty() && price[s.top()] <= price[i]) {
      s.pop();
    }

    // If stack empty → no previous greater element → span = i + 1
    if (s.empty()) {
      ans[i] = i + 1;
    }
    // Otherwise → difference of indices gives span
    else {
      ans[i] = i - s.top();
    }

    // Push current index
    s.push(i);
  }

  // ---------------- PRINT RESULT ----------------
  cout << "Stock Span Result: ";
  for (int val : ans) {
    cout << val << " ";
  }
  cout << endl;

  return 0;
}
