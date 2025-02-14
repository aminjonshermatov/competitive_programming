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
  int64_t n, a, b;
  int m;
  Scan(n, m, a, b);
  std::map<int64_t, int> evs;
  std::set<int64_t> all;
  for (int i = 0; i < n; ++i) {
    int64_t l, r;
    Scan(l, r);
    evs[l] += 1;
    all.emplace(l);
    evs[r + 1] -= 1;
    all.emplace(r + 1);
  }
  std::set<int64_t> may;
  may.emplace(0LL);
  auto acc = 0;
  for (auto x : all) {
    while (!may.empty() && x - *may.begin() > b) {
      may.erase(may.begin());
    }
    if ((acc += evs[x]) == 0) {
      auto nMay = may;
      for (auto y : may) {
        for (int jmp = a; jmp <= b && x + jmp <= n; ++jmp) {
          nMay.emplace(x + jmp);
        }
      }
      std::swap(may, nMay);
    }
  }
  Println(may.contains(n) ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
