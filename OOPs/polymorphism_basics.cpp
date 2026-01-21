// ✅ POLYMORPHISM IN C++ (With Super Simple Comments)

#include <iostream>
using namespace std;

// ------------------------------------------------------------
// ✅ PART 1: Compile-Time Polymorphism (Function Overloading)
// ------------------------------------------------------------
// Same function name but different parameters.
// This is decided by the compiler → BEFORE the program runs.
class Math {
 public:
  int add(int a, int b) { return a + b; }

  double add(double a, double b) { return a + b; }

  int add(int a, int b, int c) { return a + b + c; }
};

// ------------------------------------------------------------
// ✅ PART 2: Run-Time Polymorphism (More Important & Confusing Part)
// ------------------------------------------------------------
// This happens when:
// 👉 A Base class pointer is used to call Derived class function
// 👉 Which function will run is decided DURING PROGRAM EXECUTION (runtime)

// 📌 Base Class
class Animal {
 public:
  // ✅ 'virtual' keyword:
  // Tells C++: if a derived class has the same function,
  // then call the DERIVED CLASS version instead of this one.
  virtual void sound() { cout << "Animal makes a sound\n"; }

  // ✅ Virtual Destructor:
  // Ensures correct destructor is called for derived class.
  virtual ~Animal() { cout << "Animal Destructor called\n"; }
};

// 📌 Derived Class 1
class Dog : public Animal {
 public:
  // ✅ 'override':
  // This tells the compiler: "Yes, I am intentionally
  // replacing (overriding) the base class function."
  void sound() override { cout << "Dog barks\n"; }

  ~Dog() { cout << "Dog Destructor called\n"; }
};

// 📌 Derived Class 2
class Cat : public Animal {
 public:
  void sound() override { cout << "Cat meows\n"; }

  ~Cat() { cout << "Cat Destructor called\n"; }
};

// ------------------------------------------------------------
// ✅ MAIN FUNCTION
// ------------------------------------------------------------
int main() {
  // ---- Compile-Time Polymorphism ----
  Math m;
  cout << "Addition (int): " << m.add(5, 3) << endl;
  cout << "Addition (double): " << m.add(5.5, 2.3) << endl;
  cout << "Addition of 3 numbers: " << m.add(4, 6, 8) << endl;

  cout << "\n--- Runtime Polymorphism Explained Clearly ---\n";

  // ✅ Very IMPORTANT:
  // Animal* = pointer of BASE class
  // new Dog() = object of DERIVED class
  // We are storing derived object in base class pointer
  Animal* a1 = new Dog();
  Animal* a2 = new Cat();

  // Because 'sound()' is virtual →
  // These calls will go to the respective derived class function.
  a1->sound();  // Output: Dog barks
  a2->sound();  // Output: Cat meows

  // ✅ delete to free memory
  // Calling 'delete' will call derived destructor first (Dog/Cat),
  // and then base class destructor (Animal)
  delete a1;
  delete a2;

  return 0;
}
