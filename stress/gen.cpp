//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

void gen(std::ofstream &out) {
  const auto n = utils::random(2, 10);
  out << n << '\n';
  for (int i = 0; i < n; ++i) {
    auto len = utils::random(2, 5);
    std::string s(len, '#');
    for (auto &c : s) {
      c = char('0' + utils::random(0, 1));
    }
    if (utils::random(0, 1) == 0) {
      s[utils::random(0, len - 1)] = '?';
    }
    out << s << '\n';
  }
}

int main() {
  std::ofstream out(constants::DATA_IN);
  gen(out);
}