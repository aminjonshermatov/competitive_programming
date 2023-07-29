#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m; cin >> n >> m;
  vector<i64> pull, reg, opener;
  for (int i = 0; i < n; ++i) {
    char type;
    i64 x;
    cin >> type >> x;
    if (type == '0') {
      pull.emplace_back(x);
    } else if (type == '1') {
      reg.emplace_back(x);
    } else if (type == '2') {
      opener.emplace_back(x);
    }
  }

  sort(pull.rbegin(), pull.rend());
  sort(reg.rbegin(), reg.rend());
  sort(opener.rbegin(), opener.rend());

  dbg(opener);
  dbg(reg);

  i64 cur = 0;
  int j = -1;
  int i = -1;
  int cnt = 0;
  int given = 0, op = 0;
  while (given < m && i + 1 < reg.size()) {
    while (cnt + 1 > op && j + 1 < opener.size()) {
      op += opener[++j];
      ++given;
    }
    if (cnt + 1 > op) break;
    if (given < m && i + 1 < reg.size()) {
      dbg(cnt, op);
      cur += reg[++i];
      ++cnt;
      ++given;
    }
  }
  i64 ans = cur;
  dbg(i, j, cur, given, op);
  for (auto x : pull) {
    if (given >= m) {
      if (i >= 0) {
        cur -= reg[i--];
        --given;
      }
      while (j >= 0 && (i + 1) <= op - opener[j]) {
        op -= opener[j--];
        --given;
      }
      if (i < 0 && j >= 0) {
        --given;
      }
    }
    dbg(x, i, j, given, cur);
    if (given < m) {
      ++given;
      cur += x;
    }

    ans = max(ans, cur);
  }
  cout << ans << '\n';
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
