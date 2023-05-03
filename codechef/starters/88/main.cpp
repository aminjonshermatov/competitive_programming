// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

i64 f(i64 p, i64 q, i64 r) {
  return (r | p) - (q & p);
}

i64 slow(i64 a, i64 b, i64 c) {
  map<i64, i64> cnt{};
  for (i64 x = 0; x < (1ll << c); ++x) {
    ++cnt[f(x, a, b)];
  }
  cout << "val_s: " << prev(cnt.end())->first << '\n';
  return prev(cnt.end())->second;
}

i64 fast(i64 a, i64 b, i64 c) {
  if (c == 0) return 1;

  i64 need = 0;
  for (i64 bit = c - 1; bit >= 0; --bit) {
    if (((b >> bit) & 1) >= ((a >> bit) & 1)) {
      need |= 1ll << bit;
    }
  }
  i64 tot = a == b;
  for (i64 bit = c; bit > 0; --bit) {
    if (((b >> bit) & 1) != ((a >> bit) & 1)) {
      ++tot;
    }
  }
  cout << "val_f: " << need << '\n';
  return 1ll << (c - tot);
}

random_device rd{};
mt19937 rnd(rd());
const int nax = 10;
uniform_int_distribution<i64> distC(0, nax), distO(0, 1ll << nax);

void check() {
  auto c = distC(rnd);
  auto a = distO(rnd) & ((1ll << c) - 1);
  auto b = distO(rnd) & ((1ll << c) - 1);
  auto f = fast(a, b, c);
  auto s = slow(a, b, c);
  if (f != s) {
    cout << a << ' ' << b << ' ' << c << ' ' << f << ' ' << s << '\n';
  }
}

bool test = 1;

void solve() {
  if (test) {
    const int N = 10;
    for (int i = 0; i < N; ++i) {
      check();
    }
  } else {
    i64 a, b, c;
    cin >> a >> b >> c;
    cout << fast(a, b, c) << '\n';
    return ;
    auto f = fast(a, b, c);
    auto s = slow(a, b, c);
    cout << f << ' ' << s << '\n';
  }
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
