/*
 * ============================================================================
 * FILE: 03_Deletion.cpp
 * ============================================================================
 *
 * ARRAY DELETION OPERATIONS
 *
 * Deletion fills the gap by shifting elements leftward.
 *
 * ┌──────────────────────────┬──────────┬──────────────────────────────────┐
 * │ Deletion Type            │ Time     │ Notes                            │
 * ├──────────────────────────┼──────────┼──────────────────────────────────┤
 * │ From End                 │ O(1)     │ Just decrement size              │
 * │ From Beginning           │ O(n)     │ Shift all elements left by 1     │
 * │ From Position i          │ O(n − i) │ Shift elements from i+1 onward   │
 * │ By Value (first)         │ O(n)     │ Search O(n) + shift O(n)         │
 * │ All Occurrences          │ O(n)     │ Two-pointer, single pass         │
 * └──────────────────────────┴──────────┴──────────────────────────────────┘
 *
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// UTILITY: Print Array
// ─────────────────────────────────────────────────────────────────────────────
void printArray(const int arr[], int size) {
    if (size == 0) { cout << "[empty]" << endl; return; }
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 1: Delete from End — O(1)
// ─────────────────────────────────────────────────────────────────────────────
//   Simply decrement size. The old value still exists in memory but is
//   logically removed.
// ─────────────────────────────────────────────────────────────────────────────
bool deleteFromEnd(int arr[], int& size) {
    if (size <= 0) { cout << "  ✗ Array empty!" << endl; return false; }

    int deleted = arr[--size];
    cout << "  Deleted " << deleted << " from end." << endl;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 2: Delete from Beginning — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//     Before: [10, 20, 30, 40]   size=4
//     Shift←  [20, 30, 40, 40]   arr[i] = arr[i+1]
//     size--  [20, 30, 40]       size=3
// ─────────────────────────────────────────────────────────────────────────────
bool deleteFromBeginning(int arr[], int& size) {
    if (size <= 0) { cout << "  ✗ Array empty!" << endl; return false; }

    int deleted = arr[0];
    for (int i = 0; i < size - 1; i++) arr[i] = arr[i + 1];
    size--;
    cout << "  Deleted " << deleted << " from beginning." << endl;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 3: Delete from Position — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Valid positions: 0 ≤ pos < size
//
//   Delete pos 2 from [10, 20, 30, 40, 50]:
//     Shift←  [10, 20, 40, 50, 50]
//     size--  [10, 20, 40, 50]   size=4
// ─────────────────────────────────────────────────────────────────────────────
bool deleteFromPosition(int arr[], int& size, int pos) {
    if (size <= 0) { cout << "  ✗ Array empty!" << endl; return false; }
    if (pos < 0 || pos >= size) {
        cout << "  ✗ Invalid position " << pos << "!" << endl;
        return false;
    }

    int deleted = arr[pos];
    for (int i = pos; i < size - 1; i++) arr[i] = arr[i + 1];
    size--;
    cout << "  Deleted " << deleted << " from position " << pos << "." << endl;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 4: Delete by Value (First Occurrence) — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Two-phase: search for value → shift left over it.
// ─────────────────────────────────────────────────────────────────────────────
bool deleteByValue(int arr[], int& size, int value) {
    // Phase 1: Find
    int pos = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) { pos = i; break; }
    }
    if (pos == -1) {
        cout << "  ✗ " << value << " not found!" << endl;
        return false;
    }

    // Phase 2: Shift left
    for (int i = pos; i < size - 1; i++) arr[i] = arr[i + 1];
    size--;
    cout << "  Deleted first " << value << " (was at pos " << pos << ")." << endl;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// OPERATION 5: Delete ALL Occurrences — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Two-pointer (read/write) technique — single pass, in-place.
//
//       read  →  scans every element
//       write →  only advances when element ≠ target
//
//   Before: [10, 30, 20, 30, 30, 40]   value = 30
//     r=0 → 10 ≠ 30 → arr[w=0]=10, w=1
//     r=1 → 30 = 30 → skip
//     r=2 → 20 ≠ 30 → arr[w=1]=20, w=2
//     r=3 → 30 = 30 → skip
//     r=4 → 30 = 30 → skip
//     r=5 → 40 ≠ 30 → arr[w=2]=40, w=3
//   After:  [10, 20, 40]   size=3, removed 3 occurrences
// ─────────────────────────────────────────────────────────────────────────────
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
    cout << "  Removed " << count << " occurrence(s) of " << value << "." << endl;
    return count;
}

// ═════════════════════════════════════════════════════════════════════════════
// MAIN — Demonstrate All Deletion Operations
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    cout << "============================================" << endl;
    cout << "   03 · ARRAY DELETION OPERATIONS" << endl;
    cout << "============================================" << endl;

    // ── Delete from End ──────────────────────────────────────────────────
    cout << "\n--- Delete from End ---" << endl;
    int a1[] = {10, 20, 30, 40, 50}; int s1 = 5;
    cout << "Before: "; printArray(a1, s1);
    deleteFromEnd(a1, s1);
    cout << "After:  "; printArray(a1, s1);

    // ── Delete from Beginning ────────────────────────────────────────────
    cout << "\n--- Delete from Beginning ---" << endl;
    int a2[] = {10, 20, 30, 40, 50}; int s2 = 5;
    cout << "Before: "; printArray(a2, s2);
    deleteFromBeginning(a2, s2);
    cout << "After:  "; printArray(a2, s2);

    // ── Delete from Position ─────────────────────────────────────────────
    cout << "\n--- Delete from Position 2 ---" << endl;
    int a3[] = {10, 20, 30, 40, 50}; int s3 = 5;
    cout << "Before: "; printArray(a3, s3);
    deleteFromPosition(a3, s3, 2);
    cout << "After:  "; printArray(a3, s3);

    // ── Delete by Value ──────────────────────────────────────────────────
    cout << "\n--- Delete by Value (20) ---" << endl;
    int a4[] = {10, 20, 30, 20, 40}; int s4 = 5;
    cout << "Before: "; printArray(a4, s4);
    deleteByValue(a4, s4, 20);
    cout << "After:  "; printArray(a4, s4);

    // ── Delete All Occurrences ───────────────────────────────────────────
    cout << "\n--- Delete All Occurrences (30) ---" << endl;
    int a5[] = {10, 30, 20, 30, 30, 40}; int s5 = 6;
    cout << "Before: "; printArray(a5, s5);
    deleteAllOccurrences(a5, s5, 30);
    cout << "After:  "; printArray(a5, s5);

    // ── Edge: Empty array ────────────────────────────────────────────────
    cout << "\n--- Edge: Delete from Empty ---" << endl;
    int empty[5]; int es = 0;
    deleteFromEnd(empty, es);

    cout << "\n============================================" << endl;
    cout << "   Deletion Operations Completed!" << endl;
    cout << "============================================" << endl;

    return 0;
}
