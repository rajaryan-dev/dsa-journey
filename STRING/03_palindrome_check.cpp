#include <iostream>
#include <string>

using namespace std;

/*
 * ============================================================================
 * PALINDROME CHECKING ALGORITHMS
 * ============================================================================
 * 
 * A palindrome is a string that reads the same forwards and backwards.
 * Examples: "racecar", "madam", "A man a plan a canal Panama"
 * 
 * This file covers:
 * 1. Basic palindrome check (simple strings)
 * 2. Valid palindrome (ignoring non-alphanumeric characters and case)
 * 3. Two-pointer technique
 */


// ============================================================================
// APPROACH 1: Basic Palindrome Check
// ============================================================================

/*
 * ALGORITHM:
 * - Use two pointers: one at start, one at end
 * - Compare characters at both pointers
 * - Move pointers toward center
 * - If any mismatch found, return false
 * - If all characters match, return true
 * 
 * TIME COMPLEXITY: O(n/2) = O(n) where n is string length
 * SPACE COMPLEXITY: O(1) - only using two pointer variables
 */

bool isBasicPalindrome(string s) {
    
    // STEP 1: Initialize two pointers
    int start = 0;              // Points to beginning of string
    int end = s.length() - 1;   // Points to end of string
    
    // STEP 2: Compare characters from both ends moving toward center
    while(start < end) {
        
        // STEP 3: If characters don't match, not a palindrome
        if(s[start] != s[end]) {
            return false;
        }
        
        // STEP 4: Move pointers toward center
        start++;    // Move right
        end--;      // Move left
    }
    
    // STEP 5: All characters matched, it's a palindrome
    return true;
}


// ============================================================================
// APPROACH 2: Valid Palindrome (Alphanumeric Only, Case Insensitive)
// ============================================================================

/*
 * PROBLEM: Check if string is palindrome considering only alphanumeric 
 * characters and ignoring case.
 * 
 * Example: "A man, a plan, a canal: Panama" -> true
 * After filtering: "amanaplanacanalpanama" -> palindrome!
 * 
 * ALGORITHM:
 * - Use two pointers like before
 * - Skip non-alphanumeric characters
 * - Compare characters in lowercase
 * 
 * TIME COMPLEXITY: O(n)
 * SPACE COMPLEXITY: O(1)
 */

// Helper function to check if character is alphanumeric
bool isAlphaNumeric(char ch) {
    // Check if character is:
    // - Digit (0-9) OR
    // - Uppercase letter (A-Z) OR
    // - Lowercase letter (a-z)
    
    if((ch >= '0' && ch <= '9') ||           // Is digit?
       (ch >= 'A' && ch <= 'Z') ||           // Is uppercase letter?
       (ch >= 'a' && ch <= 'z')) {           // Is lowercase letter?
        return true;
    }
    
    return false;
}

// Alternative: Using built-in function
bool isAlphaNumericBuiltIn(char ch) {
    // isalnum() is a built-in function from <cctype>
    // Returns true if character is alphanumeric
    return isalnum(ch);
}

bool isValidPalindrome(string s) {
    
    // STEP 1: Initialize two pointers
    int start = 0;
    int end = s.length() - 1;
    
    // STEP 2: Process string from both ends
    while(start < end) {
        
        // STEP 3: Skip non-alphanumeric characters from left
        // If current character is not alphanumeric, move to next
        if(!isalnum(s[start])) {
            start++;
            continue;  // Skip to next iteration
        }
        
        // STEP 4: Skip non-alphanumeric characters from right
        // If current character is not alphanumeric, move to previous
        if(!isalnum(s[end])) {
            end--;
            continue;  // Skip to next iteration
        }
        
        // STEP 5: Compare characters (case-insensitive)
        // tolower() converts character to lowercase
        // This ensures 'A' and 'a' are treated as same
        if(tolower(s[start]) != tolower(s[end])) {
            return false;  // Mismatch found
        }
        
        // STEP 6: Move both pointers toward center
        start++;
        end--;
    }
    
    // STEP 7: All valid characters matched
    return true;
}


