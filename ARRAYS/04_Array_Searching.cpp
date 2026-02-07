/*
 * ============================================================================
 * FILE: 04_Array_Searching.cpp
 * ============================================================================
 * 
 * ARRAY SEARCHING ALGORITHMS
 * 
 * Two main approaches:
 * 1. LINEAR SEARCH - Works on any array, O(n)
 * 2. BINARY SEARCH - Requires sorted array, O(log n)
 * 
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ============================================================================
// LINEAR SEARCH - O(n)
// ============================================================================
// Algorithm:
// 1. Start from first element
// 2. Compare each element with target
// 3. If match found, return index
// 4. If end reached, return -1
// 
// Works on: UNSORTED or SORTED arrays
// ============================================================================
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Found at index i
        }
    }
    return -1;  // Not found
}

// ============================================================================
// BINARY SEARCH (Iterative) - O(log n)
// ============================================================================
// Algorithm:
// 1. Set low = 0, high = size-1
// 2. Find mid = (low + high) / 2
// 3. If arr[mid] == target, return mid
// 4. If target < arr[mid], search left half (high = mid-1)
// 5. If target > arr[mid], search right half (low = mid+1)
// 6. Repeat until low <= high
// 
// REQUIRES: Array must be SORTED
// 
// Example: Search 23 in [10, 15, 20, 23, 30, 35, 40]
// Step 1: low=0, high=6, mid=3, arr[3]=23 ✓ Found!
// ============================================================================
int binarySearchIterative(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;  // Prevents overflow
        
        if (arr[mid] == target) {
            return mid;  // Found
        }
        else if (target < arr[mid]) {
            high = mid - 1;  // Search left half
        }
        else {
            low = mid + 1;   // Search right half
        }
    }
    return -1;  // Not found
}

// ============================================================================
// BINARY SEARCH (Recursive) - O(log n)
// ============================================================================
int binarySearchRecursive(int arr[], int low, int high, int target) {
    // Base case: element not found
    if (low > high) return -1;
    
    int mid = low + (high - low) / 2;
    
    if (arr[mid] == target) {
        return mid;
    }
    else if (target < arr[mid]) {
        return binarySearchRecursive(arr, low, mid - 1, target);
    }
    else {
        return binarySearchRecursive(arr, mid + 1, high, target);
    }
}

// ============================================================================
// FIND FIRST OCCURRENCE - O(log n)
// Used when duplicates exist
// ============================================================================
int findFirstOccurrence(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    int result = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == target) {
            result = mid;      // Possible answer
            high = mid - 1;    // Keep searching left
        }
        else if (target < arr[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return result;
}

// ============================================================================
// FIND LAST OCCURRENCE - O(log n)
// ============================================================================
int findLastOccurrence(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    int result = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == target) {
            result = mid;      // Possible answer
            low = mid + 1;     // Keep searching right
        }
        else if (target < arr[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return result;
}

// ============================================================================
// COUNT OCCURRENCES - O(log n)
// ============================================================================
int countOccurrences(int arr[], int size, int target) {
    int first = findFirstOccurrence(arr, size, target);
    if (first == -1) return 0;
    int last = findLastOccurrence(arr, size, target);
    return last - first + 1;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    cout << "=== ARRAY SEARCHING ALGORITHMS ===" << endl;
    
    // Linear Search Demo
    cout << "\n--- Linear Search ---" << endl;
    int arr1[] = {45, 12, 67, 23, 89, 34};
    int size1 = 6;
    cout << "Array: [45, 12, 67, 23, 89, 34]" << endl;
    cout << "Search 23: Index = " << linearSearch(arr1, size1, 23) << endl;
    cout << "Search 100: Index = " << linearSearch(arr1, size1, 100) << endl;
    
    // Binary Search Demo
    cout << "\n--- Binary Search ---" << endl;
    int arr2[] = {10, 20, 30, 40, 50, 60, 70};
    int size2 = 7;
    cout << "Sorted Array: [10, 20, 30, 40, 50, 60, 70]" << endl;
    cout << "Search 40 (Iterative): Index = " << binarySearchIterative(arr2, size2, 40) << endl;
    cout << "Search 40 (Recursive): Index = " << binarySearchRecursive(arr2, 0, size2-1, 40) << endl;
    cout << "Search 100: Index = " << binarySearchIterative(arr2, size2, 100) << endl;
    
    // First/Last Occurrence Demo
    cout << "\n--- First/Last Occurrence ---" << endl;
    int arr3[] = {1, 2, 2, 2, 3, 4, 4, 5};
    int size3 = 8;
    cout << "Array: [1, 2, 2, 2, 3, 4, 4, 5]" << endl;
    cout << "First occurrence of 2: " << findFirstOccurrence(arr3, size3, 2) << endl;
    cout << "Last occurrence of 2: " << findLastOccurrence(arr3, size3, 2) << endl;
    cout << "Count of 2: " << countOccurrences(arr3, size3, 2) << endl;
    
    // Complexity Summary
    cout << "\n=== COMPLEXITY SUMMARY ===" << endl;
    cout << "| Algorithm      | Time     | Space |" << endl;
    cout << "|----------------|----------|-------|" << endl;
    cout << "| Linear Search  | O(n)     | O(1)  |" << endl;
    cout << "| Binary Search  | O(log n) | O(1)  |" << endl;
    
    return 0;
}
