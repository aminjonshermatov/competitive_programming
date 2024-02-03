#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;
constexpr int N = 4e6 + 10;
std::vector<int> vals[N];
std::vector<i64> pf[N];

void add(int pos, int val, int x, int lx, int rx) {
  vals[x].emplace_back(val);
  if (rx - lx == 1) {
    return;
  }
  auto mid = lx + (rx - lx) / 2;
  if (pos < mid) {
    add(pos, val, 2 * x + 1, lx, mid);
  } else {
    add(pos, val, 2 * x + 2, mid, rx);
  }
}
i64 qry(int ql, int qr, int y, int x, int lx, int rx) {
  if (ql >= rx || qr <= lx) return 0;
  if (ql <= lx && rx <= qr) {
    if (vals[x].empty()) {
      return 0;
    }
    auto id = int(std::ranges::upper_bound(vals[x], y) - vals[x].begin());
    return id > 0 ? pf[x][id - 1] : 0;
  }
  auto mid = lx + (rx - lx) / 2;
  return qry(ql, qr, y, 2 * x + 1, lx, mid) + qry(ql, qr, y, 2 * x + 2, mid, rx);
}

void solve() {
  int n;
  std::cin >> n;
  int m = 1;
  for (; m < n; m *= 2) { }
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    add(i, x, 0, 0, m);
  }
  for (int i = 0; i < 2 * m - 1; ++i) {
    const auto sz = int(vals[i].size());
    std::ranges::sort(vals[i]);
    pf[i].resize(sz);
    for (int j = 0; j < sz; ++j) {
      pf[i][j] = (j > 0 ? pf[i][j - 1] : 0) + vals[i][j];
    }
  }
  i64 B = 0;
  int q;
  std::cin >> q;
  while (q-- > 0) {
    i64 a, b, c;
    std::cin >> a >> b >> c;
    auto l = a ^ B, r = b ^ B, x = c ^ B;
    std::cout << (B = qry(l - 1, r, x, 0, 0, m)) << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}