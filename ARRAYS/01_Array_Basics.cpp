/*
 * ============================================================================
 * FILE: 01_Array_Basics.cpp
 * ============================================================================
 * 
 * ARRAYS - Introduction and Fundamentals
 * 
 * WHAT IS AN ARRAY?
 * -----------------
 * An array is a collection of elements of the SAME data type stored in 
 * CONTIGUOUS (adjacent) memory locations. Think of it like a row of boxes,
 * where each box can hold one item and has a number (index) starting from 0.
 * 
 * Example Memory Layout for int arr[5] = {10, 20, 30, 40, 50}:
 * 
 *   Index:     [0]    [1]    [2]    [3]    [4]
 *   Value:     10     20     30     40     50
 *   Address:  1000   1004   1008   1012   1016  (4 bytes each for int)
 * 
 * WHY USE ARRAYS?
 * ---------------
 * 1. Random Access: Access any element in O(1) time using index
 * 2. Cache Friendly: Contiguous memory = better CPU cache performance
 * 3. Simple: Easy to understand and implement
 * 4. Foundation: Basis for many other data structures (stacks, queues, heaps)
 * 
 * LIMITATIONS:
 * ------------
 * 1. Fixed Size: Static arrays cannot grow/shrink at runtime
 * 2. Insertion/Deletion: O(n) time complexity - elements must shift
 * 3. Memory Waste: If not fully used, memory is wasted
 * 
 * TIME COMPLEXITY:
 * ----------------
 * | Operation         | Time Complexity |
 * |-------------------|-----------------|
 * | Access by index   | O(1)            |
 * | Search (unsorted) | O(n)            |
 * | Insert at end     | O(1)*           |
 * | Insert at start   | O(n)            |
 * | Delete at end     | O(1)            |
 * | Delete at start   | O(n)            |
 * 
 * * Assuming space is available
 * 
 * ============================================================================
 */

#include <iostream>
#include <climits>  // For INT_MIN and INT_MAX
using namespace std;

// ============================================================================
// UTILITY FUNCTION: Print Array
// ============================================================================
// Purpose: Helper function to display array elements
// Time Complexity: O(n) where n is the size of array
// ============================================================================
void printArray(int arr[], int size) {
    cout << "Array: [";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ============================================================================
// OPERATION 1: Find Length of Array
// ============================================================================
// NOTE: In C++, arrays decay to pointers when passed to functions,
//       so we lose size information. We need to pass size separately
//       OR use sizeof() in the same scope where array is declared.
// 
// sizeof(arr) returns total bytes occupied by array
// sizeof(arr[0]) returns bytes of one element
// Length = sizeof(arr) / sizeof(arr[0])
// ============================================================================
void demonstrateFindLength() {
    cout << "\n=== Finding Array Length ===" << endl;
    
    int arr[] = {10, 20, 30, 40, 50};
    
    // Calculate length using sizeof
    // This ONLY works in the same scope where array is declared
    int length = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Array elements: ";
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Total bytes: " << sizeof(arr) << endl;
    cout << "Bytes per element: " << sizeof(arr[0]) << endl;
    cout << "Length of array: " << length << endl;
}

// ============================================================================
// OPERATION 2: Traverse Array
// ============================================================================
// Purpose: Visit each element of the array once
// Time Complexity: O(n)
// Space Complexity: O(1)
// ============================================================================
void traverseArray(int arr[], int size) {
    cout << "\n=== Array Traversal ===" << endl;
    
    // Method 1: Using index-based for loop
    cout << "Method 1 (Index-based): ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Method 2: Using pointer arithmetic
    cout << "Method 2 (Pointer-based): ";
    int* ptr = arr;  // arr decays to pointer to first element
    for (int i = 0; i < size; i++) {
        cout << *(ptr + i) << " ";  // *(ptr + i) is same as arr[i]
    }
    cout << endl;
}

// ============================================================================
// OPERATION 3: Find Maximum Element
// ============================================================================
// Algorithm:
// 1. Assume first element is maximum
// 2. Compare with each element
// 3. If current element > max, update max
// 4. Return max after full traversal
// 
// Time Complexity: O(n) - must check all elements
// Space Complexity: O(1) - only one variable for max
// ============================================================================
int findMax(int arr[], int size) {
    // Edge case: empty array
    if (size <= 0) {
        cout << "Error: Empty array!" << endl;
        return INT_MIN;
    }
    
    // Step 1: Initialize max with first element
    int maxElement = arr[0];
    
    // Step 2-3: Compare with remaining elements
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxElement) {
            maxElement = arr[i];  // Found new maximum
        }
    }
    
    // Step 4: Return the maximum
    return maxElement;
}

// ============================================================================
// OPERATION 4: Find Minimum Element
// ============================================================================
// Algorithm: Same as findMax, but find smallest element
// Time Complexity: O(n)
// Space Complexity: O(1)
// ============================================================================
int findMin(int arr[], int size) {
    if (size <= 0) {
        cout << "Error: Empty array!" << endl;
        return INT_MAX;
    }
    
    int minElement = arr[0];
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < minElement) {
            minElement = arr[i];
        }
    }
    
    return minElement;
}

