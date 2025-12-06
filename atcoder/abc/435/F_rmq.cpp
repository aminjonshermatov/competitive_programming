#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

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
  int Val = std::numeric_limits<int>::min(), Id = -1;

  auto operator<=>(const Info&) const = default;
};
Info operator+(const Info& lhs, const Info& rhs) {
  return lhs > rhs ? lhs : rhs;
}

void Solve() {
  int n;
  Scan(n);
  std::vector<int> ps(n);
  for (int i = 0; i < n; ++i) {
    Scan(ps[i]);
  }

  std::vector<Info> init(n);
  std::ranges::generate(init, [i = 0, &ps] mutable {
    return Info(ps[i], i++);
  });
  SparseTable<Info> rmq(init);
  Println([&](this auto self, const int l, const int r, const int pos) -> int64_t {
    if (l >= r) {
      return std::abs(pos - l);
    }
    const auto [val, id] = rmq.Query(l, r + 1);
    auto ret = int64_t{0};
    if (l <= id - 1) {
      ret = std::max(ret, self(l, id - 1, id) + std::abs(id - pos));
    }
    if (id + 1 <= r) {
      ret = std::max(ret, self(id + 1, r, id) + std::abs(id - pos));
    }
    return ret;
  }(0, n - 1, std::ranges::find(ps, n) - ps.begin()));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
