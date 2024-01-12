//
// Created by aminjon on 4/13/23.
//
#pragma once

#include <random>
#include <chrono>
#include <string>
#include <cassert>

namespace utils {

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

decltype(auto) randomInt(int lo, int hi) { // [lo, hi]
  assert(lo <= hi);
  return lo + std::abs(static_cast<int>(rng())) % (hi - lo + 1);
}

decltype(auto) randomString(int len, char from, char to) {
  assert(len > 0);
  std::string s(len, '#');
  for (auto &ch : s) {
    ch = char(from + randomInt(0, to - from));
  }
  return s;
}

decltype(auto) randomTree(int nVertices) { // 0 - indexed
  assert(nVertices > 0);
  std::vector<std::pair<int, int>> edges(nVertices - 1);
  for (int v = 1; v < nVertices; ++v) {
    edges[v - 1] = std::pair(v, randomInt(0, v - 1));
  }
  return edges;
}

} // namespace utils