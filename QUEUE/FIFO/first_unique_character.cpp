// first_unique_character.cpp
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

/*
 LeetCode 387: First Unique Character in a String
*/

class Solution {
 public:
  int firstUniqChar(const string& s) {
    unordered_map<char, int> freq;
    queue<int> q;

    for (int i = 0; i < s.size(); i++) {
            if (freq.find(s[i]) == freq.end()) {
        q.push(i);
      }
      freq[s[i]]++;

      // Remove all indices pointing to non-unique chars
      while (!q.empty() && freq[s[q.front()]] > 1) {
        q.pop();
      }
    }

    return q.empty() ? -1 : q.front();
  }
};

string generateRandomString() {
  string chars = "abcdefghijklmnopqrstuvwxyz";
  int n = rand() % 10 + 5;  // length between 5 and 14
  string s;

  for (int i = 0; i < n; i++) {
    s += chars[rand() % chars.size()];
  }
  return s;
}

int main() {
  srand(time(nullptr));

  string s = generateRandomString();

  cout << "Random String: " << s << endl;

  Solution obj;
  int index = obj.firstUniqChar(s);

  cout << "First unique character index: " << index << endl;

  return 0;
}
