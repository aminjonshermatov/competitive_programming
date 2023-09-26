#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

struct SegmentTree {
  int n, neutral;
  vector<int> tree;
  explicit SegmentTree(vector<int> &as) {
    n = 1;
    while (n < as.size()) n <<= 1;
    neutral = 1;
    while (neutral - 1 <= 1e9) neutral <<= 1;
    --neutral;
    tree.assign(2 * n - 1, neutral);
    const auto build = [&](auto &f, int x, int lx, int rx) -> void {
      if (rx - lx == 1) {
        if (lx < as.size()) {
          tree[x] = as[lx];
        }
        return;
      }
      auto mid = lx + (rx - lx) / 2;
      f(f, 2 * x + 1, lx, mid);
      f(f, 2 * x + 2, mid, rx);
      tree[x] = tree[2 * x + 1] & tree[2 * x + 2];
    };
    build(build, 0, 0, n);
  }
  int qry(int ql, int qr, int x, int lx, int rx) {
    if (ql >= rx || qr <= lx) return neutral;
    if (ql <= lx && rx <= qr) return tree[x];
    auto mid = lx + (rx - lx) / 2;
    return qry(ql, qr, 2 * x + 1, lx, mid) & qry(ql, qr, 2 * x + 2, mid, rx);
  }
  int qry(int l, int r) {
    return qry(l, r, 0, 0, n);
  }
};

void solve() {
  int n;
  cin >> n;
  vector<int> as(n);
  for (auto &a : as) {
    cin >> a;
  }
  auto sg = SegmentTree(as);
  int q;
  cin >> q;
  while (q--) {
    int l, k;
    cin >> l >> k;
    --l;
    if (as[l] < k) {
      cout << "-1 ";
      continue;
    }
    int lo = l + 1, hi = n + 1;
    while (hi - lo > 1) {
      auto mid = lo + (hi - lo) / 2;
      (sg.qry(l, mid) >= k ? lo : hi) = mid;
    }
    cout << lo << ' ';
  }
  cout << '\n';
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