#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

void solve() {
  int n;
  scan(n);
  std::vector<i64> as(n);
  for (auto&& a : as) {
    scan(a);
  }

  std::vector<i64> deg(n, 1);
  auto tot = std::accumulate(as.begin(), as.end(), i64{});
  auto sqr = [&](const auto x) { return x * x; };
  auto cmp = [&](const auto a, const auto b) -> i64 {
    return as[a] * (sqr(deg[a] + 1) - sqr(deg[a])) > as[b] * (sqr(deg[b] + 1) - sqr(deg[b]));
  };
  std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
  for (int i = 0; i < n; ++i) {
    pq.emplace(i);
  }
  for (int _ = 0; _ + 2 < n; ++_) {
    auto idx = pq.top();
    pq.pop();
    tot -= as[idx] * sqr(deg[idx]);
    ++deg[idx];
    tot += as[idx] * sqr(deg[idx]);
    pq.emplace(idx);
  }
  dbg(deg);
  assert(std::ranges::min(deg) >= 1);
  assert(std::accumulate(deg.begin(), deg.end(), i64{}) >= 2 * n - 2);
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}