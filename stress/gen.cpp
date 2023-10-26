//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

using namespace std;

void gen(ofstream &out) {
  const auto n = utils::random(2, 400);
  const auto q = utils::random(2, 400);
  out << n << ' ' << q << '\n';
  vector<int> as(n);
  for (auto &a : as) {
    a = utils::random(1, 1000000000);
  }
  for (auto a : as) {
    out << a << ' ';
  }
  out << '\n';
  for (int i = 0; i < q; ++i) {
    auto l1 = utils::random(1, n / 2);
    auto r1 = utils::random(l1, n / 2);
    auto l2 = utils::random(r1 + 1, n);
    auto r2 = utils::random(l2, n);
    out << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << '\n';
  }
}

int main() {
  ofstream out(constants::DATA_IN);
  gen(out);
}