/*
 * ============================================================================
 * FILE: 07_2D_Arrays.cpp
 * ============================================================================
 *
 * 2D ARRAYS (MATRICES)
 *
 * A 2D array is an array of arrays — think of it as a table with rows and
 * columns. In C++, memory is laid out in ROW-MAJOR order (row by row).
 *
 *   int m[3][4]:
 *     Row 0: [m[0][0], m[0][1], m[0][2], m[0][3]]
 *     Row 1: [m[1][0], m[1][1], m[1][2], m[1][3]]   ← contiguous in memory
 *     Row 2: [m[2][0], m[2][1], m[2][2], m[2][3]]
 *
 * ┌──────────────────────────┬──────────┬───────┐
 * │ Operation                │ Time     │ Space │
 * ├──────────────────────────┼──────────┼───────┤
 * │ Traversal (any order)    │ O(r × c) │ O(1)  │
 * │ Transpose                │ O(r × c) │ O(r×c)│
 * │ Spiral Traversal         │ O(r × c) │ O(1)  │
 * │ Wave Print               │ O(r × c) │ O(1)  │
 * │ Diagonal Sum (square)    │ O(n)     │ O(1)  │
 * │ Search in sorted matrix  │ O(r + c) │ O(1)  │
 * └──────────────────────────┴──────────┴───────┘
 *
 * ============================================================================
 */

#include <iostream>
using namespace std;

const int MAXR = 10;
const int MAXC = 10;

