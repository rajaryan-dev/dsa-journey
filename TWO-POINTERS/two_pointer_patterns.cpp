/*
 * ============================================================
 *  TWO POINTERS TECHNIQUE
 * ============================================================
 *  Pattern: Use two indices (lo/hi, slow/fast, left/right)
 *  to scan the array from both ends or at different speeds.
 *
 *  When to use:
 *   - Sorted array problems
 *   - Finding pairs/triplets with a condition
 *   - In-place array modification
 *   - Linked list cycle detection
 *
 *  Topics:
 *   1. Two Sum II (sorted array) — LC 167
 *   2. Three Sum — LC 15
 *   3. Four Sum — LC 18
 *   4. Container With Most Water — LC 11
 *   5. Trapping Rain Water — LC 42
 *   6. Remove Duplicates from Sorted Array — LC 26
 *   7. Move Zeros — LC 283
 *   8. Sort Colors (Dutch National Flag) — LC 75
 *   9. Palindrome Check (two pointers)
 *  10. Linked List Cycle Detection (Floyd's) — LC 141/142
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  1. Two Sum II — sorted array — LC 167
// ─────────────────────────────────────────────────────────────
vector<int> twoSumSorted(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int sum = nums[lo] + nums[hi];
        if (sum == target) return {lo + 1, hi + 1}; // 1-indexed
        else if (sum < target) lo++;
        else                   hi--;
    }
    return {-1, -1};
}

// ─────────────────────────────────────────────────────────────
//  2. Three Sum — LC 15
//  Sort, fix one element, two-pointer on rest.
// ─────────────────────────────────────────────────────────────
vector<vector<int>> threeSum(vector<int> nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    int n = nums.size();
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue; // skip duplicates
        int lo = i + 1, hi = n - 1;
        while (lo < hi) {
            int sum = nums[i] + nums[lo] + nums[hi];
            if (sum == 0) {
                res.push_back({nums[i], nums[lo], nums[hi]});
                while (lo < hi && nums[lo] == nums[lo+1]) lo++;
                while (lo < hi && nums[hi] == nums[hi-1]) hi--;
                lo++; hi--;
            }
            else if (sum < 0) lo++;
            else              hi--;
        }
    }
    return res;
}

// ─────────────────────────────────────────────────────────────
//  3. Four Sum — LC 18
//  Fix two elements, two-pointer on remaining.
// ─────────────────────────────────────────────────────────────
vector<vector<int>> fourSum(vector<int> nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    int n = nums.size();
    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j-1]) continue;
            int lo = j + 1, hi = n - 1;
            while (lo < hi) {
                long long sum = (long long)nums[i] + nums[j] + nums[lo] + nums[hi];
                if (sum == target) {
                    res.push_back({nums[i], nums[j], nums[lo], nums[hi]});
                    while (lo < hi && nums[lo] == nums[lo+1]) lo++;
                    while (lo < hi && nums[hi] == nums[hi-1]) hi--;
                    lo++; hi--;
                }
                else if (sum < target) lo++;
                else                   hi--;
            }
        }
    }
    return res;
}

// ─────────────────────────────────────────────────────────────
//  4. Container With Most Water — LC 11
//  Two pointers from both ends; move the shorter side inward.
// ─────────────────────────────────────────────────────────────
int maxArea(vector<int>& height) {
    int lo = 0, hi = height.size() - 1, best = 0;
    while (lo < hi) {
        int water = min(height[lo], height[hi]) * (hi - lo);
        best = max(best, water);
        if (height[lo] < height[hi]) lo++;
        else                          hi--;
    }
    return best;
}

// ─────────────────────────────────────────────────────────────
//  5. Trapping Rain Water — LC 42
//  Water at i = min(maxLeft[i], maxRight[i]) - height[i]
//  Two-pointer approach (O(1) space):
// ─────────────────────────────────────────────────────────────
int trap(vector<int>& height) {
    int lo = 0, hi = height.size() - 1;
    int maxL = 0, maxR = 0, water = 0;
    while (lo <= hi) {
        if (height[lo] <= height[hi]) {
            if (height[lo] >= maxL) maxL = height[lo];
            else water += maxL - height[lo];
            lo++;
        } else {
            if (height[hi] >= maxR) maxR = height[hi];
            else water += maxR - height[hi];
            hi--;
        }
    }
    return water;
}

// ─────────────────────────────────────────────────────────────
//  6. Remove Duplicates from Sorted Array — LC 26
//  Slow pointer: next unique position  |  Fast: scanner
// ─────────────────────────────────────────────────────────────
int removeDuplicates(vector<int>& nums) {
    int slow = 0;
    for (int fast = 1; fast < (int)nums.size(); fast++)
        if (nums[fast] != nums[slow]) nums[++slow] = nums[fast];
    return slow + 1;
}

// ─────────────────────────────────────────────────────────────
//  7. Move Zeros — LC 283
// ─────────────────────────────────────────────────────────────
void moveZeroes(vector<int>& nums) {
    int slow = 0;
    for (int fast = 0; fast < (int)nums.size(); fast++)
        if (nums[fast] != 0) nums[slow++] = nums[fast];
    while (slow < (int)nums.size()) nums[slow++] = 0;
}

// ─────────────────────────────────────────────────────────────
//  8. Sort Colors (Dutch National Flag) — LC 75
//  Three pointers: lo(red boundary), mid(current), hi(blue boundary)
// ─────────────────────────────────────────────────────────────
void sortColors(vector<int>& nums) {
    int lo = 0, mid = 0, hi = nums.size() - 1;
    while (mid <= hi) {
        if      (nums[mid] == 0) { swap(nums[lo++], nums[mid++]); }
        else if (nums[mid] == 1) { mid++; }
        else                     { swap(nums[mid],  nums[hi--]); }
    }
}

// ─────────────────────────────────────────────────────────────
//  9. Valid Palindrome — LC 125
// ─────────────────────────────────────────────────────────────
bool isPalindrome(const string& s) {
    int lo = 0, hi = s.size() - 1;
    while (lo < hi) {
        while (lo < hi && !isalnum(s[lo])) lo++;
        while (lo < hi && !isalnum(s[hi])) hi--;
        if (tolower(s[lo]) != tolower(s[hi])) return false;
        lo++; hi--;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────
//  10. Floyd's Cycle Detection — LC 141 / 142
// ─────────────────────────────────────────────────────────────
struct ListNode { int val; ListNode* next; ListNode(int v) : val(v), next(nullptr) {} };

bool hasCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

ListNode* detectCycleStart(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) { slow = slow->next; fast = fast->next; }
            return slow;
        }
    }
    return nullptr;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Two Pointers Technique =====\n\n";

    vector<int> sorted = {2, 7, 11, 15};
    auto [i1, i2] = twoSumSorted(sorted, 9);
    cout << "1. Two Sum II {2,7,11,15} target=9: [" << i1 << "," << i2 << "]\n\n";

    vector<int> ts = {-1, 0, 1, 2, -1, -4};
    cout << "2. Three Sum {-1,0,1,2,-1,-4}:\n";
    for (auto& t : threeSum(ts)) {
        cout << "   ["; for (int v : t) cout << v << ","; cout << "]\n";
    }

    vector<int> fs = {1, 0, -1, 0, -2, 2};
    cout << "\n3. Four Sum {1,0,-1,0,-2,2} target=0:\n";
    for (auto& t : fourSum(fs, 0)) {
        cout << "   ["; for (int v : t) cout << v << ","; cout << "]\n";
    }

    vector<int> h = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "\n4. Max water (1,8,6,2,5,4,8,3,7): " << maxArea(h) << "\n"; // 49

    vector<int> elev = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "\n5. Trapping Rain Water: " << trap(elev) << "\n"; // 6

    vector<int> dup = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    cout << "\n6. Remove duplicates: new length = " << removeDuplicates(dup) << "\n"; // 5

    vector<int> mz = {0, 1, 0, 3, 12};
    moveZeroes(mz);
    cout << "\n7. Move zeros: ";
    for (int x : mz) cout << x << " "; cout << "\n"; // 1 3 12 0 0

    vector<int> colors = {2, 0, 2, 1, 1, 0};
    sortColors(colors);
    cout << "\n8. Sort colors: ";
    for (int x : colors) cout << x << " "; cout << "\n"; // 0 0 1 1 2 2

    cout << "\n9. isPalindrome(\"A man a plan a canal Panama\"): "
         << (isPalindrome("A man a plan a canal Panama") ? "YES" : "NO") << "\n"; // YES

    return 0;
}
