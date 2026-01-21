// ✅ Inheritance Example in C++

#include <iostream>
#include <string>
using namespace std;

// 🔹 Base Class (Parent)
class Person {
 public:
  string name;
  int age;

  // ✅ Parameterized Constructor (Base Class)
  Person(string name, int age) {
    this->name = name;
    this->age = age;
    cout << "Parent (Person) Constructor Called...\n";
  }

  // ✅ Destructor (Base Class)
  ~Person() { cout << "Parent (Person) Destructor Called...\n"; }
};

// 🔹 Derived Class (Child) inherits from Person
class Student : public Person {
 public:
  int rollNo;

  /* ✅ Parameterized Constructor (Child Class)
     - Uses Initialization List to call Parent Class Constructor
     - Why use it? Because base class members (name, age) are private to Person
       and should be initialized by Person's constructor.
  */
  Student(string name, int age, int rollNo) : Person(name, age) {
    this->rollNo = rollNo;
    cout << "Child (Student) Constructor Called...\n";
  }

  // ✅ Destructor (Child Class)
  // Note: Destructors are called in reverse order (Child → Parent)
  ~Student() { cout << "Child (Student) Destructor Called...\n"; }

  // ✅ Function to Display Information
  void getInfo() {
    cout << "\n--- Student Details ---\n";
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Roll No: " << rollNo << endl;
  }
};

int main() {
  // Object Creation → Constructor of Parent is called first, then Child
  Student s1("Alex", 21, 1234);
  s1.getInfo();

  // When main ends → Destructors are called automatically
  // Order: Child Destructor → Parent Destructor
  return 0;
}
