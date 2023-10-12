#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

const int NAX = 1e6 + 10;
int spf[NAX];

void solve() {
  int n;
  cin >> n;
  map<int, int> ds;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    while (x > 1) {
      ++ds[spf[x]];
      x /= spf[x];
    }
  }
  for (auto [_, c] : ds) {
    if (c % n != 0) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  memset(spf, -1, sizeof spf);
  spf[1] = 1;
  for (int i = 2; i < NAX; ++i) {
    if (spf[i] != -1) continue;
    for (int j = i; j < NAX; j += i) {
      spf[j] = i;
    }
  }

  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
