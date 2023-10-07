#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> as(m);
  for (auto &a : as) {
    cin >> a;
  }
  vector<string> g(n);
  vector<int> tot(n, 0);
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    cin >> g[i];
    tot[i] = i + 1;
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == 'o') {
        tot[i] += as[j];
      }
    }
    mx = max(mx, tot[i]);
  }

  vector<int> ord(m);
  multiset<int> ms = {tot.begin(), tot.end()};
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&as](int i, int j) {
    return as[i] > as[j];
  });
  dbg(mx);
  for (int i = 0; i < n; ++i) {
    int cur = tot[i], cnt = 0;
    ms.erase(ms.find(tot[i]));
    for (int j = 0; j < m && !ms.empty() && cur <= *ms.rbegin(); ++j) {
      if (g[i][ord[j]] == 'o') continue;
      cur += as[ord[j]];
      ++cnt;
    }
    ms.emplace(tot[i]);
    cout << cnt << '\n';
  }
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
