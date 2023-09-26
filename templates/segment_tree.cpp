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

struct SegmentTree {
  int n;
  vector<int> tree;

  static inline constexpr auto neutral = numeric_limits<int>::min();

  explicit SegmentTree(int n_) : n(n_), tree(2 * n_, neutral) { }

  void set(int pos, int nval) {
    pos += n;
    tree[pos] = nval;
    while (pos > 1) {
      pos >>= 1;
      tree[pos] = max(tree[pos << 1], tree[pos << 1 | 1]);
    }
  }

  int query(int ql, int qr) {
    ql += n; qr += n;
    auto ans = neutral;
    while (ql < qr) {
      if (ql & 1) ans = max(ans, tree[ql++]);
      if (qr & 1) ans = max(ans, tree[--qr]);
      ql >>= 1;
      qr >>= 1;
    }
    return ans;
  }

};
