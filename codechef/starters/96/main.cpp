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

  if (all_of(as.begin(), as.end(), [](auto x) { return x == 0; })) {
    cout << "YES\n";
    return;
  }

  if (n == 2) {
    cout << (as[0] == as[1] ? "YES" : "NO") << '\n';
    return;
  }

  set<pair<int, int>> ss;
  for (int i = 0; i < n; ++i) {
    if (as[i] > 0) {
      ss.emplace(as[i], i);
    }
  }
  while (!ss.empty()) {
    auto [val, pos] = *ss.rbegin(); ss.erase(prev(ss.end()));
    auto lhs = val / 2;
    auto rhs = val - lhs;
    vector<pair<int, int>> maybe;
    for (auto i : {(pos + 1) % n, (pos - 1 + n) % n}) {
      if (as[i] > 0) {
        maybe.emplace_back(as[i], i);
      }
    }
    if (maybe.empty()) {
      cout << "NO\n";
      return;
    }
    if (maybe.size() == 1) {
      if (val != maybe[0].first) {
        cout << "NO\n";
        return;
      }
      ss.erase(ss.find(maybe[0]));
      as[pos] = as[maybe[0].second] = 0;
    } else {
      sort(maybe.begin(), maybe.end());
      {
        auto mn = min(as[maybe[0].second], lhs);
        lhs -= mn;
        ss.erase(ss.find(maybe[0]));
        as[maybe[0].second] -= mn;
        ss.emplace(as[maybe[0].second], maybe[0].second);
        rhs += lhs;
      }
      {
        auto mn = min(as[maybe[1].second], rhs);
        rhs -= mn;
        dbg(maybe);
        ss.erase(ss.find(maybe[1]));
        as[maybe[1].second] -= mn;
        ss.emplace(as[maybe[1].second], maybe[1].second);
        if (rhs != 0) {
          cout << "NO\n";
          return;
        }
      }
    }
  }
  cout << "YES\n";
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
