#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  // Check if placing 'digit' at (row, col) is valid
  bool isSafe(vector<vector<char>>& board, int row, int col, char digit) {
    // Check row & column
    for (int i = 0; i < 9; i++) {
      if (board[row][i] == digit) return false;
      if (board[i][col] == digit) return false;
    }

    // Check 3×3 grid
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++) {
      for (int j = startCol; j < startCol + 3; j++) {
        if (board[i][j] == digit) return false;
      }
    }
    return true;
  }

  // Backtracking function
  bool solve(vector<vector<char>>& board, int row, int col) {
    if (row == 9) return true;  // Solved

    int nextRow = row, nextCol = col + 1;
    if (nextCol == 9) {  // Move to next row
      nextRow = row + 1;
      nextCol = 0;
    }

    if (board[row][col] != '.')  // Skip prefilled cells
      return solve(board, nextRow, nextCol);

    for (char digit = '1'; digit <= '9'; digit++) {
      if (isSafe(board, row, col, digit)) {
        board[row][col] = digit;
        if (solve(board, nextRow, nextCol)) return true;
      }
      board[row][col] = '.';  // Backtrack
    }
    return false;
  }

  void solveSudoku(vector<vector<char>>& board) { solve(board, 0, 0); }
};

// Utility function to print Sudoku board
void printBoard(const vector<vector<char>>& board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << board[i][j] << ' ';
    }
    cout << endl;
  }
}

int main() {
  vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  cout << " Input Sudoku Board:\n";
  printBoard(board);

  Solution obj;
  obj.solveSudoku(board);

  cout << "\n Solved Sudoku Board:\n";
  printBoard(board);

  return 0;
}
