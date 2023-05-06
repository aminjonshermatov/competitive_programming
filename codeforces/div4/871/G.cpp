// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

constexpr int N = 2023;
constexpr int MX = N * (N + 1) / 2;
array<i64, MX + 1> sm{};
array<int, MX + 1> level{};

int get_idx(int lev, int pos) {
  auto under = lev * (lev - 1) / 2;
  auto npos = under + pos;
  return npos > under + lev || npos <= under ? -1 : npos;
}

pair<int, int> get_under(int x) {
  auto under_cnt = level[x] * (level[x] - 1) / 2;
  auto idx = x - under_cnt;
  auto lhs = get_idx(level[x] - 1, idx - 1);
  auto rhs = get_idx(level[x] - 1, idx);
  return {lhs, rhs};
}

void prep() {
  for (int i = 1, lev = 1, lst = 1; i <= MX; ++i) {
    level[i] = lev;
    if (i == lst) {
      lst = lst + ++lev;
    }
  }
  sm[1] = 1;
  for (int x = 2; x <= MX; ++x) {
    sm[x] = 1ll * x * x;
    auto [l, r] = get_under(x);
    if (~l) sm[x] += sm[l];
    if (~r) sm[x] += sm[r];
    if (~l && ~r) {
      auto [_, lr] = get_under(l);
      auto [rl, __] = get_under(r);
      if (~lr) sm[x] -= sm[lr];
      else if (~rl) sm[x] -= sm[rl];
    }
  }
}

void solve() {
  int n; cin >> n;
  cout << sm[min(n, MX)] << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  prep();
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
