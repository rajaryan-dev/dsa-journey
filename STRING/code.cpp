#include <iostream>
#include <string>
using namespace std;

int main() {
  // Strings:
  string greet = "Welcome Guest";
  cout << greet << endl;

  //----------------------------------------------------------------------------
  /*
  String Concatenation:
   The + operator can be used between strings to add them together to make a
   new string. This is called concatenation:
   */
  string firstName = "John";
  string lastName = "Doe";
  string fullName = firstName + " " + lastName;
  cout << fullName << endl;

  /*
//-------------------------------------------------------------------------
Append:
  A string in C++ is actually an object, which contain functions that can
  perform certain operations on strings. For example, you can also
 concatenate strings with the append() function:
*/
  string firstName2 = "john";
  string lastName2 = "Doe";
  string fullName2 = firstName2.append(lastName2);
  cout << "fullname with firstName2.append(lastName): " << fullName2 << endl;

  return 0;
}
