#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = long long;

void solve() {
  int n, k; cin >> n >> k;
  vector<i64> A(n);
  for (auto &a : A) cin >> a;

  sort(A.begin(), A.end());
  auto s = accumulate(A.begin(), A.end(), i64(0));
  i64 r = 0;
  for (int i = 0; i < k; ++i) {
    r += A[n - i - 1];
  }
  i64 ans = s - r;
  for (i64 ls = 0, l = 0, i = 0; i < k; ++i) {
    r -= A[n - k + i];
    ls += A[l++] + A[l++];
    ans = max(ans, s - ls - r);
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
