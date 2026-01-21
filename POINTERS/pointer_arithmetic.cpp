#include <iostream>
using namespace std;

/*
    Pointer Arithmetic in C++
    --------------------------
    1. Increment (ptr++)
    2. Decrement (ptr--)
    3. Add/Subtract integer (ptr + n, ptr - n)
    4. Pointer difference (ptr1 - ptr2)
    5. Pointer comparison (ptr1 < ptr2, ptr1 == ptr2)
    6. Using pointer with arrays (arr + i)
*/

int main() {
  // Example 1: Basic pointer increment and decrement
  int a = 10;
  int* ptr = &a;

  cout << "Pointer Arithmetic (Increment / Decrement):" << endl;
  cout << "Initial ptr address: " << ptr << endl;

  ptr++;  // Moves by 4 bytes (size of int)
  cout << "After ptr++        : " << ptr << endl;

  ptr--;  // Back to original
  cout << "After ptr--        : " << ptr << endl;

  cout << "--------------------------------------------------" << endl;

  // Example 2: Adding and subtracting integers to a pointer
  int* p2 = &a;
  cout << "Pointer before +2  : " << p2 << endl;
  p2 = p2 + 2;  // Moves 2 * 4 bytes = 8 bytes forward
  cout << "Pointer after +2   : " << p2 << endl;

  p2 = p2 - 1;  // Moves back by 4 bytes
  cout << "Pointer after -1   : " << p2 << endl;

  cout << "--------------------------------------------------" << endl;

  // Example 3: Pointer comparison
  int x = 5, y = 20;
  int* p3 = &x;
  int* p4 = &y;

  cout << "Pointer Comparison:" << endl;
  cout << "p3 = " << p3 << endl;
  cout << "p4 = " << p4 << endl;
  cout << "(p3 < p4) : " << (p3 < p4) << endl;
  cout << "(p3 == p4): " << (p3 == p4) << endl;

  cout << "--------------------------------------------------" << endl;

  // Example 4: Pointer difference
  int arr[] = {1, 2, 3, 4, 5};
  int* start = &arr[0];
  int* end = &arr[4];

  cout << "Pointer Difference (end - start): " << (end - start) << endl;

  cout << "--------------------------------------------------" << endl;

  // Example 5: Accessing array elements using pointers
  cout << "Array Access Using Pointer Notation:" << endl;
  cout << "*arr       : " << *arr << endl;        // 1
  cout << "*(arr + 1) : " << *(arr + 1) << endl;  // 2
  cout << "*(arr + 2) : " << *(arr + 2) << endl;  // 3
  cout << "*(arr + 3) : " << *(arr + 3) << endl;  // 4
  cout << "*(arr + 4) : " << *(arr + 4) << endl;  // 5

  return 0;
}
