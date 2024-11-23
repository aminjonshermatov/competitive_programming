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
  int n, q;
  std::string s;
  Scan(n, q, s);

  std::vector<int> ids1, ids2, ids3;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '1') {
      ids1.emplace_back(i);
    } else if (s[i] == '2') {
      ids2.emplace_back(i);
    } else {
      ids3.emplace_back(i);
    }
  }

  while (q-- > 0) {
    int l, r;
    Scan(l, r);
    --l, --r;

    if (auto it = std::ranges::lower_bound(ids3, l); it == ids3.end() || *it > r) {
      Println(0);
      continue;
    }
    auto can = [&](int len) -> bool {
      int beg = l;
      {
        auto pos = std::distance(ids1.begin(), std::ranges::lower_bound(ids1, beg));
        if (pos + len > ids1.size() || ids1[pos + len - 1] > r) {
          return false;
        }
        beg = ids1[pos + len - 1];
      }
      {
        auto it = std::ranges::lower_bound(ids3, beg);
        if (it == ids3.end() || *it > r) {
          return false;
        }
        beg = *it + 1;
      }
      {
        auto pos = std::distance(ids2.begin(), std::ranges::lower_bound(ids2, beg));
        if (pos + len > ids2.size() || ids2[pos + len - 1] > r) {
          return false;
        }
      }
      return true;
    };
    int lo = 0, hi = n;
    while (hi - lo > 1) {
      const auto mid = lo + (hi - lo) / 2;
      (can(mid) ? lo : hi) = mid;
    }
    Println(2 * lo + 1);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
