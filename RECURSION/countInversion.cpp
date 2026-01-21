#include <bits/stdc++.h>
using namespace std;

/* --------------------------------------------------------------------
   BRUTE FORCE APPROACH  (Time: O(N²), Space: O(1) )
   Simply check for every pair (i < j) where arr[i] > arr[j]
---------------------------------------------------------------------*/
int bruteForceInversionCount(const vector<int>& arr) {
  int count = 0;
  for (int i = 0; i < arr.size() - 1; i++) {
    for (int j = i + 1; j < arr.size(); j++) {
      if (arr[i] > arr[j]) {
        count++;
      }
    }
  }
  return count;
}

/* --------------------------------------------------------------------
   MERGE FUNCTION — merges both halves and counts cross inversions
   When arr[i] > arr[j] (i in left half, j in right half)
   → contributes (mid - i + 1) inversions
---------------------------------------------------------------------*/
int mergeAndCount(vector<int>& arr, int left, int mid, int right) {
  vector<int> temp;
  int i = left;     // pointer for left subarray
  int j = mid + 1;  // pointer for right subarray
  int inversions = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      // No inversion, smaller element goes first
      temp.push_back(arr[i]);
      i++;
    } else {
      // Inversion found, because arr[i] > arr[j]
      temp.push_back(arr[j]);
      j++;
      inversions += (mid - i + 1);
    }
  }

  // Push remaining elements from left & right halves
  while (i <= mid) temp.push_back(arr[i++]);
  while (j <= right) temp.push_back(arr[j++]);

  // Copy back to original array
  for (int k = 0; k < temp.size(); k++) {
    arr[left + k] = temp[k];
  }

  return inversions;
}

/* --------------------------------------------------------------------
   MERGE SORT BASED APPROACH (Time: O(N log N), Space: O(N))
   Recursively sorts and counts inversions
---------------------------------------------------------------------*/
int mergeSortAndCount(vector<int>& arr, int left, int right) {
  if (left >= right) return 0;

  int mid = left + (right - left) / 2;

  int leftCount = mergeSortAndCount(arr, left, mid);
  int rightCount = mergeSortAndCount(arr, mid + 1, right);
  int mergeCount = mergeAndCount(arr, left, mid, right);

  return leftCount + rightCount + mergeCount;
}

/* --------------------------------------------------------------------
   MAIN
---------------------------------------------------------------------*/
int main() {
  vector<int> arr = {12, 31, 35, 8, 32, 17};

  // MERGE SORT METHOD (Optimized)
  vector<int> arrCopy = arr;  // making copy because mergeSort modifies array
  int inversionCount = mergeSortAndCount(arrCopy, 0, arrCopy.size() - 1);
  cout << "Inversion Count using Merge Sort (Optimized): " << inversionCount
       << endl;

  // BRUTE FORCE METHOD (for reference/checking)
  int bruteCount = bruteForceInversionCount(arr);
  cout << "Inversion Count using Brute Force (Slow): " << bruteCount << endl;

  return 0;
}
