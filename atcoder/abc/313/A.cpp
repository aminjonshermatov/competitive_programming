#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> ps(n);
  for (auto &p : ps) cin >> p;
  auto mx = *max_element(ps.begin(), ps.end());
  cout << (mx == ps.front() && count(ps.begin(), ps.end(), mx) == 1 ? 0 : mx - ps.front() + 1) << '\n';
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
