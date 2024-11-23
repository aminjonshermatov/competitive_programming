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
  std::string s;
  Scan(n, s);

  std::vector<int> os(n), ts(n);
  for (int i = 0; i < n; ++i) {
    os[i] += i > 0 ? os[i - 1] : 0;
    if (s[i] == '1') {
      ++os[i];
    } else {
      os[i] = 0;
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    ts[i] += i + 1 < n ? ts[i + 1] : 0;
    if (s[i] == '2') {
      ++ts[i];
    } else {
      ts[i] = 0;
    }
  }
  int ret = 1;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '/' && std::clamp(i, 1, n - 2) == i) {
      ret = std::max(ret, std::min(os[i - 1], ts[i + 1]) * 2 + 1);
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
