#include <iostream>
#include <cmath>    // pow()
#include <string>   // to_string()

using namespace std;

bool isArmstrong(int n) {
    int copyN = n;
    int sumOfPowers = 0;

    // Armstrong number: each digit raised to the power of total digit count
    int numDigits = to_string(n).length();

    while(n != 0) {
        int dig = n % 10;
        sumOfPowers += (int)pow(dig, numDigits);  // use numDigits, not always 3

        n = n / 10;
    }

    return sumOfPowers == copyN;
}

int main() {
    // 153 = 1^3 + 5^3 + 3^3 = 153  → true
    // 1634 = 1^4 + 6^4 + 3^4 + 4^4 = 1634 → true (4-digit Armstrong)
    // 173 → false
    for(int n : {153, 1634, 173}) {
        cout << n << (isArmstrong(n) ? " is an Armstrong number" : " is NOT an Armstrong number") << "\n";
    }

    return 0;
}