#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
 public:
  string removeOuterParentheses(string s) {
    string result = "";
    stack<char> st;

    for (char c : s) {
      if (c == '(') {
        // If the stack is NOT empty, this '(' is NOT an outermost one.
        // It belongs to an inner part of a primitive string.
        if (!st.empty()) {
          result += c;
        }
        // Push every '(' onto the stack to track the nesting level.
        st.push(c);
      } else {
        // Pop from the stack first to match the current ')'.
        st.pop();

        // If the stack is NOT empty after popping, this ')' was NOT
        // the outermost closing parenthesis of a primitive group.
        if (!st.empty()) {
          result += c;
        }
      }
    }
    return result;
  }
};