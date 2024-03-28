//
// Created by aminjon on 3/28/24.
//
#include <bits/stdc++.h>

struct RollingHash {
  static constexpr std::size_t nTimes = 2;

  using T = int64_t;
  using hash_type = std::array<T, nTimes>;

  static constexpr std::array<T, 10> mods = {1000000007, 1000150309, 1000300597, 1000450937, 1000601171, 1000751471, 1000901723, 1001052037, 1001202337, 1001352593};
  static constexpr std::array<T, 10> bases = {9383, 886, 2777, 6915, 7793, 8335, 5386, 492, 6649, 1421};

  static_assert(mods.size() == bases.size() && "Mismatch `mods` and `bases` length");
  static_assert(0 < nTimes && nTimes <= mods.size() && "`nTimes` not in range [1, |mods|]");

  static std::array<std::size_t, nTimes> selectedIds;
  static bool initializedModsAndBases;

  static std::vector<std::array<T, nTimes>> powerOfBases;
  std::vector<std::array<T, nTimes>> hashes;

  explicit RollingHash(std::string_view s) {
    if (!initializedModsAndBases) {
      initModsAndBases();
    }

    if (powerOfBases.empty()) {
      powerOfBases.emplace_back();
      powerOfBases.back().fill(T(1));
    }
    for (; powerOfBases.size() <= s.size();) {
      powerOfBases.emplace_back();
      for (std::size_t i{}; i < nTimes; ++i) {
        powerOfBases.back()[i] = mul(powerOfBases[powerOfBases.size() - 2][i], bases[selectedIds[i]], i);
      }
    }

    hashes.reserve(s.size());
    std::array<T, nTimes> cur{};
    cur.fill(T{});
    for (std::size_t i{}; i < s.size(); ++i) {
      for (std::size_t j{}; j < nTimes; ++j) {
        cur[j] = add(mul(cur[j], bases[selectedIds[j]], j), T(s[i] - '\0'), j);
      }
      hashes.emplace_back(cur);
    }
  }

  [[nodiscard]] hash_type operator()(int l, int r) const {
    assert(0 <= l && l <= r && r < hashes.size());
    auto ret = hashes[r];
    if (l > 0) {
      for (std::size_t j{}; j < nTimes; ++j) {
        ret[j] = sub(ret[j], mul(hashes[l - 1][j], powerOfBases[r - l + 1][j], j), j);
      }
    }
    return ret;
  }

  static void initModsAndBases() {
    initializedModsAndBases = true;

    std::random_device rd{};
    std::mt19937 rng(rd());
    std::vector<std::size_t> ids(mods.size());
    std::iota(ids.begin(), ids.end(), std::size_t{});
    std::shuffle(ids.begin(), ids.end(), rng);
    for (std::size_t i{}; i < nTimes; ++i) {
      selectedIds[i] = ids[i];
    }
  }

  [[nodiscard]] static inline T add(const T& a, const T& b, std::size_t which) {
    auto ret = (a + b) % mods[selectedIds[which]];
    if (ret < 0) {
      ret += mods[selectedIds[which]];
    }
    return ret;
  }
  [[nodiscard]] static inline T sub(const T& a, const T& b, std::size_t which) {
    auto ret = (a - b) % mods[selectedIds[which]];
    if (ret < 0) {
      ret += mods[selectedIds[which]];
    }
    return ret;
  }
  [[nodiscard]] static inline T mul(const T& a, const T& b, std::size_t which) {
    auto ret = a * 1LL * b % mods[selectedIds[which]];
    if (ret < 0) {
      ret += mods[selectedIds[which]];
    }
    return ret;
  }
};
bool RollingHash::initializedModsAndBases = false;
std::vector<std::array<RollingHash::T, RollingHash::nTimes>> RollingHash::powerOfBases;
std::array<std::size_t, RollingHash::nTimes> RollingHash::selectedIds;
