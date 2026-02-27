/*
 * ============================================================================
 * FILE: 01_Basics.cpp
 * ============================================================================
 *
 * ARRAYS — Introduction & Fundamental Operations
 *
 * An array is a collection of elements of the SAME data type stored in
 * CONTIGUOUS (adjacent) memory locations.
 *
 *   Memory Layout for int arr[5] = {10, 20, 30, 40, 50}:
 *
 *     Index:    [0]    [1]    [2]    [3]    [4]
 *     Value:     10     20     30     40     50
 *     Address: 1000   1004   1008   1012   1016   (4 bytes per int)
 *
 * ┌────────────────────────────────────────────────────────────────────┐
 * │  COMPLEXITY CHEAT-SHEET                                          │
 * ├───────────────────────┬──────────┬────────────────────────────────┤
 * │ Operation             │ Time     │ Notes                         │
 * ├───────────────────────┼──────────┼────────────────────────────────┤
 * │ Access by index       │ O(1)     │ Direct jump via base + offset │
 * │ Search (unsorted)     │ O(n)     │ Must scan every element       │
 * │ Insert at end         │ O(1)*    │ *Assuming space available     │
 * │ Insert at beginning   │ O(n)     │ Shift all elements right      │
 * │ Delete at end         │ O(1)     │ Just decrement size           │
 * │ Delete at beginning   │ O(n)     │ Shift all elements left       │
 * │ Reverse               │ O(n)     │ Two-pointer swap              │
 * │ Check if sorted       │ O(n)     │ Single pass comparison        │
 * └───────────────────────┴──────────┴────────────────────────────────┘
 *
 * WHY USE ARRAYS?
 *   1. O(1) random access via index
 *   2. Cache-friendly — contiguous memory = faster CPU cache hits
 *   3. Foundation for stacks, queues, heaps, hash tables
 *
 * LIMITATIONS:
 *   1. Fixed size (static arrays can't grow at runtime)
 *   2. O(n) insert/delete — elements must shift
 *   3. Wasted memory if not fully utilized
 *
 * ============================================================================
 */

