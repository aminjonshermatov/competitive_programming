//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "constants.h"

using namespace std;

bool is_ok() {
  ifstream data(constants::DATA_IN);
  ifstream slow(constants::SLOW_OUT);
  ifstream fast(constants::FAST_OUT);

  int n, q; data >> n >> q;
  vector<int> A(n);
  for (auto &a : A) data >> a;
  vector<pair<int, int>> edges(n - 1);
  for (auto &[u, v] : edges) data >> u >> v;

  for (int i = 0; i < q; ++i) {
    int actual, expected;
    slow >> expected;
    fast >> actual;
    if (actual != expected) {
      cerr << "FAIL, tc:" << i << " !!!" << endl;
      cerr << "actual: " << actual << " expected: " << expected << endl;

      for (auto a : A) cerr << a << ' '; cerr << endl;
      for (auto [u, v] : edges) cerr << u << ' ' << v << endl;
      return false;
    }
  }
  return true;
}

int main() {
  for (int i = 0; i < 100; ++i) {
    ::system("./gen");
    ::system("./slow");
    ::system("./fast");
    if (!is_ok()) break;
  }
}