/*
 * ============================================================================
 * FILE: 04_Searching.cpp
 * ============================================================================
 *
 * ARRAY SEARCHING ALGORITHMS
 *
 * ┌──────────────────────┬──────────┬─────────┬───────────────────────────┐
 * │ Algorithm            │ Time     │ Space   │ Prerequisite              │
 * ├──────────────────────┼──────────┼─────────┼───────────────────────────┤
 * │ Linear Search        │ O(n)     │ O(1)    │ None                      │
 * │ Binary Search (iter) │ O(log n) │ O(1)    │ Sorted array              │
 * │ Binary Search (rec)  │ O(log n) │ O(logn) │ Sorted array              │
 * │ Ternary Search       │ O(log₃n) │ O(1)    │ Sorted array              │
 * │ First/Last Occur.    │ O(log n) │ O(1)    │ Sorted array              │
 * │ Count Occurrences    │ O(log n) │ O(1)    │ Sorted array              │
 * └──────────────────────┴──────────┴─────────┴───────────────────────────┘
 *
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// UTILITY: Print Array
// ─────────────────────────────────────────────────────────────────────────────
void printArray(const int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]";
}

// ─────────────────────────────────────────────────────────────────────────────
// 1. LINEAR SEARCH — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Scan left to right. Return index on first match, −1 if not found.
//   Works on ANY array (sorted or unsorted).
// ─────────────────────────────────────────────────────────────────────────────
int linearSearch(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────────────────────
// 2. BINARY SEARCH (Iterative) — O(log n)
// ─────────────────────────────────────────────────────────────────────────────
//   Requires: SORTED array.
//
//   Algorithm:
//     lo = 0,  hi = size−1
//     while lo ≤ hi:
//       mid = lo + (hi−lo)/2          ← prevents integer overflow
//       if arr[mid] == target → found
//       if target < arr[mid]  → hi = mid−1  (search LEFT half)
//       if target > arr[mid]  → lo = mid+1  (search RIGHT half)
//
//   Example: search 30 in [10, 20, 30, 40, 50]
//     lo=0 hi=4 mid=2 → arr[2]=30 ✓ found at index 2
// ─────────────────────────────────────────────────────────────────────────────
int binarySearch(const int arr[], int size, int target) {
    int lo = 0, hi = size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (target < arr[mid]) hi = mid - 1;
        else                        lo = mid + 1;
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────────────────────
// 3. BINARY SEARCH (Recursive) — O(log n) time, O(log n) stack space
// ─────────────────────────────────────────────────────────────────────────────
int binarySearchRec(const int arr[], int lo, int hi, int target) {
    if (lo > hi) return -1;                   // base case: not found

    int mid = lo + (hi - lo) / 2;
    if (arr[mid] == target) return mid;
    if (target < arr[mid]) return binarySearchRec(arr, lo, mid - 1, target);
    return binarySearchRec(arr, mid + 1, hi, target);
}

// ─────────────────────────────────────────────────────────────────────────────
// 4. TERNARY SEARCH — O(log₃ n)
// ─────────────────────────────────────────────────────────────────────────────
//   Split the range into THREE parts instead of two.
//   Slightly more comparisons per step than binary search,
//   but useful in some unimodal-function optimization problems.
//
//     mid1 = lo + (hi−lo)/3
//     mid2 = hi − (hi−lo)/3
// ─────────────────────────────────────────────────────────────────────────────
int ternarySearch(const int arr[], int lo, int hi, int target) {
    while (lo <= hi) {
        int mid1 = lo + (hi - lo) / 3;
        int mid2 = hi - (hi - lo) / 3;

        if (arr[mid1] == target) return mid1;
        if (arr[mid2] == target) return mid2;

        if (target < arr[mid1])       hi = mid1 - 1;
        else if (target > arr[mid2])  lo = mid2 + 1;
        else { lo = mid1 + 1; hi = mid2 - 1; }
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────────────────────
// 5. FIRST OCCURRENCE (in sorted array with duplicates) — O(log n)
// ─────────────────────────────────────────────────────────────────────────────
//   On finding target, record answer but keep searching LEFT (hi = mid−1)
//   to find an even earlier occurrence.
// ─────────────────────────────────────────────────────────────────────────────
int findFirstOccurrence(const int arr[], int size, int target) {
    int lo = 0, hi = size - 1, result = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) { result = mid; hi = mid - 1; }
        else if (target < arr[mid]) hi = mid - 1;
        else                        lo = mid + 1;
    }
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// 6. LAST OCCURRENCE — O(log n)
// ─────────────────────────────────────────────────────────────────────────────
//   Same idea, but keep searching RIGHT (lo = mid+1) after a match.
// ─────────────────────────────────────────────────────────────────────────────
int findLastOccurrence(const int arr[], int size, int target) {
    int lo = 0, hi = size - 1, result = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) { result = mid; lo = mid + 1; }
        else if (target < arr[mid]) hi = mid - 1;
        else                        lo = mid + 1;
    }
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// 7. COUNT OCCURRENCES — O(log n)
// ─────────────────────────────────────────────────────────────────────────────
//   count = lastIndex − firstIndex + 1   (if found)
// ─────────────────────────────────────────────────────────────────────────────
int countOccurrences(const int arr[], int size, int target) {
    int first = findFirstOccurrence(arr, size, target);
    if (first == -1) return 0;
    return findLastOccurrence(arr, size, target) - first + 1;
}

// ═════════════════════════════════════════════════════════════════════════════
// MAIN — Demonstrate All Search Algorithms
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    cout << "============================================" << endl;
    cout << "   04 · ARRAY SEARCHING ALGORITHMS" << endl;
    cout << "============================================" << endl;

    // ── Linear Search ────────────────────────────────────────────────────
    cout << "\n--- Linear Search ---" << endl;
    int a[] = {45, 12, 67, 23, 89, 34};
    cout << "Array: "; printArray(a, 6); cout << endl;
    cout << "Search 23:  index = " << linearSearch(a, 6, 23)  << endl;
    cout << "Search 100: index = " << linearSearch(a, 6, 100) << endl;

    // ── Binary Search ────────────────────────────────────────────────────
    cout << "\n--- Binary Search ---" << endl;
    int b[] = {10, 20, 30, 40, 50, 60, 70};
    cout << "Sorted: "; printArray(b, 7); cout << endl;
    cout << "Search 40 (iter): index = " << binarySearch(b, 7, 40) << endl;
    cout << "Search 40 (rec):  index = " << binarySearchRec(b, 0, 6, 40) << endl;
    cout << "Search 100:       index = " << binarySearch(b, 7, 100) << endl;

    // ── Ternary Search ───────────────────────────────────────────────────
    cout << "\n--- Ternary Search ---" << endl;
    cout << "Search 60: index = " << ternarySearch(b, 0, 6, 60) << endl;
    cout << "Search 15: index = " << ternarySearch(b, 0, 6, 15) << endl;

    // ── First / Last Occurrence ──────────────────────────────────────────
    cout << "\n--- First / Last Occurrence ---" << endl;
    int c[] = {1, 2, 2, 2, 3, 4, 4, 5};
    cout << "Array: "; printArray(c, 8); cout << endl;
    cout << "First occurrence of 2: " << findFirstOccurrence(c, 8, 2) << endl;
    cout << "Last  occurrence of 2: " << findLastOccurrence(c, 8, 2)  << endl;
    cout << "Count of 2:            " << countOccurrences(c, 8, 2)    << endl;
    cout << "Count of 9 (absent):   " << countOccurrences(c, 8, 9)    << endl;

    cout << "\n============================================" << endl;
    cout << "   Searching Operations Completed!" << endl;
    cout << "============================================" << endl;

    return 0;
}
