#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

struct Point {
  i64 x, y, w;
  Point(i64 x, i64 y, i64 w) : x(x), y(y), w(w) { }
  Point() : Point(0, 0, 0) { }
};

void solve() {
  int n; cin >> n;
  vector<Point> pts(n);
  vector<int> xs, ys;
  for (auto &[x, y, w] : pts) {
    cin >> x >> y >> w;
    xs.emplace_back(x);
    ys.emplace_back(y);
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());

  const int nx = int(xs.size());
  const int ny = int(ys.size());
  vector<vector<i64>> ft(nx + 1, vector<i64>(ny + 1, 0));
  auto upd = [&](int x, int y, i64 val) -> void {
    for (int i = x; i <= nx; i += i & -i) {
      for (int j = y; j <= ny; j += j & -j) {
        ft[i][j] += val;
      }
    }
  };
  auto qry = [&](int x, int y) -> i64 {
    i64 ans = 0;
    for (int i = x; i > 0; i -= i & -i) {
      for (int j = y; j > 0; j -= j & -j) {
        ans += ft[i][j];
      }
    }
    return ans;
  };

  auto comp = [&](int x, int y) -> pair<int, int> {
    auto ix = int(lower_bound(xs.begin(), xs.end(), x) - xs.begin()) + 1;
    ix = min(ix, nx);
    if (xs[ix - 1] > x) --ix;
    auto iy = int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1;
    iy = min(iy, ny);
    if (ys[iy - 1] > y) --iy;
    return {ix, iy};
  };

  for (auto [x, y, w] : pts) {
    auto [ix, iy] = comp(x, y);
    upd(ix, iy, w);
  }

  int q; cin >> q;
  while (q--) {
    string cmd; cin >> cmd;
    if (cmd.front() == 'g') {
      int rx, ry; cin >> rx >> ry;
      auto [x, y] = comp(rx, ry);
      cout << qry(x, y) << '\n';
    } else if (cmd.front() == 'c') {
      int i, z; cin >> i >> z;
      --i;
      auto [x, y, w] = pts[i];
      auto [ix, iy] = comp(x, y);
      upd(ix, iy, -w);
      upd(ix, iy, z);
      pts[i].w = z;
    } else {
      assert(false);
    }
  }
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
