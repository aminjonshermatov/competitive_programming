#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int N = 10000;

void solve() {
  unordered_map<int, int> cache;
  auto d = [&](int a) -> int {
    if (cache.contains(a)) return cache.at(a);
    int sm = 1;
    for (int x = 2; x * x <= a; ++x) {
      auto [q, r] = div(a, x);
      if (r != 0) continue;
      sm += x + q;
      if (x == q) sm -= q;
    }
    return cache[a] = sm;
  };

  int sm = 0;
  for (int a = 2; a <= N; ++a) {
    if (d(a) != a && d(d(a)) == a) {
      sm += a;
    }
  }
  cout << sm << '\n';
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