#include <climits>   // INT_MIN, INT_MAX
#include <iostream>
#include <utility>   // std::swap

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// UTILITY: Print Array
// Time: O(n)   Space: O(1)
// ─────────────────────────────────────────────────────────────────────────────
void printArray(const int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 1: Find Length of Array (compile-time only)
// ─────────────────────────────────────────────────────────────────────────────
// sizeof(arr) / sizeof(arr[0])  works ONLY in the scope where the array
// was declared. Arrays decay to pointers when passed to functions, losing
// their size info. Always pass size as a separate parameter.
// ─────────────────────────────────────────────────────────────────────────────
void demonstrateFindLength() {
    cout << "\n=== Finding Array Length ===" << endl;

    int arr[] = {10, 20, 30, 40, 50};
    int length = sizeof(arr) / sizeof(arr[0]);

    cout << "Array:            "; printArray(arr, length);
    cout << "Total bytes:      " << sizeof(arr)    << endl;
    cout << "Bytes per element: " << sizeof(arr[0]) << endl;
    cout << "Length:           " << length          << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 2: Traverse Array
// Time: O(n)   Space: O(1)
// Three common traversal techniques in C++.
// ─────────────────────────────────────────────────────────────────────────────
void traverseArray(const int arr[], int size) {
    cout << "\n=== Array Traversal ===" << endl;

    // Method 1: Index-based for loop (most common)
    cout << "Index-based:   ";
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;

    // Method 2: Pointer arithmetic
    cout << "Pointer-based: ";
    const int* ptr = arr;
    for (int i = 0; i < size; i++) cout << *(ptr + i) << " ";
    cout << endl;

    // Method 3: Range-based for (only when size is known at compile time)
    // Cannot demo here since arr[] decayed to pointer.
    // Usage:  int local[] = {1,2,3}; for (int x : local) cout << x;
    cout << "(Range-based for: available when size is known at compile time)" << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 3: Find Maximum Element
// ─────────────────────────────────────────────────────────────────────────────
// Algorithm:
//   1. Assume arr[0] is the maximum.
//   2. Compare with every remaining element.
//   3. Update max whenever a larger value is found.
//
// Time: O(n)   Space: O(1)
// ─────────────────────────────────────────────────────────────────────────────
int findMax(const int arr[], int size) {
    if (size <= 0) return INT_MIN;            // edge case

    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 4: Find Minimum Element
// Time: O(n)   Space: O(1)
// ─────────────────────────────────────────────────────────────────────────────
int findMin(const int arr[], int size) {
    if (size <= 0) return INT_MAX;

    int minVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
    }
    return minVal;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 5: Sum of All Elements
// Time: O(n)   Space: O(1)
// ─────────────────────────────────────────────────────────────────────────────
long long calculateSum(const int arr[], int size) {
    long long sum = 0;                        // long long to avoid overflow
    for (int i = 0; i < size; i++) sum += arr[i];
    return sum;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 6: Average of Elements
// Time: O(n)   Space: O(1)
// ─────────────────────────────────────────────────────────────────────────────
double calculateAverage(const int arr[], int size) {
    if (size <= 0) return 0.0;
    return static_cast<double>(calculateSum(arr, size)) / size;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 7: Reverse Array (In-Place, Two-Pointer)
// ─────────────────────────────────────────────────────────────────────────────
//   Before: [1, 2, 3, 4, 5]
//           ↑start        ↑end      → swap 1 & 5
//           [5, 2, 3, 4, 1]
//              ↑start  ↑end         → swap 2 & 4
//           [5, 4, 3, 2, 1]
//                 ↑↑                → start >= end → STOP
//
// Time: O(n/2) = O(n)   Space: O(1)
// ─────────────────────────────────────────────────────────────────────────────
void reverseArray(int arr[], int size) {
    int lo = 0, hi = size - 1;
    while (lo < hi) {
        swap(arr[lo], arr[hi]);               // std::swap
        lo++;
        hi--;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 8: Copy Array
// Time: O(n)   Space: O(n) for destination
// ─────────────────────────────────────────────────────────────────────────────
void copyArray(const int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) dest[i] = src[i];
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 9: Check if Array is Sorted (Non-Decreasing)
// ─────────────────────────────────────────────────────────────────────────────
// Scan once: if any arr[i] > arr[i+1], it's NOT sorted.
//
// Time: O(n)   Space: O(1)
// ─────────────────────────────────────────────────────────────────────────────
bool isSorted(const int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 10: Remove Duplicates from Sorted Array (In-Place)
// ─────────────────────────────────────────────────────────────────────────────
//   Two-pointer approach:
//     write = 0 (last unique position)
//     read  = 1..n-1
//   If arr[read] != arr[write], advance write and copy.
//
//   Before: [1, 1, 2, 2, 3, 4, 4]        (size = 7)
//   After:  [1, 2, 3, 4, -, -, -]        (new size = 4)
//
// Time: O(n)   Space: O(1)
// ─────────────────────────────────────────────────────────────────────────────
int removeDuplicates(int arr[], int size) {
    if (size <= 1) return size;

    int write = 0;
    for (int read = 1; read < size; read++) {
        if (arr[read] != arr[write]) {
            write++;
            arr[write] = arr[read];
        }
    }
    return write + 1;                         // new logical size
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 11: Second Largest Element
// ─────────────────────────────────────────────────────────────────────────────
//   Single-pass: track both largest and secondLargest.
//
// Time: O(n)   Space: O(1)
// ─────────────────────────────────────────────────────────────────────────────
int secondLargest(const int arr[], int size) {
    if (size < 2) return INT_MIN;

    int first = INT_MIN, second = INT_MIN;
    for (int i = 0; i < size; i++) {
        if (arr[i] > first) {
            second = first;
            first = arr[i];
        } else if (arr[i] > second && arr[i] != first) {
            second = arr[i];
        }
    }
    return second;   // INT_MIN if no distinct second largest
}

// ═════════════════════════════════════════════════════════════════════════════
// MAIN — Demonstrate All Operations
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    cout << "============================================" << endl;
    cout << "   01 · ARRAY BASICS — All Operations" << endl;
    cout << "============================================" << endl;

    // ── 1. Declaration & Initialization ──────────────────────────────────
    cout << "\n=== Declaration & Initialization ===" << endl;

    int a1[5];                                // uninitialized
    a1[0] = 10; a1[1] = 20; a1[2] = 30; a1[3] = 40; a1[4] = 50;
    cout << "Individual assign: "; printArray(a1, 5);

    int a2[] = {5, 15, 25, 35, 45};          // size auto-deduced
    cout << "Initializer list:  "; printArray(a2, 5);

    int a3[5] = {1, 2};                      // rest become 0
    cout << "Partial init:      "; printArray(a3, 5);

    int a4[5] = {};                           // all zeros
    cout << "All zeros:         "; printArray(a4, 5);

    // ── 2. Find Length ───────────────────────────────────────────────────
    demonstrateFindLength();

    // ── 3. Traversal ────────────────────────────────────────────────────
    int nums[] = {100, 200, 300, 400, 500};
    traverseArray(nums, 5);

    // ── 4. Max & Min ────────────────────────────────────────────────────
    cout << "\n=== Max & Min ===" << endl;
    int data[] = {23, 45, 12, 67, 34, 89, 11};
    int dataSz = 7;
    cout << "Array:   "; printArray(data, dataSz);
    cout << "Max:     " << findMax(data, dataSz) << endl;
    cout << "Min:     " << findMin(data, dataSz) << endl;

    // ── 5. Sum & Average ────────────────────────────────────────────────
    cout << "\n=== Sum & Average ===" << endl;
    int vals[] = {10, 20, 30, 40, 50};
    int valsSz = 5;
    cout << "Array:   "; printArray(vals, valsSz);
    cout << "Sum:     " << calculateSum(vals, valsSz)     << endl;
    cout << "Average: " << calculateAverage(vals, valsSz) << endl;

    // ── 6. Reverse ──────────────────────────────────────────────────────
    cout << "\n=== Reverse ===" << endl;
    int rev[] = {1, 2, 3, 4, 5};
    cout << "Before:  "; printArray(rev, 5);
    reverseArray(rev, 5);
    cout << "After:   "; printArray(rev, 5);

    // ── 7. Copy ─────────────────────────────────────────────────────────
    cout << "\n=== Copy ===" << endl;
    int src[] = {11, 22, 33, 44, 55};
    int dst[5];
    copyArray(src, dst, 5);
    cout << "Source:  "; printArray(src, 5);
    cout << "Copied:  "; printArray(dst, 5);

    // ── 8. Is Sorted? ───────────────────────────────────────────────────
    cout << "\n=== Check Sorted ===" << endl;
    int s1[] = {1, 3, 5, 7, 9};
    int s2[] = {1, 5, 3, 7, 9};
    cout << "{1,3,5,7,9} sorted? " << (isSorted(s1, 5) ? "YES" : "NO") << endl;
    cout << "{1,5,3,7,9} sorted? " << (isSorted(s2, 5) ? "YES" : "NO") << endl;

    // ── 9. Remove Duplicates (sorted array) ─────────────────────────────
    cout << "\n=== Remove Duplicates (Sorted) ===" << endl;
    int dup[] = {1, 1, 2, 2, 3, 4, 4};
    int dupSz = 7;
    cout << "Before:  "; printArray(dup, dupSz);
    dupSz = removeDuplicates(dup, dupSz);
    cout << "After:   "; printArray(dup, dupSz);

    // ── 10. Second Largest ──────────────────────────────────────────────
    cout << "\n=== Second Largest ===" << endl;
    int sl[] = {12, 35, 1, 10, 34, 1};
    cout << "Array:   "; printArray(sl, 6);
    cout << "2nd Max: " << secondLargest(sl, 6) << endl;

    cout << "\n============================================" << endl;
    cout << "   All Basic Operations Completed!" << endl;
    cout << "============================================" << endl;

    return 0;
}
