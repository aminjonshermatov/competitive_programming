#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;
using ld = long double;

constexpr auto inf = numeric_limits<i64>::max();

void solve() {
  i64 n, m, k; cin >> n >> m >> k;
  vector<i64> A(n), B(m);
  for (auto &a : A) cin >> a;
  for (auto &b : B) cin >> b;

  auto sA = accumulate(A.begin(), A.end(), i64(0));
  auto sB = accumulate(B.begin(), B.end(), i64(0));
  i64 ans = inf;
  {
    auto curA = ld(sA) / n;
    auto curB = ld(sB) / m;
    int x = 0, y = 0;
    for (int _ = 0; _ < n + m + 2 && curA <= curB; ++_) {
      auto newA = ld(sA + k * (x + 1)) / (n + x + 1);
      auto newB = ld(sB + y + 1) / (m + y + 1);
      if (abs(newA - curB) > abs(curA - newB)) {
        ++x;
        curA = newA;
      } else {
        ++y;
        curB = newB;
      }
    }
    if (curA > curB) ans = x + y;
  }
  {
    auto curA = ld(sA) / n;
    auto curB = ld(sB) / m;
    int x = 0;
    for (; x < n + 1; ++x) {
      curA = ld(sA + k * x) / (n + x);
      if (curA > curB) break;
    }
    if (curA > curB) ans = min<i64>(ans, x);
  }
  {
    auto curA = ld(sA) / n;
    auto curB = ld(sB) / m;
    int y = 0;
    for (; y < m + 1; ++y) {
      curB = ld(sB + y) / (m + y);
      if (curA > curB) break;
    }
    if (curA > curB) ans = min<i64>(ans, y);
  }
  {
    for (i64 x = 1; x <= min<i64>(1000, n); ++x) {
      for (i64 y = 1; y <= min<i64>(1000, m); ++y) {
        auto newA = ld(sA + k * x) / (n + x);
        auto newB = ld(sB + y) / (m + y);
        if (newA > newB) {
          ans = min<i64>(ans, x + y);
        }
      }
    }
  }
  cout << (ans == inf ? -1 : ans) << '\n';
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
