#include <iostream>
using namespace std;

/*
    Double Pointer (int**)
    -----------------------
    - int*  -> stores the address of an integer
    - int** -> stores the address of a pointer (pointer to pointer)

    Important:
    - Uninitialized pointers (garbage values in memory) are dangerous.
    - Dereferencing NULL or uninitialized pointer will cause program crash.
*/

int main() {
  // Example 1: Uninitialized double pointer (contains garbage address)
  int** ptrA;
  // Example 2: Initialized to NULL (safe but points to nowhere)
  int** ptrB = NULL;

  cout << "Example 1: Garbage pointer (ptrA)" << endl;
  cout << "ptrA (address stored): " << ptrA << endl;
  // Dereferencing ptrA directly is unsafe → *ptrA is unpredictable

  cout << "\nExample 2: NULL pointer (ptrB)" << endl;
  cout << "ptrB (address stored): " << ptrB << endl;

  // Safe check before dereferencing
  if (ptrB == NULL) {
    cout << "*ptrB cannot be accessed (NULL pointer)" << endl;
  }

  cout << "\n---------------------------------------------" << endl;

  // Example 3: Proper use of double pointer
  int num = 50;
  int* p = &num;  // pointer to int
  int** pp = &p;  // double pointer (pointer to pointer)

  cout << "Example 3: Valid Double Pointer Usage" << endl;
  cout << "Value of num        : " << num << endl;
  cout << "Address of num(&num): " << &num << endl;
  cout << "Value in p (&num)   : " << p << endl;
  cout << "Value at *p         : " << *p << endl;
  cout << "Address of p(&p)    : " << &p << endl;
  cout << "Value in pp (&p)    : " << pp << endl;
  cout << "Value at *pp (p)    : " << *pp << endl;
  cout << "Value at **pp (num) : " << **pp << endl;

  return 0;
}
