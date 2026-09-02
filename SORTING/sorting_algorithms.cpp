/*
 * ============================================================
 *  SORTING ALGORITHMS — Complete Reference
 * ============================================================
 *  Algorithms covered:
 *   1. Bubble Sort     O(n²)      stable
 *   2. Selection Sort  O(n²)      unstable
 *   3. Insertion Sort  O(n²)      stable, good for nearly sorted
 *   4. Merge Sort      O(n log n) stable, extra space O(n)
 *   5. Quick Sort      O(n log n) avg, unstable, in-place
 *   6. Heap Sort       O(n log n) unstable, in-place
 *   7. Counting Sort   O(n+k)     stable (for integers in range)
 *   8. Radix Sort      O(d*(n+k)) for d-digit numbers
 *   9. Shell Sort      O(n log² n)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

void printArr(const vector<int>& a, const string& label = "") {
    if (!label.empty()) cout << label << ": ";
    for (int x : a) cout << x << " ";
    cout << "\n";
}

// ─────────────────────────────────────────────────────────────
//  1. Bubble Sort
//  Compare adjacent pairs, bubble max to end each pass.
//  Optimisation: stop early if no swap in a pass.
// ─────────────────────────────────────────────────────────────
void bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1]) { swap(arr[j], arr[j+1]); swapped = true; }
        if (!swapped) break;
    }
    printArr(arr, "Bubble Sort");
}

// ─────────────────────────────────────────────────────────────
//  2. Selection Sort
//  Find minimum in remaining array, place at front.
// ─────────────────────────────────────────────────────────────
void selectionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
    printArr(arr, "Selection Sort");
}

// ─────────────────────────────────────────────────────────────
//  3. Insertion Sort
//  Build sorted portion left to right, insert each element.
//  Best for small / nearly-sorted arrays.
// ─────────────────────────────────────────────────────────────
void insertionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; j--; }
        arr[j + 1] = key;
    }
    printArr(arr, "Insertion Sort");
}

// ─────────────────────────────────────────────────────────────
//  4. Merge Sort
//  Divide array in half, sort each half, merge sorted halves.
//  Stable, guaranteed O(n log n).
// ─────────────────────────────────────────────────────────────
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> L(arr.begin() + l, arr.begin() + m + 1);
    vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < (int)L.size() && j < (int)R.size())
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < (int)L.size()) arr[k++] = L[i++];
    while (j < (int)R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// ─────────────────────────────────────────────────────────────
//  5. Quick Sort
//  Partition around pivot; elements < pivot left, > pivot right.
//  Lomuto partition (simple) vs Hoare (faster in practice).
// ─────────────────────────────────────────────────────────────
int partitionLomuto(vector<int>& arr, int lo, int hi) {
    int pivot = arr[hi], i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (arr[j] <= pivot) swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[hi]);
    return i + 1;
}

void quickSort(vector<int>& arr, int lo, int hi) {
    if (lo >= hi) return;
    int p = partitionLomuto(arr, lo, hi);
    quickSort(arr, lo, p - 1);
    quickSort(arr, p + 1, hi);
}

// ─────────────────────────────────────────────────────────────
//  6. Heap Sort
//  Build max-heap, repeatedly extract max to end.
// ─────────────────────────────────────────────────────────────
void heapify(vector<int>& arr, int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) { swap(arr[i], arr[largest]); heapify(arr, n, largest); }
}

void heapSort(vector<int> arr) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i); // Build max-heap
    for (int i = n - 1; i > 0; i--) { swap(arr[0], arr[i]); heapify(arr, i, 0); }
    printArr(arr, "Heap Sort");
}

// ─────────────────────────────────────────────────────────────
//  7. Counting Sort   — for non-negative integers in range [0,k]
// ─────────────────────────────────────────────────────────────
void countingSort(vector<int> arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    for (int x : arr) count[x]++;
    for (int i = 1; i <= maxVal; i++) count[i] += count[i - 1]; // prefix sum
    vector<int> out(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--)
        out[--count[arr[i]]] = arr[i];
    printArr(out, "Counting Sort");
}

// ─────────────────────────────────────────────────────────────
//  8. Radix Sort (LSD — Least Significant Digit)
//  Sort digit by digit using stable counting sort.
// ─────────────────────────────────────────────────────────────
void countSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> out(n), count(10, 0);
    for (int x : arr) count[(x / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) out[--count[(arr[i] / exp) % 10]] = arr[i];
    arr = out;
}

void radixSort(vector<int> arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countSortByDigit(arr, exp);
    printArr(arr, "Radix Sort");
}

// ─────────────────────────────────────────────────────────────
//  9. Shell Sort
//  Insertion sort with decreasing gap sizes.
// ─────────────────────────────────────────────────────────────
void shellSort(vector<int> arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap]; j -= gap;
            }
            arr[j] = temp;
        }
    printArr(arr, "Shell Sort");
}

// ─────────────────────────────────────────────────────────────
int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    cout << "===== Sorting Algorithms =====\n";
    printArr(arr, "Input");
    cout << "\n";

    bubbleSort(arr);
    selectionSort(arr);
    insertionSort(arr);

    vector<int> ms = arr;
    mergeSort(ms, 0, ms.size() - 1);
    printArr(ms, "Merge Sort");

    vector<int> qs = arr;
    quickSort(qs, 0, qs.size() - 1);
    printArr(qs, "Quick Sort");

    heapSort(arr);
    countingSort(arr);
    radixSort(arr);
    shellSort(arr);

    cout << "\n===== Complexity Reference =====\n";
    cout << "Algorithm       | Best      | Avg       | Worst     | Space | Stable\n";
    cout << "Bubble Sort     | O(n)      | O(n²)     | O(n²)     | O(1)  | Yes\n";
    cout << "Selection Sort  | O(n²)     | O(n²)     | O(n²)     | O(1)  | No\n";
    cout << "Insertion Sort  | O(n)      | O(n²)     | O(n²)     | O(1)  | Yes\n";
    cout << "Merge Sort      | O(nlogn)  | O(nlogn)  | O(nlogn)  | O(n)  | Yes\n";
    cout << "Quick Sort      | O(nlogn)  | O(nlogn)  | O(n²)     | O(logn)| No\n";
    cout << "Heap Sort       | O(nlogn)  | O(nlogn)  | O(nlogn)  | O(1)  | No\n";
    cout << "Counting Sort   | O(n+k)    | O(n+k)    | O(n+k)    | O(k)  | Yes\n";
    cout << "Radix Sort      | O(d(n+k)) | O(d(n+k)) | O(d(n+k)) | O(n+k)| Yes\n";

    return 0;
}
