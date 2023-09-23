#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, x;
  cin >> n >> x;
  vector<int> as(n);
  for (int i = 0; i < n - 1; ++i) {
    cin >> as[i];
  }

  for (int y = 0; y <= 100; ++y) {
    vector<int> na = as;
    na[n - 1] = y;
    sort(na.begin(), na.end());
    int sm = 0;
    for (int i = 1; i + 1 < n; ++i) {
      sm += na[i];
    }
    if (sm >= x) {
      cout << y << '\n';
      return;
    }
  }
  cout << "-1\n";
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
