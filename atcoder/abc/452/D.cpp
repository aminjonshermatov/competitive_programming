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
  std::string s, t;
  Scan(s, t);

  const auto n = int(s.size());

  std::array<std::vector<int>, 26> pos{};
  for (int i = 0; i < n; ++i) {
    pos[s[i] - 'a'].emplace_back(i);
  }

  auto ret = 0LL;
  for (int i = 0; i < n; ++i) {
    auto j = i - 1;
    for (const auto c : t) {
      auto it = std::ranges::upper_bound(pos[c - 'a'], j);
      if (it == pos[c - 'a'].end()) {
        j = n;
        break;
      }
      j = *it;
    }
    ret += j - i;
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
