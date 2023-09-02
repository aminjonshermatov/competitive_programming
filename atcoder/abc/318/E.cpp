#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n;
  cin >> n;

  vector<int> as(n);
  map<int, i64> rhs{};
  for (auto &a : as) {
    cin >> a;
    ++rhs[a];
  }

  i64 ans = 0, cur = 0;
  map<int, i64> lhs{};
  for (int j = 0; j < n; ++j) {
    cur -= lhs[as[j]] * rhs[as[j]];
    ++lhs[as[j]];
    --rhs[as[j]];
    ans += cur;
    cur += lhs[as[j]] * rhs[as[j]];
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
