#include <iostream>
#include <vector>
using namespace std;

// check if array is sorted
bool isSorted(vector<int> arr, int n) {
  if (n == 0 || n == 1) {
    return true;
  }

  return arr[n - 1] >= arr[n - 2] && isSorted(arr, n - 1);
}

// bin-search
int binSearch(vector<int> arr, int tar, int st, int end) {
  if (st <= end) {
    int mid = st + (end - st) / 2;
    if (arr[mid] == tar) {
      return mid;
    } else if (arr[mid] < tar) {
      return binSearch(arr, tar, mid + 1, end);
    } else
      return binSearch(arr, tar, st, mid - 1);
  }
  return -1;
}
int search(vector<int>& nums, int target) {
  int st = 0;
  int end = nums.size() - 1;

  return binSearch(nums, target, st, end);
}

int main() {
  vector<int> arr = {7, 2, 3, 4, 5};

  cout << isSorted(arr, arr.size()) << endl;

  return 0;
}