#include <iostream>
using namespace std;

/*
 * ---------------------------- TOPIC OVERVIEW -----------------------------
 * 1. Array Name as a Pointer (Constant Pointer)
 *    - 'arr' stores the address of the first element
 *    - But its address CANNOT be changed (read-only pointer)
 *
 * 2. Normal Pointer (Modifiable)
 *    - A pointer variable can be reassigned to point to
 *      different variables
 * -------------------------------------------------------------------------
 */

int main() {
  /* ------------------ PART 1: Array and Its Fixed Address ------------------
   */

  int arr[] = {1, 2, 3, 4, 5};

  // Displaying how array name behaves like a pointer
  cout << "Array Basics:\n";
  cout << "Address of first element (arr) : " << arr << endl;
  cout << "Value at arr (same as arr[0])  : " << *arr << endl;

  // ❌ Not Allowed: Array name 'arr' is a constant pointer, cannot be
  // reassigned int x = 100; arr = &x;  // ERROR

  cout << "\n--------------------------------------------------------\n";

  /* ------------------ PART 2: Pointer (Modifiable Address) ------------------
   */

  int a = 15, b = 10;

  cout << "Pointer Basics:\n";

  // Pointer pointing to variable 'a'
  int* ptr = &a;
  cout << "ptr points to a -> Address: " << ptr << ", Value: " << *ptr << endl;

  // Changing pointer to point to variable 'b'
  ptr = &b;
  cout << "ptr now points to b -> Address: " << ptr << ", Value: " << *ptr
       << endl;

  cout << "\n--------------------------------------------------------\n";

  /* ------------------ PART 3: Why Arrays Can't Change Address?
   * ------------------
   * - 'arr' is stored in symbol table as a READ-ONLY base address
   * - 'ptr' is a normal variable stored in stack memory → can be modified
   * -----------------------------------------------------------------------------
   */

  cout << "Conclusion Summary:\n";
  cout << " . Array name (arr) = constant pointer  cannot change address\n";
  cout << " . Normal pointer (ptr) = variable pointer  can change address\n";
  cout << " . *arr gives first element, *ptr gives value of pointed variable\n";

  return 0;
}
