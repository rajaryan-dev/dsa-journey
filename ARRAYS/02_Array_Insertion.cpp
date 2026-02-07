/*
 * ============================================================================
 * FILE: 02_Array_Insertion.cpp
 * ============================================================================
 * 
 * ARRAY INSERTION OPERATIONS
 * 
 * Insertion in arrays requires shifting elements to make room for new element.
 * The position of insertion determines the time complexity:
 * 
 * | Insertion Position | Shifts Required | Time Complexity |
 * |--------------------|-----------------|-----------------|
 * | At End             | 0               | O(1)            |
 * | At Beginning       | n               | O(n)            |
 * | At Position i      | n - i           | O(n)            |
 * 
 * IMPORTANT: Arrays have fixed size! We need to track:
 * - capacity: Maximum elements array can hold
 * - size: Current number of elements in use
 * 
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ============================================================================
// UTILITY FUNCTION: Print Array
// ============================================================================
void printArray(int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ============================================================================
// OPERATION 1: Insert at End
// ============================================================================
// Algorithm:
// 1. Check if array has space (size < capacity)
// 2. If yes, add element at index 'size'
// 3. Increment size
// 
// Time Complexity: O(1) - No shifting needed
// Space Complexity: O(1)
// ============================================================================
bool insertAtEnd(int arr[], int& size, int capacity, int element) {
    // Step 1: Check if space is available
    if (size >= capacity) {
        cout << "Error: Array is full! Cannot insert " << element << endl;
        return false;
    }
    
    // Step 2: Add element at the end (current size is the next available index)
    arr[size] = element;
    
    // Step 3: Increment size
    size++;
    
    cout << "Inserted " << element << " at end. ";
    return true;
}

// ============================================================================
// OPERATION 2: Insert at Beginning
// ============================================================================
// Algorithm:
// 1. Check if array has space
// 2. Shift ALL elements one position to the right
//    - Start from the last element, move towards first
//    - This prevents overwriting elements
// 3. Place new element at index 0
// 4. Increment size
// 
// Time Complexity: O(n) - Must shift all n elements
// Space Complexity: O(1)
// 
// Visual Example: Insert 5 at beginning of [10, 20, 30]
// 
// Before:  [10, 20, 30, _, _]  (size=3, capacity=5)
// Step 2a: [10, 20, 30, 30, _] (shift 30)
// Step 2b: [10, 20, 20, 30, _] (shift 20)
// Step 2c: [10, 10, 20, 30, _] (shift 10)
// Step 3:  [5, 10, 20, 30, _]  (insert 5 at index 0)
// After:   size = 4
// ============================================================================
bool insertAtBeginning(int arr[], int& size, int capacity, int element) {
    // Step 1: Check space
    if (size >= capacity) {
        cout << "Error: Array is full! Cannot insert " << element << endl;
        return false;
    }
    
    // Step 2: Shift all elements to the right
    // IMPORTANT: Start from END and move backwards to avoid overwriting
    for (int i = size - 1; i >= 0; i--) {
        arr[i + 1] = arr[i];
    }
    
    // Step 3: Insert at index 0
    arr[0] = element;
    
    // Step 4: Increment size
    size++;
    
    cout << "Inserted " << element << " at beginning. ";
    return true;
}

// ============================================================================
// OPERATION 3: Insert at Specific Position
// ============================================================================
// Algorithm:
// 1. Validate position (0 <= position <= size)
// 2. Check if array has space
// 3. Shift elements from 'position' to 'size-1' one position right
// 4. Place new element at 'position'
// 5. Increment size
// 
// Time Complexity: O(n) - Worst case shifts n elements
// Space Complexity: O(1)
// 
// Visual Example: Insert 25 at position 2 in [10, 20, 30, 40]
// 
// Before:  [10, 20, 30, 40, _, _]  (size=4, position=2)
// Step 3a: [10, 20, 30, 40, 40, _] (shift 40)
// Step 3b: [10, 20, 30, 30, 40, _] (shift 30)
// Step 4:  [10, 20, 25, 30, 40, _] (insert 25 at position 2)
// After:   size = 5
// ============================================================================
bool insertAtPosition(int arr[], int& size, int capacity, int position, int element) {
    // Step 1: Validate position
    if (position < 0 || position > size) {
        cout << "Error: Invalid position " << position << "! Valid range: 0 to " << size << endl;
        return false;
    }
    
    // Step 2: Check space
    if (size >= capacity) {
        cout << "Error: Array is full! Cannot insert " << element << endl;
        return false;
    }
    
    // Step 3: Shift elements to the right starting from end
    for (int i = size - 1; i >= position; i--) {
        arr[i + 1] = arr[i];
    }
    
    // Step 4: Insert element at position
    arr[position] = element;
    
    // Step 5: Increment size
    size++;
    
    cout << "Inserted " << element << " at position " << position << ". ";
    return true;
}

// ============================================================================
// OPERATION 4: Insert in Sorted Array (Maintain Sorted Order)
// ============================================================================
// Algorithm:
// 1. Find correct position where element should be inserted
//    - Element should be greater than all elements before it
// 2. Shift elements from that position to end
// 3. Insert element
// 
// Time Complexity: O(n) - Search + Shift both O(n)
// Space Complexity: O(1)
// 
// Example: Insert 25 in sorted [10, 20, 30, 40, 50]
// - Compare 25 > 10 ✓, 25 > 20 ✓, 25 > 30 ✗
// - Position found: 2 (between 20 and 30)
// - Result: [10, 20, 25, 30, 40, 50]
// ============================================================================
bool insertInSortedArray(int arr[], int& size, int capacity, int element) {
    // Check space
    if (size >= capacity) {
        cout << "Error: Array is full!" << endl;
        return false;
    }
    
    // Step 1: Find the correct position
    int position = 0;
    while (position < size && arr[position] < element) {
        position++;
    }
    
    // Step 2-3: Use our existing function to insert at found position
    cout << "Found position " << position << " for " << element << ". ";
    
    // Shift elements
    for (int i = size - 1; i >= position; i--) {
        arr[i + 1] = arr[i];
    }
    
    // Insert element
    arr[position] = element;
    size++;
    
    return true;
}

// ============================================================================
// MAIN FUNCTION - Demonstrates All Insertion Operations
// ============================================================================
int main() {
    cout << "============================================" << endl;
    cout << "   ARRAY INSERTION OPERATIONS DEMO" << endl;
    cout << "============================================" << endl;
    
    // Create array with capacity 10
    const int CAPACITY = 10;
    int arr[CAPACITY];
    int size = 0;  // Current number of elements
    
    // ========================================
    // 1. Insert at End
    // ========================================
    cout << "\n=== Insert at End ===" << endl;
    cout << "Initial array (empty): ";
    printArray(arr, size);
    
    insertAtEnd(arr, size, CAPACITY, 10);
    printArray(arr, size);
    
    insertAtEnd(arr, size, CAPACITY, 20);
    printArray(arr, size);
    
    insertAtEnd(arr, size, CAPACITY, 30);
    printArray(arr, size);
    
    // ========================================
    // 2. Insert at Beginning
    // ========================================
    cout << "\n=== Insert at Beginning ===" << endl;
    cout << "Current array: ";
    printArray(arr, size);
    
    insertAtBeginning(arr, size, CAPACITY, 5);
    cout << "After inserting 5: ";
    printArray(arr, size);
    
    insertAtBeginning(arr, size, CAPACITY, 1);
    cout << "After inserting 1: ";
    printArray(arr, size);
    
    // ========================================
    // 3. Insert at Specific Position
    // ========================================
    cout << "\n=== Insert at Specific Position ===" << endl;
    cout << "Current array: ";
    printArray(arr, size);
    
    // Insert 15 at position 3 (between 10 and 20)
    insertAtPosition(arr, size, CAPACITY, 3, 15);
    cout << "After inserting 15 at position 3: ";
    printArray(arr, size);
    
    // Insert 25 at position 5 (between 20 and 30)
    insertAtPosition(arr, size, CAPACITY, 5, 25);
    cout << "After inserting 25 at position 5: ";
    printArray(arr, size);
    
    // Test invalid position
    cout << "\nTesting invalid position: ";
    insertAtPosition(arr, size, CAPACITY, 20, 100);
    
    // ========================================
    // 4. Insert in Sorted Array
    // ========================================
    cout << "\n=== Insert in Sorted Array ===" << endl;
    
    // Create a new sorted array for this demo
    int sortedArr[CAPACITY] = {10, 20, 40, 50, 60};
    int sortedSize = 5;
    
    cout << "Sorted array: ";
    printArray(sortedArr, sortedSize);
    
    insertInSortedArray(sortedArr, sortedSize, CAPACITY, 30);
    cout << "After inserting 30: ";
    printArray(sortedArr, sortedSize);
    
    insertInSortedArray(sortedArr, sortedSize, CAPACITY, 5);
    cout << "After inserting 5: ";
    printArray(sortedArr, sortedSize);
    
    insertInSortedArray(sortedArr, sortedSize, CAPACITY, 70);
    cout << "After inserting 70: ";
    printArray(sortedArr, sortedSize);
    
    // ========================================
    // 5. Test Array Full Condition
    // ========================================
    cout << "\n=== Testing Array Full Condition ===" << endl;
    
    int smallArr[3] = {1, 2, 3};
    int smallSize = 3;
    
    cout << "Array (capacity 3): ";
    printArray(smallArr, smallSize);
    
    cout << "Trying to insert 4: ";
    insertAtEnd(smallArr, smallSize, 3, 4);
    
    cout << "\n============================================" << endl;
    cout << "   INSERTION OPERATIONS SUMMARY" << endl;
    cout << "============================================" << endl;
    cout << "| Operation        | Time Complexity |" << endl;
    cout << "|------------------|-----------------|" << endl;
    cout << "| Insert at End    | O(1)            |" << endl;
    cout << "| Insert at Start  | O(n)            |" << endl;
    cout << "| Insert at Pos i  | O(n)            |" << endl;
    cout << "| Insert in Sorted | O(n)            |" << endl;
    cout << "============================================" << endl;
    
    return 0;
}
