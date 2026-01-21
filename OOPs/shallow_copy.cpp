#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------
// Student Class
// ---------------------------------------------
class Student {
 public:
  string name;  // Stored in stack (inside object). No dynamic memory.
  double cgpa;  // Stored in stack as a normal variable.

  //  Parameterized Constructor
  // Initializes object with given values.
  Student(string name, double cgpa) {
    // 'this' pointer is used to refer to the current object's members
    this->name = name;
    this->cgpa = cgpa;
  }

  //  Copy Constructor (Shallow Copy)
  // Copies values from an existing object into the new object.
  // Since no pointers or heap memory exist, this is safe.
  Student(Student& obj) {
    cout << "\n[Copy Constructor Called]\n";
    this->name = obj.name;  // Copying value of string (internally deep)
    this->cgpa = obj.cgpa;  // Copying value of double
  }

  //  Display object's data
  void getInfo() {
    cout << "Name: " << name << endl;
    cout << "CGPA: " << cgpa << endl;
  }
};

// ---------------------------------------------
// Main Function
// ---------------------------------------------
int main() {
  //  Creating s1 using parameterized constructor
  Student s1("Kane", 9.5);
  cout << "Original Object (s1):\n";
  s1.getInfo();

  //  Creating s2 as a copy of s1 using Copy Constructor (Shallow Copy)
  Student s2(s1);

  //  Modifying copied object's members
  // These are stored in stack memory (static allocation inside object)
  s2.name = "Ricky";  // Only s2 is modified, s1 remains unchanged
  s2.cgpa = 8.9;

  cout << "\nCopied Object (s2) after modification:\n";
  s2.getInfo();

  cout << "\nChecking if original object (s1) is unchanged:\n";
  s1.getInfo();

  return 0;
}
