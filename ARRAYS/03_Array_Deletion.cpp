/*
 * ============================================================================
 * FILE: 03_Array_Deletion.cpp
 * ============================================================================
 * 
 * ARRAY DELETION OPERATIONS
 * 
 * Deletion requires shifting elements to fill the gap.
 * 
 * | Deletion Position | Time Complexity |
 * |-------------------|-----------------|
 * | At End            | O(1)            |
 * | At Beginning      | O(n)            |
 * | At Position i     | O(n)            |
 * | By Value          | O(n)            |
 * 
 * ============================================================================
 */

#include <iostream>
using namespace std;

// Utility: Print Array
void printArray(int arr[], int size) {
    if (size == 0) { cout << "[empty]" << endl; return; }
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ============================================================================
// OPERATION 1: Delete from End - O(1)
// Simply decrement size
// ============================================================================
bool deleteFromEnd(int arr[], int& size) {
    if (size <= 0) {
        cout << "Error: Array is empty!" << endl;
        return false;
    }
    int deleted = arr[size - 1];
    size--;
    cout << "Deleted " << deleted << " from end. ";
    return true;
}

// ============================================================================
// OPERATION 2: Delete from Beginning - O(n)
// Shift all elements left by one position
// ============================================================================
bool deleteFromBeginning(int arr[], int& size) {
    if (size <= 0) {
        cout << "Error: Array is empty!" << endl;
        return false;
    }
    int deleted = arr[0];
    // Shift elements left
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
    cout << "Deleted " << deleted << " from beginning. ";
    return true;
}

// ============================================================================
// OPERATION 3: Delete from Position - O(n)
// Shift elements from position+1 onwards to the left
// ============================================================================
bool deleteFromPosition(int arr[], int& size, int pos) {
    if (size <= 0) {
        cout << "Error: Array is empty!" << endl;
        return false;
    }
    if (pos < 0 || pos >= size) {
        cout << "Error: Invalid position!" << endl;
        return false;
    }
    int deleted = arr[pos];
    for (int i = pos; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
    cout << "Deleted " << deleted << " from position " << pos << ". ";
    return true;
}

// ============================================================================
// OPERATION 4: Delete by Value (First Occurrence) - O(n)
// Search for element, then shift to remove
// ============================================================================
bool deleteByValue(int arr[], int& size, int value) {
    if (size <= 0) return false;
    
    // Find the element
    int pos = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) { pos = i; break; }
    }
    if (pos == -1) {
        cout << "Element " << value << " not found!" << endl;
        return false;
    }
    
    // Shift and remove
    for (int i = pos; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
    cout << "Deleted " << value << " from position " << pos << ". ";
    return true;
}

// ============================================================================
// OPERATION 5: Delete All Occurrences - O(n)
// Use two-pointer technique for in-place deletion
// ============================================================================
int deleteAllOccurrences(int arr[], int& size, int value) {
    int write = 0, count = 0;
    for (int read = 0; read < size; read++) {
        if (arr[read] != value) {
            arr[write++] = arr[read];
        } else {
            count++;
        }
    }
    size = write;
    cout << "Deleted " << count << " occurrence(s) of " << value << ". ";
    return count;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    cout << "=== ARRAY DELETION OPERATIONS ===" << endl;
    
    // Delete from End
    cout << "\n--- Delete from End ---" << endl;
    int arr1[] = {10, 20, 30, 40, 50}; int size1 = 5;
    printArray(arr1, size1);
    deleteFromEnd(arr1, size1);
    printArray(arr1, size1);
    
    // Delete from Beginning
    cout << "\n--- Delete from Beginning ---" << endl;
    int arr2[] = {10, 20, 30, 40, 50}; int size2 = 5;
    printArray(arr2, size2);
    deleteFromBeginning(arr2, size2);
    printArray(arr2, size2);
    
    // Delete from Position
    cout << "\n--- Delete from Position ---" << endl;
    int arr3[] = {10, 20, 30, 40, 50}; int size3 = 5;
    printArray(arr3, size3);
    deleteFromPosition(arr3, size3, 2);
    printArray(arr3, size3);
    
    // Delete by Value
    cout << "\n--- Delete by Value ---" << endl;
    int arr4[] = {10, 20, 30, 20, 40}; int size4 = 5;
    printArray(arr4, size4);
    deleteByValue(arr4, size4, 20);
    printArray(arr4, size4);
    
    // Delete All Occurrences
    cout << "\n--- Delete All Occurrences ---" << endl;
    int arr5[] = {10, 30, 20, 30, 30, 40}; int size5 = 6;
    printArray(arr5, size5);
    deleteAllOccurrences(arr5, size5, 30);
    printArray(arr5, size5);
    
    return 0;
}
