//
// Created by aminjon on 8/27/22.
//

#include <bits/stdc++.h>

template <typename Info>
class SparseTable {
 public:
  template <typename T>
  explicit SparseTable(const std::vector<T>& init) {
    Init(init);
  }

  template <typename T>
  auto Init(const std::vector<T>& init) {
    assert(!init.empty());
    const auto b = std::bit_width(init.size());
    Infos_.assign(b, std::vector(init.size(), Info{}));
    for (std::size_t i = 0; i < init.size(); ++i) {
      Infos_[0][i] = Info{init[i]};
    }
    for (std::size_t w = 1; w < b; ++w) {
      for (std::size_t i = 0; i < init.size(); ++i) {
        Infos_[w][i] = Infos_[w - 1][i] + Infos_[w - 1][std::min(init.size() - 1, i + (1u << (w - 1)))];
      }
    }
  }

  auto Query(std::size_t l, std::size_t r) const -> Info {
    if (l == r) {
      return {};
    }
    const auto b = std::bit_width(r - l) - 1;
    return Infos_[b][l] + Infos_[b][r - (1 << b)];
  }

 private:
  std::vector<std::vector<Info>> Infos_{};
};

class Info {
 public:
  int Val = std::numeric_limits<int>::min();
};
Info operator+(const Info& lhs, const Info& rhs) {
  return {std::max(lhs.Val, rhs.Val)};
}
