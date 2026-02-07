/*
 * ============================================================================
 * FILE: 06_Array_Rotation.cpp
 * ============================================================================
 * 
 * ARRAY ROTATION OPERATIONS
 * 
 * Left Rotation: Elements shift left, first element goes to end
 * Right Rotation: Elements shift right, last element goes to front
 * 
 * Example: [1, 2, 3, 4, 5]
 * Left rotate by 2:  [3, 4, 5, 1, 2]
 * Right rotate by 2: [4, 5, 1, 2, 3]
 * 
 * ============================================================================
 */

#include <iostream>
using namespace std;

void printArray(int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ============================================================================
// LEFT ROTATE BY ONE - O(n)
// ============================================================================
// Move each element one position left, first goes to last
// ============================================================================
void leftRotateByOne(int arr[], int size) {
    int first = arr[0];  // Store first element
    
    // Shift all elements left
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    
    arr[size - 1] = first;  // First goes to last
}

// ============================================================================
// LEFT ROTATE BY D (Naive) - O(n*d)
// ============================================================================
// Call leftRotateByOne d times
// ============================================================================
void leftRotateByDNaive(int arr[], int size, int d) {
    d = d % size;  // Handle if d > size
    for (int i = 0; i < d; i++) {
        leftRotateByOne(arr, size);
    }
}

// ============================================================================
// REVERSE ARRAY HELPER
// ============================================================================
void reverseArray(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

// ============================================================================
// LEFT ROTATE BY D (Reversal Algorithm) - O(n)
// ============================================================================
// Algorithm:
// 1. Reverse first d elements
// 2. Reverse remaining n-d elements
// 3. Reverse entire array
// 
// Example: Rotate [1, 2, 3, 4, 5] by d=2
// Step 1: Reverse [1, 2] -> [2, 1, 3, 4, 5]
// Step 2: Reverse [3, 4, 5] -> [2, 1, 5, 4, 3]
// Step 3: Reverse all -> [3, 4, 5, 1, 2]
// ============================================================================
void leftRotateByD(int arr[], int size, int d) {
    d = d % size;  // Handle if d > size
    if (d == 0) return;
    
    reverseArray(arr, 0, d - 1);        // Reverse first d
    reverseArray(arr, d, size - 1);     // Reverse remaining
    reverseArray(arr, 0, size - 1);     // Reverse all
}

// ============================================================================
// RIGHT ROTATE BY D - O(n)
// ============================================================================
// Same as left rotate by (n - d)
// Or: Reverse last d elements, then remaining, then all
// ============================================================================
void rightRotateByD(int arr[], int size, int d) {
    d = d % size;
    if (d == 0) return;
    
    // Right rotate by d = Left rotate by (size - d)
    leftRotateByD(arr, size, size - d);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    cout << "=== ARRAY ROTATION DEMO ===" << endl;
    
    // Left Rotate by One
    cout << "\n--- Left Rotate by One ---" << endl;
    int arr1[] = {1, 2, 3, 4, 5};
    cout << "Original: "; printArray(arr1, 5);
    leftRotateByOne(arr1, 5);
    cout << "After:    "; printArray(arr1, 5);
    
    // Left Rotate by D (Naive)
    cout << "\n--- Left Rotate by D (Naive) ---" << endl;
    int arr2[] = {1, 2, 3, 4, 5};
    cout << "Original: "; printArray(arr2, 5);
    leftRotateByDNaive(arr2, 5, 2);
    cout << "Rotate by 2: "; printArray(arr2, 5);
    
    // Left Rotate by D (Efficient - Reversal)
    cout << "\n--- Left Rotate by D (Reversal Algorithm) ---" << endl;
    int arr3[] = {1, 2, 3, 4, 5, 6, 7};
    cout << "Original: "; printArray(arr3, 7);
    leftRotateByD(arr3, 7, 3);
    cout << "Rotate by 3: "; printArray(arr3, 7);
    
    // Right Rotate
    cout << "\n--- Right Rotate by D ---" << endl;
    int arr4[] = {1, 2, 3, 4, 5};
    cout << "Original: "; printArray(arr4, 5);
    rightRotateByD(arr4, 5, 2);
    cout << "Right rotate by 2: "; printArray(arr4, 5);
    
    // Edge Case: Rotate by size
    cout << "\n--- Edge Case: Rotate by Array Size ---" << endl;
    int arr5[] = {1, 2, 3, 4, 5};
    cout << "Original: "; printArray(arr5, 5);
    leftRotateByD(arr5, 5, 5);
    cout << "Rotate by 5 (full rotation): "; printArray(arr5, 5);
    
    cout << "\n=== COMPLEXITY SUMMARY ===" << endl;
    cout << "| Method              | Time  | Space |" << endl;
    cout << "|---------------------|-------|-------|" << endl;
    cout << "| Naive (d rotations) | O(n*d)| O(1)  |" << endl;
    cout << "| Reversal Algorithm  | O(n)  | O(1)  |" << endl;
    
    return 0;
}
