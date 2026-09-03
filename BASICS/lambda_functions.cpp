/*
 * ============================================================
 *  LAMBDA FUNCTIONS (C++11)
 * ============================================================
 *  Lambdas are anonymous functions (functions without a name) 
 *  that can be defined inline. They are heavily used in DSA for 
 *  custom sorting and STL algorithms like `std::count_if`.
 * 
 *  Syntax:
 *      [capture_clause] (parameters) -> return_type {
 *          // body
 *      };
 * 
 *  Capture Clause `[]`:
 *  Defines which outside variables are available inside the lambda.
 *   - `[]`      : Capture nothing.
 *   - `[x]`     : Capture `x` by value (read-only).
 *   - `[&x]`    : Capture `x` by reference (can modify it).
 *   - `[=]`     : Capture ALL local variables by value.
 *   - `[&]`     : Capture ALL local variables by reference.
 * 
 *  Note: Return type is usually inferred automatically.
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    cout << "===== Lambda Functions Examples =====\n\n";

    // 1. Basic Lambda
    auto greet = []() { cout << "1. Hello from lambda!\n\n"; };
    greet();

    // 2. Lambda with parameters
    auto add = [](int a, int b) { return a + b; };
    cout << "2. Lambda with params (3 + 4): " << add(3, 4) << "\n\n";

    // 3. Capturing variables
    int multiplier = 5;
    
    // Capture 'multiplier' by value
    auto multiply = [multiplier](int x) { return x * multiplier; };
    cout << "3. Capture by value (10 * 5): " << multiply(10) << "\n";

    // Capture 'multiplier' by reference so we can modify it inside
    auto changeMultiplier = [&multiplier]() { multiplier = 10; };
    changeMultiplier();
    cout << "   Multiplier changed to: " << multiplier << "\n\n";

    // 4. Practical DSA usage: Custom sorting
    vector<int> nums = {4, 2, 8, 5, 1};
    
    // Sort descending using an inline lambda
    sort(nums.begin(), nums.end(), [](int a, int b) {
        return a > b; 
    });

    cout << "4. Custom Sort (Descending):\n   ";
    for(int n : nums) cout << n << " ";
    cout << "\n";

    return 0;
}
