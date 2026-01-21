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

class Cat : public Animal {
 public:
  void meow() { cout << "Cat is meowing\n"; }
};

int main() {
  Dog d;
  d.eat();
  d.bark();

  Cat c;
  c.eat();
  c.meow();
  return 0;
}
