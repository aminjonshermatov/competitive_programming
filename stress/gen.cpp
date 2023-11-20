//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

void gen(std::ofstream &out) {
  const auto n = utils::random(2, 1000);
  const auto q = utils::random(2, 1000);
  out << n << ' ' << q << '\n';
  int prv_t = 0;
  for (int i = 0; i < n; ++i) {
    auto t = utils::random(prv_t + 1, prv_t + 6);
    auto k = utils::random(1, 1000);
    out << "+-"[utils::random(0, 1)] << ' ' << t << ' ' << k << '\n';
    prv_t = t;
  }
  for (int i = 0; i < q; ++i) {
    out << utils::random(1, 1000) << ' ';
  }
  out << '\n';
}

int main() {
  std::ofstream out(constants::DATA_IN);
  gen(out);
}