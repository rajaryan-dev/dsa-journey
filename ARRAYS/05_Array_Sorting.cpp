/*
 * ============================================================================
 * FILE: 05_Array_Sorting.cpp
 * ============================================================================
 * 
 * BASIC SORTING ALGORITHMS
 * 
 * | Algorithm      | Best    | Average | Worst   | Space | Stable |
 * |----------------|---------|---------|---------|-------|--------|
 * | Bubble Sort    | O(n)    | O(n²)   | O(n²)   | O(1)  | Yes    |
 * | Selection Sort | O(n²)   | O(n²)   | O(n²)   | O(1)  | No     |
 * | Insertion Sort | O(n)    | O(n²)   | O(n²)   | O(1)  | Yes    |
 * 
 * Stable: Maintains relative order of equal elements
 * 
 * ============================================================================
 */

#include <iostream>
using namespace std;

// Utility Functions
void printArray(int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// ============================================================================
// BUBBLE SORT - O(n²)
// ============================================================================
// Algorithm:
// 1. Compare adjacent elements
// 2. Swap if first > second
// 3. Repeat for all elements (largest "bubbles up" to end)
// 4. Repeat for remaining unsorted portion
// 
// Optimization: If no swaps in a pass, array is already sorted
// ============================================================================
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        
        // Last i elements are already sorted
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // Optimization: If no swapping, array is sorted
        if (!swapped) break;
    }
}

// ============================================================================
// SELECTION SORT - O(n²)
// ============================================================================
// Algorithm:
// 1. Find minimum element in unsorted portion
// 2. Swap it with first element of unsorted portion
// 3. Move boundary of sorted portion one step right
// 4. Repeat until entire array is sorted
// ============================================================================
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        // Find minimum in unsorted portion [i, size-1]
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap minimum with first unsorted element
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// ============================================================================
// INSERTION SORT - O(n²)
// ============================================================================
// Algorithm (like sorting cards in hand):
// 1. Start with second element (first is "sorted")
// 2. Pick current element as "key"
// 3. Shift larger elements in sorted portion to the right
// 4. Insert key at correct position
// 5. Repeat for all elements
// 
// Best for: Nearly sorted arrays or small arrays
// ============================================================================
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];  // Element to insert
        int j = i - 1;
        
        // Shift elements greater than key to the right
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // Insert key at correct position
        arr[j + 1] = key;
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    cout << "=== SORTING ALGORITHMS DEMO ===" << endl;
    
    // Bubble Sort
    cout << "\n--- Bubble Sort ---" << endl;
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int size1 = 7;
    cout << "Before: "; printArray(arr1, size1);
    bubbleSort(arr1, size1);
    cout << "After:  "; printArray(arr1, size1);
    
    // Selection Sort
    cout << "\n--- Selection Sort ---" << endl;
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    int size2 = 7;
    cout << "Before: "; printArray(arr2, size2);
    selectionSort(arr2, size2);
    cout << "After:  "; printArray(arr2, size2);
    
    // Insertion Sort
    cout << "\n--- Insertion Sort ---" << endl;
    int arr3[] = {64, 34, 25, 12, 22, 11, 90};
    int size3 = 7;
    cout << "Before: "; printArray(arr3, size3);
    insertionSort(arr3, size3);
    cout << "After:  "; printArray(arr3, size3);
    
    // Nearly Sorted Array (Insertion Sort shines here)
    cout << "\n--- Insertion Sort on Nearly Sorted ---" << endl;
    int arr4[] = {1, 2, 4, 3, 5, 6, 7};
    int size4 = 7;
    cout << "Before: "; printArray(arr4, size4);
    insertionSort(arr4, size4);
    cout << "After:  "; printArray(arr4, size4);
    
    cout << "\n=== WHEN TO USE WHICH? ===" << endl;
    cout << "Bubble Sort: Educational, rarely used in practice" << endl;
    cout << "Selection Sort: When memory writes are expensive" << endl;
    cout << "Insertion Sort: Small/nearly sorted arrays, online sorting" << endl;
    
    return 0;
}
