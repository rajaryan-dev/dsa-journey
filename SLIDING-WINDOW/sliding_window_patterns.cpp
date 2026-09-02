/*
 * ============================================================
 *  SLIDING WINDOW TECHNIQUE
 * ============================================================
 *  Pattern: Maintain a window [lo, hi] over the array/string.
 *   - Fixed-size window  : hi - lo + 1 = k always
 *   - Variable-size window: expand hi, shrink lo when condition breaks
 *
 *  Template (variable window):
 *    int lo = 0;
 *    for (int hi = 0; hi < n; hi++) {
 *        // Add arr[hi] to window
 *        while (window is invalid) {
 *            // Remove arr[lo] from window
 *            lo++;
 *        }
 *        // Update answer
 *    }
 *
 *  Topics:
 *   1. Max Sum Subarray of Size K (fixed)
 *   2. Longest Substring Without Repeating Chars — LC 3
 *   3. Minimum Window Substring — LC 76
 *   4. Longest Substring with At Most K Distinct Chars — LC 340
 *   5. Permutation in String — LC 567
 *   6. Minimum Size Subarray Sum — LC 209
 *   7. Sliding Window Maximum — LC 239 (deque)
 *   8. Find All Anagrams in String — LC 438
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  1. Max Sum Subarray of Size K (fixed window)
// ─────────────────────────────────────────────────────────────
int maxSumKWindow(vector<int>& arr, int k) {
    int sum = 0, best = INT_MIN;
    for (int i = 0; i < (int)arr.size(); i++) {
        sum += arr[i];
        if (i >= k - 1) {
            best = max(best, sum);
            sum -= arr[i - k + 1];
        }
    }
    return best;
}

// ─────────────────────────────────────────────────────────────
//  2. Longest Substring Without Repeating Characters — LC 3
// ─────────────────────────────────────────────────────────────
int lengthOfLongestSubstring(const string& s) {
    unordered_map<char, int> lastSeen;
    int lo = 0, best = 0;
    for (int hi = 0; hi < (int)s.size(); hi++) {
        if (lastSeen.count(s[hi]) && lastSeen[s[hi]] >= lo)
            lo = lastSeen[s[hi]] + 1;
        lastSeen[s[hi]] = hi;
        best = max(best, hi - lo + 1);
    }
    return best;
}

// ─────────────────────────────────────────────────────────────
//  3. Minimum Window Substring — LC 76
//  Find smallest window in s containing all chars of t.
// ─────────────────────────────────────────────────────────────
string minWindow(const string& s, const string& t) {
    unordered_map<char, int> need, have;
    for (char c : t) need[c]++;
    int lo = 0, satisfied = 0, required = need.size();
    int bestLen = INT_MAX, bestLo = 0;

    for (int hi = 0; hi < (int)s.size(); hi++) {
        have[s[hi]]++;
        if (need.count(s[hi]) && have[s[hi]] == need[s[hi]]) satisfied++;

        while (satisfied == required) {
            if (hi - lo + 1 < bestLen) { bestLen = hi - lo + 1; bestLo = lo; }
            have[s[lo]]--;
            if (need.count(s[lo]) && have[s[lo]] < need[s[lo]]) satisfied--;
            lo++;
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestLo, bestLen);
}

// ─────────────────────────────────────────────────────────────
//  4. Longest Substring with At Most K Distinct Characters — LC 340
// ─────────────────────────────────────────────────────────────
int lengthOfLongestSubstringKDistinct(const string& s, int k) {
    unordered_map<char, int> freq;
    int lo = 0, best = 0;
    for (int hi = 0; hi < (int)s.size(); hi++) {
        freq[s[hi]]++;
        while ((int)freq.size() > k) {
            freq[s[lo]]--;
            if (freq[s[lo]] == 0) freq.erase(s[lo]);
            lo++;
        }
        best = max(best, hi - lo + 1);
    }
    return best;
}

// ─────────────────────────────────────────────────────────────
//  5. Permutation in String — LC 567
//  Is any permutation of p a substring of s?
// ─────────────────────────────────────────────────────────────
bool checkInclusion(const string& p, const string& s) {
    if (p.size() > s.size()) return false;
    vector<int> need(26, 0), have(26, 0);
    for (char c : p) need[c - 'a']++;

    int k = p.size();
    for (int hi = 0; hi < (int)s.size(); hi++) {
        have[s[hi] - 'a']++;
        if (hi >= k) have[s[hi - k] - 'a']--;
        if (have == need) return true;
    }
    return false;
}

// ─────────────────────────────────────────────────────────────
//  6. Minimum Size Subarray Sum — LC 209
//  Smallest subarray with sum >= target
// ─────────────────────────────────────────────────────────────
int minSubArrayLen(int target, vector<int>& nums) {
    int lo = 0, sum = 0, best = INT_MAX;
    for (int hi = 0; hi < (int)nums.size(); hi++) {
        sum += nums[hi];
        while (sum >= target) {
            best = min(best, hi - lo + 1);
            sum -= nums[lo++];
        }
    }
    return best == INT_MAX ? 0 : best;
}

// ─────────────────────────────────────────────────────────────
//  7. Sliding Window Maximum — LC 239
//  Use monotonic deque to track maximum efficiently.
// ─────────────────────────────────────────────────────────────
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; // stores INDICES, front = largest element's index
    vector<int> res;
    for (int hi = 0; hi < (int)nums.size(); hi++) {
        // Remove indices outside window
        while (!dq.empty() && dq.front() < hi - k + 1) dq.pop_front();
        // Remove smaller elements (they'll never be the max)
        while (!dq.empty() && nums[dq.back()] < nums[hi]) dq.pop_back();
        dq.push_back(hi);
        if (hi >= k - 1) res.push_back(nums[dq.front()]);
    }
    return res;
}

// ─────────────────────────────────────────────────────────────
//  8. Find All Anagrams in String — LC 438
// ─────────────────────────────────────────────────────────────
vector<int> findAnagrams(const string& s, const string& p) {
    if (p.size() > s.size()) return {};
    vector<int> need(26, 0), have(26, 0), res;
    for (char c : p) need[c - 'a']++;
    int k = p.size();
    for (int hi = 0; hi < (int)s.size(); hi++) {
        have[s[hi] - 'a']++;
        if (hi >= k) have[s[hi - k] - 'a']--;
        if (have == need) res.push_back(hi - k + 1);
    }
    return res;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Sliding Window Technique =====\n\n";

    vector<int> arr = {2, 1, 5, 1, 3, 2};
    cout << "1. Max sum of size 3 in {2,1,5,1,3,2}: "
         << maxSumKWindow(arr, 3) << "\n"; // 9

    cout << "\n2. Longest substring without repeating:\n";
    cout << "   \"abcabcbb\": " << lengthOfLongestSubstring("abcabcbb") << "\n"; // 3
    cout << "   \"pwwkew\":   " << lengthOfLongestSubstring("pwwkew")   << "\n"; // 3

    cout << "\n3. Minimum Window Substring:\n";
    cout << "   s=\"ADOBECODEBANC\" t=\"ABC\": \""
         << minWindow("ADOBECODEBANC", "ABC") << "\"\n"; // BANC

    cout << "\n4. Longest substr with at most 2 distinct:\n";
    cout << "   \"eceba\" k=2: " << lengthOfLongestSubstringKDistinct("eceba", 2) << "\n"; // 3

    cout << "\n5. Permutation in String:\n";
    cout << "   p=\"ab\" in s=\"eidbaooo\": "
         << (checkInclusion("ab","eidbaooo") ? "YES":"NO") << "\n"; // YES

    cout << "\n6. Min subarray sum >= 7 in {2,3,1,2,4,3}:\n";
    vector<int> ms = {2,3,1,2,4,3};
    cout << "   Length = " << minSubArrayLen(7, ms) << "\n"; // 2

    cout << "\n7. Sliding window max {1,3,-1,-3,5,3,6,7} k=3:\n   ";
    vector<int> sw = {1,3,-1,-3,5,3,6,7};
    for (int v : maxSlidingWindow(sw, 3)) cout << v << " ";
    cout << "\n"; // 3 3 5 5 6 7

    cout << "\n8. Anagram positions of \"abc\" in \"cbaebabacd\":\n   ";
    for (int pos : findAnagrams("cbaebabacd", "abc")) cout << pos << " ";
    cout << "\n"; // 0 6

    return 0;
}
