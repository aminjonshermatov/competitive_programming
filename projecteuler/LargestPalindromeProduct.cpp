// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int LO = 100;
constexpr int HI = 999;

bool is_pal(int x) {
  int rev = 0;
  for (auto tmp = x; tmp > 0;) {
    auto [q, r] = div(tmp, 10);
    rev = rev * 10 + r;
    tmp = q;
  }
  return rev == x;
}

void solve() {
  int ans = 0;
  for (int a = LO; a <= HI; ++a) {
    for (int b = a; b <= HI; ++b) {
      auto mul = a * b;
      if (is_pal(mul) && ans < mul) {
        ans = mul;
      }
    }
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
