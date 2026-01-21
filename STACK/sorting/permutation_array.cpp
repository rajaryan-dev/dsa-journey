#include <iostream>
using namespace std;

void reverse(int A[], int start, int end) {
    while (start < end) {
        swap(A[start], A[end]);
        start++;
        end--;
    }
}

void nextPermutation(int A[], int n) {
    int pivot = -1;

    // Step 1: Find pivot
    for (int i = n - 2; i >= 0; i--) {
        if (A[i] < A[i + 1]) {
            pivot = i;
            break;
        }
    }

    // If no pivot, reverse whole array
    if (pivot == -1) {
        reverse(A, 0, n - 1);
        return;
    }

    // Step 2: Find next larger element to the right of pivot
    for (int i = n - 1; i > pivot; i--) {
        if (A[i] > A[pivot]) {
            swap(A[i], A[pivot]);
            break;
        }
    }

    // Step 3: Reverse the suffix (pivot+1 to end)
    reverse(A, pivot + 1, n - 1);
}

int main() {
    int Arr[] = {2, 5, 3, 1, 8};
    int n = sizeof(Arr) / sizeof(Arr[0]);

    nextPermutation(Arr, n);

    // Print the result
    for (int i = 0; i < n; i++) {
        cout << Arr[i] << " ";
    }
    cout << endl;

    return 0;
}
