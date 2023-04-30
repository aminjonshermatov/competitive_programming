// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int N = 20;
constexpr array<int, 8> primes{
  2, 3, 5, 7, 11, 13, 17, 19
};

using i64 = ::int64_t;

i64 pow(int x, int p) {
  i64 ans = 1;
  while (p > 0) {
    if (p & 1) ans *= x;
    x *= x;
    p >>= 1;
  }
  return ans;
}

void solve() {
  map<int, int> divs;
  for (int i = 2; i <= N; ++i) {
    int x = i;
    for (auto p : primes) {
      int cnt = 0;
      while (x > 0 && x % p == 0) {
        ++cnt;
        x /= p;
      }
      divs[p] = max(divs[p], cnt);
    }
  }
  i64 ans = 1;
  for (auto [d, a] : divs) {
    ans *= pow(d, a);
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
