#include <iostream>
using namespace std;

class ATM {
 public:
  virtual void transaction() = 0;  // pure virtual function → abstraction

  void insertCard() { cout << "Card Inserted...\n"; }
};

class Withdraw : public ATM {
 public:
  void transaction() override { cout << "Withdraw Money Process Started...\n"; }
};

class CheckBalance : public ATM {
 public:
  void transaction() override {
    cout << "Balance Checking Process Started...\n";
  }
};

int main() {
  ATM* user1 = new Withdraw();
  ATM* user2 = new CheckBalance();

  user1->insertCard();
  user1->transaction();

  user2->insertCard();
  user2->transaction();

  delete user1;
  delete user2;

  return 0;
}
