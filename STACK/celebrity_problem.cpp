#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Celebrity Problem
// matrix[a][b] == 1 → a knows b
// Celebrity conditions:
// 1) Everybody knows celebrity
// 2) Celebrity knows nobody
int getCelebrity(const vector<vector<int>>& matrix) {
  int n = matrix.size();
  stack<int> candidateStack;

  // Push all persons into stack
  for (int person = 0; person < n; person++) {
    candidateStack.push(person);
  }

  // Step 1: Find potential celebrity
  // Compare top 2 people at a time & eliminate 1
  while (candidateStack.size() > 1) {
    int A = candidateStack.top();
    candidateStack.pop();
    int B = candidateStack.top();
    candidateStack.pop();

    // If A knows B → A cannot be celebrity, B may be
    // Else → B cannot be celebrity, A may be
    if (matrix[A][B] == 1) {
      candidateStack.push(B);
    } else {
      candidateStack.push(A);
    }
  }

  // Only one candidate remains
  int celebrity = candidateStack.top();

  // Step 2: Verify candidate
  for (int i = 0; i < n; i++) {
    // Skip checking self
    if (i == celebrity) continue;

    // Condition to FAIL celebrity:
    // 1. If someone does NOT know celebrity
    // OR
    // 2. Celebrity knows someone
    if (matrix[i][celebrity] == 0 || matrix[celebrity][i] == 1) {
      return -1;  // No celebrity
    }
  }

  return celebrity;
}

int main() {
  vector<vector<int>> matrix = {{0, 1, 0}, {0, 0, 0}, {0, 1, 0}};

  int result = getCelebrity(matrix);

  cout << "Celebrity is: " << result << endl;

  return 0;
}
