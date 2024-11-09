#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int q;
  scan(q);

  using i64 = int64_t;
  std::multiset<i64> fs;

  i64 acc = 0;
  for (int i = 0; i < q; ++i) {
    char cmd;
    scan(cmd);
    if (cmd == '1') {
      fs.emplace(acc);
    } else if (cmd == '2') {
      i64 t;
      scan(t);
      acc += t;
    } else {
      i64 h;
      scan(h);
      int cnt = 0;
      while (!fs.empty() && *fs.begin() <= acc - h) {
        ++cnt;
        fs.erase(fs.begin());
      }
      println(cnt);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}