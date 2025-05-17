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
class FenwickTree {
 public:
  FenwickTree() = default;
  explicit FenwickTree(const int n) {
    Init(std::vector(n, Info{}));
  }
  FenwickTree(const int n, const Info& info) {
    Init(std::vector(n, info));
  }
  template<typename U>
  explicit FenwickTree(const std::vector<U>& as) {
    std::vector<Info> init(as.size());
    std::ranges::generate(init, [id = std::size_t{0}, &as]() mutable {
      return Info{as[id++]};
    });
    Init(init);
  }

  auto Init(const std::vector<Info>& init) {
    N_ = static_cast<int>(init.size());
    Bit_.assign(N_, Info{});
    for (int i = 0; i < N_; ++i) {
      Modify(i, init[i]);
    }
  }

  auto Modify(const int idx, const Info& val) {
    for (auto id = idx; id < N_; id = id | (id + 1)) {
      Bit_[id] = Bit_[id] + val;
    }
  }

  auto Query(const int idx) const -> Info {
    return Query(idx, idx + 1);
  }

  // [l, r)
  auto Query(const int l, const int r) const -> Info {
    return QueryImpl(r - 1) - QueryImpl(l - 1);
  }

 private:
  auto QueryImpl(const int idx) const -> Info {
    auto ret = Info{};
    for (auto id = idx; id >= 0; id = (id & (id + 1)) - 1) {
      ret = ret + Bit_[id];
    }
    return ret;
  }

 private:
  int N_{0};
  std::vector<Info> Bit_;
};

void Solve() {
  int n;
  Scan(n);
  std::vector<std::vector<int>> g(n);
  std::vector<int> us(n - 1), vs(n - 1);
  for (int i = 0; i + 1 < n; ++i) {
    Scan(us[i], vs[i]);
    --us[i], --vs[i];
    g[us[i]].emplace_back(vs[i]);
    g[vs[i]].emplace_back(us[i]);
  }

  std::vector<int> tin(n), tout(n);
  auto timer = 0;
  auto dfs = [&](auto&& self, int v, int p) -> void {
    tin[v] = timer++;
    for (const auto u : g[v]) {
      if (u != p) {
        self(self, u, v);
      }
    }
    tout[v] = timer;
  };
  dfs(dfs, 0, -1);

  FenwickTree<int64_t> ft(n);
  for (int i = 0; i < n; ++i) {
    ft.Modify(tin[i], +1);
  }

  int q;
  Scan(q);
  int64_t tot = n;
  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int x, w;
      Scan(x, w);
      ft.Modify(tin[--x], +w);
      tot += w;
    } else {
      int y;
      Scan(y);
      --y;
      auto u = us[y];
      auto v = vs[y];
      if (tin[u] > tin[v]) {
        std::swap(u, v);
      }
      const auto sub = ft.Query(tin[v], tout[v]);
      Println(std::llabs(tot - sub * 2));
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
