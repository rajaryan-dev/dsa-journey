#include <iostream>
#include <string>
using namespace std;

class Student {
 public:
  string name;
  double* cgpaPtr;  // Pointer → dynamic memory stored in Heap

  //  1. Parameterized Constructor
  Student(string name, double cgpa) {
    cout << "\n[Parameterized Constructor Called]\n";
    this->name = name;
    cgpaPtr =
        new double;   // Allocate memory in Heap | Dynamic Memory Allocation
    *cgpaPtr = cgpa;  // Store value
  }

  //  2. Shallow Copy Constructor (Default Copy Behavior)
  Student(const Student& obj) {
    cout << "\n[Shallow Copy Constructor Called]\n";
    this->name = obj.name;
    this->cgpaPtr =
        obj.cgpaPtr;  // ❌ Only pointer copied → both objects share same memory
  }

  /*
     3. Deep Copy Constructor (Custom Made)

    ⚠ QUESTION: Why did we add a 'bool' parameter here?

    👉 Because C++ does NOT allow two constructors with exactly the same
    parameter type & count. Example: Student(Student&)           // shallow copy
    constructor Student(Student&)           // deep copy? ❌ ERROR (same
    function signature)

     So we add a dummy parameter "bool deepCopyFlag" to make function
    signature UNIQUE: Student(Student&, bool)

     That means:
       - If only 1 parameter (Student&) → Shallow Copy
       - If 2 parameters (Student&, bool) → Deep Copy

     This bool parameter is used ONLY to differentiate between constructors.
       (true/false doesn't matter much, it's just a way to overload the
    constructor)
  */
  Student(const Student& obj, bool deepCopyFlag) {
    cout << "\n[Deep Copy Constructor Called]\n";
    this->name = obj.name;
    cgpaPtr = new double;       // Allocate NEW memory (separate from obj)
    *cgpaPtr = *(obj.cgpaPtr);  // Copy VALUE, not pointer address
  }

  //  Destructor → Called automatically when object goes out of scope
  // Frees dynamically allocated memory → prevents memory leaks
  ~Student() {
    cout << "\n[Destructor Called for " << name << "]\n";
    delete cgpaPtr;
  }

  void getInfo() {
    cout << "Name: " << name << endl;
    cout << "CGPA: " << *cgpaPtr << endl;
  }
};

int main() {
  //  Original object
  Student s1("Kane", 9.5);
  cout << "\nOriginal Object (s1):\n";
  s1.getInfo();

  //  Shallow Copy (uses copy constructor without bool)
  Student s2(s1);
  s2.name = "Ricky";
  *(s2.cgpaPtr) = 9.8;  // ❌ This also affects s1 due to same memory

  cout << "\nAfter Shallow Copy Modification (s2):\n";
  s2.getInfo();

  cout << "\nEffect on Original Object (s1) after shallow copy:\n";
  s1.getInfo();

  //  Deep Copy (uses constructor with bool parameter to differentiate)
  Student s3(s1, true);
  s3.name = "Steve";
  *(s3.cgpaPtr) = 8.7;  //  This does NOT affect s1

  cout << "\nAfter Deep Copy Modification (s3):\n";
  s3.getInfo();

  cout << "\nOriginal Object (s1) Remains Unchanged After Deep Copy:\n";
  s1.getInfo();

  return 0;
}
