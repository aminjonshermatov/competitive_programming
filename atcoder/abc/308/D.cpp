#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr inline array<int, 5> dk{1, 0, -1, 0, 1};
constexpr inline string_view s{"snuke"};

void solve() {
  int h, w; cin >> h >> w;
  vector<string> g(h);
  for (auto &r : g) cin >> r;

  auto ok = [&](int i, int j) -> bool { return clamp(i, 0, h - 1) == i && clamp(j, 0, w - 1) == j; };
  using T = array<bool, 5>;
  vector<vector<T>> seen(h, vector<T>(w, {false, false, false, false, false}));
  queue<tuple<int, int, int>> q;
  for (int t = 0; t < 5; ++t) {
    if (g[0][0] == s[t]) {
      q.emplace(0, 0, t);
    }
  }
  while (!q.empty()) {
    auto [i, j, t] = q.front(); q.pop();
    if (i == h - 1 && j == w - 1) {
      cout << "Yes\n";
      return;
    }
    for (int k = 0; k < 4; ++k) {
      auto ni = i + dk[k];
      auto nj = j + dk[k + 1];
      auto nt = (t + 1) % 5;
      if (!ok(ni, nj) || g[ni][nj] != s[nt] || seen[ni][nj][nt]) continue;
      seen[ni][nj][nt] = true;
      q.emplace(ni, nj, nt);
    }
  }
  cout << "No\n";
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