// ============================================================================
// MAIN FUNCTION - Testing Both Approaches
// ============================================================================

int main() {
    
    cout << "============================================" << endl;
    cout << "PALINDROME CHECKING DEMONSTRATIONS" << endl;
    cout << "============================================" << endl;
    
    
    // ========================================================================
    // TEST 1: Basic Palindrome Check
    // ========================================================================
    
    cout << "\n--- TEST 1: Basic Palindrome Check ---" << endl;
    
    string test1 = "racecar";
    cout << "String: '" << test1 << "'" << endl;
    cout << "Is palindrome? " << (isBasicPalindrome(test1) ? "YES" : "NO") << endl;
    
    string test2 = "hello";
    cout << "\nString: '" << test2 << "'" << endl;
    cout << "Is palindrome? " << (isBasicPalindrome(test2) ? "YES" : "NO") << endl;
    
    string test3 = "madam";
    cout << "\nString: '" << test3 << "'" << endl;
    cout << "Is palindrome? " << (isBasicPalindrome(test3) ? "YES" : "NO") << endl;
    
    
    // ========================================================================
    // TEST 2: Valid Palindrome (Alphanumeric, Case Insensitive)
    // ========================================================================
    
    cout << "\n\n--- TEST 2: Valid Palindrome (Ignore Special Chars & Case) ---" << endl;
    
    string test4 = "r@ace$ca&r";
    cout << "String: '" << test4 << "'" << endl;
    cout << "After filtering: 'racecar'" << endl;
    cout << "Is valid palindrome? " << (isValidPalindrome(test4) ? "YES" : "NO") << endl;
    
    string test5 = "A man, a plan, a canal: Panama";
    cout << "\nString: '" << test5 << "'" << endl;
    cout << "After filtering: 'amanaplanacanalpanama'" << endl;
    cout << "Is valid palindrome? " << (isValidPalindrome(test5) ? "YES" : "NO") << endl;
    
    string test6 = "race a car";
    cout << "\nString: '" << test6 << "'" << endl;
    cout << "After filtering: 'raceacar'" << endl;
    cout << "Is valid palindrome? " << (isValidPalindrome(test6) ? "YES" : "NO") << endl;
    
    string test7 = "RaceCar";
    cout << "\nString: '" << test7 << "'" << endl;
    cout << "After filtering: 'racecar'" << endl;
    cout << "Is valid palindrome? " << (isValidPalindrome(test7) ? "YES" : "NO") << endl;
    
    
    // ========================================================================
    // ALGORITHM EXPLANATION
    // ========================================================================
    
    cout << "\n\n============================================" << endl;
    cout << "TWO-POINTER TECHNIQUE EXPLANATION" << endl;
    cout << "============================================" << endl;
    cout << "\nFor string 'racecar':" << endl;
    cout << "Step 1: Compare r(0) and r(6) -> Match" << endl;
    cout << "Step 2: Compare a(1) and a(5) -> Match" << endl;
    cout << "Step 3: Compare c(2) and c(4) -> Match" << endl;
    cout << "Step 4: Pointers meet at e(3) -> PALINDROME!" << endl;
    
    cout << "\nFor string 'hello':" << endl;
    cout << "Step 1: Compare h(0) and o(4) -> MISMATCH!" << endl;
    cout << "Result: NOT a palindrome" << endl;
    
    
    // ========================================================================
    // SUMMARY
    // ========================================================================
    
    cout << "\n\n============================================" << endl;
    cout << "KEY CONCEPTS" << endl;
    cout << "============================================" << endl;
    cout << "1. Two-pointer technique: Start and end pointers" << endl;
    cout << "2. Basic palindrome: Exact character match" << endl;
    cout << "3. Valid palindrome: Ignore non-alphanumeric, case" << endl;
    cout << "4. Time: O(n), Space: O(1)" << endl;
    cout << "5. Use isalnum() and tolower() for filtering" << endl;
    
    return 0;
}
