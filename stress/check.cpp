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

  int n, m;
  data >> n >> m;
  string s(n, '#');
  for (auto &c : s) {
    int x;
    data >> x;
    c = char('a' + x);
  }

  const auto parse = [&](ifstream &in) -> pair<int, vector<int>> {
    int ans;
    in >> ans;
    int len;
    in >> len;
    vector<int> subs(len);
    for (auto &x : subs) {
      in >> x;
    }
    return {ans, subs};
  };
  auto [sx, sy] = parse(slow);
  auto [fx, fy] = parse(fast);
  if (sx != fx) {
    cerr << "FAIL" << '\n';
    cerr << n << ' ' << m << '\n' << s << '\n';
    cerr << sx << ' ' << fx << '\n';
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