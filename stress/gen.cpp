//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

using namespace std;

void gen(ofstream &out) {
  const auto n = utils::random(5, 1000);
  const auto m = utils::random(5, 1000);
  const auto k = utils::random(1, max(n, m));
  vector<pair<int, int>> cs(k);
  set<pair<int, int>> seen;
  for (auto &[i, j] : cs) {
    do {
      i = utils::random(1, n);
      if (i == 1) {
        j = utils::random(2, m);
      } else if (i == n) {
        j = utils::random(1, m - 1);
      } else {
        j = utils::random(1, m);
      }
    } while (seen.contains(pair(i, j)));
    seen.emplace(i, j);
  }
  out << n << ' ' << m << ' ' << k << '\n';
  for (auto [i, j] : cs) {
    out << i << ' ' << j << '\n';
  }
}

int main() {
  ofstream out(constants::DATA_IN);
  gen(out);
}