#include <iostream>
using namespace std;

class Developer {
 public:
  void code() { cout << "Writing clean and efficient code.\n"; }
};

class Designer {
 public:
  void designUI() { cout << "Designing user-friendly UI/UX layouts.\n"; }
};

class UIEngineer : public Developer, public Designer {
 public:
  void buildProduct() {
    cout << "Building a functional and beautiful application.\n";
  }
};

int main() {
  UIEngineer u;
  u.code();
  u.designUI();
  u.buildProduct();
  return 0;
}
