/*
 * ============================================================
 *  VARIABLE SCOPE IN C++
 * ============================================================
 *  Scope determines the lifetime and visibility (where a 
 *  variable can be accessed or modified) of a variable.
 * 
 *  Types of Scope:
 *  1. Local Scope: Variables declared inside a function.
 *     They are destroyed when the function exits.
 *  
 *  2. Global Scope: Variables declared outside all functions.
 *     Accessible from anywhere in the file.
 * 
 *  3. Block Scope: Variables declared inside a specific block `{}` 
 *     (e.g., inside an `if`, `for`, or `while` loop). 
 * 
 *  4. Class Scope: Variables declared inside a class (member variables).
 * 
 *  --- Name Hiding (Shadowing) ---
 *  If a local/block variable has the SAME NAME as an outer or 
 *  global variable, the inner variable "shadows" (hides) the outer one.
 * 
 *  --- Scope Resolution Operator (::) ---
 *  If a local variable shadows a global variable, you can still 
 *  access the GLOBAL variable using the `::` operator (e.g., `::varName`).
 * ============================================================
 */

#include <iostream>
using namespace std;

// === 1. GLOBAL SCOPE ===
int myVar = 100; // This is a global variable

void demonstrateScope() {
    // === 2. LOCAL SCOPE ===
    int myVar = 20; // This local variable SHADOWS the global 'myVar'
    
    cout << "Inside demonstrateScope() function:\n";
    cout << "  Local myVar             : " << myVar << "\n";
    
    // Accessing the global variable using Scope Resolution Operator (::)
    cout << "  Global ::myVar          : " << ::myVar << "\n\n";

    // === 3. BLOCK SCOPE ===
    if (true) {
        int myVar = 5; // This block variable SHADOWS both local and global 'myVar'
        cout << "  Inside if-block:\n";
        cout << "    Block myVar           : " << myVar << "\n";
        cout << "    Global ::myVar        : " << ::myVar << "\n";
        // Note: There is NO way to access the outer local 'myVar' (20) from here 
        // using an operator. It is completely shadowed by the block 'myVar'.
    }

    cout << "\n  Back to demonstrateScope() function (after if-block):\n";
    cout << "  Local myVar is restored : " << myVar << "\n";
}

int main() {
    cout << "===== Variable Scope & Shadowing =====\n\n";
    
    cout << "Inside main() function:\n";
    cout << "  Global ::myVar initially: " << myVar << "\n\n";

    demonstrateScope();

    cout << "\nBack in main() function:\n";
    // Modifying the global variable
    myVar = 999;
    cout << "  Global ::myVar modified : " << myVar << "\n";

    return 0;
}
