/*
 * ============================================================
 *  DATA TYPE MODIFIERS IN C++
 * ============================================================
 *  Modifiers alter the meaning of base data types to fit 
 *  various situations more precisely.
 * 
 *  The 4 main data type modifiers in C++ are:
 *  1. signed       3. short
 *  2. unsigned     4. long (and long long)
 * 
 *  --- How they work ---
 * 
 *  [ signed & unsigned ]
 *  - Applicable to: int, char
 *  - Default: int and char are `signed` by default.
 *  - `signed`   : Can hold both negative and positive values.
 *                 (1 bit is used for the sign).
 *  - `unsigned` : Can hold ONLY positive values and zero.
 *                 Because it frees up the sign bit, the maximum
 *                 positive value is doubled!
 * 
 *  [ short & long ]
 *  - Applicable to: int, double (only long)
 *  - `short` : Optimizes space (usually 2 bytes for int).
 *  - `long`  : Increases capacity (usually 4 or 8 bytes for int).
 *  - `long long` : Guarantees at least 8 bytes for massive numbers.
 * 
 *  Note: Size in bytes depends on the compiler/architecture, 
 *  but the relationships (short <= int <= long) always hold.
 * ============================================================
 */

#include <iostream>
#include <climits> // For INT_MAX, UINT_MAX, etc.
using namespace std;

int main() {
    cout << "===== Data Type Modifiers =====\n\n";

    // 1. SIGNED vs UNSIGNED
    int normalInt = -10; // Same as 'signed int'
    unsigned int uInt = 10;
    
    cout << "1. SIGNED vs UNSIGNED:\n";
    cout << "   Max Signed Int   : " << INT_MAX << "\n";
    cout << "   Max Unsigned Int : " << UINT_MAX << " (Notice it's 2x the signed max!)\n\n";

    // What happens if you assign a negative number to an unsigned int?
    // It "wraps around" the maximum value (Underflow)
    unsigned int wrapped = -1;
    cout << "   Assigning -1 to unsigned int results in: " << wrapped << " (Underflow!)\n\n";

    // 2. SHORT, LONG, and LONG LONG sizes
    cout << "2. SIZES IN BYTES (using sizeof):\n";
    cout << "   short int     : " << sizeof(short int) << " bytes\n";
    cout << "   int           : " << sizeof(int) << " bytes\n";
    cout << "   long int      : " << sizeof(long int) << " bytes\n";
    cout << "   long long int : " << sizeof(long long int) << " bytes\n\n";
    
    // For floating point numbers
    cout << "   double        : " << sizeof(double) << " bytes\n";
    cout << "   long double   : " << sizeof(long double) << " bytes\n";

    return 0;
}
