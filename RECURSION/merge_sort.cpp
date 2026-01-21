#include <bits/stdc++.h>
using namespace std;

// ------------------- MERGE TWO PARTS -------------------
void merge(vector<int>& arr, int start, int mid, int end, bool descending) {
  vector<int> temp;
  int left = start;
  int right = mid + 1;

  // Compare and merge based on sorting order
  while (left <= mid && right <= end) {
    if (descending) {
      // For descending order pick the larger element first
      if (arr[left] >= arr[right]) {
        temp.push_back(arr[left]);
        left++;
      } else {
        temp.push_back(arr[right]);
        right++;
      }
    } else {
      // For ascending order pick the smaller element first
      if (arr[left] <= arr[right]) {
        temp.push_back(arr[left]);
        left++;
      } else {
        temp.push_back(arr[right]);
        right++;
      }
    }
  }

  // Remaining elements from left half
  while (left <= mid) {
    temp.push_back(arr[left]);
    left++;
  }

  // Remaining elements from right half
  while (right <= end) {
    temp.push_back(arr[right]);
    right++;
  }

  // Copy sorted data back to original array
  for (int i = 0; i < temp.size(); i++) {
    arr[start + i] =
        temp[i];  // start + i is necessary to place data at correct position
  }
}

// ------------------- MERGE SORT -------------------
void mergeSort(vector<int>& arr, int start, int end, bool descending) {
  if (start >= end) return;

  int mid = start + (end - start) / 2;  // safer than (start + end) / 2

  mergeSort(arr, start, mid, descending);    // left half
  mergeSort(arr, mid + 1, end, descending);  // right half
  merge(arr, start, mid, end, descending);   // merge both halves
}

// ------------------- MAIN -------------------
int main() {
  vector<int> arr = {12, 31, 35, 8, 32, 17};

  bool sortDescending = true;  // ----> change to false for ascending order

  mergeSort(arr, 0, arr.size() - 1, sortDescending);

  cout << (sortDescending ? "Sorted (Descending): " : "Sorted (Ascending): ");

  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl;

  return 0;
}
