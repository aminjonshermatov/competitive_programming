#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int64_t n, k; cin >> n >> k;
  vector<int64_t> A(n), pref;
  pref.reserve(n + 1);
  pref.emplace_back(0);
  for (int i = 0; i < n; ++i) {
    cin >> A[i];
    A[i] -= k;
    pref.emplace_back(pref.back() + A[i]);
  }

  auto ss = pref;
  sort(ss.begin(), ss.end());
  ss.erase(unique(ss.begin(), ss.end()), ss.end());
  const int nn(ss.size());
  vector<int64_t> ft(nn + 1, 0);
  auto add = [&](int pos) -> void {
    for (++pos; pos <= nn; pos += pos & -pos) {
      ++ft[pos];
    }
  };
  auto sum = [&](int pos) -> int {
    int64_t ans = 0;
    for (++pos; pos > 0; pos -= pos & -pos) {
      ans += ft[pos];
    }
    return ans;
  };

  int64_t ans = 0;
  dbg(pref);
  dbg(ss);
  for (int i = 0; i <= n; ++i) {
    auto pos = int(lower_bound(ss.begin(), ss.end(), pref[i]) - ss.begin());
    ans += sum(pos);
    add(pos);
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
