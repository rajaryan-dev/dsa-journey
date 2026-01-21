/*
   LeetCode 20. Valid Parentheses
   --------------------------------
   Given a string s containing just the characters:
       '(', ')', '{', '}', '[' and ']'
   Determine if the input string is valid.

   A string is valid if:
     ✔ Open brackets are closed by the same type of brackets.
     ✔ Open brackets are closed in the correct order.

   Examples:
     Input: "()"          → Output: true
     Input: "()[]{}"      → Output: true
     Input: "(]"          → Output: false
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isValid(string str) {
    stack<char> st;

    for (char ch : str) {
      // ---- Opening brackets ----
      if (ch == '(' || ch == '{' || ch == '[') {
        st.push(ch);
      }
      // ---- Closing brackets ----
      else {
        if (st.empty()) return false;  // no matching opening bracket

        char top = st.top();
        bool match = (top == '(' && ch == ')') || (top == '{' && ch == '}') ||
                     (top == '[' && ch == ']');

        if (match)
          st.pop();
        else
          return false;
      }
    }

    // If stack became empty → all brackets matched correctly
    return st.empty();
  }
};

// -------------------------------------
// MAIN FUNCTION (trial / testing)
// -------------------------------------
int main() {
  Solution obj;

  vector<string> testCases = {"()",       "()[]{}", "(]",   "{[]}", "((()))",
                              "({[()]})", "([)]",   "((((", "",     "){"};

  for (string s : testCases) {
    bool result = obj.isValid(s);
    cout << "Input: " << s << "  ->  Output: " << (result ? "true" : "false")
         << endl;
  }

  return 0;
}
