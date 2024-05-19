#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n;
  scan(n);
  std::vector<int> as(n), cs(n);
  for (int i = 0; i < n; ++i) {
    scan(as[i], cs[i]);
  }
  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return as[i] == as[j] ? cs[i] < cs[j] : as[i] > as[j];
  });
  std::vector<int> ids;
  for (int i = 0; i < n; ++i) {
    ids.emplace_back(ord[i]);
    int j = i;
    while (j + 1 < n && as[ord[i]] > as[ord[j + 1]] && cs[ord[i]] < cs[ord[j + 1]]) {
      ++j;
    }
    i = j;
  }
  std::ranges::sort(ids);
  println(ids.size());;
  for (auto&& id : ids) {
    print(id + 1);
  }
  println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}