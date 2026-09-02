/*
 * ============================================================
 *  BITWISE OPERATORS — Complete Concept Reference
 * ============================================================
 *
 *  Operators covered:
 *   &   AND
 *   |   OR
 *   ^   XOR
 *   ~   NOT (bitwise complement)
 *   <<  Left Shift
 *   >>  Right Shift
 *
 *  Plus common bit-manipulation tricks & interview problems.
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ── helpers ──────────────────────────────────────────────────
void printBinary(int n, int bits = 8) {
    cout << "  " << n << " = ";
    for (int i = bits - 1; i >= 0; --i)
        cout << ((n >> i) & 1);
    cout << " (binary)\n";
}

// ─────────────────────────────────────────────────────────────
//  1. AND  ( & )
//  Rule : bit is 1 only when BOTH bits are 1
//  Uses : masking, checking specific bits, clearing bits
// ─────────────────────────────────────────────────────────────
void demo_AND() {
    cout << "\n========== AND ( & ) ==========\n";
    int a = 0b10110110; // 182
    int b = 0b11001101; // 205

    cout << "a = " << a << " (0b10110110)\n";
    cout << "b = " << b << " (0b11001101)\n";
    cout << "a & b = " << (a & b) << "\n"; // 0b10000100 = 132

    // Trick 1 : check if number is ODD
    int n = 13;
    cout << "\nn=" << n << (n & 1 ? " is ODD" : " is EVEN") << "\n";

    // Trick 2 : check if n-th bit is set
    n = 0b10110110; // 182
    int bit = 5;
    bool isSet = (n >> bit) & 1;
    cout << "Is bit " << bit << " set in " << n << "? " << (isSet ? "YES" : "NO") << "\n";

    // Trick 3 : clear the n-th bit  →  n & ~(1 << bit)
    int cleared = n & ~(1 << bit);
    cout << "After clearing bit " << bit << ": " << cleared << "\n";

    // Trick 4 : n & (n-1) clears the lowest set bit
    n = 0b10110000; // 176
    cout << "\nn=" << n << ",  n & (n-1) = " << (n & (n - 1)) << "\n";

    // Trick 5 : check if n is a power of 2
    n = 64;
    cout << n << (n > 0 && (n & (n - 1)) == 0 ? " IS" : " is NOT") << " a power of 2\n";
}

// ─────────────────────────────────────────────────────────────
//  2. OR  ( | )
//  Rule : bit is 1 when AT LEAST ONE bit is 1
//  Uses : setting specific bits, combining flags
// ─────────────────────────────────────────────────────────────
void demo_OR() {
    cout << "\n========== OR ( | ) ==========\n";
    int a = 0b10100000; // 160
    int b = 0b00010101; //  21

    cout << "a = " << a << " (0b10100000)\n";
    cout << "b = " << b << " (0b00010101)\n";
    cout << "a | b = " << (a | b) << "\n"; // 0b10110101 = 181

    // Trick : set the n-th bit  →  n | (1 << bit)
    int n = 0b00000000; // 0
    int bit = 3;
    int result = n | (1 << bit);
    cout << "\nSet bit " << bit << " in " << n << " → " << result << "\n";
}

// ─────────────────────────────────────────────────────────────
//  3. XOR  ( ^ )
//  Rule : bit is 1 when bits are DIFFERENT
//  Properties:
//    a ^ a  = 0       (self-cancellation)
//    a ^ 0  = a       (identity)
//    a ^ b  = b ^ a   (commutative)
//    (a^b)^b = a      (used to swap / find missing)
// ─────────────────────────────────────────────────────────────
void demo_XOR() {
    cout << "\n========== XOR ( ^ ) ==========\n";
    int a = 0b10111010; // 186
    int b = 0b11001101; // 205

    cout << "a = " << a << " (0b10111010)\n";
    cout << "b = " << b << " (0b11001101)\n";
    cout << "a ^ b = " << (a ^ b) << "\n"; // 0b01110111 = 119

    // Trick 1 : swap without temp
    int x = 42, y = 99;
    cout << "\nBefore swap: x=" << x << " y=" << y << "\n";
    x ^= y; y ^= x; x ^= y;
    cout << "After  swap: x=" << x << " y=" << y << "\n";

    // Trick 2 : toggle the n-th bit  →  n ^ (1 << bit)
    int n = 0b00001000; // 8
    int bit = 3;
    cout << "\nToggle bit " << bit << " in " << n << " → " << (n ^ (1 << bit)) << "\n";

    // Trick 3 : find the single non-duplicate element
    vector<int> arr = {4, 1, 2, 1, 2, 4, 7};
    int unique = 0;
    for (int v : arr) unique ^= v;
    cout << "\nArray {4,1,2,1,2,4,7} — only non-duplicate: " << unique << "\n";

    // Trick 4 : find missing number in [0..n]
    vector<int> nums = {0, 1, 3, 4, 5}; // missing 2
    int totalXor = 0;
    for (int i = 0; i <= (int)nums.size(); ++i) totalXor ^= i;
    for (int v : nums) totalXor ^= v;
    cout << "Missing in {0,1,3,4,5}: " << totalXor << "\n";
}

// ─────────────────────────────────────────────────────────────
//  4. NOT  ( ~ )
//  Flips every bit (bitwise complement)
//  For int n : ~n = -(n+1)   (two's complement)
// ─────────────────────────────────────────────────────────────
void demo_NOT() {
    cout << "\n========== NOT ( ~ ) ==========\n";
    int n = 5;  // 0b00000101
    cout << "n  = " << n << "\n";
    cout << "~n = " << ~n << "  (= -(n+1))\n";

    // Useful : clear n-th bit
    int bit = 2;
    int mask = ~(1 << bit); // flip only bit 2
    int num  = 0b11111111;  // 255
    cout << "\nClear bit " << bit << " in 255 → " << (num & mask) << "\n";
}

// ─────────────────────────────────────────────────────────────
//  5. LEFT SHIFT  ( << )
//  n << k  multiplies n by 2^k
//  Shifts all bits k positions to the LEFT (fills 0s on right)
// ─────────────────────────────────────────────────────────────
void demo_LEFT_SHIFT() {
    cout << "\n========== LEFT SHIFT ( << ) ==========\n";
    int n = 1;
    for (int k = 0; k <= 7; ++k)
        cout << "  1 << " << k << " = " << (n << k) << "\n";

    // Multiply by power of 2
    int val = 13;
    cout << "\n13 << 3 = " << (val << 3) << "  (= 13 * 8)\n";
}

// ─────────────────────────────────────────────────────────────
//  6. RIGHT SHIFT  ( >> )
//  n >> k  divides n by 2^k  (integer division)
//  Arithmetic shift for signed ints (fills sign bit)
// ─────────────────────────────────────────────────────────────
void demo_RIGHT_SHIFT() {
    cout << "\n========== RIGHT SHIFT ( >> ) ==========\n";
    int n = 256;
    for (int k = 0; k <= 8; ++k)
        cout << "  256 >> " << k << " = " << (n >> k) << "\n";

    // Divide by power of 2
    int val = 100;
    cout << "\n100 >> 2 = " << (val >> 2) << "  (= 100 / 4)\n";
}

// ─────────────────────────────────────────────────────────────
//  7. ADVANCED TRICKS
// ─────────────────────────────────────────────────────────────
void demo_advanced() {
    cout << "\n========== ADVANCED TRICKS ==========\n";

    // A. Count set bits  (Brian Kernighan's Algorithm)
    auto countSetBits = [](int n) {
        int count = 0;
        while (n) { n &= (n - 1); count++; }
        return count;
    };
    cout << "Set bits in 255  = " << countSetBits(255) << "\n";   // 8
    cout << "Set bits in 0b10110100 (180) = " << countSetBits(180) << "\n"; // 4

    // B. Lowest set bit (isolate)
    int n = 0b10110100; // 180
    cout << "\nLowest set bit of 180: " << (n & (-n)) << "\n"; // 4

    // C. Turn off lowest set bit
    cout << "180 with lowest set bit off: " << (n & (n - 1)) << "\n"; // 176

    // D. Sign of a number using bit trick
    int pos = 42, neg = -7;
    cout << "\nSign of  42: " << (1 | (pos >> 31)) << "\n"; // 1
    cout << "Sign of -7 : " << (1 | (neg >> 31)) << "\n";  // -1

    // E. Absolute value without branch
    int num = -55;
    int mask = num >> 31;
    cout << "abs(-55) = " << ((num ^ mask) - mask) << "\n";

    // F. Generate all subsets of a set using bits
    cout << "\nAll subsets of {A, B, C}:\n";
    string set[] = {"A", "B", "C"};
    int sz = 3;
    for (int mask2 = 0; mask2 < (1 << sz); ++mask2) {
        cout << "  { ";
        for (int i = 0; i < sz; ++i)
            if (mask2 & (1 << i)) cout << set[i] << " ";
        cout << "}\n";
    }
}

// ─────────────────────────────────────────────────────────────
//  8. QUICK REFERENCE TABLE (printed at runtime)
// ─────────────────────────────────────────────────────────────
void printReference() {
    cout << "\n"
         << "╔══════════════════════════════════════════════════════════════╗\n"
         << "║           BITWISE OPERATORS QUICK REFERENCE                  ║\n"
         << "╠══════════╦═══════════════╦══════════════════════════════════╣\n"
         << "║ Operator ║  Name         ║ Key use / trick                  ║\n"
         << "╠══════════╬═══════════════╬══════════════════════════════════╣\n"
         << "║   &      ║ AND           ║ mask, clear bit, check parity    ║\n"
         << "║   |      ║ OR            ║ set bit, combine flags           ║\n"
         << "║   ^      ║ XOR           ║ toggle, swap, find unique        ║\n"
         << "║   ~      ║ NOT           ║ complement, create mask          ║\n"
         << "║   <<     ║ Left Shift    ║ multiply by 2^k                  ║\n"
         << "║   >>     ║ Right Shift   ║ divide by 2^k                    ║\n"
         << "╠══════════╩═══════════════╩══════════════════════════════════╣\n"
         << "║  Common Bit Tricks                                           ║\n"
         << "║  n & 1           → check odd/even                           ║\n"
         << "║  n & (n-1)       → clear lowest set bit                     ║\n"
         << "║  n & (-n)        → isolate lowest set bit                   ║\n"
         << "║  n | (1<<k)      → set k-th bit                             ║\n"
         << "║  n & ~(1<<k)     → clear k-th bit                           ║\n"
         << "║  n ^ (1<<k)      → toggle k-th bit                          ║\n"
         << "║  (n>>k) & 1      → read k-th bit                            ║\n"
         << "║  n & (n-1) == 0  → n is power of 2                         ║\n"
         << "║  a^b^b = a       → undo XOR                                 ║\n"
         << "╚══════════════════════════════════════════════════════════════╝\n";
}

// ─────────────────────────────────────────────────────────────
int main() {
    printReference();
    demo_AND();
    demo_OR();
    demo_XOR();
    demo_NOT();
    demo_LEFT_SHIFT();
    demo_RIGHT_SHIFT();
    demo_advanced();

    cout << "\n[Done]\n";
    return 0;
}
