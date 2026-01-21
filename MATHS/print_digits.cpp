#include <iostream>   

using namespace std;

void printDigits(int n) {
    while(n != 0) {
        int digit = n % 10;
        cout << digit << endl;

        n = n / 10;
    }
}

void printCount(int n) {
    int count = 0;

    while(n != 0) {
        int digit = n % 10;
        count++;

        n = n / 10;
    }

    cout << count << endl;
}

void sumOfDigits(int n) {
    int sum = 0;

    while(n != 0) {
        int digit = n % 10;
        sum += digit;

        n = n / 10;
    }
    cout << sum << endl;
}

int main() {

    int n = 3568;

    sumOfDigits(n);
  

    return 0;
}
