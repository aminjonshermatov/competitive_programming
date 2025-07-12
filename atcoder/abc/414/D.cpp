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
  std::vector<int64_t> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  std::ranges::sort(as);
  dbg(as);
  auto ret = as[n - 1] - as[0];
  std::priority_queue<int64_t> pq;
  for (int i = 0; i + 1 < n; ++i) {
    pq.emplace(as[i] - as[i + 1]);
    if (pq.size() >= m) {
      pq.pop();
    }
  }
  assert(pq.size() + 1 == m);
  while (!pq.empty()) {
    ret += pq.top();
    pq.pop();
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
