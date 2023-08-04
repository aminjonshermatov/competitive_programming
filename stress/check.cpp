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
  data >> n;
  vector<string> ws(n);
  for (auto &w : ws) {
    data >> w;
  }
  data >> q;
  for (int i = 0; i < q; ++i) {
    string qs;
    int k;
    data >> qs >> k;
    int s, f;
    slow >> s;
    fast >> f;
    if (s != f) {
      cerr << "FAIL" << '\n';
      for (auto &w : ws) {
        cerr << w << '\n';
      }
      cerr << qs << ' ' << k << '\n';
      cerr << "slow: " << s << " fast: " << f << '\n';
      return false;
    }
  }

  return true;
}

int main() {
  for (int i = 0; i < 1000; ++i) {
    ::system("./gen");
    ::system("./slow");
    ::system("./fast");
    if (!check()) break;
    this_thread::sleep_for(300ms);
    cout << "done " << i << endl;
  }
}