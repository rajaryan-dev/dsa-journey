#include <iostream>
#include <vector>
using namespace std;

/*
  🔥 Problem: Generate and print all subsets of a given array using recursion &
  backtracking.

  ▪ Core Idea:
      At every index, we have two choices — include the current element or
  exclude it. Recursively exploring both choices forms all possible subsets.

  ▪ Time Complexity:
      O(2^N)    → because each element has 2 choices (include/exclude)

  ▪ Space Complexity:
      O(N)      → recursion stack + subset vector (max N elements at depth)

  📌 This approach avoids extra array copies by using backtracking (push + pop).
*/

void getAllSubsets(vector<int>& arr, vector<int>& currentSubset, int index) {
  // Base Case: If we reach end of array, print the subset
  if (index == arr.size()) {
    if (currentSubset.empty()) {
      cout << "{}" << endl;  // print null/empty set indicator
    } else {
      for (int x : currentSubset) cout << x << " ";
      cout << endl;
    }

    return;
  }

  // 1️⃣ Choice: Include current element
  currentSubset.push_back(arr[index]);
  // Continue recursion after including the current element
  getAllSubsets(arr, currentSubset, index + 1);

  // Backtrack → remove last inserted element before exploring next choice
  currentSubset.pop_back();

  // 2️⃣ Choice: Exclude current element
  // no push_back(arr[index]) operations due to Exclude
  // Continue recursion after excluding the current element
  getAllSubsets(arr, currentSubset, index + 1);
}

int main() {
  vector<int> arr = {1, 2, 3};
  vector<int> currentSubset;  // stores elements of the subset being formed

  getAllSubsets(arr, currentSubset, 0);

  return 0;
}
