//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "constants.h"

bool check() {
  std::ifstream data(constants::DATA_IN);
  std::ifstream slow(constants::SLOW_OUT);
  std::ifstream fast(constants::FAST_OUT);

  int n;
  data >> n;
  std::vector<int> ps(n);
  for (auto &p : ps) {
    data >> p;
  }

  int q;
  data >> q;

  for (int i = 0; i < q; ++i) {
    int l, r;
    data >> l >> r;

    int s, f;
    slow >> s;
    fast >> f;
    if (s != f) {
      std::cerr << "FAIL " << i << '\n';
      std::cerr << n << '\n';
      for (auto p : ps) {
        std::cerr << p << ' ';
      }
      std::cerr << '\n';
      std::cerr << l << ' ' << r << '\n';
      std::cerr << "! " << s << ' ' << f << '\n';
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
    std::this_thread::sleep_for(300ms);
    std::cout << "done " << i << std::endl;
  }
}