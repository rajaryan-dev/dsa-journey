/*
 * ============================================================
 *  NUMBER CONVERSION  –  Decimal ↔ Binary
 * ============================================================
 *  Topics covered:
 *    1. Decimal  →  Binary  (iterative)
 *    2. Decimal  →  Binary  (recursive)
 *    3. Binary   →  Decimal (iterative, string input)
 *    4. Binary   →  Decimal (recursive, string input)
 *    5. Bonus    →  Using STL bitset for quick conversion
 *
 *  Key concept:
 *    - To convert decimal → binary, repeatedly divide by 2
 *      and collect remainders (LSB first, then reverse).
 *    - To convert binary  → decimal, process each bit from
 *      left to right and apply Horner's rule (val = val*2 + bit).
 * ============================================================
 */

#include <iostream>
#include <string>
#include <algorithm>   // reverse
#include <bitset>      // bonus STL approach
#include <cmath>       // pow

using namespace std;

// ──────────────────────────────────────────────
//  1. Decimal → Binary  (ITERATIVE)
//     Returns binary representation as a string.
// ──────────────────────────────────────────────
string decimalToBinary_Iterative(int n) {
    if (n == 0) return "0";

    string binary = "";

    while (n > 0) {
        int remainder = n % 2;          // get LSB
        binary += to_string(remainder); // append bit
        n = n / 2;                      // move to next bit
    }

    // bits were collected LSB→MSB, so reverse for correct order
    reverse(binary.begin(), binary.end());
    return binary;
}

// ──────────────────────────────────────────────
//  2. Decimal → Binary  (RECURSIVE)
//     Prints bits in correct MSB→LSB order.
// ──────────────────────────────────────────────
void decimalToBinary_Recursive(int n) {
    if (n == 0) return;                 // base case

    decimalToBinary_Recursive(n / 2);  // recurse first (builds MSB side)
    cout << (n % 2);                   // print current bit on the way back
}

// ──────────────────────────────────────────────
//  3. Binary → Decimal  (ITERATIVE, string input)
//     E.g. "1101" → 13
// ──────────────────────────────────────────────
int binaryToDecimal_Iterative(const string& binary) {
    int decimal = 0;
    int power   = 0;                          // tracks current bit position (2^power)

    // traverse from rightmost bit (LSB) to leftmost (MSB)
    for (int i = binary.size() - 1; i >= 0; i--) {
        int bit = binary[i] - '0';            // convert char '0'/'1' to int 0/1
        decimal += bit * (1 << power);        // bit * 2^power  (using bit-shift)
        power++;
    }
    return decimal;
}

// ──────────────────────────────────────────────
//  4. Binary → Decimal  (RECURSIVE, string input)
//     Uses Horner's rule: process MSB → LSB
//     val = val * 2 + current_bit
// ──────────────────────────────────────────────
int binaryToDecimal_Recursive(const string& binary, int index, int result) {
    if (index == (int)binary.size()) return result;   // base case

    int bit = binary[index] - '0';
    return binaryToDecimal_Recursive(binary, index + 1, result * 2 + bit);
}

// ──────────────────────────────────────────────
//  5. BONUS – STL bitset approach
//     bitset<N> stores N bits; very handy for
//     fixed-width binary representations.
// ──────────────────────────────────────────────
void bonusSTL(int n) {
    // decimal → 8-bit binary string
    bitset<8> bits(n);
    cout << "bitset (8-bit) : " << bits << endl;

    // binary string → decimal via bitset
    bitset<8> fromString("00001101");       // "00001101" = 13
    cout << "bitset to_ulong : " << fromString.to_ulong() << endl;
}

// ──────────────────────────────────────────────
//  MAIN – demonstration
// ──────────────────────────────────────────────
int main() {

    // ── Decimal → Binary ──────────────────────
    int decimal = 13;
    cout << "=== Decimal to Binary ===" << endl;

    cout << "Iterative : " << decimalToBinary_Iterative(decimal) << endl;

    cout << "Recursive : ";
    if (decimal == 0) cout << "0";
    else decimalToBinary_Recursive(decimal);
    cout << endl;

    // ── Binary → Decimal ──────────────────────
    string binary = "1101";
    cout << "\n=== Binary to Decimal ===" << endl;

    cout << "Iterative : " << binaryToDecimal_Iterative(binary) << endl;

    cout << "Recursive : "
         << binaryToDecimal_Recursive(binary, 0, 0) << endl;

    // ── Bonus STL ─────────────────────────────
    cout << "\n=== Bonus STL (bitset) ===" << endl;
    bonusSTL(decimal);

    return 0;
}
