//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "constants.h"

auto check() -> bool {
  std::ifstream data(constants::DATA_IN);
  std::ifstream slow(constants::SLOW_OUT);
  std::ifstream fast(constants::FAST_OUT);

  int s, f;
  if (s != f) {
    return false;
  }

  return true;
}

int main() {
  constexpr int ITER = 1'000;
  for (int i = 0; i < ITER; ++i) {
    std::system("./gen");
    std::system("./slow");
    std::system("./fast");
    if (!check()) {
      break;
    }
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(150ms);
    std::cout << std::format("done {}\n", i);
  }
}