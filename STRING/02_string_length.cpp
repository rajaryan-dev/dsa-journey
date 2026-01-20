#include <iostream>
#include <cstring>  // For strlen() function
#include <string>   // For std::string

using namespace std;

/*
 * ============================================================================
 * STRING LENGTH OPERATIONS IN C++
 * ============================================================================
 * 
 * This file demonstrates different methods to find string length:
 * 1. strlen() for C-style strings
 * 2. .length() and .size() for C++ strings
 * 3. Common pitfalls and edge cases
 */

int main() {
    
    // ========================================================================
    // STEP 1: Finding Length of C-Style Strings using strlen()
    // ========================================================================
    
    // strlen() counts characters until it finds null terminator '\0'
    // It does NOT count the null terminator itself
    
    char cStr1[] = "Hello";
    // Memory: ['H']['e']['l']['l']['o']['\0']
    // strlen() counts: 5 characters (stops at '\0')
    
    cout << "C-style string: " << cStr1 << endl;
    cout << "Length using strlen(): " << strlen(cStr1) << endl;
    
    
    // ========================================================================
    // STEP 2: Edge Case - Single Character Array
    // ========================================================================
    
    // IMPORTANT: This is a common pitfall!
    char singleChar[] = {'a'};  // No null terminator added!
    
    // WARNING: This is DANGEROUS!
    // strlen() will keep reading memory beyond 'a' until it finds '\0'
    // This can cause undefined behavior (random values or crashes)
    
    cout << "\nSingle character array (NO null terminator):" << endl;
    cout << "Length: " << strlen(singleChar) << " (UNDEFINED BEHAVIOR!)" << endl;
    
    // CORRECT WAY: Always add null terminator for C-style strings
    char singleCharCorrect[] = {'a', '\0'};  // Explicitly add '\0'
    cout << "Single character with null terminator: " << strlen(singleCharCorrect) << endl;
    
    // OR use string literal (automatically adds '\0')
    char singleCharBetter[] = "a";
    cout << "Using string literal: " << strlen(singleCharBetter) << endl;
    
    
    // ========================================================================
    // STEP 3: Finding Length of C++ std::string
    // ========================================================================
    
    // C++ strings have built-in methods to get length
    // Both .length() and .size() do the same thing
    
    string cppStr = "apna college";
    
    // Method 1: Using .length()
    cout << "\nC++ string: " << cppStr << endl;
    cout << "Length using .length(): " << cppStr.length() << endl;
    
    // Method 2: Using .size() (identical to .length())
    cout << "Length using .size(): " << cppStr.size() << endl;
    
    
    // ========================================================================
    // STEP 4: Comparing strlen() vs .length()
    // ========================================================================
    
    /*
     * strlen() - For C-style strings (char arrays):
     * - Requires #include <cstring>
     * - Counts characters until '\0'
     * - Returns size_t (unsigned integer)
     * - O(n) time complexity (must traverse entire string)
     * - Dangerous if string is not null-terminated
     * 
     * .length() / .size() - For C++ std::string:
     * - Requires #include <string>
     * - Returns stored length value
     * - Returns size_t (unsigned integer)
     * - O(1) time complexity (constant time)
     * - Always safe (string manages its own length)
     */
    
    
    // ========================================================================
    // STEP 5: Edge Cases and Special Scenarios
    // ========================================================================
    
    // Empty string
    string emptyStr = "";
    cout << "\nEmpty string length: " << emptyStr.length() << endl;
    
    // String with spaces
    string strWithSpaces = "Hello World";
    cout << "String with spaces: '" << strWithSpaces << "'" << endl;
    cout << "Length (spaces count): " << strWithSpaces.length() << endl;
    
    // String with special characters
    string specialStr = "Hello@123!";
    cout << "String with special chars: '" << specialStr << "'" << endl;
    cout << "Length: " << specialStr.length() << endl;
    
    // String with newline and tab
    string escapeStr = "Line1\nLine2\tTab";
    cout << "String with escape sequences: " << endl;
    cout << escapeStr << endl;
    cout << "Length (\\n and \\t count as 1 char each): " << escapeStr.length() << endl;
    
    
    // ========================================================================
    // STEP 6: Using Length in Loops
    // ========================================================================
    
    string word = "DSA";
    cout << "\nIterating through string '" << word << "':" << endl;
    
    // Common pattern: Use length() to iterate through string
    for(int i = 0; i < word.length(); i++) {
        cout << "Character at index " << i << ": " << word[i] << endl;
    }
    
    // Alternative: Store length in variable (more efficient in loops)
    int len = word.length();
    cout << "\nReverse iteration:" << endl;
    for(int i = len - 1; i >= 0; i--) {
        cout << word[i] << " ";
    }
    cout << endl;
    
    
    // ========================================================================
    // SUMMARY
    // ========================================================================
    /*
     * KEY TAKEAWAYS:
     * 1. Use strlen() for C-style strings (char arrays)
     * 2. Use .length() or .size() for C++ std::string
     * 3. Always ensure C-style strings are null-terminated
     * 4. C++ strings are safer - they manage length automatically
     * 5. .length() is O(1) for std::string, strlen() is O(n) for C-strings
     * 6. Spaces and special characters count toward length
     */
    
    return 0;
}
