#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void nextPermutation(vector<int>& nums) {
    int pivot = -1, n = nums.size();

     // Step 1: Find the pivot
    for(int i = n - 2; i >= 0; i--) {
        if(nums[i] < nums[i + 1]) {
            pivot = i;
            break;
        }
    }

    if(pivot == -1) {
        reverse(nums.begin(), nums.end()); 
        return;
    }

    // Step 2: Find next larger element to pivot
    for(int i = n - 1; i > pivot; i--) {
        if(nums[i] > nums[pivot]) {
            swap(nums[i], nums[pivot]);
            break;
        }
    }

    // Step 3: Reverse suffix starting at pivot+1

     //reverse(nums.begin() + pivot + 1, nums.end());

    
    int i = pivot + 1, j = n - 1;
    while(i <= j) {
        swap(nums[i++], nums[j--]);
    }
};

int main() {
    vector<int> arr = {2, 5, 3, 1, 8};

    nextPermutation(arr);  // modify in-place

    // Print the result
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
