#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> as(n, -1);
  vector<int> rest;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    if (i >= k || i + k < n) {
      rest.emplace_back(x);
    } else {
      as[i] = x;
    }
  }
  dbg(rest);
  sort(rest.begin(), rest.end());
  int i = 0;
  for (int j = 0; j < n; ++j) {
    if (as[j] == -1) {
      as[j] = rest[i++];
    }
  }
  for (auto a : as) {
    cout << a << ' ';
  }
  cout << '\n';
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
