#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

struct Pt { int x, y; };

void solve() {
  int n; cin >> n;
  vector<Pt> pts(n);
  for (auto &[x, y] : pts) {
    cin >> x >> y;
  }

  using ld = long double;
  auto dist = [&](int i, int j) -> ld {
    auto dx = abs(pts[i].x - pts[j].x);
    auto dy = abs(pts[i].y - pts[j].y);
    return sqrt(dx * dx + dy * dy);
  };
  vector<vector<ld>> dp(n, vector<ld>(n + 1, 1e14));
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {

    }
  }
  cout << *min_element(dp.back().begin(), dp.back().end()) << '\n';
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
