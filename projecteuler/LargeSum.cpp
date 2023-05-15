#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int N = 100;
constexpr int M = 50;
constexpr int LIM = 10;

void solve() {
  array<string, N> nums{};
  for (auto &d : nums) {
    cin >> d;
    reverse(d.begin(), d.end());
  }

  string res;
  for (int j = 0, rem = 0; j < M || rem > 0; ++j) {
    int cur = rem;
    if (j < M) {
      for (auto &d : nums) {
        cur += d[j] - '0';
      }
    }
    auto [q, r] = div(cur, 10);
    res.push_back(char('0' + r));
    rem = q;
  }
  reverse(res.begin(), res.end());
  for (int i = 0; i < LIM; ++i) {
    cout << res[i];
  }
  cout << '\n';
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
