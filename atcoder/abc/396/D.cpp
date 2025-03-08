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
  int n, m;
  Scan(n, m);
  std::vector dist(n, std::vector(n, int64_t{-1}));
  for (int i = 0; i < m; ++i) {
    int u, v;
    uint64_t w;
    Scan(u, v, w);
    assert(u != v);
    --u, --v;
    dist[u][v] = dist[v][u] = w;
  }

  std::vector<int> ord(n - 2);
  std::iota(ord.begin(), ord.end(), 0);
  auto ret = dist[0][n - 1] != -1 ? dist[0][n - 1] : std::numeric_limits<uint64_t>::max();
  do {
    uint64_t d = 0;
    int lst = 0;
    for (auto id : ord) {
      const auto v = id + 1;
      if (dist[lst][v] != -1) {
        d ^= dist[lst][v];
        if (dist[v][n - 1] != -1) {
          ret = std::min(ret, d ^ dist[v][n - 1]);
        }
      } else {
        break;
      }
      lst = v;
    }
  } while (std::ranges::next_permutation(ord).found);
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
