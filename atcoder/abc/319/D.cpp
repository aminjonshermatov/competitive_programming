#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> ls(n);
  for (auto &l : ls) {
    cin >> l;
  }
  dbg(ls);

  const auto ok = [&](i64 w) -> bool {
    if (ls[0] > w) return false;
    i64 cur = ls[0];
    int cnt = 1;
    int lines = 1;
    dbg("init", w);
    for (int i = 1; i < n; ++i) {
      if (ls[i] > w) return false;
      if (cur + cnt + ls[i] <= w) {
        cur += ls[i];
        ++cnt;
      } else {
        dbg(i);
        ++lines;
        cur = ls[i];
        cnt = 1;
      }
    }
    dbg("done", w, lines);
    return lines <= m;
  };

  i64 l = 0, r = accumulate(ls.begin(), ls.end(), i64(0)) + n - 1;
  while (r - l > 1) {
    auto w = l + (r - l) / 2;
    (ok(w) ? r : l) = w;
  }
  cout << r << '\n';
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
