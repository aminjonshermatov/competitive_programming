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
  string s;
  cin >> s;

  while (m-- > 0) {
    char cmd;
    cin >> cmd;
    if (cmd == '1') {
      int l, r, x;
      cin >> l >> r >> x;
      --l;

    } else if (cmd == '2') {
      int l, r;
      cin >> l >> r;
      --l;
    }
  }
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
