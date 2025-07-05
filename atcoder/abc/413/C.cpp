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
  int q;
  Scan(q);

  int head = 0;
  std::vector<std::pair<int, int>> ops;
  while (q-- > 0) {
    char cmd;
    Scan(cmd);

    if (cmd == '1') {
      int c, x;
      Scan(c, x);
      ops.emplace_back(c, x);
    } else {
      int k;
      Scan(k);

      auto sum = int64_t{};
      for (; k > 0;) {
        assert(head < ops.size());
        auto cur = std::min(k, ops[head].first);
        k -= cur;
        sum += cur * 1LL * ops[head].second;
        if ((ops[head].first -= cur) == 0) {
          ++head;
        }
      }
      Println(sum);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
