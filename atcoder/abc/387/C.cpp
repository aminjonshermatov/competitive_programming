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
  auto work = [&](int64_t lim) -> int64_t {
    if (lim < 10) {
      return 0;
    }
    std::vector<int> ds;
    for (auto tmp = lim; tmp > 0;) {
      const auto [q, r] = std::lldiv(tmp, 10);
      ds.emplace_back(r);
      tmp = q;
    }
    auto tot = 0LL;
    for (int len = 2; len <= ds.size(); ++len) {
      for (int fst = 1; fst <= (len == ds.size() ? ds.back() : 9); ++fst) {
        std::vector cache(len + 1, std::vector<int64_t>(2, -1));
        auto dp = [&](auto&& self, int pos, bool canUseAny) -> int64_t {
          if (pos < 0) {
            return 1;
          }
          auto& loc = cache[pos][canUseAny];
          if (loc != -1) {
            return loc;
          }
          loc = 0;
          for (int c = 0; c < fst; ++c) {
            if (canUseAny || c <= ds[pos]) {
              loc += self(self, pos - 1, canUseAny || c < ds[pos]);
            }
          }
          return loc;
        };
        tot += dp(dp, len - 2, len < ds.size() || fst < ds.back());
      }
    }
    return tot;
  };
  int64_t l, r;
  Scan(l, r);
  Println(work(r) - work(l - 1));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
