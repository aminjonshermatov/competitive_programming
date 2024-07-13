#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

bool imin(auto&& a, auto&& b) noexcept {
  return a > b && (a = b, true);
}

using i64 = int64_t;

void solve() {
  int n, m;
  scan(n, m);
  auto in = [&](const int v) {
    return 2 * v;
  };
  auto out = [&](const int v) {
    return 2 * v + 1;
  };
  std::vector<std::vector<std::pair<int, i64>>> g(2 * n);
  for (int i = 0; i < n; ++i) {
    i64 w;
    scan(w);
    g[in(i)].emplace_back(out(i), w);
    g[out(i)].emplace_back(in(i), w);
  }
  for (int i = 0; i < m; ++i) {
    int u, v;
    i64 w;
    scan(u, v, w);
    --u, --v;
    g[out(u)].emplace_back(in(v), w);
    g[out(v)].emplace_back(in(u), w);
  }

  using T = std::pair<i64, int>;
  std::priority_queue<T, std::vector<T>, std::greater<>> pq;
  constexpr auto inf = std::numeric_limits<i64>::max() / 2;
  std::vector<i64> dist(2 * n, inf);
  pq.emplace(dist[in(0)] = 0, in(0));
  while (!pq.empty()) {
    const auto [d, v] = pq.top();
    pq.pop();
    if (d != dist[v]) {
      continue;
    }
    for (auto&& [u, w] : g[v]) {
      if (imin(dist[u], d + w)) {
        pq.emplace(dist[u], u);
      }
    }
  }
  for (int i = 1; i < n; ++i) {
    print(dist[out(i)]);
  }
  println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef LOCAL
  freopen("../../input.txt", "r", stdin);
#endif

  solve();
}