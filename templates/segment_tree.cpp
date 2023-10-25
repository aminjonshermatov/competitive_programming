//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

using namespace std;

template <typename Node>
struct SegmentTree {
  const Node NEUTRAL_ELEMENT{};

  int size;
  vector<Node> tree;

  SegmentTree() = default;
  explicit SegmentTree(int n) {
    size = 1;
    while (size < n) size <<= 1;
    tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
    build(0, 0, size);
  }
  explicit SegmentTree(vector<typename Node::value_type> &A) {
    size = 1;
    while (size < A.size()) size <<= 1;
    tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
    build(A, 0, 0, size);
  }

  void init(int n) {
    size = 1;
    while (size < n) size <<= 1;
    tree.resize(2 * size - 1);
    build(0, 0, size);
  }

  inline void push(int x, int lx, int rx) {
    if (rx - lx == 1 || !tree[x].has_lazy) return;

    auto mid = lx + (rx - lx) / 2;
    tree[2 * x + 1].apply(lx, mid, tree[x].lazy);
    tree[2 * x + 2].apply(mid, rx, tree[x].lazy);
    tree[x].lazy = Node::DEFAULT_LAZY;
    tree[x].has_lazy = false;
  }

  inline void pull(int x) {
    tree[x] = Node::unite(tree[2 * x + 1], tree[2 * x + 2]);
  }

  void build(int x, int lx, int rx) {
    if (rx - lx == 1) {
      tree[x] = {Node::DEFAULT_VALUE, Node::DEFAULT_LAZY, lx, false};
      return;
    }

    auto mid = lx + (rx - lx) / 2;
    build(2 * x + 1, lx, mid);
    build(2 * x + 2, mid, rx);
    pull(x);
  }

  void build(vector<typename Node::value_type> &A, int x, int lx, int rx) {
    if (rx - lx == 1) {
      if (lx < A.size()) {
        tree[x] = {A[lx], Node::DEFAULT_LAZY, lx, false};
      }
      return;
    }

    auto mid = lx + (rx - lx) / 2;
    build(A, 2 * x + 1, lx, mid);
    build(A, 2 * x + 2, mid, rx);
    pull(x);
  }

  void modify(int ql, int qr, typename Node::value_type v, int x, int lx, int rx) {
    push(x, lx, rx);
    if (ql >= rx || qr <= lx) return;
    if (ql <= lx && rx <= qr) {
      tree[x].apply(lx, rx, v);
      return;
    }

    auto mid = lx + (rx - lx) / 2;
    modify(ql, qr, v, 2 * x + 1, lx, mid);
    modify(ql, qr, v, 2 * x + 2, mid, rx);
    pull(x);
  }

  inline void modify(int idx, typename Node::value_type v) { modify(idx, idx + 1, v, 0, 0, size); }
  inline void modify(int l, int r, typename Node::value_type v) { modify(l, r, v, 0, 0, size); }

  Node query(int ql, int qr, typename Node::value_type x, int lx, int rx) {
    push(x, lx, rx);
    if (ql >= rx || qr <= lx) return NEUTRAL_ELEMENT;
    if (ql <= lx && rx <= qr) return tree[x];

    auto mid = lx + (rx - lx) / 2;
    auto res = Node::unite(query(ql, qr, 2 * x + 1, lx, mid),
                           query(ql, qr, 2 * x + 2, mid, rx));
    pull(x);
    return res;
  }

  int query(int l, int r) { return query(l, r, 0, 0, size).val; }
  int query(int idx) { return query(idx, idx + 1, 0, 0, size).val; }

  friend ostream& operator<<(ostream &out, const SegmentTree &st) {
    for (auto i = 1u, j = 0u; j < st.tree.size(); i <<= 1) {
      auto c = 0u;
      while (c++ < i) out << st.tree[j].val << ',' << st.tree[j++].lazy << ' ';
      out << '\n';
    }
    return out;
  }
};

struct NodeSetOperationSumQuery {
  using value_type = int;

  value_type val;
  value_type lazy;
  int right;
  bool has_lazy;

  static constexpr auto DEFAULT_VALUE = value_type(0);
  static constexpr auto DEFAULT_LAZY = value_type(0);

