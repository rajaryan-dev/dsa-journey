#include <iostream>
using namespace std;

class Base {
 private:
  int privateVar = 1;  // ❌ Never inherited (not accessible in derived classes)
 protected:
  int protectedVar =
      2;  // ✅ Inherited but only accessible inside derived class
 public:
  int publicVar =
      3;  // ✅ Inherited (access depends on mode: private/protected/public)
};

/* --------- 1. Private Inheritance ---------
   - public & protected members of Base → become PRIVATE in Derived_Private
   - private members of Base → not inherited
*/
class Derived_Private : private Base {
 public:
  void show() {
    // cout << privateVar;   // ❌ Not accessible
    cout << "Derived_Private -> protectedVar = " << protectedVar
         << endl;  // ✅ Now private in this class
    cout << "Derived_Private -> publicVar = " << publicVar
         << endl;  // ✅ Now private
  }
};

/* --------- 2. Protected Inheritance ---------
   - public & protected members of Base → become PROTECTED in Derived_Protected
*/
class Derived_Protected : protected Base {
 public:
  void show() {
    cout << "Derived_Protected -> protectedVar = " << protectedVar
         << endl;  // ✅ Accessible (protected)
    cout << "Derived_Protected -> publicVar = " << publicVar
         << endl;  // ✅ Accessible (now protected)
  }
};

/* --------- 3. Public Inheritance ---------
   - public of Base → stays PUBLIC
   - protected of Base → stays PROTECTED
*/
class Derived_Public : public Base {
 public:
  void show() {
    cout << "Derived_Public -> protectedVar = " << protectedVar
         << endl;  // ✅ Accessible (protected in derived)
    cout << "Derived_Public -> publicVar = " << publicVar
         << endl;  // ✅ Accessible (still public)
  }
};

int main() {
  Derived_Private obj1;
  Derived_Protected obj2;
  Derived_Public obj3;

  obj1.show();  // ✅ Allowed
  obj2.show();  // ✅ Allowed
  obj3.show();  // ✅ Allowed

  // obj1.publicVar;   // ❌ Not accessible (became private)
  // obj2.publicVar;   // ❌ Not accessible (became protected)
  // obj3.publicVar;   // ✅ Accessible (still public)

  return 0;
}
