#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

struct SegmentTree {
    int n;
    vector<i64> tree;
    explicit SegmentTree(int n_) {
      n = 1;
      while (n < n_) n <<= 1;
      tree.assign(2 * n - 1, 1e9);
    }
    void upd(int pos, i64 v, int x, int l, int r) {
      if (r - l == 1) {
        tree[x] = min(tree[x], v);
        return;
      }
      auto mid = l + (r - l) / 2;
      if (pos < mid) {
        upd(pos, v, 2 * x + 1, l, mid);
      } else {
        upd(pos, v, 2 * x + 2, mid, r);
      }
      tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void upd(int pos, i64 v) {
      upd(pos, v, 0, 0, n);
    }
    i64 qry(int ql, int qr, int x, int l, int r) {
      if (ql >= r || qr <= l) return 1e9;
      if (ql <= l && r <= qr) return tree[x];
      auto mid = l + (r - l) / 2;
      return min(qry(ql, qr, 2 * x + 1, l, mid), qry(ql, qr, 2 * x + 2, mid, r));
    }
    int qry(int ql, int qr) {
      return qry(ql, qr, 0, 0, n);
    }
};

void solve() {
  int n;
  cin >> n;
  vector<int> as(n);
  for (auto &a : as) {
    cin >> a;
  }

  //vector<i64> dp(n + 1, 1e9);
  SegmentTree dp(n + 1);
  dp.upd(n, n);
  for (int i = n - 1; i >= 0; --i) {
    //i64 mn = 1e9;
    //for (int j = as[i] + i + 1; j <= n; ++j) {
    //  mn = min(mn, dp[j]);
    //}
    i64 mn = dp.qry(as[i] + i + 1, n + 1);
    //dbg(i, mn);
    dp.upd(i, mn - as[i] - 1);
    //dp[i] = min(dp[i], mn - as[i] - 1);
    //for (int k = 0; k + as[i] + i + 1 <= n; ++k) {
    //  dp[i] = min(dp[i], dp[as[i] + i + 1 + k] + k);
    //}
  }
  //for (int i = 0; i <= n; ++i) {
  //  cerr << dp.qry(i, i + 1) << ' ';
  //}
  //cerr << '\n';
  i64 ans = min(n, dp.qry(0, n + 1));
  //for (int i = 0; i < n; ++i) {
  //  ans = min(ans, dp[i]);
  //}
  cout << ans << '\n';
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
