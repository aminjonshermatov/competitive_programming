//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "constants.h"

bool check() {
  std::ifstream data(constants::DATA_IN);
  std::ifstream slow(constants::SLOW_OUT);
  std::ifstream fast(constants::FAST_OUT);

  using i64 = int64_t;

  int n, q;
  data >> n >> q;
  std::vector<std::tuple<char, i64, i64>> evs(n);
  for (auto &[op, t, k] : evs) {
    data >> op >> t >> k;
  }
  std::vector<i64> init(q);
  for (int i = 0; i < q; ++i) {
    data >> init[i];
  }
  for (int i = 0; i < q; ++i) {
    i64 s;
    slow >> s;
    i64 f;
    fast >> f;

    if (s != f) {
      std::cerr << n << ' ' << q << '\n';
      for (auto [op, t, k] : evs) {
        std::cerr << op << ' ' << t << ' ' << k << '\n';
      }
      for (auto x : init) {
        std::cerr << x << ' ';
      }
      std::cerr << '\n';
      std::cerr << "bad: " << i << ' ' << s << ' ' << f << '\n';
      return false;
    }
  }

  return true;
}

int main() {
  for (int i = 0; i < 1000; ++i) {
    std::system("./gen");
    std::system("./slow");
    std::system("./fast");
    if (!check()) break;
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(150ms);
    std::cout << "done " << i << std::endl;
  }
}