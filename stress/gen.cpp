//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

void gen(std::ofstream &out) {
  const auto n = utils::random(2e5, 5e5);
  std::vector<int> ps(n);
  std::iota(ps.begin(), ps.end(), 0);
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::shuffle(ps.begin(), ps.end(), rng);
  out << n << '\n';
  for (auto p : ps) {
    out << p << ' ';
  }
  out << '\n';

  auto q = utils::random(2e5, 5e5);
  out << q << '\n';
  while (q-- > 0) {
    auto l = utils::random(0, n - 1);
    auto r = utils::random(l, n - 1);
    out << l << ' ' << r << '\n';
  }
}

int main() {
  std::ofstream out(constants::DATA_IN);
  gen(out);
}