//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

using namespace std;

constexpr int N = 100;

void gen(ofstream &out) {
  for (int k = 0; k < N; ++k) {
    const int n = utils::random(1, N);
    const int q = utils::random(N, 2 * N);

    out << n << ' ' << q << '\n';
    for (int i = 0; i < q; ++i) {
      int l = utils::random(1, n);
      int r = utils::random(l, n);
      if (utils::random(0, 1) == 0) {
        out << '^' << ' ' << l << ' ' << r << ' ' << utils::random(1, 1e9) << '\n';
      } else {
        out << '?' << ' ' << l << ' ' << r << '\n';
      }
    }
  }
  out << "0 0\n";
}

int main() {
  ofstream out(constants::DATA_IN);
  gen(out);
}