#include <iostream>
#include <string>

using namespace std;

/*
 * ============================================================================
 * PERMUTATION IN STRING - SLIDING WINDOW PATTERN
 * ============================================================================
 * 
 * PROBLEM: Given two strings s1 and s2, return true if s2 contains a 
 * permutation of s1, or false otherwise.
 * 
 * In other words, return true if one of s1's permutations is a substring of s2.
 * 
 * Example 1:
 * Input: s1 = "ab", s2 = "eidbaooo"
 * Output: true
 * Explanation: s2 contains "ba" which is a permutation of "ab"
 * 
 * Example 2:
 * Input: s1 = "ab", s2 = "eidboaoo"
 * Output: false
 * 
 * APPROACH: Sliding Window + Frequency Array
 * TIME COMPLEXITY: O(n * m) where n = s2.length(), m = s1.length()
 * SPACE COMPLEXITY: O(1) - fixed size arrays (26 for lowercase letters)
 */


// ============================================================================
// HELPER FUNCTION: Compare Two Frequency Arrays
// ============================================================================

/*
 * PURPOSE: Check if two frequency arrays are identical
 * 
 * PARAMETERS:
 * - freq1[]: Frequency array of target string (s1)
 * - freq2[]: Frequency array of current window in s2
 * 
 * RETURNS: true if both arrays have same frequencies, false otherwise
 */

bool isFrequencySame(int freq1[], int freq2[]) {
    
    // STEP 1: Compare all 26 positions (for 'a' to 'z')
    for(int i = 0; i < 26; i++) {
        
        // STEP 2: If any frequency doesn't match, arrays are different
        if(freq1[i] != freq2[i]) {
            return false;
        }
    }
    
    // STEP 3: All frequencies matched
    return true;
}


// ============================================================================
// MAIN FUNCTION: Check if s2 Contains Permutation of s1
// ============================================================================

/*
 * ALGORITHM BREAKDOWN:
 * 
 * 1. Create frequency array for s1 (target pattern)
 * 2. Use sliding window of size = s1.length() on s2
 * 3. For each window position:
 *    a. Calculate frequency of characters in current window
 *    b. Compare with s1's frequency
 *    c. If match found, return true
 * 4. If no match found after checking all windows, return false
 */

bool checkInclusion(string s1, string s2) {
    
    // ========================================================================
    // STEP 1: Build Frequency Array for Target String (s1)
    // ========================================================================
    
    // Create array to store frequency of each character (a-z)
    // Index 0 = 'a', Index 1 = 'b', ..., Index 25 = 'z'
    int targetFreq[26] = {0};  // Initialize all to 0
    
    // Count frequency of each character in s1
    for(int i = 0; i < s1.length(); i++) {
        // Convert character to index: 'a' -> 0, 'b' -> 1, etc.
        // Example: 'c' - 'a' = 99 - 97 = 2 (index for 'c')
        targetFreq[s1[i] - 'a']++;
    }
    
    // Example: s1 = "ab"
    // targetFreq[0] = 1 (for 'a')
    // targetFreq[1] = 1 (for 'b')
    // All other indices = 0
    
    
    // ========================================================================
    // STEP 2: Define Sliding Window Size
    // ========================================================================
    
    // Window size should be same as s1's length
    // We're looking for permutation of s1, so length must match
    int windowSize = s1.length();
    
    
    // ========================================================================
    // STEP 3: Slide Window Through s2 and Check Each Position
    // ========================================================================
    
    // Try each possible starting position in s2
    for(int i = 0; i < s2.length(); i++) {
        
        // --------------------------------------------------------------------
        // STEP 3a: Initialize Window Variables
        // --------------------------------------------------------------------
        
        int windowIndex = 0;     // Tracks how many chars we've added to window
        int currentPos = i;      // Current position in s2
        
        // Create frequency array for current window
        int windowFreq[26] = {0};
        
        
        // --------------------------------------------------------------------
        // STEP 3b: Build Frequency Array for Current Window
        // --------------------------------------------------------------------
        
        // Fill window with characters starting from position i
        // Continue until window is full OR we reach end of s2
        while(windowIndex < windowSize && currentPos < s2.length()) {
            
            // Add current character to window's frequency array
            windowFreq[s2[currentPos] - 'a']++;
            
            // Move to next character
            windowIndex++;
            currentPos++;
        }
        
        // Example: s2 = "eidbaooo", i = 3, windowSize = 2
        // Window covers: "ba"
        // windowFreq[0] = 1 (for 'a')
        // windowFreq[1] = 1 (for 'b')
        
        
        // --------------------------------------------------------------------
        // STEP 3c: Compare Window Frequency with Target Frequency
        // --------------------------------------------------------------------
        
        // If frequencies match, we found a permutation!
        if(isFrequencySame(targetFreq, windowFreq)) {
            return true;
        }
        
        // Otherwise, continue to next window position
    }
    
    
    // ========================================================================
    // STEP 4: No Permutation Found
    // ========================================================================
    
    // Checked all possible windows, no match found
    return false;
}


