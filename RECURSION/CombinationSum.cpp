#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  // Backtracking to explore all valid combinations
  void backtrack(int idx, int target, vector<int>& candidates,
                 vector<int>& curr, vector<vector<int>>& result) {
    // If target becomes 0 → valid combination found
    if (target == 0) {
      result.push_back(curr);
      return;
    }

    // If index goes out of range OR target goes negative → invalid path
    if (idx == candidates.size() || target < 0) {
      return;
    }

    // ---- PICK the current number ----
    curr.push_back(candidates[idx]);
    backtrack(idx, target - candidates[idx], candidates, curr, result);
    curr.pop_back();  // backtrack

    // ---- SKIP the current number ----
    backtrack(idx + 1, target, candidates, curr, result);
  }

  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> curr;

    // Sorting ensures consistent ordering & avoids duplicates
    sort(candidates.begin(), candidates.end());

    backtrack(0, target, candidates, curr, result);
    return result;
  }
};

int main() {
  Solution sol;

  // -------- Hardcoded example (no input required) --------
  vector<int> arr = {2, 3, 5, 7};  // random example array
  int target = 10;                 // random target

  // Function call
  vector<vector<int>> ans = sol.combinationSum(arr, target);

  // Output
  cout << "Array: [ ";
  for (int x : arr) cout << x << " ";
  cout << "]\n";

  cout << "Target: " << target << "\n\n";

  cout << "Combinations that sum to " << target << ":\n";
  for (auto& comb : ans) {
    cout << "[ ";
    for (int x : comb) cout << x << " ";
    cout << "]\n";
  }

  return 0;
}
