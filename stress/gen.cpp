//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

void gen(std::ofstream &out) {
  const auto n = utils::random(2, 10);
  const auto m = utils::random(2, 10);
  out << n << ' ' << m << '\n';
  for (int i = 0; i < m; ++i) {
    auto l = utils::random(1, n);
    auto r = utils::random(l, n);
    out << l << ' ' << r << '\n';
  }
}

int main() {
  std::ofstream out(constants::DATA_IN);
  gen(out);
}