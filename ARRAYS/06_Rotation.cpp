/*
 * ============================================================================
 * FILE: 06_Rotation.cpp
 * ============================================================================
 *
 * ARRAY ROTATION OPERATIONS
 *
 * Left Rotation:  elements shift left;  first d go to the end.
 * Right Rotation: elements shift right; last d go to the front.
 *
 *   Original:          [1, 2, 3, 4, 5]
 *   Left  rotate by 2: [3, 4, 5, 1, 2]
 *   Right rotate by 2: [4, 5, 1, 2, 3]
 *
 * ┌──────────────────────────┬──────────┬───────┐
 * │ Method                   │ Time     │ Space │
 * ├──────────────────────────┼──────────┼───────┤
 * │ Naive (d single rotates) │ O(n × d) │ O(1)  │
 * │ Reversal Algorithm       │ O(n)     │ O(1)  │
 * │ Juggling (GCD-based)     │ O(n)     │ O(1)  │
 * └──────────────────────────┴──────────┴───────┘
 *
 * ============================================================================
 */

#include <algorithm>   // std::swap, std::__gcd (or use manual gcd)
#include <iostream>
#include <utility>

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// UTILITY
// ─────────────────────────────────────────────────────────────────────────────
void printArray(const int arr[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int gcd(int a, int b) {
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

// ─────────────────────────────────────────────────────────────────────────────
// 1. LEFT ROTATE BY ONE — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Save arr[0], shift everything left by 1, put saved value at end.
// ─────────────────────────────────────────────────────────────────────────────
void leftRotateByOne(int arr[], int size) {
    int first = arr[0];
    for (int i = 0; i < size - 1; i++) arr[i] = arr[i + 1];
    arr[size - 1] = first;
}

// ─────────────────────────────────────────────────────────────────────────────
// 2. LEFT ROTATE BY D — Naive O(n × d)
// ─────────────────────────────────────────────────────────────────────────────
//   Call leftRotateByOne() d times.  Simple but slow for large d.
// ─────────────────────────────────────────────────────────────────────────────
void leftRotateNaive(int arr[], int size, int d) {
    d %= size;
    for (int i = 0; i < d; i++) leftRotateByOne(arr, size);
}

// ─────────────────────────────────────────────────────────────────────────────
// HELPER: Reverse sub-array arr[lo..hi]
// ─────────────────────────────────────────────────────────────────────────────
void reverse(int arr[], int lo, int hi) {
    while (lo < hi) { swap(arr[lo++], arr[hi--]); }
}

// ─────────────────────────────────────────────────────────────────────────────
// 3. LEFT ROTATE BY D — Reversal Algorithm O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Three reverses:
//     Step 1: Reverse first d elements        [d-1 .. 0 | d .. n-1]
//     Step 2: Reverse remaining n-d elements   [d-1 .. 0 | n-1 .. d]
//     Step 3: Reverse entire array             [d .. n-1 | 0 .. d-1]  ✓
//
//   Example: [1, 2, 3, 4, 5]  d=2
//     Step 1: [2, 1, 3, 4, 5]
//     Step 2: [2, 1, 5, 4, 3]
//     Step 3: [3, 4, 5, 1, 2]  ✓
// ─────────────────────────────────────────────────────────────────────────────
void leftRotateReversal(int arr[], int size, int d) {
    d %= size;
    if (d == 0) return;

    reverse(arr, 0, d - 1);            // reverse first d
    reverse(arr, d, size - 1);          // reverse rest
    reverse(arr, 0, size - 1);          // reverse all
}

// ─────────────────────────────────────────────────────────────────────────────
// 4. LEFT ROTATE BY D — Juggling Algorithm O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Divide the array into gcd(n, d) sets and cyclically shift each set.
//
//   Example: [1, 2, 3, 4, 5, 6]  d=2, n=6, gcd=2
//     Set 0 (indices 0→2→4): move 1→ ,3→0,5→2,1→4  → positions 0,2,4
//     Set 1 (indices 1→3→5): move 2→ ,4→1,6→3,2→5  → positions 1,3,5
//     Result: [3, 4, 5, 6, 1, 2]  ✓
//
//   Why it works: every element is visited exactly once, each placed in
//   its final destination directly — no wasted moves.
// ─────────────────────────────────────────────────────────────────────────────
void leftRotateJuggling(int arr[], int size, int d) {
    d %= size;
    if (d == 0) return;

    int g = gcd(size, d);
    for (int i = 0; i < g; i++) {
        int temp = arr[i];                    // save starting element
        int j = i;
        while (true) {
            int k = (j + d) % size;
            if (k == i) break;                // full cycle
            arr[j] = arr[k];
            j = k;
        }
        arr[j] = temp;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 5. RIGHT ROTATE BY D — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Right rotate by d  ≡  Left rotate by (n − d).
// ─────────────────────────────────────────────────────────────────────────────
void rightRotate(int arr[], int size, int d) {
    d %= size;
    if (d == 0) return;
    leftRotateReversal(arr, size, size - d);
}

// ─────────────────────────────────────────────────────────────────────────────
// 6. CHECK IF B IS A ROTATION OF A — O(n)
// ─────────────────────────────────────────────────────────────────────────────
//   Trick: concatenate A with itself → "A+A".
//   If B is a sub-array of A+A with same length, B is a rotation of A.
//   (Here we check by trying every offset d.)
// ─────────────────────────────────────────────────────────────────────────────
bool isRotation(const int a[], const int b[], int n) {
    for (int d = 0; d < n; d++) {
        bool match = true;
        for (int i = 0; i < n; i++) {
            if (a[(i + d) % n] != b[i]) { match = false; break; }
        }
        if (match) return true;
    }
    return false;
}

// ═════════════════════════════════════════════════════════════════════════════
// MAIN — Demonstrate All Rotation Operations
// ═════════════════════════════════════════════════════════════════════════════
int main() {
    cout << "============================================" << endl;
    cout << "   06 · ARRAY ROTATION" << endl;
    cout << "============================================" << endl;

    // ── Left Rotate by One ───────────────────────────────────────────────
    cout << "\n--- Left Rotate by One ---" << endl;
    int a1[] = {1, 2, 3, 4, 5};
    cout << "Before: "; printArray(a1, 5);
    leftRotateByOne(a1, 5);
    cout << "After:  "; printArray(a1, 5);

    // ── Left Rotate by D (Naive) ────────────────────────────────────────
    cout << "\n--- Left Rotate by 2 (Naive) ---" << endl;
    int a2[] = {1, 2, 3, 4, 5};
    cout << "Before: "; printArray(a2, 5);
    leftRotateNaive(a2, 5, 2);
    cout << "After:  "; printArray(a2, 5);

    // ── Left Rotate by D (Reversal) ─────────────────────────────────────
    cout << "\n--- Left Rotate by 3 (Reversal Algorithm) ---" << endl;
    int a3[] = {1, 2, 3, 4, 5, 6, 7};
    cout << "Before: "; printArray(a3, 7);
    leftRotateReversal(a3, 7, 3);
    cout << "After:  "; printArray(a3, 7);

    // ── Left Rotate by D (Juggling) ─────────────────────────────────────
    cout << "\n--- Left Rotate by 2 (Juggling Algorithm) ---" << endl;
    int a4[] = {1, 2, 3, 4, 5, 6};
    cout << "Before: "; printArray(a4, 6);
    leftRotateJuggling(a4, 6, 2);
    cout << "After:  "; printArray(a4, 6);

    // ── Right Rotate ─────────────────────────────────────────────────────
    cout << "\n--- Right Rotate by 2 ---" << endl;
    int a5[] = {1, 2, 3, 4, 5};
    cout << "Before: "; printArray(a5, 5);
    rightRotate(a5, 5, 2);
    cout << "After:  "; printArray(a5, 5);

    // ── Edge: Rotate by array size ───────────────────────────────────────
    cout << "\n--- Edge: Rotate by n (full rotation) ---" << endl;
    int a6[] = {1, 2, 3, 4, 5};
    cout << "Before: "; printArray(a6, 5);
    leftRotateReversal(a6, 5, 5);
    cout << "After:  "; printArray(a6, 5);

    // ── Check Rotation ───────────────────────────────────────────────────
    cout << "\n--- Is B a rotation of A? ---" << endl;
    int arrA[] = {1, 2, 3, 4, 5};
    int arrB[] = {3, 4, 5, 1, 2};
    int arrC[] = {3, 4, 1, 5, 2};
    cout << "A = "; printArray(arrA, 5);
    cout << "B = "; printArray(arrB, 5);
    cout << "C = "; printArray(arrC, 5);
    cout << "B is rotation of A? " << (isRotation(arrA, arrB, 5) ? "YES" : "NO") << endl;
    cout << "C is rotation of A? " << (isRotation(arrA, arrC, 5) ? "YES" : "NO") << endl;

    cout << "\n============================================" << endl;
    cout << "   Rotation Operations Completed!" << endl;
    cout << "============================================" << endl;

    return 0;
}
