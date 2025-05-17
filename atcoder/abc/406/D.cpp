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
  int h, w, n;
  Scan(h, w, n);
  std::vector<int> is(n), js(n);
  std::vector<std::set<int>> byRow(h), byCol(w);
  for (int i = 0; i < n; ++i) {
    Scan(is[i], js[i]);
    byRow[--is[i]].emplace(i);
    byCol[--js[i]].emplace(i);
  }
  int q;
  Scan(q);
  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int row;
      Scan(row);
      --row;

      Println(byRow[row].size());
      std::vector<int> toRem(byRow[row].begin(), byRow[row].end());
      for (auto id : toRem) {
        byRow[is[id]].erase(id);
        byCol[js[id]].erase(id);
      }
    } else {
      int col;
      Scan(col);
      --col;

      Println(byCol[col].size());
      std::vector<int> toRem(byCol[col].begin(), byCol[col].end());
      for (auto id : toRem) {
        byRow[is[id]].erase(id);
        byCol[js[id]].erase(id);
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
