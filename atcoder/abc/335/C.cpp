#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, q;
  std::cin >> n >> q;
  std::vector<std::pair<int, int>> state(n + 1);
  // n - 0 = head
  // n - 1 = before head
  for (int i = n; i > 0; --i) {
    state[i] = {n - i + 1, 0};
  }
  auto move = [&](std::pair<int, int> p, int c) {
    if (c == 'R') {
      ++p.first;
    } else if (c == 'L') {
      --p.first;
    } else if (c == 'D') {
      --p.second;
    } else {
      ++p.second;
    }
    return p;
  };
  int offset = 0;
  for (int i = 0; i < q; ++i) {
    char cmd;
    std::cin >> cmd;
    if (cmd ==  '1') {
      char c;
      std::cin >> c;
      state.emplace_back(move(state.back(), c));
      ++offset;
    } else {
      int p;
      std::cin >> p;
      std::cout << state[n - p + 1 + offset].first << ' ' << state[n - p + 1 + offset].second << '\n';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}