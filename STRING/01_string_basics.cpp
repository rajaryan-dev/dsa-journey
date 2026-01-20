#include <iostream>
#include <cstring>  // For C-style string functions like strlen()
#include <string>   // For C++ std::string class

using namespace std;

/*
 * ============================================================================
 * STRING BASICS IN C++
 * ============================================================================
 * 
 * This file covers fundamental concepts of strings in C++:
 * 1. C-style strings (character arrays)
 * 2. C++ std::string class
 * 3. Basic operations and differences between them
 */

int main() {
    
    // ========================================================================
    // STEP 1: Understanding C-Style Strings (Character Arrays)
    // ========================================================================
    
    // C-style strings are arrays of characters terminated by null character '\0'
    // They are inherited from C programming language
    
    char cStyleStr1[] = "Hello";  // Compiler automatically adds '\0' at end
    // Memory: ['H']['e']['l']['l']['o']['\0']
    
    char cStyleStr2[20] = "World"; // Fixed size array, can hold up to 19 chars + '\0'
    
    cout << "C-style string 1: " << cStyleStr1 << endl;
    cout << "C-style string 2: " << cStyleStr2 << endl;
    
    
    // ========================================================================
    // STEP 2: Understanding C++ std::string Class
    // ========================================================================
    
    // std::string is a class in C++ Standard Library
    // It provides dynamic memory management and many useful methods
    // Much safer and easier to use than C-style strings
    
    string cppString1 = "apna college";  // Simple initialization
    
    string cppString2("Hello World");   // Constructor initialization
    
    string cppString3;                   // Empty string
    cppString3 = "Assigned later";       // Assignment
    
    cout << "\nC++ string 1: " << cppString1 << endl;
    cout << "C++ string 2: " << cppString2 << endl;
    cout << "C++ string 3: " << cppString3 << endl;
    
    
    // ========================================================================
    // STEP 3: Key Differences Between C-Style and C++ Strings
    // ========================================================================
    
    /*
     * C-STYLE STRINGS:
     * - Fixed size (must declare size in advance)
     * - Manual memory management
     * - Need to use functions like strlen(), strcpy(), strcat()
     * - Prone to buffer overflow errors
     * - Null-terminated ('\0')
     * 
     * C++ std::string:
     * - Dynamic size (grows/shrinks automatically)
     * - Automatic memory management
     * - Rich set of member functions (.length(), .append(), etc.)
     * - Safer, prevents common errors
     * - Internally manages null termination
     */
    
    
    // ========================================================================
    // STEP 4: Basic String Operations with std::string
    // ========================================================================
    
    string str = "Learning";
    
    // Get length of string
    cout << "\nLength of '" << str << "': " << str.length() << endl;
    
    // Concatenation (joining strings)
    string str2 = " DSA";
    string combined = str + str2;  // Using + operator
    cout << "Combined: " << combined << endl;
    
    // Accessing individual characters (0-indexed)
    cout << "First character: " << str[0] << endl;
    cout << "Last character: " << str[str.length() - 1] << endl;
    
    
    // ========================================================================
    // STEP 5: String Input/Output
    // ========================================================================
    
    // Note: cin stops reading at whitespace
    // For reading full lines with spaces, use getline()
    
    string userInput;
    cout << "\nEnter a single word: ";
    cin >> userInput;  // Reads until whitespace
    cout << "You entered: " << userInput << endl;
    
    // Clear the input buffer before using getline
    cin.ignore();
    
    string fullLine;
    cout << "Enter a full sentence: ";
    getline(cin, fullLine);  // Reads entire line including spaces
    cout << "You entered: " << fullLine << endl;
    
    
    // ========================================================================
    // SUMMARY
    // ========================================================================
    /*
     * - Use std::string for modern C++ programming (safer and easier)
     * - C-style strings are still used in legacy code and system programming
     * - std::string provides automatic memory management
     * - Use getline() for reading strings with spaces
     */
    
    return 0;
}
