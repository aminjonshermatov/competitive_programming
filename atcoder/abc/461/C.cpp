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
  int n, k, m;
  Scan(n, k, m);
  std::vector<int64_t> cs(n), vs(n);
  for (int i = 0; i < n; ++i) {
    Scan(cs[i], vs[i]);
  }

  std::vector<int> ord(n);
  std::ranges::iota(ord, 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return vs[i] > vs[j];
  });

  auto ret = 0LL;
  auto cnt = 0;
  std::vector<int> maybe;
  std::set<int> vis;
  for (const auto id : ord) {
    if (!vis.contains(cs[id]) && vis.size() < m) {
      vis.emplace(cs[id]);
      ret += vs[id];
      ++cnt;
    } else {
      maybe.emplace_back(id);
    }
  }
  std::ranges::reverse(maybe);
  while (cnt++ < k && !maybe.empty()) {
    ret += vs[maybe.back()];
    maybe.pop_back();
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
