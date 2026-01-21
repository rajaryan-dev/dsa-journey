// LeetCode: 1047 - Remove All Adjacent Duplicates in String
// Approach using stack<char>
// --------------------------
// Push characters one by one.
// If current char = stack top → pop (means duplicate pair removed)
// Otherwise push it.
// Finally, stack contains the answer but in reverse order,
// so we pop and build the result string.

#include <bits/stdc++.h>
using namespace std;

// Function to remove adjacent duplicates using stack
string removeDuplicates(string s) {
  stack<char> st;

  for (char ch : s) {
    // If stack is NOT empty AND top matches current char
    // then it's a duplicate -> remove it
    if (!st.empty() && st.top() == ch) {
      st.pop();
    } else {
      st.push(ch);  // otherwise keep it
    }
  }

  // Now build answer from stack
  string result;

  // stack stores characters in reverse order
  while (!st.empty()) {
    result.push_back(st.top());
    st.pop();
  }

  reverse(result.begin(), result.end());  // correct order
  return result;
}

int main() {
  // Random example testcases
  vector<string> tests = {
      "abbaca",       // -> "ca"
      "azxxzy",       // -> "ay"
      "abba",         // -> ""
      "aaaa",         // -> ""
      "aabccb",       // -> "b"
      "mississippi",  // -> "m"
      "abcddcba"      // -> "abcddcba"
  };

  cout << "Testing Remove Adjacent Duplicates using STACK:\n\n";

  for (string s : tests) {
    cout << "Input  : " << s << endl;
    cout << "Output : " << removeDuplicates(s) << endl;
    cout << "---------------------------------\n";
  }

  return 0;
}
