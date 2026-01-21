// LeetCode Question: 496. Next Greater Element I

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

// -------------------------------------------
// LeetCode Function: Next Greater Element I
// -------------------------------------------
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
  unordered_map<int, int> m;  // key = nums2 value, value = next greater element
  stack<int> s;               // stack will store elements in decreasing order

  // Traverse nums2 from RIGHT → LEFT
  for (int i = nums2.size() - 1; i >= 0; i--) {
    // Remove all elements from stack that are smaller/equal to nums2[i]
    while (!s.empty() && s.top() <= nums2[i]) {
      s.pop();
    }

    // If stack becomes empty → no next greater exists
    if (s.empty()) {
      m[nums2[i]] = -1;
    } else {
      m[nums2[i]] = s.top();  // top of stack is next greater
    }

    // Push current element to stack
    s.push(nums2[i]);
  }

  // Build answer for nums1 using map (O(1) lookup each)
  vector<int> ans;
  for (int x : nums1) {
    ans.push_back(m[x]);
  }

  return ans;
}

// -------------------------------------------
// MAIN (Trial / Testing for VS Code)
// -------------------------------------------
int main() {
  // Testcase from LeetCode Example
  vector<int> nums1 = {4, 1, 2};
  vector<int> nums2 = {1, 3, 4, 2};

  vector<int> res = nextGreaterElement(nums1, nums2);

  cout << "Output (Next Greater): ";
  for (int x : res) {
    cout << x << " ";
  }
  cout << endl;

  return 0;
}
