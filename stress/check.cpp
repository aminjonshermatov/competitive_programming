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

  int n, m, k;
  data >> n >> m >> k;
  vector<pair<int, int>> cs(k);
  for (auto &[i, j] : cs) {
    data >> i >> j;
  }

  int s, f;
  slow >> s;
  fast >> f;
  if (s != f) {
    cerr << "FAIL" << '\n';
    cerr << n << ' ' << m << ' ' << k << '\n';
    for (auto [i, j] : cs) {
      cerr << i << ' ' << j << '\n';
    }
    cerr << "! " << s << ' ' << f << '\n';
    return false;
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