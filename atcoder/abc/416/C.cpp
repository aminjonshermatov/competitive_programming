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
  int n, k, x;
  Scan(n, k, x);
  std::vector<std::string> ss(n);
  for (auto& s : ss) {
    Scan(s);
  }

  std::priority_queue<std::string> pq;
  std::string cur;
  auto rec = [&](auto&& self, int dep) -> void {
    if (dep == k) {
      pq.emplace(cur);
      if (pq.size() > x) {
        pq.pop();
      }
      return;
    }
    for (int i = 0; i < n; ++i) {
      cur.append(ss[i]);
      self(self, dep + 1);
      for (auto _ = 0; _ < ss[i].size(); ++_) {
        cur.pop_back();
      }
    }
  };
  rec(rec, 0);
  Println(pq.top());
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
