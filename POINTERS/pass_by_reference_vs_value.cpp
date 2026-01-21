#include <iostream>
using namespace std;

/* ------------------ 1. Pass by Value -------------------
   Only a COPY of 'x' is passed : original remains unchanged.
*/
void changeValue(int x) { x = 20; }

/* ------------------ 2. Pass by Reference (using &) -------------------
   'y' is an alias for the actual variable : changes original.
*/
void changeReference(int& y) { y = 30; }

/* ------------------ 3. Pass by Pointer -------------------
   Address is passed : *ptr modifies the actual variable.
*/
void changePointer(int* ptr) { *ptr = 40; }

int main() {
  // -------- PASS BY VALUE EXAMPLE --------
  int x = 10;
  cout << "Pass by Value:" << endl;
  cout << "Before function call : x = " << x << endl;
  changeValue(x);
  cout << "After function call  : x = " << x << "  (No change)" << endl;
  cout << "---------------------------------------\n";

  // -------- PASS BY REFERENCE EXAMPLE --------
  int y = 10;
  cout << "Pass by Reference:" << endl;
  cout << "Before function call : y = " << y << endl;
  changeReference(y);
  cout << "After function call  : y = " << y << "  (Changed)" << endl;
  cout << "---------------------------------------\n";

  // -------- PASS BY POINTER EXAMPLE --------
  int z = 10;
  cout << "Pass by Pointer:" << endl;
  cout << "Before function call : z = " << z << endl;
  changePointer(&z);  // Pass address of 'z'
  cout << "After function call  : z = " << z << "  (Changed)" << endl;
  cout << "---------------------------------------\n";

  return 0;
}
