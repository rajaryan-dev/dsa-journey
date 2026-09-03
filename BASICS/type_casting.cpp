/*
 * ============================================================
 *  C++ TYPE CASTING
 * ============================================================
 *  Type casting is converting one data type into another.
 *  C++ provides 4 specific cast operators that are safer and 
 *  more explicit than C-style casts (e.g., `(int)x`).
 * 
 *  1. static_cast<Type>(expr)
 *     - Used for normal/safe conversions (e.g., float to int).
 *     - Checked at compile time.
 * 
 *  2. dynamic_cast<Type>(expr)
 *     - Used in OOP for safe downcasting (Base* to Derived*).
 *     - Checked at runtime (requires polymorphic base class).
 *     - Returns nullptr (for pointers) if cast fails.
 * 
 *  3. const_cast<Type>(expr)
 *     - Used to add or remove the `const` qualifier.
 *     - Warning: Modifying a value that was originally declared 
 *       const results in undefined behavior!
 * 
 *  4. reinterpret_cast<Type>(expr)
 *     - Dangerous! Casts any pointer type to any other pointer type.
 *     - Used for low-level programming and bitwise manipulations of pointers.
 * ============================================================
 */

#include <iostream>
using namespace std;

void printValue(int* ptr) {
    cout << "Value via const_cast: " << *ptr << "\n";
}

int main() {
    cout << "===== C++ Type Casting Examples =====\n\n";

    // 1. static_cast
    double d = 9.99;
    int i = static_cast<int>(d); // Safely truncates to 9
    cout << "1. static_cast:\n";
    cout << "   Double: " << d << " -> Int: " << i << "\n\n";

    // 2. const_cast
    const int val = 10;
    // printValue(&val); // Error: cannot pass const int* to int*
    cout << "2. const_cast:\n";
    printValue(const_cast<int*>(&val)); // Removes constness just to pass to function
    cout << "\n";

    // 3. reinterpret_cast
    int num = 65;
    // Treat the memory of the integer as a character pointer
    char* charPtr = reinterpret_cast<char*>(&num);
    cout << "3. reinterpret_cast:\n";
    cout << "   Integer 65 interpreted as char: " << *charPtr << " (ASCII 'A')\n";

    return 0;
}
