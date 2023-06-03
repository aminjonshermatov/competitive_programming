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
  int n; cin >> n;
  vector<int> as(n);
  for (auto &a : as) cin >> a;
  auto aa = as;
  sort(aa.begin(), aa.end());
  aa.erase(unique(aa.begin(), aa.end()), aa.end());

  const int nn = int(aa.size());
  vector<i64> ft1(nn + 1, 0), ft2(nn + 1, 0);
  auto upd = [&](vector<i64> &ft, int pos, i64 val) -> void {
    for (int i = pos; i <= nn; i += i & -i) {
      ft[i] += val;
    }
  };
  auto qry = [&](vector<i64> &ft, int pos) -> i64 {
    i64 ans = 0;
    for (int i = pos; i > 0; i -= i & -i) {
      ans += ft[i];
    }
    return ans;
  };

  i64 ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    auto pos = int(lower_bound(aa.begin(), aa.end(), as[i]) - aa.begin()) + 1;
    ans += qry(ft2, pos - 1);
    upd(ft1, pos, 1);
    upd(ft2, pos, qry(ft1, pos - 1));
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
