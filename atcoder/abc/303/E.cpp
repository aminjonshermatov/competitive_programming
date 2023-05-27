#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

constexpr auto inf = numeric_limits<i64>::max();

void solve() {
  int n; cin >> n;
  vector<int> deg(n, 0);
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    ++deg[u]; ++deg[v];
  }

  vector<int> id(n);
  iota(id.begin(), id.end(), 0);
  sort(id.begin(), id.end(), [&deg](int u, int v) {
    return deg[u] > deg[v];
  });
  i64 cur = 0;
  vector<i64> ans;
  for (int i = 0; i < n && (cur + ans.size()) < n; ++i) {
    cur += deg[id[i]];
    ans.emplace_back(deg[id[i]]);
  }
  dbg(ans, cur);
  assert((cur + ans.size()) == n);
  sort(ans.begin(), ans.end());
  for (auto l : ans) {
    cout << l << ' ';
  }
  cout << '\n';
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
