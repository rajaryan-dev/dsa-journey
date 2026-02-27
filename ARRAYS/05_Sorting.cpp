/*
 * ============================================================================
 * FILE: 05_Sorting.cpp
 * ============================================================================
 *
 * SORTING ALGORITHMS (Comparison-Based)
 *
 * ┌─────────────────┬─────────┬─────────┬─────────┬───────┬────────┐
 * │ Algorithm       │ Best    │ Average │ Worst   │ Space │ Stable │
 * ├─────────────────┼─────────┼─────────┼─────────┼───────┼────────┤
 * │ Bubble Sort     │ O(n)    │ O(n²)   │ O(n²)   │ O(1)  │ Yes    │
 * │ Selection Sort  │ O(n²)   │ O(n²)   │ O(n²)   │ O(1)  │ No     │
 * │ Insertion Sort  │ O(n)    │ O(n²)   │ O(n²)   │ O(1)  │ Yes    │
 * │ Merge Sort      │ O(nlogn)│ O(nlogn)│ O(nlogn)│ O(n)  │ Yes    │
 * │ Quick Sort      │ O(nlogn)│ O(nlogn)│ O(n²)   │ O(logn)│ No    │
 * └─────────────────┴─────────┴─────────┴─────────┴───────┴────────┘
 *
 * Stable = maintains relative order of equal elements.
 *
 * WHEN TO USE WHICH?
 *   • Bubble Sort     → Educational only; rarely used in practice.
 *   • Selection Sort  → When memory writes are expensive.
 *   • Insertion Sort  → Small / nearly-sorted arrays; online sorting.
 *   • Merge Sort      → Guaranteed O(n log n); used for linked lists.
 *   • Quick Sort      → Fastest in practice (cache-friendly); default
 *                        in many standard libraries.
 *
 * ============================================================================
 */

#include <iostream>
#include <utility>   // std::swap

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
    cout << "]" << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// 1. BUBBLE SORT — O(n²)
// ─────────────────────────────────────────────────────────────────────────────
//   Compare adjacent pairs; swap if out of order.
//   After each pass, the largest unsorted element "bubbles" to the end.
//
//   Optimization: if no swaps occur in a full pass, the array is already
//   sorted → break early (O(n) best case for nearly-sorted input).
// ─────────────────────────────────────────────────────────────────────────────
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++) {   // last i already sorted
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;                         // already sorted
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 2. SELECTION SORT — O(n²)
// ─────────────────────────────────────────────────────────────────────────────
//   Find the minimum in the unsorted region, swap it to the front.
//   Repeat, advancing the sorted boundary.
//
//   Pass 0: find min in [0..n-1], swap with arr[0]
//   Pass 1: find min in [1..n-1], swap with arr[1]
//   ...
// ─────────────────────────────────────────────────────────────────────────────
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) swap(arr[i], arr[minIdx]);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 3. INSERTION SORT — O(n²)
// ─────────────────────────────────────────────────────────────────────────────
//   Like sorting playing cards in your hand:
//     Pick the next card (key), shift larger cards right, insert key.
//
//   Best for: nearly sorted arrays or small arrays (< ~20 elements).
// ─────────────────────────────────────────────────────────────────────────────
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 4. MERGE SORT — O(n log n)                          [Divide & Conquer]
// ─────────────────────────────────────────────────────────────────────────────
//   1. Divide the array into two halves.
//   2. Recursively sort each half.
//   3. MERGE the two sorted halves into one sorted array.
//
//                [38, 27, 43, 3, 9, 82, 10]
//               /                           \
//        [38, 27, 43, 3]            [9, 82, 10]
//         /          \               /        \
//     [38, 27]    [43, 3]       [9, 82]     [10]
//      /   \       /   \        /   \
//   [38]  [27]  [43]  [3]   [9]  [82]
//      \   /       \   /      \   /
//     [27, 38]    [3, 43]   [9, 82]     [10]
//         \          /          \        /
//       [3, 27, 38, 43]       [9, 10, 82]
//               \                /
//        [3, 9, 10, 27, 38, 43, 82]
//
//   Time:  O(n log n) always
//   Space: O(n) for temporary arrays
// ─────────────────────────────────────────────────────────────────────────────

// Merge two sorted halves: arr[lo..mid] and arr[mid+1..hi]
void merge(int arr[], int lo, int mid, int hi) {
    int n1 = mid - lo + 1;                    // size of left half
    int n2 = hi - mid;                        // size of right half

    // Create temp arrays
    int* left  = new int[n1];
    int* right = new int[n2];

    for (int i = 0; i < n1; i++) left[i]  = arr[lo + i];
    for (int i = 0; i < n2; i++) right[i] = arr[mid + 1 + i];

    // Merge back into arr[lo..hi]
    int i = 0, j = 0, k = lo;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else                     arr[k++] = right[j++];
    }
    while (i < n1) arr[k++] = left[i++];     // remaining from left
    while (j < n2) arr[k++] = right[j++];    // remaining from right

    delete[] left;
    delete[] right;
}

