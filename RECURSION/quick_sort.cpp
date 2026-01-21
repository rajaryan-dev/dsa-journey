#include <bits/stdc++.h>
using namespace std;

// Partition function that supports both ascending & descending
int partitionFunc(vector<int>& arr, int low, int high, bool descending) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    // If descending = false → ascending
    // If descending = true  → descending
    if ((!descending && arr[j] < pivot) || (descending && arr[j] > pivot)) {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return i + 1;
}

// Recursive QuickSort
void quickSort(vector<int>& arr, int low, int high, bool descending = false) {
  if (low < high) {
    int pivotIndex = partitionFunc(arr, low, high, descending);

    quickSort(arr, low, pivotIndex - 1, descending);
    quickSort(arr, pivotIndex + 1, high, descending);
  }
}

int main() {
  vector<int> arr = {8, 4, 7, 2, 9};

  cout << "Ascending: ";
  vector<int> ascArr = arr;
  quickSort(ascArr, 0, ascArr.size() - 1, false);
  for (int x : ascArr) cout << x << " ";
  cout << endl;

  cout << "Descending: ";
  vector<int> dscArr = arr;
  quickSort(dscArr, 0, dscArr.size() - 1, true);
  for (int x : dscArr) cout << x << " ";
  return 0;
}