// ============================================================================
// MAIN FUNCTION - Testing the Algorithm
// ============================================================================

int main() {
    
    cout << "============================================" << endl;
    cout << "PERMUTATION IN STRING - DEMONSTRATIONS" << endl;
    cout << "============================================" << endl;
    
    
    // ========================================================================
    // TEST CASE 1: Permutation Found
    // ========================================================================
    
    cout << "\n--- TEST CASE 1 ---" << endl;
    string s1_test1 = "ab";
    string s2_test1 = "eidbaooo";
    
    cout << "s1 = \"" << s1_test1 << "\"" << endl;
    cout << "s2 = \"" << s2_test1 << "\"" << endl;
    cout << "\nSearching for permutation of '" << s1_test1 << "' in '" << s2_test1 << "'..." << endl;
    cout << "Possible permutations of 'ab': 'ab', 'ba'" << endl;
    cout << "Found 'ba' at index 3-4 in s2!" << endl;
    cout << "Result: " << (checkInclusion(s1_test1, s2_test1) ? "TRUE" : "FALSE") << endl;
    
    
    // ========================================================================
    // TEST CASE 2: Permutation Not Found
    // ========================================================================
    
    cout << "\n--- TEST CASE 2 ---" << endl;
    string s1_test2 = "ab";
    string s2_test2 = "eidboaoo";
    
    cout << "s1 = \"" << s1_test2 << "\"" << endl;
    cout << "s2 = \"" << s2_test2 << "\"" << endl;
    cout << "\nSearching for permutation of '" << s1_test2 << "' in '" << s2_test2 << "'..." << endl;
    cout << "Possible permutations of 'ab': 'ab', 'ba'" << endl;
    cout << "Neither 'ab' nor 'ba' found as substring in s2" << endl;
    cout << "Result: " << (checkInclusion(s1_test2, s2_test2) ? "TRUE" : "FALSE") << endl;
    
    
    // ========================================================================
    // TEST CASE 3: Custom Example
    // ========================================================================
    
    cout << "\n--- TEST CASE 3 ---" << endl;
    string s1_test3 = "ab";
    string s2_test3 = "xynaefbd";
    
    cout << "s1 = \"" << s1_test3 << "\"" << endl;
    cout << "s2 = \"" << s2_test3 << "\"" << endl;
    cout << "\nSearching for permutation of '" << s1_test3 << "' in '" << s2_test3 << "'..." << endl;
    cout << "Result: " << (checkInclusion(s1_test3, s2_test3) ? "TRUE" : "FALSE") << endl;
    
    
    // ========================================================================
    // ALGORITHM VISUALIZATION
    // ========================================================================
    
    cout << "\n\n============================================" << endl;
    cout << "ALGORITHM VISUALIZATION" << endl;
    cout << "============================================" << endl;
    cout << "\nFor s1='ab', s2='eidbaooo':" << endl;
    cout << "\nTarget frequency (s1='ab'):" << endl;
    cout << "a:1, b:1, others:0" << endl;
    
    cout << "\nSliding window process:" << endl;
    cout << "Window at index 0-1: 'ei' -> a:0, b:0, e:1, i:1 -> NO MATCH" << endl;
    cout << "Window at index 1-2: 'id' -> a:0, b:0, d:1, i:1 -> NO MATCH" << endl;
    cout << "Window at index 2-3: 'db' -> a:0, b:1, d:1 -> NO MATCH" << endl;
    cout << "Window at index 3-4: 'ba' -> a:1, b:1 -> MATCH FOUND!" << endl;
    
    
    // ========================================================================
    // COMPLEXITY ANALYSIS
    // ========================================================================
    
    cout << "\n\n============================================" << endl;
    cout << "COMPLEXITY ANALYSIS" << endl;
    cout << "============================================" << endl;
    cout << "Time Complexity: O(n * m)" << endl;
    cout << "  - n = length of s2 (outer loop)" << endl;
    cout << "  - m = length of s1 (window size)" << endl;
    cout << "  - Frequency comparison: O(26) = O(1)" << endl;
    
    cout << "\nSpace Complexity: O(1)" << endl;
    cout << "  - Two fixed-size arrays of 26 integers" << endl;
    cout << "  - Not dependent on input size" << endl;
    
    
    // ========================================================================
    // KEY CONCEPTS
    // ========================================================================
    
    cout << "\n\n============================================" << endl;
    cout << "KEY CONCEPTS" << endl;
    cout << "============================================" << endl;
    cout << "1. Frequency Array: Map characters to indices (a=0, b=1, ...)" << endl;
    cout << "2. Sliding Window: Fixed-size window moving through string" << endl;
    cout << "3. Permutation Check: Same characters with same frequencies" << endl;
    cout << "4. Character to Index: Use (char - 'a') formula" << endl;
    cout << "5. Pattern: Common in substring/permutation problems" << endl;
    
    return 0;
}
