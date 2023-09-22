//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

using namespace std;

void gen(ofstream &out) {
  string a, b;
  vector<string> un;

  do {
    a = utils::random_string(utils::random(5, 15), '0', 2);
    b = utils::random_string(utils::random(5, 15), '0', 2);
    set<string> aa, bb;
    for (int i = 0; i < a.size(); ++i) {
      for (int j = i; j < a.size(); ++j) {
        aa.emplace(a.substr(i, j - i + 1));
      }
    }
    for (int i = 0; i < b.size(); ++i) {
      for (int j = i; j < b.size(); ++j) {
        bb.emplace(b.substr(i, j - i + 1));
      }
    }
    for (auto &aaa : aa) {
      if (bb.contains(aaa)) {
        un.emplace_back(aaa);
      }
    }
  } while (un.empty());

  assert(!un.empty());
  out << a << '\n';
  out << b << '\n';
  out << utils::random(1, int(un.size())) << '\n';
}

int main() {
  ofstream out(constants::DATA_IN);
  gen(out);
}