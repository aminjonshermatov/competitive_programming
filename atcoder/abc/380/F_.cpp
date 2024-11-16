#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

int8_t cache[2][1 << 13][1 << 13];

void Solve() {
  int n, m, l;
  Scan(n, m, l);
  std::vector<int> as(n), bs(m), cs(l);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  for (int i = 0; i < m; ++i) {
    Scan(bs[i]);
  }
  for (int i = 0; i < l; ++i) {
    Scan(cs[i]);
  }

  const auto all = n + m + l;
  auto get = [&](int pos) {
    assert(std::clamp(pos, 0, all - 1) == pos);
    if (pos < n) {
      return as[pos];
    }
    if (pos - n < + m) {
      return bs[pos - n];
    }
    assert(pos - n - m < l);
    return cs[pos - n - m];
  };

  auto dp = [&](auto&& self, uint32_t alice, uint32_t bob, uint32_t isAlice) -> bool {
    assert(std::popcount(alice) > 0);
    assert(std::popcount(bob) > 0);
    assert((alice & bob) == 0U);
    auto& loc = cache[isAlice][alice][bob];
    if (loc != -1) {
      return loc;
    }
    std::vector<int8_t> curA, curB, curT;
    for (int8_t i = 0; i < all; ++i) {
      if (alice >> i & 1) {
        curA.emplace_back(i);
      } else if (bob >> i & 1) {
        curB.emplace_back(i);
      } else {
        curT.emplace_back(i);
      }
    }
    const auto nxt = 1 - isAlice;
    loc = 0;
    for (auto id : (isAlice ? curA : curB)) {
      for (auto tId : curT) {
        if (get(tId) < get(id)) {
          loc |= !self(self, alice | (isAlice << tId), bob | (nxt << tId), nxt);
        }
      }
    }
    return loc;
  };
  std::memset(cache, -1, sizeof(cache));
  Println(dp(dp, (1U << n) - 1, ((1U << m) - 1) << n, 1U) ? "Takahashi" : "Aoki");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
