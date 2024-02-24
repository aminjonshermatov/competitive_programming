#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> as(n);
  for (auto& a : as) {
    std::cin >> a;
  }
  int q;
  std::cin >> q;
  std::vector<std::tuple<int, int, int, int>> qs(q);
  for (auto& [t, l, r, x] : qs) {
    std::cin >> t >> l;
    if (t == 1) {
      std::cin >> r >> x;
    }
  }

  int m = 1;
  for (; m <= n; m *= 2) { }
  std::vector<std::multiset<int>> tree(2 * m - 1);
  auto upd = [&](auto& f, int ql, int qr, int t, int val, int x, int lx, int rx) -> void {
    if (ql >= rx || qr <= lx) return;
    if (ql <= lx && rx <= qr) {
      if (t == 1) {
        tree[x].emplace(val);
      } else {
        assert(tree[x].contains(val));
        tree[x].erase(tree[x].find(val));
      }
      return;
    }
    auto mid = lx + (rx - lx) / 2;
    f(f, ql, qr, t, val, 2 * x + 1, lx, mid);
    f(f, ql, qr, t, val, 2 * x + 2, mid, rx);
  };
  auto qry = [&](auto& f, int pos, int x, int lx, int rx) -> int {
    int ret = tree[x].empty() ? 0 : *tree[x].rbegin();
    if (rx - lx == 1) {
      return ret;
    }
    auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      return std::max(ret, f(f, pos, 2 * x + 1, lx, mid));
    }
    return std::max(ret, f(f, pos, 2 * x + 2, mid, rx));
  };
  for (int i = 0; i < n; ++i) {
    upd(upd, i, i + 1, 1, as[i], 0, 0, m);
  }
  for (auto [t, l, r, x] : qs) {
    if (t == 1) {
      upd(upd, l - 1, r, 1, x, 0, 0, m);
    } else if (t == 2) {
      auto q_id = l - 1;
      l = std::get<1>(qs[q_id]);
      r = std::get<2>(qs[q_id]);
      x = std::get<3>(qs[q_id]);
      upd(upd, l - 1, r, 2, x, 0, 0, m);
    } else {
      std::cout << qry(qry, l - 1, 0, 0, m) << '\n';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}