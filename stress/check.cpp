//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "constants.h"

using namespace std;

bool check() {
  ifstream data(constants::DATA_IN);
  ifstream slow(constants::SLOW_OUT);
  ifstream fast(constants::FAST_OUT);

  int n, q;

  while (data >> n >> q) {
    if (n == 0 && q == 0) break;
    for (int i = 0; i < q; ++i) {
      char cmd;
      int l, r;
      data >> cmd >> l >> r;
      if (cmd == '?') {
        string actual, expected;
        getline(slow, expected);
        slow >> expected;
        getline(fast, actual);
        fast >> actual;
        if (actual != expected) {
          cerr << "FAIL, tc:" << i << " !!! " << n << ' ' << q << ", l=" << l << ", r=" << r << endl;
          cerr << "sg: " << actual << " sqrt: " << expected << endl;
          return false;
        }
      } else if (cmd == '^') {
        int x; data >> x;
      } else {
        assert(false);
      }
    }
  }

  return true;
}

int main() {
  ::system("./gen");
  ::system("./slow");
  ::system("./fast");
  check();
}