//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

using namespace std;

void gen(ofstream &out) {
  const auto n = utils::random(6, 12);
  const auto m = 4;
  const auto s = utils::random_string(n, '1', m);
  out << n << ' ' << m << '\n';
  for (auto c : s) {
    out << c << ' ';
  }
  out << '\n';
}

int main() {
  ofstream out(constants::DATA_IN);
  gen(out);
}