#include <iostream>
using namespace std;

// Corrected merge function
// m = number of initialized elements in arrA
// n = number of elements in arrB
void merge(int arrA[], int m, int arrB[], int n) {
    // Index of the last position in the merged array (arrA)
    int idx = m + n - 1;
    // Index of the last initialized element in arrA
    int i = m - 1;
    // Index of the last element in arrB
    int j = n - 1;

    // Compare elements from the end of both arrays and place the larger one at the end of arrA
    while (i >= 0 && j >= 0) {
        if (arrA[i] >= arrB[j]) {
            arrA[idx--] = arrA[i--];
        } else {
            arrA[idx--] = arrB[j--]; // FIX: Corrected from arrA[j--]
        }
    }

    // If there are remaining elements in arrB, copy them over
    while (j >= 0) {
        arrA[idx--] = arrB[j--];
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arrA[6] = {1, 2, 3, 0, 0, 0};
    int arrB[] = {2, 5, 6};

    // m is the number of INITIALIZED elements in arrA, not its total capacity
    int m = 3;
    int n = 3;
    int totalSize = m + n;

    cout << "Array A before merge: ";
    printArray(arrA, totalSize);

    // NEW: Printing arrB
    cout << "Array B before merge: ";
    printArray(arrB, n);

    // Call merge with the correct count of initialized elements (m=3)
    merge(arrA, m, arrB, n);

    cout << "Array A after merge:  ";
    printArray(arrA, totalSize);

    return 0;
}