void mergeSort(int arr[], int lo, int hi) {
    if (lo >= hi) return;                     // base: 0 or 1 element

    int mid = lo + (hi - lo) / 2;
    mergeSort(arr, lo, mid);                  // sort left half
    mergeSort(arr, mid + 1, hi);              // sort right half
    merge(arr, lo, mid, hi);                  // merge sorted halves
}

// ─────────────────────────────────────────────────────────────────────────────
// 5. QUICK SORT — O(n log n) average, O(n²) worst     [Divide & Conquer]
// ─────────────────────────────────────────────────────────────────────────────
//   1. Pick a PIVOT element.
//   2. PARTITION: rearrange so elements < pivot are left, > pivot are right.
//   3. Recursively sort left and right partitions.
//
//   Lomuto Partition (pivot = last element):
//     i tracks the boundary of "≤ pivot" region.
//     j scans from lo to hi−1.
//     If arr[j] <= pivot, swap arr[j] with arr[++i].
//     Finally, swap pivot (arr[hi]) into position i+1.
//
//   Time:  O(n log n) avg, O(n²) worst (already sorted + bad pivot)
//   Space: O(log n) stack frames on average
// ─────────────────────────────────────────────────────────────────────────────
int partition(int arr[], int lo, int hi) {
    int pivot = arr[hi];                      // pick last as pivot
    int i = lo - 1;                           // boundary of ≤ pivot zone

    for (int j = lo; j < hi; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[hi]);                // place pivot in final position
    return i + 1;                             // pivot index
}

void quickSort(int arr[], int lo, int hi) {
    if (lo >= hi) return;

    int pivotIdx = partition(arr, lo, hi);
    quickSort(arr, lo, pivotIdx - 1);         // sort left of pivot
    quickSort(arr, pivotIdx + 1, hi);         // sort right of pivot
}

// ═════════════════════════════════════════════════════════════════════════════
// MAIN — Demonstrate All Sorting Algorithms
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    cout << "============================================" << endl;
    cout << "   05 · SORTING ALGORITHMS" << endl;
    cout << "============================================" << endl;

    // ── Bubble Sort ──────────────────────────────────────────────────────
    cout << "\n--- Bubble Sort ---" << endl;
    int a1[] = {64, 34, 25, 12, 22, 11, 90};
    cout << "Before: "; printArray(a1, 7);
    bubbleSort(a1, 7);
    cout << "After:  "; printArray(a1, 7);

    // ── Selection Sort ───────────────────────────────────────────────────
    cout << "\n--- Selection Sort ---" << endl;
    int a2[] = {64, 34, 25, 12, 22, 11, 90};
    cout << "Before: "; printArray(a2, 7);
    selectionSort(a2, 7);
    cout << "After:  "; printArray(a2, 7);

    // ── Insertion Sort ───────────────────────────────────────────────────
    cout << "\n--- Insertion Sort ---" << endl;
    int a3[] = {64, 34, 25, 12, 22, 11, 90};
    cout << "Before: "; printArray(a3, 7);
    insertionSort(a3, 7);
    cout << "After:  "; printArray(a3, 7);

    // ── Insertion Sort on nearly-sorted ──────────────────────────────────
    cout << "\n--- Insertion Sort (Nearly Sorted) ---" << endl;
    int a4[] = {1, 2, 4, 3, 5, 6, 7};
    cout << "Before: "; printArray(a4, 7);
    insertionSort(a4, 7);
    cout << "After:  "; printArray(a4, 7);

    // ── Merge Sort ───────────────────────────────────────────────────────
    cout << "\n--- Merge Sort ---" << endl;
    int a5[] = {38, 27, 43, 3, 9, 82, 10};
    cout << "Before: "; printArray(a5, 7);
    mergeSort(a5, 0, 6);
    cout << "After:  "; printArray(a5, 7);

    // ── Quick Sort ───────────────────────────────────────────────────────
    cout << "\n--- Quick Sort ---" << endl;
    int a6[] = {10, 7, 8, 9, 1, 5};
    cout << "Before: "; printArray(a6, 6);
    quickSort(a6, 0, 5);
    cout << "After:  "; printArray(a6, 6);

    cout << "\n============================================" << endl;
    cout << "   Sorting Algorithms Completed!" << endl;
    cout << "============================================" << endl;

    return 0;
}
