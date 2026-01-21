#include <iostream>
using namespace std;

// ✅ Abstract Class = A class that has at least one pure virtual function
class Shape {
 public:
  // ✅ Pure Virtual Function
  // = 0 means: This function has no body here.
  // Every child class MUST provide its own version (implementation).
  virtual void draw() = 0;  // pure virtual function → makes class abstract

  // Normal function (can be inherited normally)
  void info() { cout << "This is a shape.\n"; }
};

// ✅ Derived Class 1 (Circle)
class Circle : public Shape {
 public:
  // Overriding pure virtual function
  void draw() override { cout << "Drawing a Circle\n"; }
};

// ✅ Derived Class 2 (Rectangle)
class Rectangle : public Shape {
 public:
  void draw() override { cout << "Drawing a Rectangle\n"; }
};

int main() {
  // Shape s;  // ❌ Error: Cannot create object of abstract class

  Shape* shape1 = new Circle();  // Base pointer → Derived object
  Shape* shape2 = new Rectangle();

  shape1->draw();  // Calls Circle version
  shape2->draw();  // Calls Rectangle version

  shape1->info();  // Function from abstract class
  shape2->info();

  delete shape1;
  delete shape2;

  return 0;
}
