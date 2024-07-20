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
  int n, k;
  std::string s;
  scan(n, k, s);
  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);

  std::set<std::string> seen;
  int tot{};
  do {
    std::string t(n, '#');
    for (int i = 0; i < n; ++i) {
      t[i] = s[ord[i]];
    }
    if (seen.contains(t)) {
      continue;
    }
    bool ok = true;
    for (int i = 0; i + k <= n; ++i) {
      auto x = t.substr(i, k);
      auto y = x;
      std::ranges::reverse(y);
      ok &= x != y;
    }
    tot += ok;
    seen.emplace(t);
  } while (std::next_permutation(ord.begin(), ord.end()));
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef LOCAL
  freopen("../../input.txt", "r", stdin);
#endif

  solve();
}