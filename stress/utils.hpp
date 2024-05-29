#pragma once

#include <random>
#include <chrono>
#include <string>
#include <cassert>

namespace utils {

inline std::random_device randomDevice{};
inline std::mt19937 rng(randomDevice());

inline int randomInt(const int lo, const int hi) { // [lo, hi]
  assert(lo <= hi);
  return lo + std::abs(static_cast<decltype(lo)>(rng())) % (hi - lo + 1);
}

inline decltype(auto) randomString(const std::size_t len, const char from, const char to) {
  assert(len > 0u);
  std::string s(len, '#');
  for (auto&& ch : s) {
    ch = static_cast<char>(from + randomInt(0, to - from));
  }
  return s;
}

using namespace std::literals;
inline decltype(auto) randomTree(const std::size_t nVertices) { // 0 - indexed
  assert(nVertices > 0u);
  std::vector<std::pair<uint32_t, uint32_t>> edges(nVertices - 1);
  for (std::size_t v = 1u; v < nVertices; ++v) {
    edges[v - 1u] = std::pair(v, randomInt(0, v - 1));
  }
  return edges;
}

} // namespace utils