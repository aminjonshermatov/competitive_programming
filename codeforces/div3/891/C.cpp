#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  map<int, int> cnt{};
  for (int i = 0; i < n * (n - 1) / 2; ++i) {
    int x; cin >> x;
    ++cnt[x];
  }

  vector<pair<int, int>> bs;
  bs.reserve(cnt.size());
  for (auto [k, v] : cnt) {
    bs.emplace_back(v, k);
  }
  sort(bs.begin(), bs.end(), [](const auto &lhs, const auto &rhs) {
    if (lhs.second == rhs.second) {
      return lhs.first > rhs.first;
    }
    return lhs.second < rhs.second;
  });
  int j = 0;
  vector<int> ans(n);
  ans[n - 1] = 1e9;
  for (int i = 0; i + 1 < n; ++i) {
    auto x = n - i - 1;
    assert(bs[j].first >= x);
    bs[j].first -= x;
    ans[i] = bs[j].second;
    if (bs[j].first == 0) ++j;
  }
  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << '\n';
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
