/*
 * ============================================================================
 * FILE: 07_Array_2D_Basics.cpp
 * ============================================================================
 * 
 * 2D ARRAYS (MATRICES)
 * 
 * A 2D array is an array of arrays - like a table with rows and columns.
 * 
 * Memory Layout (Row-Major in C++):
 * [0][0] [0][1] [0][2] [1][0] [1][1] [1][2] ... (contiguous in memory)
 * 
 * Declaration: int arr[ROWS][COLS];
 * 
 * ============================================================================
 */

#include <iostream>
using namespace std;

const int MAX_ROWS = 10;
const int MAX_COLS = 10;

// ============================================================================
// Print 2D Array
// ============================================================================
void print2DArray(int arr[][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        cout << "[ ";
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

// ============================================================================
// ROW-MAJOR TRAVERSAL
// ============================================================================
// Process row by row: [0][0], [0][1], [0][2], [1][0], [1][1]...
// ============================================================================
void rowMajorTraversal(int arr[][MAX_COLS], int rows, int cols) {
    cout << "Row-Major: ";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
    }
    cout << endl;
}

// ============================================================================
// COLUMN-MAJOR TRAVERSAL
// ============================================================================
// Process column by column: [0][0], [1][0], [2][0], [0][1], [1][1]...
// ============================================================================
void columnMajorTraversal(int arr[][MAX_COLS], int rows, int cols) {
    cout << "Column-Major: ";
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            cout << arr[i][j] << " ";
        }
    }
    cout << endl;
}

// ============================================================================
// TRANSPOSE MATRIX - O(n*m)
// ============================================================================
// Swap rows with columns: result[j][i] = arr[i][j]
// ============================================================================
void transpose(int arr[][MAX_COLS], int result[][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = arr[i][j];
        }
    }
}

// ============================================================================
// DIAGONAL SUM (Square Matrix) - O(n)
// ============================================================================
// Primary diagonal: arr[i][i]
// Secondary diagonal: arr[i][n-1-i]
// ============================================================================
int diagonalSum(int arr[][MAX_COLS], int n) {
    int sum = 0;
    
    for (int i = 0; i < n; i++) {
        sum += arr[i][i];              // Primary diagonal
        if (i != n - 1 - i) {          // Avoid counting center twice
            sum += arr[i][n - 1 - i];  // Secondary diagonal
        }
    }
    
    return sum;
}

// ============================================================================
// ROW-WISE SUM
// ============================================================================
void rowWiseSum(int arr[][MAX_COLS], int rows, int cols) {
    cout << "Row-wise sums: ";
    for (int i = 0; i < rows; i++) {
        int sum = 0;
        for (int j = 0; j < cols; j++) {
            sum += arr[i][j];
        }
        cout << sum << " ";
    }
    cout << endl;
}

// ============================================================================
// COLUMN-WISE SUM
// ============================================================================
void columnWiseSum(int arr[][MAX_COLS], int rows, int cols) {
    cout << "Column-wise sums: ";
    for (int j = 0; j < cols; j++) {
        int sum = 0;
        for (int i = 0; i < rows; i++) {
            sum += arr[i][j];
        }
        cout << sum << " ";
    }
    cout << endl;
}

// ============================================================================
// BOUNDARY ELEMENTS
// ============================================================================
void printBoundary(int arr[][MAX_COLS], int rows, int cols) {
    cout << "Boundary elements: ";
    // Top row
    for (int j = 0; j < cols; j++) cout << arr[0][j] << " ";
    // Right column (excluding top)
    for (int i = 1; i < rows; i++) cout << arr[i][cols-1] << " ";
    // Bottom row (excluding right, if rows > 1)
    if (rows > 1) {
        for (int j = cols-2; j >= 0; j--) cout << arr[rows-1][j] << " ";
    }
    // Left column (excluding top and bottom)
    for (int i = rows-2; i >= 1; i--) cout << arr[i][0] << " ";
    cout << endl;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    cout << "=== 2D ARRAY OPERATIONS ===" << endl;
    
    // Initialize 2D Array
    int arr[MAX_ROWS][MAX_COLS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int rows = 3, cols = 3;
    
    cout << "\n--- Original Matrix ---" << endl;
    print2DArray(arr, rows, cols);
    
    // Traversals
    cout << "\n--- Traversals ---" << endl;
    rowMajorTraversal(arr, rows, cols);
    columnMajorTraversal(arr, rows, cols);
    
    // Transpose
    cout << "\n--- Transpose ---" << endl;
    int transposed[MAX_ROWS][MAX_COLS];
    transpose(arr, transposed, rows, cols);
    cout << "Transposed Matrix:" << endl;
    print2DArray(transposed, cols, rows);
    
    // Diagonal Sum
    cout << "\n--- Diagonal Sum ---" << endl;
    cout << "Sum of both diagonals: " << diagonalSum(arr, 3) << endl;
    
    // Row and Column Sums
    cout << "\n--- Row & Column Sums ---" << endl;
    rowWiseSum(arr, rows, cols);
    columnWiseSum(arr, rows, cols);
    
    // Boundary Elements
    cout << "\n--- Boundary Elements ---" << endl;
    printBoundary(arr, rows, cols);
    
    return 0;
}
