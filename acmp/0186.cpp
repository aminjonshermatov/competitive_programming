// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr auto inf = numeric_limits<int>::max();

void solve() {
  int n; cin >> n;
  vector<int> A(n);
  for (auto &a : A) cin >> a;
  sort(A.begin(), A.end());

  vector<int> cache(n, -1);
  auto dp = [&](auto &f, int i) -> int {
    if (i >= n) return 0;
    if (i + 1 == n) return inf;
    if (~cache[i]) return cache[i];
    int ans = inf;
    for (int j = i + 1; j < n; ++j) {
      ans = min(ans, max(A[j] - A[i], f(f, j + 1)));
    }
    return cache[i] = ans;
  };
  cout << dp(dp, 0) << '\n';
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
}