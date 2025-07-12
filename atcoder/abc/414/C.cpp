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
  int a;
  int64_t n;
  Scan(a, n);

  auto ret = int64_t{};
  for (int len = 1; len <= 12; ++len) {
    std::vector<int> buf;
    auto rec = [&](auto&& self, int i) -> void {
      if (i * 2 >= len) {
        auto tmp = buf;
        if (len % 2 == 1) {
          tmp.pop_back();
        }
        std::ranges::reverse(buf);
        tmp.insert(tmp.end(), buf.begin(), buf.end());
        std::ranges::reverse(buf);
        auto num = int64_t{};
        for (auto x : tmp) {
          num = num * 10 + x;
        }
        if (num <= n) {
          tmp.clear();
          for (auto x = num; x > 0;) {
            const auto [q, r] = std::lldiv(x, a);
            tmp.emplace_back(r);
            x = q;
          }
          auto ok = true;
          for (int l = 0, r = int(tmp.size()) - 1; l < r && ok; ++l, --r) {
            ok &= tmp[l] == tmp[r];
          }
          if (ok) {
            ret += num;
          }
        }
        return;
      }
      for (int x = i == 0 ? 1 : 0; x < 10; ++x) {
        buf.emplace_back(x);
        self(self, i + 1);
        buf.pop_back();
      }
    };
    rec(rec, 0);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
