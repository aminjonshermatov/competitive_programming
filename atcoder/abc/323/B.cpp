#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<string> g(n);
  for (auto &r : g) {
    cin >> r;
  }
  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&g](int i, int j) {
    auto ca = count(g[i].begin(), g[i].end(), 'o');
    auto cb = count(g[j].begin(), g[j].end(), 'o');
    if (ca != cb) return ca > cb;
    return i < j;
  });
  for (auto id : ord) {
    cout << id + 1 << ' ';
  }
  cout << '\n';
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
