#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// Function to check if substring s[l..r] is a palindrome using two pointers
// -----------------------------------------------------------------------------
bool isPalindrome(const string& s, int l, int r) {
  while (l < r) {
    if (s[l] != s[r]) return false;
    l++;
    r--;
  }
  return true;
}

// -----------------------------------------------------------------------------
// Backtracking function to find all palindrome partitions
// index → current position in the string
// currentPartition → stores the current list of palindromic substrings
// result → stores all valid partitions
// -----------------------------------------------------------------------------
void backtrack(int index, const string& s, vector<string>& currentPartition,
               vector<vector<string>>& result) {
  // Base case: end of string reached → valid partition found
  if (index == s.size()) {
    result.push_back(currentPartition);
    return;
  }

  // Try forming all substrings from index..i
  for (int i = index; i < s.size(); i++) {
    // Proceed only if substring s[index..i] is a palindrome
    if (isPalindrome(s, index, i)) {
      // Include this palindrome in the current path
      currentPartition.push_back(s.substr(index, i - index + 1));

      // Explore upcoming choices
      backtrack(i + 1, s, currentPartition, result);

      // Backtrack (undo the last choice)
      currentPartition.pop_back();
    }
  }
}

// -----------------------------------------------------------------------------
// Main API function
// -----------------------------------------------------------------------------
vector<vector<string>> partition(string s) {
  vector<vector<string>> result;
  vector<string> currentPartition;
  backtrack(0, s, currentPartition, result);
  return result;
}

// -----------------------------------------------------------------------------
// MAIN FUNCTION
// -----------------------------------------------------------------------------
int main() {
  // ---------------------------------------------------------------------------
  // 📝 Method 1: Take input from user (for terminal testing)
  //
  // string s;
  // cout << "Enter string: ";
  // cin >> s;
  //
  // vector<vector<string>> ans = partition(s);
  //
  // cout << "\nAll Palindrome Partitions:\n";
  // for (auto& vec : ans) {
  //   cout << "[ ";
  //   for (auto& word : vec) cout << word << " ";
  //   cout << "]\n";
  // }
  // ---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  // 🔥 Method 2: Fixed random example (change anytime for testing)
  // ---------------------------------------------------------------------------
  string s = "banana";

  vector<vector<string>> ans = partition(s);

  cout << "Input string: " << s << "\n\n";
  cout << "All Palindromic Partitions:\n";

  for (auto& vec : ans) {
    cout << "[ ";
    for (auto& word : vec) {
      cout << word << " ";
    }
    cout << "]\n";
  }

  return 0;
}
