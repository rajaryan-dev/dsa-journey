#include <iostream>
#include <string>
using namespace std;

// -----------------------------------
// Teacher Class
// -----------------------------------
class Teacher {
 private:
  double salary;  // Private → Encapsulation

 public:
  string name;
  string dept;
  string subject;

  /*
    'this' Keyword Explanation:
   - 'this' is a special pointer in C++.
   - It stores the address of the current object (the object which is calling
   the function).
   - We use it when function parameters have the same name as class attributes.
   - Example:
      this->name  → refers to class member
      name        → refers to constructor parameter
   - this->name is same as (*this).name (pointer dereferencing)
  */

  //  Parameterized Constructor
  Teacher(string name, string dept, string subject, double salary) {
    cout << "\n[Parameterized Constructor Called]\n";
    this->name = name;  // using 'this' pointer
    this->dept = dept;
    this->subject = subject;
    this->salary = salary;
  }

  //  Copy Constructor (Custom)
  Teacher(Teacher& orgObj) {
    cout << "\n[Copy Constructor Called]\n";
    this->name = orgObj.name;
    this->dept = orgObj.dept;
    this->subject = orgObj.subject;
    this->salary = orgObj.salary;
  }

  // Change department
  void changeDept(string newDept) {
    this->dept = newDept;  // Not necessary but used for clarity
  }

  // Setter for salary
  void setSalary(double newSalary) { this->salary = newSalary; }

  // Getter for salary
  double getSalary() { return this->salary; }

  // Display information
  void getInfo() {
    cout << "----- Teacher Details -----\n";
    cout << "Name       : " << this->name << endl;
    cout << "Department : " << this->dept << endl;
    cout << "Subject    : " << this->subject << endl;
    cout << "Salary     : " << this->salary << endl;
    cout << "----------------------------\n";
  }
};

// -----------------------------------
// Main Function
// -----------------------------------
int main() {
  //  Creates object using parameterized constructor
  Teacher t1("Alice", "CSE", "Operating System", 50000);

  //  Creates a new object using Copy Constructor (t2 = copy of t1)
  Teacher t2(t1);  // Custom Copy Constructor called

  t2.getInfo();

  return 0;
}
