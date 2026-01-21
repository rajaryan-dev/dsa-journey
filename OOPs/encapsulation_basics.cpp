#include <iostream>
#include <string>
using namespace std;

// -----------------------------
// Teacher Class
// -----------------------------
class Teacher {
 private:
  // Private data can only be accessed within the class
  double salary;  // Sensitive data -> should not be public for security

 public:
  // Public attributes (can be accessed from outside the class)
  string name;
  string dept;
  string subject;

  // Function to change department (Setter-like function)
  void changeDept(string newDept) { dept = newDept; }

  // Setter function to set/update salary
  void setSalary(double newSalary) { salary = newSalary; }

  // Getter function to access private salary
  double getSalary() { return salary; }
};

// -----------------------------
// Account Class (Example of Encapsulation)
// -----------------------------
class Account {
 private:
  string password;  // Private -> hidden from outside
  double balance;   // Private -> cannot be directly accessed

 public:
  // Public attributes
  string username;
  string accountId;

  // Setter for password
  void setPassword(string pass) { password = pass; }

  // Getter (not recommended for real password but shown for learning)
  string getPassword() { return password; }

  // Setter for balance
  void setBalance(double amount) { balance = amount; }

  // Getter for balance
  double getBalance() { return balance; }
};

// -----------------------------
// Main Function - Program Entry Point
// -----------------------------
int main() {
  // Creating an object 't1' of Teacher class
  Teacher t1;
  t1.name = "Sam";  // Directly accessing public attribute
  t1.subject = "Operating System";
  t1.dept = "CSE";
  t1.setSalary(50000);  // Setting private salary using setter

  // Displaying Teacher's details
  cout << "----- Teacher Details -----" << endl;
  cout << "Name       : " << t1.name << endl;
  cout << "Subject    : " << t1.subject << endl;
  cout << "Department : " << t1.dept << endl;
  cout << "Salary     : " << t1.getSalary()
       << endl;  // Access salary using getter

  return 0;
}
