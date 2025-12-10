#include <iostream>
using namespace std;

/*
    Double Pointer Concept (Pointer to Pointer)

    - int a        → normal integer variable
    - int* ptr     → stores address of integer variable 'a'
    - int** parPtr → stores address of pointer variable 'ptr'
*/

int main() {
  int a = 10;           // Normal variable
  int* ptr = &a;        // Pointer to int
  int** parPtr = &ptr;  // Pointer to pointer (stores address of ptr)

      cout << "Value of a            : " << a << endl;
  cout << "Address of a (&a)     : " << &a << endl;
  cout << "Address stored in ptr : " << ptr << endl;
  cout << "Value at *ptr         : " << *ptr << endl;

  cout << "--------------------------------------------------" << endl;

  cout << "Address of ptr (&ptr) : " << &ptr << endl;
  cout << "Address stored in parPtr : " << parPtr << endl;
  cout << "Value at *parPtr (ptr)   : " << *parPtr << endl;
  cout << "Value at **parPtr (a)    : " << **parPtr << endl;

  return 0;
}
