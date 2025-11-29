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
  int n;
  int64_t h;
  Scan(n, h);
  std::vector<int64_t> ts(n), ls(n), rs(n);
  for (int i = 0; i < n; ++i) {
    Scan(ts[i], ls[i], rs[i]);
  }

  constexpr int64_t kLo = 1;
  constexpr int64_t kHi = 1E9;

  std::vector<std::pair<int64_t, int64_t>> segs;
  segs.emplace_back(h, h);
  int64_t prv = 0;
  for (int i = 0; i < n; ++i) {
    decltype(segs) nsegs;
    const auto len = ts[i] - prv;
    for (auto [l, r] : segs) {
      const auto nl = std::max({kLo, l - len, ls[i]});
      const auto nr = std::min({kHi, r + len, rs[i]});
      if (nl <= nr) {
        nsegs.emplace_back(nl, nr);
      }
    }
    std::ranges::sort(nsegs);
    auto ptr = 0;
    for (int j = 0; j < nsegs.size(); ++j) {
      auto [l, r] = nsegs[j];
      while (j + 1 < nsegs.size() && nsegs[j + 1].first <= r) {
        r = std::max(r, nsegs[++j].second);
      }
      segs[ptr++] = {l, r};
    }
    segs.resize(ptr);
    prv = ts[i];
  }
  Println(segs.empty() ? "No" : "Yes");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}
