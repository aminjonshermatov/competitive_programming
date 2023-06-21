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
  vector<i64> as(n);
  for (auto &a : as) cin >> a;
  sort(as.begin(), as.end(), [](i64 a, i64 b) {
    auto ca = __builtin_clzll(a);
    auto cb = __builtin_clzll(b);
    if (ca != cb) return ca < cb;
    return a > b;
  });
  dbg(as);
  multiset<i64> ms;
  for (auto a : as) {
    if (ms.empty() || a > *ms.rbegin()) {
      ms.emplace(a);
    } else {
      auto x = *ms.rbegin();
      assert(a <= x);
      ms.erase(ms.find(x));
      ms.emplace(x ^ a);
    }
  }
  cout << ms.size() << '\n';
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
