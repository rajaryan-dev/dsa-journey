#include <iostream>
#include <string>
using namespace std;

class Student {
 public:
  string name;      // Student's name
  double* cgpaPtr;  // Pointer for dynamically allocated CGPA (heap memory)

  /*  Default Constructor (Compiler provides automatically if no constructor
     is written)
     - But since we are defining our own constructor below,
       the compiler will NOT generate a default constructor automatically.
     - If you still want an object to be created without parameters, you must
     write it manually.
  */
  // Student() {
  //     name = "Unknown";
  //     cgpaPtr = new double(0.0);
  //     cout << "Default Constructor called!\n";
  // }

  /*  Parameterized Constructor (Custom)
     - Initializes object with user-defined values.
     - Also allocates memory on HEAP using 'new'.
  */
  Student(string name, double cgpa) {
    this->name = name;
    cgpaPtr = new double;  // Allocate memory dynamically
    *cgpaPtr = cgpa;       // Store value in allocated memory
    cout << "Constructor called! Memory allocated for CGPA.\n";
  }

  /*  Destructor (Custom Destructor)
     🔹 What is a destructor?
         - A special function automatically called when object goes out of scope
     or is deleted.
         - Syntax: ~ClassName()

     🔹 Default Destructor (if we don’t write one)
         - Compiler creates an empty destructor automatically.
         - It only destroys normal variables (like string, int, etc.)
         - ❌ BUT it does NOT free HEAP memory allocated by 'new'.

     🔹 Why write a Custom Destructor?
         ✔ To manually free dynamically allocated memory using 'delete'
         ✔ Prevents MEMORY LEAKS
  */
  ~Student() {
    cout << "Destructor called! Releasing allocated memory.\n";
    delete cgpaPtr;     // Free heap memory (prevents memory leak)
    cgpaPtr = nullptr;  // Good habit → avoids dangling pointer
  }

  void getInfo() {
    cout << "Name: " << name << endl;
    cout << "CGPA: " << *cgpaPtr << endl;
  }
};

int main() {
  Student s1("Kane", 9.5);  // Parameterized constructor is called
  s1.getInfo();

  // When main() ends, s1 goes out of scope → Destructor is called automatically
  return 0;
}
