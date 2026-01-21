/*
LeetCode 682: Baseball Game
--------------------------------
You are keeping the scores for a baseball game with strange rules.

You are given a list of strings operations, where operations[i] is the ith
operation you must apply to the record and is one of the following:

1️⃣ An integer x
   Record a new score of x.

2️⃣ "+"
   Record a new score that is the sum of the previous two scores.

3️⃣ "D"
   Record a new score that is the double of the previous score.

4️⃣ "C"
   Invalidate the previous score, removing it from the record.

Return the sum of all the scores on the record after applying all the
operations.

It is guaranteed that all operations are valid and all values fit in 32-bit
integer.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int calPoints(vector<string>& operations) {
    stack<int> st;

    for (string& op : operations) {
      // Case 1: integer score
      if (op != "C" && op != "D" && op != "+") {
        st.push(stoi(op));
      }

      // Case 2: remove previous score
      else if (op == "C") {
        st.pop();
      }

      // Case 3: double previous score
      else if (op == "D") {
        st.push(st.top() * 2);
      }

      // Case 4: sum of previous two scores
      else if (op == "+") {
        int last = st.top();
        st.pop();
        int secondLast = st.top();
        st.push(last);  // restore value

        st.push(last + secondLast);
      }
    }

    // Sum all scores
    int totalScore = 0;
    while (!st.empty()) {
      totalScore += st.top();
      st.pop();
    }

    return totalScore;
  }
};

int main() {
  Solution obj;

  int n;
  cout << "Enter number of operations: ";
  cin >> n;

  vector<string> ops(n);
  cout << "Enter operations (integers / C / D / +):\n";
  for (int i = 0; i < n; i++) {
    cin >> ops[i];
  }

  cout << "\nFinal Score = " << obj.calPoints(ops) << endl;

  return 0;
}
