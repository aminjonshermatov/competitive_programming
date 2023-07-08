#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

struct SegmentTree {
  int n;
  vector<int> h, w, d;
  int neutral = numeric_limits<int>::max();
  explicit SegmentTree(int n_) {
    n = 1;
    while (n < n_) n <<= 1;
    h.assign(2 * n - 1, neutral);
    w.assign(2 * n - 1, neutral);
    d.assign(2 * n - 1, neutral);
  }
  void set(int pos, int h_, int w_, int d_, int x, int lx, int rx) {
    if (rx - lx == 1) {
      h[x] = h_;
      w[x] = w_;
      d[x] = d_;
      return;
    }
    auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      set(pos, h_, w_, d_, 2 * x + 1, lx, mid);
    } else {
      set(pos, h_, w_, d_, 2 * x + 2, mid, rx);
    }
    if (h[2 * x + 1] != h[2 * x + 2]) {
      if (h[2 * x + 1] < h[2 * x + 2]) {
        h[x] = h[2 * x + 1];
        w[x] = w[2 * x + 1];
        d[x] = d[2 * x + 1];
      } else {
        h[x] = h[2 * x + 2];
        w[x] = w[2 * x + 2];
        d[x] = d[2 * x + 2];
      }
    } else if (w[2 * x + 1] != w[2 * x + 2]) {
      if (w[2 * x + 1] < w[2 * x + 2]) {
        h[x] = h[2 * x + 1];
        w[x] = w[2 * x + 1];
        d[x] = d[2 * x + 1];
      } else {
        h[x] = h[2 * x + 2];
        w[x] = w[2 * x + 2];
        d[x] = d[2 * x + 2];
      }
    } else {
      if (d[2 * x + 1] < d[2 * x + 2]) {
        h[x] = h[2 * x + 1];
        w[x] = w[2 * x + 1];
        d[x] = d[2 * x + 1];
      } else {
        h[x] = h[2 * x + 2];
        w[x] = w[2 * x + 2];
        d[x] = d[2 * x + 2];
      }
    }
  }
  void set(int pos, int h_, int w_, int d_) {
    set(pos, h_, w_, d_, 0, 0, n);
  }
  int qry(int h_, int w_, int d_, int x, int lx, int rx) {
    if (h[x] >= h_ || w[x] >= w_ || d[x] >= d_) return -1;
    if (h[x] < h_ && w[x] < w_ && d[x] < d_) return 69;
    if (rx - lx == 1) return lx;
    auto mid = lx + (rx - lx) / 2;
    auto res = qry(h_, w_, d_, 2 * x + 1, lx, mid);
    if (res == -1) {
      res = qry(h_, w_, d_, 2 * x + 2, mid, rx);
    }
    return res;
  }
  int qry(int h_, int w_, int d_) {
    return qry(h_, w_, d_, 0, 0, n);
  }
};

void solve() {
  int n; cin >> n;
  bool ok = false;
  SegmentTree sg(n);
  for (int i = 0; i < n; ++i) {
    array<int, 3> x{};
    for (int j = 0; j < 3; ++j) {
      cin >> x[j];
    }
    sort(x.begin(), x.end());
    ok |= sg.qry(x[0], x[1], x[2]) != -1;
    dbg(x);
    if (ok) {
      dbg(i);
    }
    sg.set(i, x[0], x[1], x[2]);
  }

  cout << (ok ? "Yes" : "No") << '\n';
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
