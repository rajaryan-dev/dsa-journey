#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
  vector<int> arr = {6, 8, 0, 1, 3};
  int n = arr.size();

  // Previoush Smaller Element
  stack<int> s;
  vector<int> ans(n);

  for (int i = 0; i < n; i++) {
    // Remove all elements greater/equal to current
    while (!s.empty() && s.top() >= arr[i]) {
      s.pop();
    }
 
    // If stack becomes empty → no smaller element
    if (s.empty()) {
      ans[i] = -1;
    } else {
      ans[i] = s.top();
    }

    // Push current element into stack
    s.push(arr[i]);
  }

  // Print result
  for (int x : ans) {
    cout << x << " ";
  }
  cout << endl;

  return 0;
}
