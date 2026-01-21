#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void nextPermutation(vector<int>& A) {
    int pivot = -1, n = A.size();

    // Step 1: Find the pivot
    for (int i = n - 2; i >= 0; i--) {
        if (A[i] < A[i + 1]) {
            pivot = i;
            break;
        }
    }

    if (pivot == -1) {
        reverse(A.begin(), A.end());
        return;
    }

    // Step 2: Find next larger element to pivot
    for (int i = n - 1; i > pivot; i--) {
        if (A[i] > A[pivot]) {
            swap(A[i], A[pivot]);
            break;
        }
    }

    // Step 3: Reverse suffix starting at pivot+1
    reverse(A.begin() + pivot + 1, A.end());
}

int main() {
    vector<int> Arr = {2, 5, 3, 1, 8};

    nextPermutation(Arr);  // modify in-place

    // Print the result
    for (int num : Arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
