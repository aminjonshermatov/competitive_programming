#pragma once

#include <random>
#include <chrono>
#include <string>
#include <cassert>

namespace utils {

std::random_device randomDevice{};
std::mt19937 rng(randomDevice());

decltype(auto) randomInt(auto&& lo, auto&& hi) { // [lo, hi]
  assert(lo <= hi);
  return lo + std::abs(static_cast<decltype(lo)>(rng())) % (hi - lo + 1);
}

decltype(auto) randomString(std::size_t len, char from, char to) {
  assert(len > 0uz);
  std::string s(len, '#');
  for (auto&& ch : s) {
    ch = static_cast<char>(from + randomInt(0, to - from));
  }
  return s;
}

decltype(auto) randomTree(std::size_t nVertices) { // 0 - indexed
  assert(nVertices > 0uz);
  std::vector<std::pair<uint32_t, uint32_t>> edges(nVertices - 1);
  for (std::size_t v = 1uz; v < nVertices; ++v) {
    edges[v - 1uz] = std::pair(v, randomInt(0, v - 1));
  }
  return edges;
}

} // namespace utils