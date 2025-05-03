#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Solve() {
  int n, m;
  Scan(n, m);
  std::vector<int64_t> cs(n);
  for (int i = 0; i < n; ++i) {
    Scan(cs[i]);
  }
  std::vector<std::vector<int>> byZoo(n);
  for (int i = 0; i < m; ++i) {
    int k;
    Scan(k);
    for (int j = 0; j < k; ++j) {
      int zoo;
      Scan(zoo);
      byZoo[zoo - 1].emplace_back(i);
    }
  }
  std::vector zooCnt(n, std::vector(m, 0));
  for (int i = 0; i < n; ++i) {
    for (auto x : byZoo[i]) {
      zooCnt[i][x] = std::min(zooCnt[i][x] + 1, 1);
    }
  }

  std::vector cnt(m, 0);
  auto ret = std::numeric_limits<int64_t>::max() / 2;
  int64_t curCost = 0;
  auto rec = [&](auto&& self, int zoo) -> void {
    if (zoo >= n) {
      if (std::ranges::all_of(cnt, [](auto x) { return x >= 2; })) {
        ret = std::min(ret, curCost);
      }
      return;
    }
    for (auto x = 0; x < 3; ++x) {
      curCost += cs[zoo] * x;
      for (int i = 0; i < m; ++i) {
        cnt[i] += zooCnt[zoo][i] * x;
      }
      self(self, zoo + 1);
      for (int i = 0; i < m; ++i) {
        cnt[i] -= zooCnt[zoo][i] * x;
      }
      curCost -= cs[zoo] * x;
    }
  };
  rec(rec, 0);
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
