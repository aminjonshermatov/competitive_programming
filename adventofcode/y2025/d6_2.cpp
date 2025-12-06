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
  std::vector<std::string> xs;
  for (std::string s; ; s.clear()) {
    std::getline(std::cin, s);
    if (s.empty()) {
      break;
    }
    xs.emplace_back(s);
  }
  const auto n = int(xs.size());
  const auto maxLen = std::ranges::max(xs, {}, &std::string::size).size();
  for (int i = 0; i < n; ++i) {
    for (; xs[i].size() < maxLen; xs[i].push_back(' ')) {
    }
    std::cerr << xs[i] << '\n';
  }

  std::vector<int64_t> acc;
  for (int l = 0; l < xs.front().size(); ++l) {
    auto maxR = 0;
    for (int i = 0; i + 1 < n; ++i) {
      auto curR = l;
      while (curR + 1 < maxLen && std::isspace(xs[i][curR + 1]) == 0) {
        ++curR;
      }
      maxR = std::max(maxR, curR);
    }
    const auto op = xs.back()[l];
    assert(op == '+' || op == '*');
    acc.emplace_back(op == '+' ? 0 : 1);
    for (; l <= maxR; ++l) {
      auto x = 0LL;
      for (int i = 0; i + 1 < n; ++i) {
        if (std::isspace(xs[i][l]) != 0) {
          continue;
        }
        x = x * 10 + xs[i][l] - '0';
      }
      if (op == '+') {
        acc.back() += x;
      } else {
        acc.back() *= x;
      }
    }
    for (int i = 0; i < n && l < maxLen; ++i) {
      assert(std::isspace(xs[i][l]) != 0);
    }
  }
  Println(std::ranges::fold_left(acc, 0LL, std::plus{}));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
