#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

struct Node {
  Node *l, *r;
  i64 sum = 0;
  int cnt = 0;
  Node() : sum(0), cnt(0), l(nullptr), r(nullptr) { }
  explicit Node(i64 x) : sum(x), cnt(1), l(nullptr), r(nullptr) { }
  Node(Node *a, Node *b) : sum(0), cnt(0), l(a), r(b) {
    if (a != nullptr) {
      sum += a->sum;
      cnt += a->cnt;
    }
    if (b != nullptr) {
      sum += b->sum;
      cnt += b->cnt;
    }
  }
};
Node* build(int lx, int rx) {
  if (rx - lx == 1) {
    return new Node;
  }
  const auto mid = lx + (rx - lx) / 2;
  return new Node(build(lx, mid), build(mid, rx));
}
Node* upd(int pos, i64 delta, Node *node, int lx, int rx) {
  if (rx - lx == 1) {
    return new Node(node->sum + delta);
  }
  const auto mid = lx + (rx - lx) / 2;
  if (pos < mid) {
    return new Node(upd(pos, delta, node->l, lx, mid), node->r);
  }
  return new Node(node->l, upd(pos, delta, node->r, mid, rx));
}
i64 sum_kmax(int k, Node *node, int lx, int rx) {
  assert(k <= node->cnt);
  if (rx - lx == 1) {
    return node->sum;
  }
  const auto mid = lx + (rx - lx) / 2;
  if (node->r->cnt >= k) {
    return sum_kmax(k, node->r, mid, rx);
  }
  return node->r->sum + sum_kmax(k - node->r->cnt, node->l, lx, mid);
}

inline decltype(auto) monotone_maxima(int h, int w, auto&& f) {
  using T = decltype(f(0, 0));
  std::vector<T> ret(h);
  auto dnq = [&](auto&& self, int l, int r, int opt_l, int opt_r) -> void {
    const auto mid = l + (r - l) / 2;
    auto best_col = opt_l;
    auto best_val = -std::numeric_limits<T>::max() / 2; // maximization
    for (int col = opt_l; col < opt_r; ++col) {
      if (const std::integral auto val = f(mid, col); val > best_val) { // maximization
        best_col = col;
        best_val = val;
      }
    }
    ret[mid] = best_val;
    if (l < mid) {
      self(self, l, mid, opt_l, best_col + 1);
    }
    if (mid + 1 < r) {
      self(self, mid + 1, r, best_col, opt_r);
    }
  };
  dnq(dnq, 0, h, 0, w);
  return ret;
}

void solve() {
  int n;
  std::cin >> n;
  std::vector<i64> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> as[i] >> bs[i];
  }
  std::vector<int> as_ord(n);
  std::iota(as_ord.begin(), as_ord.end(), 0);
  std::ranges::sort(as_ord, [&](int i, int j) {
    return as[i] < as[j];
  });
  std::vector<int> at(n);
  for (int i = 0; i < n; ++i) {
    at[as_ord[i]] = i;
  }

  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return bs[i] == bs[j] ? as[i] > as[j] : bs[i] < bs[j];
  });

  std::vector<Node*> nodes(n + 1);
  nodes[0] = build(0, n);
  for (int i = 0; i < n; ++i) {
    nodes[i + 1] = upd(at[ord[i]], as[ord[i]], nodes[i], 0, n);
  }

  constexpr auto inf = std::numeric_limits<i64>::max() / 2;
  auto dp = monotone_maxima(n, n, [&](int i, int j) {
    return i > j ? -inf : (sum_kmax(i + 1, nodes[j + 1], 0, n) - bs[ord[j]]);
  });
  for (int i = 0; i < n; ++i) {
    std::cout << dp[i] << " \n"[i + 1 == n];
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}