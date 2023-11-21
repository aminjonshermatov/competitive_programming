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
  std::vector<std::string> ss(n);
  for (auto &s : ss) {
    data >> s;
  }

  std::string s, f;
  slow >> s;
  fast >> f;
  if (s != f) {
    std::cerr << n << '\n';
    for (auto &w : ss) {
      std::cerr << w << '\n';
    }
    std::cerr << "bad: " << s << ' ' << f << '\n';
    return false;
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