// ─────────────────────────────────────────────────────────────────────────────
// UTILITY: Print Matrix
// ─────────────────────────────────────────────────────────────────────────────
void printMatrix(int mat[][MAXC], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        cout << "  [ ";
        for (int j = 0; j < cols; j++) {
            cout << mat[i][j];
            if (j < cols - 1) cout << "\t";
        }
        cout << " ]" << endl;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 1. ROW-MAJOR TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
//   Process row by row: [0][0], [0][1], …, [1][0], [1][1], …
// ─────────────────────────────────────────────────────────────────────────────
void rowMajor(int mat[][MAXC], int r, int c) {
    cout << "Row-Major:    ";
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) cout << mat[i][j] << " ";
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// 2. COLUMN-MAJOR TRAVERSAL
// ─────────────────────────────────────────────────────────────────────────────
//   Process column by column: [0][0], [1][0], …, [0][1], [1][1], …
// ─────────────────────────────────────────────────────────────────────────────
void colMajor(int mat[][MAXC], int r, int c) {
    cout << "Column-Major: ";
    for (int j = 0; j < c; j++)
        for (int i = 0; i < r; i++) cout << mat[i][j] << " ";
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// 3. TRANSPOSE — O(r × c)
// ─────────────────────────────────────────────────────────────────────────────
//   result[j][i] = mat[i][j]      (swap rows ↔ columns)
// ─────────────────────────────────────────────────────────────────────────────
void transpose(int mat[][MAXC], int res[][MAXC], int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) res[j][i] = mat[i][j];
}

// ─────────────────────────────────────────────────────────────────────────────
// 4. SPIRAL TRAVERSAL — O(r × c)
// ─────────────────────────────────────────────────────────────────────────────
//   Peel layers from outside inward:
//     → top row, ↓ right col, ← bottom row, ↑ left col, shrink, repeat.
//
//     1  2  3  4          Spiral order:
//     5  6  7  8    →     1 2 3 4 8 12 11 10 9 5 6 7
//     9 10 11 12
// ─────────────────────────────────────────────────────────────────────────────
void spiralTraversal(int mat[][MAXC], int r, int c) {
    int top = 0, bottom = r - 1, left = 0, right = c - 1;
    cout << "Spiral:       ";

    while (top <= bottom && left <= right) {
        // → top row
        for (int j = left; j <= right; j++) cout << mat[top][j] << " ";
        top++;

        // ↓ right column
        for (int i = top; i <= bottom; i++) cout << mat[i][right] << " ";
        right--;

        // ← bottom row (if exists)
        if (top <= bottom) {
            for (int j = right; j >= left; j--) cout << mat[bottom][j] << " ";
            bottom--;
        }

        // ↑ left column (if exists)
        if (left <= right) {
            for (int i = bottom; i >= top; i--) cout << mat[i][left] << " ";
            left++;
        }
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// 5. WAVE PRINT — O(r × c)
// ─────────────────────────────────────────────────────────────────────────────
//   Even columns: top → bottom.   Odd columns: bottom → top.
//
//     1  2  3        Wave order:
//     4  5  6   →    1 4 7 8 5 2 3 6 9
//     7  8  9
// ─────────────────────────────────────────────────────────────────────────────
void wavePrint(int mat[][MAXC], int r, int c) {
    cout << "Wave Print:   ";
    for (int j = 0; j < c; j++) {
        if (j % 2 == 0) {
            for (int i = 0; i < r; i++) cout << mat[i][j] << " ";
        } else {
            for (int i = r - 1; i >= 0; i--) cout << mat[i][j] << " ";
        }
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// 6. DIAGONAL SUM (Square Matrix) — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Primary diagonal:   mat[i][i]
//   Secondary diagonal: mat[i][n-1-i]
//   If n is odd, center element is on both — don't double-count.
// ─────────────────────────────────────────────────────────────────────────────
int diagonalSum(int mat[][MAXC], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += mat[i][i];                     // primary
        if (i != n - 1 - i)
            sum += mat[i][n - 1 - i];         // secondary (avoid double count)
    }
    return sum;
}

// ─────────────────────────────────────────────────────────────────────────────
// 7. ROW-WISE & COLUMN-WISE SUMS — O(r × c)
// ─────────────────────────────────────────────────────────────────────────────
void rowSums(int mat[][MAXC], int r, int c) {
    cout << "Row sums:    ";
    for (int i = 0; i < r; i++) {
        int s = 0;
        for (int j = 0; j < c; j++) s += mat[i][j];
        cout << s << " ";
    }
    cout << endl;
}

void colSums(int mat[][MAXC], int r, int c) {
    cout << "Col sums:    ";
    for (int j = 0; j < c; j++) {
        int s = 0;
        for (int i = 0; i < r; i++) s += mat[i][j];
        cout << s << " ";
    }
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// 8. BOUNDARY ELEMENTS
// ─────────────────────────────────────────────────────────────────────────────
void printBoundary(int mat[][MAXC], int r, int c) {
    cout << "Boundary:     ";
    for (int j = 0; j < c; j++)              cout << mat[0][j] << " ";        // top
    for (int i = 1; i < r; i++)              cout << mat[i][c - 1] << " ";    // right
    if (r > 1) for (int j = c - 2; j >= 0; j--)  cout << mat[r - 1][j] << " "; // bottom
    for (int i = r - 2; i >= 1; i--)         cout << mat[i][0] << " ";        // left
    cout << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// 9. SEARCH IN ROW-WISE & COL-WISE SORTED MATRIX — O(r + c)
// ─────────────────────────────────────────────────────────────────────────────
//   Start at top-right corner:
//     • If mat[i][j] == target → found
//     • If mat[i][j] > target  → go left  (eliminate column)
//     • If mat[i][j] < target  → go down  (eliminate row)
// ─────────────────────────────────────────────────────────────────────────────
bool searchSortedMatrix(int mat[][MAXC], int r, int c, int target,
                        int& foundRow, int& foundCol) {
    int i = 0, j = c - 1;                    // start top-right
    while (i < r && j >= 0) {
        if (mat[i][j] == target) { foundRow = i; foundCol = j; return true; }
        else if (mat[i][j] > target) j--;
        else                         i++;
    }
    return false;
}

// ═════════════════════════════════════════════════════════════════════════════
// MAIN — Demonstrate All 2D Array Operations
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    cout << "============================================" << endl;
    cout << "   07 · 2D ARRAY OPERATIONS" << endl;
    cout << "============================================" << endl;

    int mat[MAXR][MAXC] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int r = 3, c = 4;

    cout << "\n--- Original Matrix ---" << endl;
    printMatrix(mat, r, c);

    // ── Traversals ───────────────────────────────────────────────────────
    cout << "\n--- Traversals ---" << endl;
    rowMajor(mat, r, c);
    colMajor(mat, r, c);
    spiralTraversal(mat, r, c);
    wavePrint(mat, r, c);

    // ── Transpose ────────────────────────────────────────────────────────
    cout << "\n--- Transpose ---" << endl;
    int trans[MAXR][MAXC];
    transpose(mat, trans, r, c);
    printMatrix(trans, c, r);           // swapped dimensions

    // ── Diagonal Sum (use 3×3 square) ────────────────────────────────────
    cout << "\n--- Diagonal Sum (3x3 sub-matrix) ---" << endl;
    int sq[MAXR][MAXC] = {{1,2,3},{4,5,6},{7,8,9}};
    printMatrix(sq, 3, 3);
    cout << "  Diagonal sum = " << diagonalSum(sq, 3) << endl;

    // ── Row & Column Sums ────────────────────────────────────────────────
    cout << "\n--- Row & Column Sums ---" << endl;
    rowSums(mat, r, c);
    colSums(mat, r, c);

    // ── Boundary ─────────────────────────────────────────────────────────
    cout << "\n--- Boundary Elements ---" << endl;
    printBoundary(mat, r, c);

    // ── Search in Sorted Matrix ──────────────────────────────────────────
    cout << "\n--- Search in Row/Col Sorted Matrix ---" << endl;
    int sorted[MAXR][MAXC] = {
        {10, 20, 30, 40},
        {15, 25, 35, 45},
        {27, 29, 37, 48}
    };
    printMatrix(sorted, 3, 4);
    int fr, fc;
    int target = 29;
    if (searchSortedMatrix(sorted, 3, 4, target, fr, fc))
        cout << "  Found " << target << " at (" << fr << ", " << fc << ")" << endl;
    else
        cout << "  " << target << " not found." << endl;

    target = 100;
    if (searchSortedMatrix(sorted, 3, 4, target, fr, fc))
        cout << "  Found " << target << " at (" << fr << ", " << fc << ")" << endl;
    else
        cout << "  " << target << " not found." << endl;

    cout << "\n============================================" << endl;
    cout << "   2D Array Operations Completed!" << endl;
    cout << "============================================" << endl;

    return 0;
}
