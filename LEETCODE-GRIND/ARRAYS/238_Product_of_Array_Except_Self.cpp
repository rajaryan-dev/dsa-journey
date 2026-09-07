#include <iostream>
#include <vector>
using namespace std;

/*
    Problem: 238. Product of Array Except Self
    Link: https://leetcode.com/problems/product-of-array-except-self/

    Given an integer array nums, return an array answer such that
    answer[i] is equal to the product of all elements of nums except
    nums[i]. Must run in O(n) time WITHOUT using division.

    Example:
    Input:  nums = [1,2,3,4]
    Output: [24,12,8,6]
    Explanation: answer[0] = 2*3*4 = 24, answer[1] = 1*3*4 = 12, etc.
*/

// ---------------------------------------------------------------------------
// Approach 1: Brute Force (Division) -> O(n) time, O(1) extra space
//
// Beginner intuition: compute the product of ALL elements once, then
// for each index just divide out that element: answer[i] = totalProduct /
// nums[i].
//
// NOT allowed on LeetCode here (explicitly forbids division), and it also
// breaks if any element is 0 (division by zero). Shown only for comparison.
// ---------------------------------------------------------------------------
vector<int> productExceptSelfDivision(vector<int>& nums) {
  int n = nums.size();
  int totalProduct = 1;
  int zeroCount = 0;

  for (int num : nums) {
    if (num == 0)
      zeroCount++;
    else
      totalProduct *= num;
  }

  vector<int> answer(n);

  for (int i = 0; i < n; i++) {
    if (zeroCount > 1) {
      answer[i] = 0;  // more than one zero -> every product is 0
    } else if (zeroCount == 1) {
      answer[i] = (nums[i] == 0) ? totalProduct : 0;
    } else {
      answer[i] = totalProduct / nums[i];
    }
  }

  return answer;
}

// ---------------------------------------------------------------------------
// Approach 2: Prefix and Suffix Arrays -> O(n) time, O(n) space
//
// Beginner intuition: answer[i] = (product of everything BEFORE i)
//                                * (product of everything AFTER i)
//
// Build two helper arrays:
//   prefix[i] = product of nums[0..i-1]  (everything to the LEFT of i)
//   suffix[i] = product of nums[i+1..n-1] (everything to the RIGHT of i)
//
// Then answer[i] = prefix[i] * suffix[i]
//
// Example: nums = [1,2,3,4]
//   prefix = [1, 1, 2, 6]     (prefix[0]=1 since nothing is to the left)
//   suffix = [24, 12, 4, 1]   (suffix[3]=1 since nothing is to the right)
//   answer = [1*24, 1*12, 2*4, 6*1] = [24, 12, 8, 6]  correct!
// ---------------------------------------------------------------------------
vector<int> productExceptSelfPrefixSuffix(vector<int>& nums) {
  int n = nums.size();
  vector<int> prefix(n), suffix(n), answer(n);

  prefix[0] = 1;
  for (int i = 1; i < n; i++) {
    prefix[i] = prefix[i - 1] * nums[i - 1];
  }

  suffix[n - 1] = 1;
  for (int i = n - 2; i >= 0; i--) {
    suffix[i] = suffix[i + 1] * nums[i + 1];
  }

  for (int i = 0; i < n; i++) {
    answer[i] = prefix[i] * suffix[i];
  }

  return answer;
}

// ---------------------------------------------------------------------------
// Approach 3: O(1) Extra Space (Optimal, follow-up answer) -> O(n) time, O(1)
// extra space (output array itself doesn't count toward space complexity, per
// problem statement)
//
// Beginner intuition: instead of two separate prefix/suffix arrays,
// reuse the `answer` array to store prefix products FIRST (one pass),
// then multiply in the suffix products on a SECOND pass using just a
// single running variable (no suffix array needed).
//
// Step 1: answer[i] = product of everything BEFORE i (same as prefix array)
// Step 2: walk from the right with a running suffix product variable,
//         multiply it directly into answer[i] as we go.
// ---------------------------------------------------------------------------
vector<int> productExceptSelfOptimal(vector<int>& nums) {
  int n = nums.size();
  vector<int> answer(n);

  // Step 1: answer[i] holds prefix product (product of everything left of i)
  answer[0] = 1;
  for (int i = 1; i < n; i++) {
    answer[i] = answer[i - 1] * nums[i - 1];
  }

  // Step 2: multiply in suffix product using a single running variable
  int suffixProduct = 1;
  for (int i = n - 1; i >= 0; i--) {
    answer[i] *= suffixProduct;
    suffixProduct *=
        nums[i];  // update running suffix product for next (left) index
  }

  return answer;
}

// ---------------------------------------------------------------------------
// Driver code (hardcoded test cases, no cin)
// ---------------------------------------------------------------------------
int main() {
  vector<vector<int>> testCases = {
      {1, 2, 3, 4},      // expected [24,12,8,6]
      {-1, 1, 0, -3, 3}  // expected [0,0,9,0,0]
  };

  auto printVec = [](const string& label, vector<int>& v) {
    cout << label << ": [";
    for (int i = 0; i < (int)v.size(); i++) {
      cout << v[i];
      if (i < (int)v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
  };

  for (auto& nums : testCases) {
    vector<int> n1 = nums, n2 = nums, n3 = nums;

    vector<int> res1 = productExceptSelfDivision(n1);
    vector<int> res2 = productExceptSelfPrefixSuffix(n2);
    vector<int> res3 = productExceptSelfOptimal(n3);

    printVec("Division (not allowed here)", res1);
    printVec("Prefix+Suffix Arrays", res2);
    printVec("Optimal O(1) space", res3);
    cout << "-----------------------------------" << endl;
  }

  return 0;
}