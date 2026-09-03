/*
 * ============================================================
 *  OPERATOR PRECEDENCE & ASSOCIATIVITY
 * ============================================================
 *  Precedence determines which operator is evaluated first.
 *  Associativity determines the order (Left-to-Right or 
 *  Right-to-Left) when operators have the SAME precedence.
 * 
 *  --- Simplified Precedence Table (Highest to Lowest) ---
 * 
 *  Level | Operators                        | Associativity
 *  ---------------------------------------------------------
 *    1   | !, +, - (unary operators)        | Right to Left
 *    2   | *, /, % (multiplicative)         | Left to Right
 *    3   | +, -    (additive)               | Left to Right
 *    4   | <<, >>  (bitwise shifts)         | Left to Right
 *    5   | <, <=, >, >= (relational)        | Left to Right
 *    6   | ==, !=  (equality)               | Left to Right
 *    7   | &       (bitwise AND)            | Left to Right
 *    8   | ^       (bitwise XOR)            | Left to Right
 *    9   | |       (bitwise OR)             | Left to Right
 *   10   | &&      (logical AND)            | Left to Right
 *   11   | ||      (logical OR)             | Left to Right
 *   12   | =       (assignment)             | Right to Left
 * 
 *  KEY TAKEAWAYS FOR REVISION:
 *  1. Arithmetic (*, /, +) happens BEFORE Bitwise shifts (<<, >>).
 *     Example: 1 << 2 + 1  => Evaluates as 1 << (2 + 1) = 8.
 *              (NOT (1 << 2) + 1 = 5).
 * 
 *  2. Relational (==, <) happens BEFORE Bitwise logic (&, |, ^).
 *     Example: if (a & b == 0) => Evaluates as a & (b == 0).
 *              ALWAYS use brackets: if ((a & b) == 0)
 * 
 *  3. Logical AND (&&) happens BEFORE Logical OR (||).
 * 
 *  Golden Rule: When in doubt, just use parentheses `()`. 
 *  It makes your code safe and readable!
 * ============================================================
 */

#include <iostream>
using namespace std;

int main() {
    cout << "===== Operator Precedence Examples =====\n\n";

    // 1. Arithmetic vs Bitwise Shift
    // Expected: + has higher precedence than <<
    int val1 = 1 << 2 + 1; 
    cout << "1 << 2 + 1       = " << val1 << "   (Evaluated as 1 << 3)\n";

    // Correct way if you wanted shift first:
    int val2 = (1 << 2) + 1;
    cout << "(1 << 2) + 1     = " << val2 << "   (Evaluated as 4 + 1)\n\n";

    // 2. Bitwise AND vs Equality
    // Expected: == has higher precedence than &
    int a = 5; // 0101 in binary
    int b = 1; // 0001 in binary
    
    // a & b is 1. We want to check if (a & b) == 1.
    // Let's see what happens without brackets:
    bool res1 = a & b == 1; 
    // Evaluates as: a & (b == 1) => 5 & 1 => 1 (true)
    // Wait, by coincidence it works here, but what if b = 4?
    
    b = 4; // 0100
    // We want to check if (a & b) == 4 (which is true)
    bool res2 = a & b == 4; 
    // Evaluates as: a & (b == 4) => 5 & (true) => 5 & 1 => 1 (true - wait, 1 is true but it evaluated wrongly!)
    // Let's print the actual integer value of the expression
    int res3 = a & b == 4; 
    cout << "a & b == 4       = " << res3 << "   (Evaluated as a & (b == 4) => 5 & 1 => 1)\n";
    
    int res4 = (a & b) == 4;
    cout << "(a & b) == 4     = " << res4 << "   (Evaluated correctly as 4 == 4 => 1)\n\n";

    // 3. Associativity (Left to Right vs Right to Left)
    // Assignment is Right to Left
    int x, y, z;
    x = y = z = 10; // Evaluated as x = (y = (z = 10))
    cout << "x = y = z = 10   => x:" << x << ", y:" << y << ", z:" << z << "\n";

    // Division is Left to Right
    int divRes = 100 / 10 / 2; // Evaluated as (100 / 10) / 2 = 5
    cout << "100 / 10 / 2     = " << divRes << "   (Evaluated left to right)\n\n";

    return 0;
}
