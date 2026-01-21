#include <iostream>
using namespace std;

class Animal {
 public:
  void eat() { cout << "Animal is eating\n"; }
};

class Dog : public Animal {
 public:
  void bark() { cout << "Dog is barking\n"; }
};

class Puppy : public Dog {  // Multilevel Inheritance
 public:
  void weep() { cout << "Puppy is weeping\n"; }
};

int main() {
  Puppy p;
  p.eat();
  p.bark();
  p.weep();
  return 0;
}
