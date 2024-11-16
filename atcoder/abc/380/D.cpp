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
  std::string s;
  int q;
  Scan(s, q);

  while (q-- > 0) {
    int64_t k;
    Scan(k);

    auto go = [&](auto&& self, int64_t len, int64_t kth, bool rev) -> char {
      assert(1 <= kth && kth <= len);
      if (len == s.size()) {
        auto c = s[kth - 1];
        if (rev) {
          if (std::clamp(c, 'A', 'Z') == c) {
            c = c - 'A' + 'a';
          } else {
            c = c - 'a' + 'A';
          }
        }
        return c;
      }
      const auto lhs = len / 2;
      if (kth <= lhs) {
        return self(self, lhs, kth, rev);
      }
      return self(self, lhs, kth - lhs, !rev);
    };
    int64_t cur = s.size();
    while (cur < k) {
      cur *= 2;
    }
    Print(go(go, cur, k, false));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