// ============================================================================
// OPERATION 5: Calculate Sum of Elements
// ============================================================================
// Time Complexity: O(n)
// Space Complexity: O(1)
// ============================================================================
int calculateSum(int arr[], int size) {
    int sum = 0;
    
    for (int i = 0; i < size; i++) {
        sum += arr[i];  // Add each element to sum
    }
    
    return sum;
}

// ============================================================================
// OPERATION 6: Calculate Average
// ============================================================================
// Average = Sum of elements / Number of elements
// Note: Return type is double for precision
// ============================================================================
double calculateAverage(int arr[], int size) {
    if (size <= 0) return 0.0;
    
    int sum = calculateSum(arr, size);
    return static_cast<double>(sum) / size;  // Cast to avoid integer division
}

// ============================================================================
// OPERATION 7: Reverse Array (In-Place)
// ============================================================================
// Algorithm (Two-Pointer Technique):
// 1. Place one pointer at start, another at end
// 2. Swap elements at both pointers
// 3. Move pointers towards center
// 4. Stop when pointers meet or cross
// 
// Time Complexity: O(n/2) = O(n)
// Space Complexity: O(1) - reversed in place
// ============================================================================
void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;
    
    while (start < end) {
        // Swap elements at start and end
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        // Move pointers towards center
        start++;
        end--;
    }
}

// ============================================================================
// OPERATION 8: Copy Array
// ============================================================================
// Time Complexity: O(n)
// Space Complexity: O(n) for the new array
// ============================================================================
void copyArray(int source[], int destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

// ============================================================================
// MAIN FUNCTION - Demonstrates All Operations
// ============================================================================
int main() {
    cout << "============================================" << endl;
    cout << "   ARRAY BASICS - All Operations Demo" << endl;
    cout << "============================================" << endl;
    
    // ========================================
    // 1. Array Declaration and Initialization
    // ========================================
    cout << "\n=== Declaration & Initialization ===" << endl;
    
    // Method 1: Declare with size, then initialize
    int arr1[5];
    arr1[0] = 10; arr1[1] = 20; arr1[2] = 30; arr1[3] = 40; arr1[4] = 50;
    cout << "Method 1 (Individual assignment): ";
    printArray(arr1, 5);
    
    // Method 2: Initialize at declaration (size auto-calculated)
    int arr2[] = {5, 15, 25, 35, 45};
    cout << "Method 2 (Initializer list): ";
    printArray(arr2, 5);
    
    // Method 3: Partial initialization (rest become 0)
    int arr3[5] = {1, 2};  // arr3 = {1, 2, 0, 0, 0}
    cout << "Method 3 (Partial init): ";
    printArray(arr3, 5);
    
    // Method 4: Initialize all to zero
    int arr4[5] = {0};  // All elements are 0
    cout << "Method 4 (All zeros): ";
    printArray(arr4, 5);
    
    // ========================================
    // 2. Find Length Demonstration
    // ========================================
    demonstrateFindLength();
    
    // ========================================
    // 3. Traverse Array
    // ========================================
    int numbers[] = {100, 200, 300, 400, 500};
    int size = 5;
    traverseArray(numbers, size);
    
    // ========================================
    // 4. Find Maximum and Minimum
    // ========================================
    cout << "\n=== Finding Max & Min ===" << endl;
    int data[] = {23, 45, 12, 67, 34, 89, 11};
    int dataSize = 7;
    
    printArray(data, dataSize);
    cout << "Maximum element: " << findMax(data, dataSize) << endl;
    cout << "Minimum element: " << findMin(data, dataSize) << endl;
    
    // ========================================
    // 5. Sum and Average
    // ========================================
    cout << "\n=== Sum & Average ===" << endl;
    int values[] = {10, 20, 30, 40, 50};
    int valuesSize = 5;
    
    printArray(values, valuesSize);
    cout << "Sum: " << calculateSum(values, valuesSize) << endl;
    cout << "Average: " << calculateAverage(values, valuesSize) << endl;
    
    // ========================================
    // 6. Reverse Array
    // ========================================
    cout << "\n=== Reversing Array ===" << endl;
    int original[] = {1, 2, 3, 4, 5};
    int origSize = 5;
    
    cout << "Before reverse: ";
    printArray(original, origSize);
    
    reverseArray(original, origSize);
    
    cout << "After reverse: ";
    printArray(original, origSize);
    
    // ========================================
    // 7. Copy Array
    // ========================================
    cout << "\n=== Copying Array ===" << endl;
    int source[] = {11, 22, 33, 44, 55};
    int destination[5];
    
    copyArray(source, destination, 5);
    
    cout << "Source: ";
    printArray(source, 5);
    cout << "Copied: ";
    printArray(destination, 5);
    
    cout << "\n============================================" << endl;
    cout << "   All Basic Operations Completed!" << endl;
    cout << "============================================" << endl;
    
    return 0;
}
