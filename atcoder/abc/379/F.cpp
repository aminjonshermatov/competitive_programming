#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <typename Node>
struct BottomUpSegmentTree {
  std::size_t n{};
  std::vector<Node> nodes;

  BottomUpSegmentTree() = default;

  explicit BottomUpSegmentTree(std::size_t n_) { init(std::vector(n_, Node())); }

  BottomUpSegmentTree(std::size_t n_, Node&& node) {
    init(std::vector(n_, std::forward<Node>(node)));
  }

  template <typename T>
  explicit BottomUpSegmentTree(const std::vector<T>& init_) { init(init_); }

  template <typename T>
  void init(const std::vector<T>& init_) {
    n = 1u << std::__lg(2 * init_.size() - 1);
    nodes.assign(2 * n, Node());
    for (std::size_t i{}; i < init_.size(); ++i) {
      nodes[i + n] = Node{init_[i]};
    }
    for (std::size_t i = n - 1; i >= 1u; --i) {
      nodes[i] = Node::unite(std::forward<Node>(nodes[i << 1]),
                             std::forward<Node>(nodes[i << 1 | 1]));
    }
  }

  void modify(std::size_t pos, Node&& val) {
    nodes[pos += n] = val;
    for (pos >>= 1; pos >= 1; pos >>= 1) {
      nodes[pos] = Node::unite(std::forward<Node>(nodes[pos << 1]),
                               std::forward<Node>(nodes[pos << 1 | 1]));
    }
  }

  Node query(std::size_t l, std::size_t r) {
    auto retL = Node(), retR = Node();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l % 2 == 1u) {
        retL = Node::unite(retL, nodes[l++]);
      }
      if (r % 2 == 1u) {
        retR = Node::unite(nodes[--r], retR);
      }
    }
    return Node::unite(std::forward<Node>(retL), std::forward<Node>(retR));
  }

  Node query(std::size_t pos) {
    return query(pos, pos + 1);
  }
};

constexpr auto inf = std::numeric_limits<int>::max() / 2;
struct NodeMin {
  int val = inf;
  static NodeMin unite(const NodeMin& a, const NodeMin& b) {
    return {std::min(a.val, b.val)};
  }
};
struct NodeMax {
  int val = 0;
  static NodeMax unite(const NodeMax& a, const NodeMax& b) {
    return {std::max(a.val, b.val)};
  }
};

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

Node* build(int lx, int rx) {
  if (rx - lx == 1) {
    return new Node;
  }
  const auto mid = lx + (rx - lx) / 2;
  return new Node(build(lx, mid), build(mid, rx));
}
Node* upd(int pos, int delta, Node *node, int lx, int rx) {
  if (rx - lx == 1) {
    return new Node(node->sum + delta);
  }
  const auto mid = lx + (rx - lx) / 2;
  if (pos < mid) {
    return new Node(upd(pos, delta, node->lc, lx, mid), node->rc);
  }
  return new Node(node->lc, upd(pos, delta, node->rc, mid, rx));
}
int qry(int ql, int qr, Node *node, int lx, int rx) {
  if (ql >= rx || qr <= lx) {
    return 0;
  }
  if (ql <= lx && rx <= qr) {
    return node->sum;
  }
  const auto mid = lx + (rx - lx) / 2;
  return qry(ql, qr, node->lc, lx, mid) + qry(ql, qr, node->rc, mid, rx);
}

void solve() {
  int n, q;
  scan(n, q);
  std::vector<int> hs(n);
  for (int i = 0; i < n; ++i) {
    scan(hs[i]);
  }
  int m;
  {
    auto nhs = hs;
    std::ranges::sort(nhs);
    nhs.erase(std::ranges::unique(nhs).begin(), nhs.end());
    m = static_cast<int>(nhs.size());
    for (int i = 0; i < n; ++i) {
      hs[i] = static_cast<int>(std::distance(nhs.begin(), std::ranges::lower_bound(nhs, hs[i])));
    }
  }
  auto empty = build(0, m);
  std::vector<Node*> nodes(n);
  BottomUpSegmentTree<NodeMin> stMin(m);
  for (int i = n - 1; i >= 0; --i) {
    const auto [j] = stMin.query(hs[i], m);
    nodes[i] = upd(hs[i], +1, j < n ? nodes[j] : empty, 0, m);
    stMin.modify(hs[i], {std::min(stMin.query(hs[i]).val, i)});
  }
  BottomUpSegmentTree<NodeMax> stMax(hs);
  while (q-- > 0) {
    int l, r;
    scan(l, r);
    --l, --r;

    const auto node = r + 1 < n ? nodes[r + 1] : empty;
    const auto [max] = stMax.query(l + 1, r + 1);
    println(qry(max, m, node, 0, m));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}