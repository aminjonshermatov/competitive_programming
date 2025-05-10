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
  int sum = 0;
  Node() = default;
  explicit Node(int x) : sum(x) { }
  Node(Node *a, Node *b) : lc(a), rc(b) {
    if (a != nullptr) {
      sum += a->sum;
    }
    if (b != nullptr) {
      sum += b->sum;
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
Node* Upd(int pos, int delta, Node *node, int lx, int rx) {
  if (rx - lx == 1) {
    return new Node(node->sum + delta);
  }
  const auto mid = std::midpoint(lx, rx);
  if (pos < mid) {
    return new Node(Upd(pos, delta, node->lc, lx, mid), node->rc);
  }
  return new Node(node->lc, Upd(pos, delta, node->rc, mid, rx));
}
int Qry(int ql, int qr, Node *lhs, Node *rhs, int lx, int rx) {
  if (ql >= rx || qr <= lx) {
    return 0;
  }
  if (ql <= lx && rx <= qr) {
    return rhs->sum - lhs->sum;
  }
  const auto mid = std::midpoint(lx, rx);
  return Qry(ql, qr, lhs->lc, rhs->lc, lx, mid) + Qry(ql, qr, lhs->rc, rhs->rc, mid, rx);
}

void Solve() {
  int n, m;
  Scan(n, m);
  std::vector<int> as(2 * m), bs(2 * m);
  for (int i = 0; i < m; ++i) {
    Scan(as[i], bs[i]);
    as[i + m] = bs[i];
    bs[i + m] = as[i];
  }
  std::vector ord(2 * m, 0);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](const int i, const int j) {
    return as[i] < as[j];
  });

  std::vector<Node*> nodes(2 * n + 1);
  nodes[0] = Build(0, 2 * n + 1);
  for (int i = 1, ptr = 0; i <= 2 * n; ++i) {
    nodes[i] = nodes[i - 1];
    if (ptr < 2 * m && as[ord[ptr]] == i) {
      nodes[i] = Upd(bs[ord[ptr]], +1, nodes[i], 0, 2 * n + 1);
      ++ptr;
    }
  }

  int q;
  Scan(q);
  while (q-- > 0) {
    int c, d;
    Scan(c, d);
    assert(c < d);
    Println(Qry(d, 2 * n + 1, nodes[c - 1], nodes[d], 0, 2 * n + 1) + Qry(1, c + 1, nodes[c - 1], nodes[d], 0, 2 * n + 1));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
