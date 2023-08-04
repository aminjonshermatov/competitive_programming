//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

using namespace std;

void gen(ofstream &out) {
  const auto n = utils::random(3, 10), q = utils::random(3, 10);
  out << n << '\n';
  vector<string> ws(n);
  for (int i = 0; i < n; ++i) {
    ws[i] = utils::random_string(utils::random(5, 8));
    out << ws[i] << '\n';
  }
  out << q * 4 << '\n';
  for (int i = 0; i < q; ++i) {
    for (int _ = 0; _ < 3; ++_) {
      auto x = utils::random(0, n - 1);
      out << ws[x].substr(0, utils::random(1, 4)) << ' ' << utils::random(1, 4) << '\n';
    }
    out << utils::random_string(utils::random(1, 5)) << ' ' << utils::random(1, 5) << '\n';
  }
}

int main() {
  ofstream out(constants::DATA_IN);
  gen(out);
}