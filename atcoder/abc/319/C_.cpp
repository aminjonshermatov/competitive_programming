#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  array<array<int, 3>, 3> g{};
  for (auto &r : g) {
    for (auto &c : r) {
      cin >> c;
    }
  }
  array<int, 9> ord{};
  iota(ord.begin(), ord.end(), 0);
  int tot = 0, bad = 0;
  do {
    vector<array<int, 2>> cs;
    for (auto x : ord) {
      auto [i, j] = div(x, 3);
      cs.push_back({i, j});
    }
    for (int i = 0; i + 2 < 9; ++i) {
      if (cs[i][0] == cs[i + 1][0] && cs[i + 1][0] == cs[i + 2][0]) {
        bad += (g[cs[i][0]][cs[i][1]] == g[cs[i + 1][0]][cs[i + 1][1]] && g[cs[i + 1][0]][cs[i + 1][1]] != g[cs[i + 2][0]][cs[i + 2][1]])
               || (g[cs[i][0]][cs[i][1]] != g[cs[i + 1][0]][cs[i + 1][1]] && g[cs[i + 1][0]][cs[i + 1][1]] == g[cs[i + 2][0]][cs[i + 2][1]]);
        break;
      } else if (cs[i][1] == cs[i + 1][1] && cs[i + 1][1] == cs[i + 2][1]) {
        bad += (g[cs[i][0]][cs[i][1]] == g[cs[i + 1][0]][cs[i + 1][1]] && g[cs[i + 1][0]][cs[i + 1][1]] != g[cs[i + 2][0]][cs[i + 2][1]])
               || (g[cs[i][0]][cs[i][1]] != g[cs[i + 1][0]][cs[i + 1][1]] && g[cs[i + 1][0]][cs[i + 1][1]] == g[cs[i + 2][0]][cs[i + 2][1]]);
        break;
      } else if ((cs[i][0] + cs[i][1]) == (cs[i + 1][0] + cs[i + 1][1]) && (cs[i + 1][0] + cs[i + 1][1]) == (cs[i + 2][0] + cs[i + 2][1])) {
        bad += (g[cs[i][0]][cs[i][1]] == g[cs[i + 1][0]][cs[i + 1][1]] && g[cs[i + 1][0]][cs[i + 1][1]] != g[cs[i + 2][0]][cs[i + 2][1]])
               || (g[cs[i][0]][cs[i][1]] != g[cs[i + 1][0]][cs[i + 1][1]] && g[cs[i + 1][0]][cs[i + 1][1]] == g[cs[i + 2][0]][cs[i + 2][1]]);
        break;
      } else if ((cs[i][0] - cs[i][1]) == (cs[i + 1][0] - cs[i + 1][1]) && (cs[i + 1][0] - cs[i + 1][1]) == (cs[i + 2][0] - cs[i + 2][1])) {
        bad += (g[cs[i][0]][cs[i][1]] == g[cs[i + 1][0]][cs[i + 1][1]] && g[cs[i + 1][0]][cs[i + 1][1]] != g[cs[i + 2][0]][cs[i + 2][1]])
               || (g[cs[i][0]][cs[i][1]] != g[cs[i + 1][0]][cs[i + 1][1]] && g[cs[i + 1][0]][cs[i + 1][1]] == g[cs[i + 2][0]][cs[i + 2][1]]);
        break;
      }
    }
    ++tot;
  } while (next_permutation(ord.begin(), ord.end()));
  dbg(bad, tot);
  cout << double(bad) / tot << '\n';
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