  NodeSetOperationSumQuery(value_type val_,
                  value_type lazy_,
                  int right_,
                  bool has_lazy_)
      : val(val_)
      , lazy(lazy_)
      , right(right_)
      , has_lazy(has_lazy_) { }
  NodeSetOperationSumQuery() : NodeSetOperationSumQuery(DEFAULT_VALUE, DEFAULT_LAZY, -1, false) { }
  void apply(int l, int r, value_type v) {
    val = v * (r - l);
    lazy += v;
    has_lazy = true;
  }

  static NodeSetOperationSumQuery unite(const NodeSetOperationSumQuery &a, const NodeSetOperationSumQuery &b) {
    return NodeSetOperationSumQuery{
            a.val + b.val,
            DEFAULT_LAZY,
            b.right,
            false
    };
  }
};

template <typename Node> struct SegmentTree {
  int n;
  std::vector<Node> nodes;

  explicit SegmentTree(int n_) {
    for (n = 1; n < n_; n <<= 1) { }
    nodes.assign(2 * n - 1, Node());
  }
  void modify(int pos, Node node, int x, int lx, int rx) {
    if (rx - lx == 1) {
      nodes[x] = node;
      return;
    }
    auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      modify(pos, node, 2 * x + 1, lx, mid);
    } else {
      modify(pos, node, 2 * x + 2, mid, rx);
    }
    nodes[x] = Node::unite(nodes[2 * x + 1], nodes[2 * x + 2]);
  }
  void modify(int pos, Node node) {
    modify(pos, node, 0, 0, n);
  }
  Node query(int ql, int qr, int x, int lx, int rx) {
    if (ql >= rx || qr <= lx) return Node();
    if (ql <= lx && rx <= qr) return nodes[x];
    auto mid = lx + (rx - lx) / 2;
    return Node::unite(query(ql, qr, 2 * x + 1, lx, mid), query(ql, qr, 2 * x + 2, mid, rx));
  }
  Node query(int ql, int qr) {
    return query(ql, qr, 0, 0, n);
  }
  template<typename F> int findFirst(int ql, int qr, F pred, int x, int lx, int rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return -1;
    }
    if (rx - lx == 1) {
      return lx;
    }
    auto mid = lx + (rx - lx) / 2;
    auto res = findFirst(ql, qr, pred, 2 * x + 1, lx, mid);
    if (res == -1) {
      res = findFirst(ql, qr, pred, 2 * x + 2, mid, rx);
    }
    return res;
  }
  template<typename F> int findFirst(int ql, int qr, F pred) {
    return findFirst(ql, qr, pred, 0, 0, n);
  }
  template<typename F> int findLast(int ql, int qr, F pred, int x, int lx, int rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return -1;
    }
    if (rx - lx == 1) {
      return lx;
    }
    auto mid = lx + (rx - lx) / 2;
    auto res = findLast(ql, qr, pred, 2 * x + 2, mid, rx);
    if (res == -1) {
      res = findLast(ql, qr, pred, 2 * x + 1, lx, mid);
    }
    return res;
  }
  template<typename F> int findLast(int ql, int qr, F pred) {
    return findLast(ql, qr, pred, 0, 0, n);
  }
};

// bottom-up segment tree
template <typename Node> struct SegmentTree {
  int n;
  std::vector<Node> nodes;

  explicit SegmentTree(int n_) : n(n_), tree(2 * n_, Node()) { }

  void modify(int pos, Node val) {
    pos += n;
    nodes[pos] = val;
    while (pos > 1) {
      pos >>= 1;
      nodes[pos] = Node::unite(nodes[pos << 1], nodes[pos << 1 | 1]);
    }
  }

  Node query(int ql, int qr) {
    ql += n; qr += n;
    auto ans = Node();
    while (ql < qr) {
      if (ql & 1) ans = Node::unite(ans, nodes[ql++]);
      if (qr & 1) ans = Node::unite(ans, nodes[--qr]);
      ql >>= 1;
      qr >>= 1;
    }
    return ans;
  }
};

struct Node {
  int64_t val = 0;
  static Node unite(Node a, Node b) {
    return Node{a.val + b.val};
  }
};
