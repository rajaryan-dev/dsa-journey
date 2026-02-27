/*
 * ============================================================================
 * FILE: 02_Insertion.cpp
 * ============================================================================
 *
 * ARRAY INSERTION OPERATIONS
 *
 * Insertion requires shifting elements to make room for the new value.
 * We track two numbers:
 *   • capacity — maximum slots the array can hold
 *   • size     — how many slots are currently in use
 *
 * ┌─────────────────────────┬──────────────┬──────────────────────────────┐
 * │ Insertion Position      │ Time         │ Why                          │
 * ├─────────────────────────┼──────────────┼──────────────────────────────┤
 * │ At End                  │ O(1)         │ No shifting needed           │
 * │ At Beginning            │ O(n)         │ Shift all n elements right   │
 * │ At Position i           │ O(n − i)     │ Shift n−i elements right     │
 * │ In Sorted (maintain)    │ O(n)         │ Find position + shift        │
 * └─────────────────────────┴──────────────┴──────────────────────────────┘
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
    cout << "]" << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 1: Insert at End — O(1)
// ─────────────────────────────────────────────────────────────────────────────
//   arr[size] = element;  size++;
//   No elements need to move.
// ─────────────────────────────────────────────────────────────────────────────
bool insertAtEnd(int arr[], int& size, int capacity, int element) {
    if (size >= capacity) {
        cout << "  ✗ Array full! Cannot insert " << element << endl;
        return false;
    }
    arr[size++] = element;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 2: Insert at Beginning — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Shift RIGHT from the last element towards index 0, then place at arr[0].
//
//     Before:  [10, 20, 30,  _,  _]   size=3
//     Shift →  [10, 20, 30, 30,  _]   move arr[2]→arr[3]
//              [10, 20, 20, 30,  _]   move arr[1]→arr[2]
//              [10, 10, 20, 30,  _]   move arr[0]→arr[1]
//     Insert:  [ 5, 10, 20, 30,  _]   arr[0] = 5,  size=4
// ─────────────────────────────────────────────────────────────────────────────
bool insertAtBeginning(int arr[], int& size, int capacity, int element) {
    if (size >= capacity) {
        cout << "  ✗ Array full! Cannot insert " << element << endl;
        return false;
    }
    for (int i = size - 1; i >= 0; i--) {     // shift right, back-to-front
        arr[i + 1] = arr[i];
    }
    arr[0] = element;
    size++;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 3: Insert at Specific Position — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Valid positions: 0 ≤ pos ≤ size
//
//     Insert 25 at pos 2 in [10, 20, 30, 40]:
//       Before:  [10, 20, 30, 40,  _,  _]   size=4
//       Shift →  [10, 20, 30, 40, 40,  _]
//                [10, 20, 30, 30, 40,  _]
//       Insert:  [10, 20, 25, 30, 40,  _]   size=5
// ─────────────────────────────────────────────────────────────────────────────
bool insertAtPosition(int arr[], int& size, int capacity, int pos, int element) {
    if (pos < 0 || pos > size) {
        cout << "  ✗ Invalid position " << pos
             << "! Range: [0, " << size << "]" << endl;
        return false;
    }
    if (size >= capacity) {
        cout << "  ✗ Array full! Cannot insert " << element << endl;
        return false;
    }
    for (int i = size - 1; i >= pos; i--) {
        arr[i + 1] = arr[i];
    }
    arr[pos] = element;
    size++;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 4: Insert in Sorted Array (Maintain Order) — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   1. Find the first index where arr[i] >= element.
//   2. Shift elements from that index rightward.
//   3. Place element at the found index.
//
//   Insert 25 into [10, 20, 30, 40, 50]:
//     25 > 10 ✓  25 > 20 ✓  25 > 30 ✗  →  pos = 2
//     Result: [10, 20, 25, 30, 40, 50]
// ─────────────────────────────────────────────────────────────────────────────
bool insertInSorted(int arr[], int& size, int capacity, int element) {
    if (size >= capacity) {
        cout << "  ✗ Array full!" << endl;
        return false;
    }

    // Find correct position
    int pos = 0;
    while (pos < size && arr[pos] < element) pos++;

    // Shift & insert
    for (int i = size - 1; i >= pos; i--) {
        arr[i + 1] = arr[i];
    }
    arr[pos] = element;
    size++;
    return true;
}

// ═════════════════════════════════════════════════════════════════════════════
// MAIN — Demonstrate All Insertion Operations
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    cout << "============================================" << endl;
    cout << "   02 · ARRAY INSERTION OPERATIONS" << endl;
    cout << "============================================" << endl;

    const int CAP = 10;
    int arr[CAP];
    int sz = 0;

    // ── Insert at End ────────────────────────────────────────────────────
    cout << "\n--- Insert at End ---" << endl;
    insertAtEnd(arr, sz, CAP, 10);
    insertAtEnd(arr, sz, CAP, 20);
    insertAtEnd(arr, sz, CAP, 30);
    cout << "After 3 inserts: "; printArray(arr, sz);

    // ── Insert at Beginning ──────────────────────────────────────────────
    cout << "\n--- Insert at Beginning ---" << endl;
    insertAtBeginning(arr, sz, CAP, 5);
    cout << "Insert 5 at front: "; printArray(arr, sz);
    insertAtBeginning(arr, sz, CAP, 1);
    cout << "Insert 1 at front: "; printArray(arr, sz);

    // ── Insert at Position ───────────────────────────────────────────────
    cout << "\n--- Insert at Position ---" << endl;
    cout << "Current: "; printArray(arr, sz);
    insertAtPosition(arr, sz, CAP, 3, 15);
    cout << "Insert 15 at pos 3: "; printArray(arr, sz);
    insertAtPosition(arr, sz, CAP, 5, 25);
    cout << "Insert 25 at pos 5: "; printArray(arr, sz);

    // Edge: invalid position
    cout << "\nEdge — invalid position: ";
    insertAtPosition(arr, sz, CAP, 99, 100);

    // ── Insert in Sorted Array ───────────────────────────────────────────
    cout << "\n--- Insert in Sorted Array ---" << endl;
    int sorted[CAP] = {10, 20, 40, 50, 60};
    int sortSz = 5;
    cout << "Sorted: "; printArray(sorted, sortSz);

    insertInSorted(sorted, sortSz, CAP, 30);
    cout << "Insert 30: "; printArray(sorted, sortSz);

    insertInSorted(sorted, sortSz, CAP, 5);
    cout << "Insert  5: "; printArray(sorted, sortSz);

    insertInSorted(sorted, sortSz, CAP, 70);
    cout << "Insert 70: "; printArray(sorted, sortSz);

    // ── Edge: Array full ─────────────────────────────────────────────────
    cout << "\n--- Edge: Array Full ---" << endl;
    int tiny[3] = {1, 2, 3};
    int tinySz = 3;
    cout << "Capacity 3: "; printArray(tiny, tinySz);
    insertAtEnd(tiny, tinySz, 3, 4);

    cout << "\n============================================" << endl;
    cout << "   Insertion Operations Completed!" << endl;
    cout << "============================================" << endl;

    return 0;
}
