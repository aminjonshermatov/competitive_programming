#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  string s;
  cin >> s;

  vector<pair<char, int>> st;
  for (auto ch : s) {
    if (st.empty() || st.back().first != ch) {
      st.emplace_back(ch, 0);
    }
    ++st.back().second;
  }
  const auto n = int(st.size());
  array<vector<int>, 3> cache{};
  for (auto &r : cache) {
    r.assign(n, -1);
  }
  const auto dp = [&](auto &f, int id, char prv, int cnt) -> int {
    if (id >= n) return 0;
    if (~cache[prv - 'A'][id]) return cache[prv - 'A'][id];

    int loc = f(f, id + 1, st[id].first, st[id].second);
    if (prv == 'B' && st[id].first == 'A') {
      loc = max(loc, st[id].second + f(f, id + 1, 'B', 1));
    }
    if (prv == 'A' && st[id].first == 'B') {
      loc = max(loc, cnt + f(f, id + 1, 'C', 1));
      if (st[id].second > 1) {
        loc = max(loc, cnt + f(f, id + 1, 'B', st[id].second - 1));
      }
    }
    return cache[prv - 'A'][id] = loc;
  };
  cout << dp(dp, 0, 'C', 0) << '\n';
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
