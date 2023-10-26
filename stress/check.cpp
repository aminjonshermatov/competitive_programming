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
  data >> n >> q;
  vector<int> as(n);
  for (auto &a : as) {
    data >> a;
  }
  vector<tuple<int, int, int, int>> qs(q);
  for (auto &[l1, r1, l2, r2] : qs) {
    data >> l1 >> r1 >> l2 >> r2;
  }

  for (int i = 0; i < q; ++i) {
    int s, f;
    slow >> s;
    fast >> f;
    if (s != f) {
      cerr << "FAIL " << i << '\n';
      cerr << n << ' ' << q << '\n';
      for (auto a : as) {
        cerr << a << ' ';
      }
      cerr << '\n';
      for (auto &[l1, r1, l2, r2] : qs) {
        cerr << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << '\n';
      }
      cerr << "! " << s << ' ' << f << '\n';
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