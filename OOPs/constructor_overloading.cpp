#include <iostream>
#include <string>
using namespace std;

// ----------------------------------
// Teacher Class
// ----------------------------------
class Teacher {
 private:
  double salary;  // Private attribute (Encapsulation)

 public:
  string name;
  string dept;
  string subject;

  /*
    Constructor Overloading Concept:
   We have more than one constructor with the same name "Teacher"
   but different parameter lists.
   This is called CONSTRUCTOR OVERLOADING.
  */

  // 1️⃣ Default / Non-Parameterized Constructor
  Teacher() {
    cout << "\n[Non-Parameterized Constructor Called]\n";
    name = "Not Assigned";
    dept = "CSE";  // Default department
    subject = "Not Assigned";
    salary = 0;
  }

  // 2️⃣ Parameterized Constructor (Full details)
  Teacher(string n, string d, string s, double sal) {
    cout << "\n[Parameterized Constructor Called]\n";
    name = n;
    dept = d;
    subject = s;
    salary = sal;
  }

  // 3️⃣ Example of another Parameterized Constructor (Partial info)
  //    This is also constructor overloading
  Teacher(string n, string s) {
    cout << "\n[Overloaded Constructor (Name + Subject) Called]\n";
    name = n;
    subject = s;
    dept = "CSE";    // Default value
    salary = 30000;  // Default salary
  }

  // Change department
  void changeDept(string newDept) { dept = newDept; }

  // Setter for salary
  void setSalary(double newSalary) { salary = newSalary; }

  // Getter for salary
  double getSalary() { return salary; }

  // Display all details
  void getInfo() {
    cout << "\n----- Teacher Details -----" << endl;
    cout << "Name       : " << name << endl;
    cout << "Department : " << dept << endl;
    cout << "Subject    : " << subject << endl;
    cout << "Salary     : " << salary << endl;
    cout << "----------------------------\n";
  }
};

// ----------------------------------
// Main Function
// ----------------------------------
int main() {
  //  Example 1: Non-Parameterized Constructor
  Teacher t1;  // Default constructor
  t1.name = "John";
  t1.subject = "Computer Networks";
  t1.setSalary(40000);
  t1.getInfo();

  // Example 2: Parameterized Constructor (all details given)
  Teacher t2("Alice", "CSE", "Operating System", 50000);
  t2.getInfo();

  // Example 3: Constructor Overloading (only name + subject passed)
  Teacher t3("Bob", "Data Structures");  // Uses overloaded constructor
  t3.getInfo();

  return 0;
}
