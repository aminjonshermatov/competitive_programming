#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

struct Node {
  int sum;
  Node *left, *right;
  explicit Node(int x) : sum(x), left(nullptr), right(nullptr) { }
  Node(Node *a, Node *b) : sum(0), left(a), right(b) {
    if (a != nullptr) {
      sum += a->sum;
    }
    if (b != nullptr) {
      sum += b->sum;
    }
  }
};
Node* build(int lx, int rx) {
  if (rx - lx == 1) {
    return new Node(0);
  }
  auto mid = lx + (rx - lx) / 2;
  return new Node(build(lx, mid), build(mid, rx));
}
Node* upd(int pos, int val, Node *node, int lx, int rx) {
  if (rx - lx == 1) {
    return new Node(node->sum + val);
  }
  auto mid = lx + (rx - lx) / 2;
  if (pos < mid) {
    return new Node(upd(pos, val, node->left, lx, mid), node->right);
  } else {
    return new Node(node->left, upd(pos, val, node->right, mid, rx));
  }
}
int qry(int ql, int qr, Node *a, Node *b, int lx, int rx) {
  if (ql >= rx || qr <= lx) return 0;
  if (ql <= lx && rx <= qr) return b->sum - a->sum;
  auto mid = lx + (rx - lx) / 2;
  return qry(ql, qr, a->left, b->left, lx, mid) + qry(ql, qr, a->right, b->right, mid, rx);
}

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> as[i] >> bs[i];
    if (as[i] > bs[i]) {
      std::swap(as[i], bs[i]);
    }
  }

  std::vector<Node*> roots(2 * n + 1);
  roots[0] = build(0, 2 * n + 1);
  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return as[i] < as[j];
  });
  for (int i = 1, ptr = 0; i <= 2 * n; ++i) {
    if (ptr < n && as[ord[ptr]] == i) {
      roots[i] = upd(bs[ord[ptr++]], 1, roots[i - 1], 0, 2 * n + 1);
    } else {
      roots[i] = roots[i - 1];
    }
  }
  for (auto i : ord) {
    auto cnt = qry(bs[i] + 1, 2 * n + 1, roots[as[i] - 1], roots[bs[i]], 0, 2 * n + 1);
    if (cnt > 0) {
      std::cout << "Yes\n";
      return;
    }
  }
  std::cout << "No\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}