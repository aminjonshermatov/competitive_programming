#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::string s;
  std::cin >> n >> s;
  int q;
  std::cin >> q;
  std::vector<std::pair<int, int>> qs(q);
  for (auto& [a, b] : qs) {
    char x, y;
    std::cin >> x >> y;
    a = x - 'a';
    b = y - 'a';
  }
  std::ranges::reverse(qs);
  std::array<bool, 26> used{};
  used.fill(false);
  std::array<char, 26> map{};
  for (int i = 0; i < 26; ++i) {
    map[i] = char('a' + i);
  }
  for (auto [from, to] : qs) {
    if (!used[from]) {
      map[from] = map[to];
    }
  }
  for (auto c : s) {
    std::cout << map[c - 'a'];
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}