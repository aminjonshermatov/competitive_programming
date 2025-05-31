#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

struct Node {
  Node *lc = nullptr, *rc = nullptr;
  int val = 0;
  Node() = default;
  explicit Node(int x) : val(x) { }
  Node(Node *a, Node *b) : lc(a), rc(b) {
    if (a != nullptr) {
      val = std::max(val, a->val);
    }
    if (b != nullptr) {
      val = std::max(val, b->val);
    }
  }
};

Node* Build(int lx, int rx) {
  if (rx - lx == 1) {
    return new Node;
  }
  const auto mid = std::midpoint(lx, rx);
  return new Node(Build(lx, mid), Build(mid, rx));
}
Node* Upd(int pos, int val, Node *node, int lx, int rx) {
  if (rx - lx == 1) {
    return new Node(val);
  }
  const auto mid = std::midpoint(lx, rx);
  if (pos < mid) {
    return new Node(Upd(pos, val, node->lc, lx, mid), node->rc);
  }
  return new Node(node->lc, Upd(pos, val, node->rc, mid, rx));
}
int Qry(int ql, int qr, Node *node, int lx, int rx) {
  if (ql >= rx || qr <= lx) {
    return 0;
  }
  if (ql <= lx && rx <= qr) {
    return node->val;
  }
  const auto mid = std::midpoint(lx, rx);
  return std::max(Qry(ql, qr, node->lc, lx, mid), Qry(ql, qr, node->rc, mid, rx));
}

void Solve() {
  int n, d, r;
  Scan(n, d, r);
  std::vector hs(n, 0);
  for (int i = 0; i < n; ++i) {
    Scan(hs[i]);
  }

  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return hs[i] > hs[j];
  });

  std::vector<Node*> nodes(n + 1);
  nodes[0] = Build(0, n);
  auto ret = 0;
  for (int i = 1; i <= n; ++i) {
    const auto best = Qry(std::max(ord[i - 1] - r, 0), std::min(n, ord[i - 1] + r + 1), nodes[std::max(0, i - d)], 0, n);
    nodes[i] = Upd(ord[i - 1], best + 1, nodes[i - 1], 0, n);
    ret = std::max(ret, Qry(0, n, nodes[i], 0, n));
  }
  assert(ret > 0);
  Println(ret - 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
