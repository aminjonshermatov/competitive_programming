#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m;
  cin >> n >> m;
  struct Event {
    i64 t, w, s;
  };
  vector<Event> es(m);
  for (auto &[t, w, s] : es) {
    cin >> t >> w >> s;
  }

  vector<i64> tot(n, 0);
  set<int> avail;
  for (int i = 0; i < n; ++i) {
    avail.emplace(i);
  }
  set<pair<i64, int>> in_future;
  for (auto [t, w, s] : es) {
    while (!in_future.empty() && in_future.begin()->first <= t) {
      assert(avail.count(in_future.begin()->second) == 0);
      avail.emplace(in_future.begin()->second);
      in_future.erase(in_future.begin());
    }

    if (avail.empty()) continue;
    auto id = *avail.begin();
    avail.erase(avail.begin());
    tot[id] += w;
    in_future.emplace(t + s, id);
  }
  for (int i = 0; i < n; ++i) {
    cout << tot[i] << ' ';
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
