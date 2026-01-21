#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  //  Check whether placing a queen at (row, col) is valid
  bool isSafe(vector<string>& board, int row, int col, int n) {
    // Check same column (no vertical conflict)
    for (int r = 0; r < row; r++) {
      if (board[r][col] == 'Q') return false;
    }

    // Check upper-left diagonal
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; r--, c--) {
      if (board[r][c] == 'Q') return false;
    }

    // Check upper-right diagonal
    for (int r = row - 1, c = col + 1; r >= 0 && c < n; r--, c++) {
      if (board[r][c] == 'Q') return false;
    }

    return true;
  }

  //  Recursive function to place queens row-by-row
  void placeQueens(vector<string>& board, int row, int n,
                   vector<vector<string>>& result) {
    // Base Case ➤ All queens successfully placed
    if (row == n) {
      result.push_back(board);
      return;
    }

    // Try placing a queen in all columns of current row
    for (int col = 0; col < n; col++) {
      if (isSafe(board, row, col, n)) {
        board[row][col] = 'Q';                   // Place queen
        placeQueens(board, row + 1, n, result);  // Recurse
        board[row][col] = '.';                   // Backtrack
      }
    }
  }

  vector<vector<string>> solveNQueens(int n) {
    vector<string> board(n, string(n, '.'));  // Initially all positions empty
    vector<vector<string>> result;

    placeQueens(board, 0, n, result);
    return result;
  }
};

int main() {
  Solution obj;

  int n = 4;  // 🔹 Example input
  vector<vector<string>> solutions = obj.solveNQueens(n);

  cout << "Number of solutions for " << n << "-Queens: " << solutions.size()
       << "\n\n";

  // Print all valid solutions
  for (int sol = 0; sol < solutions.size(); sol++) {
    cout << "Solution " << sol + 1 << ":\n";
    for (string row : solutions[sol]) {
      cout << row << "\n";
    }
    cout << "\n";
  }

  return 0;
}
