#include <iostream>
using namespace std;

class Person {
 public:
  void speak() { cout << "Person can speak\n"; }
};

class Student : public Person {
 public:
  void study() { cout << "Student is studying\n"; }
};

class Athlete {
 public:
  void play() { cout << "Athlete is playing\n"; }
};

class StudentAthlete : public Student,
                       public Athlete {  // Hybrid (Multiple + Multilevel)
 public:
  void show() { cout << "I am a student and an athlete\n"; }
};

int main() {
  StudentAthlete sa;
  sa.speak();
  sa.study();
  sa.play();
  sa.show();
  return 0;
}
