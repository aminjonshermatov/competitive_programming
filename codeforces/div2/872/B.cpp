// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

constexpr auto ninf = numeric_limits<i64>::min();

void solve() {
  int n, m; cin >> n >> m;
  vector<int> B(n * m);
  for (auto &b : B) cin >> b;
  sort(B.begin(), B.end());

  i64 ans = ninf;
  {
    i64 loc1 = 0;
    if (m > n) {
      loc1 += i64(n - 1) * (B[n*m - 1] - B[1]);
      loc1 += i64((m - 1) * n) * (B[n*m - 1] - B[0]);
    } else {
      loc1 += i64(m - 1) * (B[n*m - 1] - B[1]);
      loc1 += i64((n - 1) * m) * (B[n*m - 1] - B[0]);
    }
    ans = max(ans, loc1);
  }
  {
    i64 loc2 = 0;
    if (m > n) {
      loc2 += i64(n - 1) * (B[n*m - 2] - B[0]);
      loc2 += i64((m - 1) * n) * (B[n*m - 1] - B[0]);
    } else {
      loc2 += i64(m - 1) * (B[n*m - 2] - B[0]);
      loc2 += i64((n - 1) * m) * (B[n*m - 1] - B[0]);
    }
    ans = max(ans, loc2);
  }

  cout << ans << '\n';
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
