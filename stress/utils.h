//
// Created by aminjon on 4/13/23.
//

#ifndef COMPETITIVE_PROGRAMMING_UTILS_H
#define COMPETITIVE_PROGRAMMING_UTILS_H

#include <random>
#include <chrono>
#include <string>
#include <cassert>

namespace utils {

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

int random(int lo, int hi) { // [lo, hi]
  assert(lo <= hi);
  return lo + std::abs(static_cast<int>(rnd())) % (hi - lo + 1);
}

std::string random_string(int len, bool is_lower = true) {
  assert(len > 0);
  std::string s(len, '#');
  for (auto &ch : s) {
    ch = char((is_lower ? 'a' : 'A') + random(0, 25));
  }
  return s;
}

}// namespace utils

#endif//COMPETITIVE_PROGRAMMING_UTILS_H
