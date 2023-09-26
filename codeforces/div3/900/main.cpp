#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

template <typename Node>
struct SegmentTree {
  const Node NEUTRAL_ELEMENT = {};

  int size;
  vector<Node> tree;

  SegmentTree() = default;
  explicit SegmentTree(int n) {
    size = 1;
    while (size < n) size <<= 1;
    tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
    build(0, 0, size);
  }
  explicit SegmentTree(vector<int> &A) : SegmentTree(A.size()) {
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

  void build(vector<int> &A, int x, int lx, int rx) {
    if (rx - lx == 1) {
      if (lx < A.size()) tree[x] = {A[lx], Node::DEFAULT_LAZY, lx, false};
      return;
    }

    auto mid = lx + (rx - lx) / 2;
    build(A, 2 * x + 1, lx, mid);
    build(A, 2 * x + 2, mid, rx);
    pull(x);
  }

  void modify(int l, int r, int v, int x, int lx, int rx) {
    push(x, lx, rx);
    if (l >= rx || r <= lx) return;
    if (l <= lx && rx <= r) {
      tree[x].apply(lx, rx, v);
      return;
    }

    auto mid = lx + (rx - lx) / 2;
    modify(l, r, v, 2 * x + 1, lx, mid);
    modify(l, r, v, 2 * x + 2, mid, rx);
    pull(x);
  }

  void modify(int idx, int v) { modify(idx, idx + 1, v, 0, 0, size); }
  void modify(int l, int r, int v) { modify(l, r, v, 0, 0, size); }

  Node query(int l, int r, int x, int lx, int rx) {
    push(x, lx, rx);
    if (l >= rx || r <= lx) return NEUTRAL_ELEMENT;
    if (l <= lx && rx <= r) return tree[x];

    auto mid = lx + (rx - lx) / 2;
    auto res = Node::unite(query(l, r, 2 * x + 1, lx, mid),
                           query(l, r, 2 * x + 2, mid, rx));
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

struct NodeAnd {
  int val;
  int lazy;
  int right;
  bool has_lazy;

  static constexpr int DEFAULT_VALUE = 1073741823;
  static constexpr int DEFAULT_LAZY = 1073741823;

  NodeAnd(int val_, int lazy_, int right_, bool has_lazy_) : val(val_), lazy(lazy_), right(right_), has_lazy(has_lazy_) { }
  NodeAnd() : NodeAnd(DEFAULT_VALUE, DEFAULT_LAZY, -1, false) { }
  void apply([[maybe_unused]] int l, [[maybe_unused]] int r, int v) {
    val &= v;
    lazy &= v;
    has_lazy = true;
  }

  static NodeAnd unite(const NodeAnd &a, const NodeAnd &b) {
    return NodeAnd{
      a.val & b.val,
      DEFAULT_LAZY,
      b.right,
      false
    };
  }
};

struct NodeOr {
  int val;
  int lazy;
  int right;
  bool has_lazy;

  static constexpr int DEFAULT_VALUE = 0;
  static constexpr int DEFAULT_LAZY = 0;

  NodeOr(int val_, int lazy_, int right_, bool has_lazy_) : val(val_), lazy(lazy_), right(right_), has_lazy(has_lazy_) { }
  NodeOr() : NodeOr(DEFAULT_VALUE, DEFAULT_LAZY, -1, false) { }
  void apply([[maybe_unused]] int l, [[maybe_unused]] int r, int v) {
    val |= v;
    lazy |= v;
    has_lazy = true;
  }

  static NodeOr unite(const NodeOr &a, const NodeOr &b) {
    return NodeOr{
            a.val | b.val,
            DEFAULT_LAZY,
            b.right,
            false
    };
  }
};

template<typename T = ::int32_t> struct Hld {
  vector<int> parent, root, depth, treePos, heavy;
  SegmentTree<NodeAnd> treeAnd;
  SegmentTree<NodeOr> treeOr;

  template<typename G> explicit Hld(const G &g) {
    const int n(g.size());
    parent.assign(n, -1);
    root.assign(n, -1);
    treePos.assign(n, -1);
    heavy.assign(n, -1);
    depth.resize(n);
    depth[0] = 0;
    dfs(g, 0);

    for (int u = 0, currentPos = 0; u < n; ++u) {
      if (parent[u] == -1 || heavy[parent[u]] != u) {
        for (int v = u; ~v; v = heavy[v]) {
          root[v] = u;
          treePos[v] = currentPos++;
        }
      }
    }
    treeAnd.init(n);
    treeOr.init(n);
  }

  template<typename G> int dfs(const G &g, int v) {
    int size = 1, maxSubtree = 0;
    for (auto u : g[v]) if (u != parent[v]) {
        parent[u] = v;
        depth[u] = depth[v] + 1;
        auto subtree = dfs(g, u);
        if (subtree > maxSubtree) {
          heavy[v] = u;
          maxSubtree = subtree;
        }
        size += subtree;
      }
    return size;
  }

  template<typename BinaryOP> void processPath(int u, int v, BinaryOP op) {
    for (; root[u] != root[v]; v = parent[root[v]]) {
      if (depth[root[u]] > depth[root[v]]) swap(u, v); // u closer to lca rather than v
      op(treePos[root[v]], treePos[v] + 1);
    }
    if (depth[u] > depth[v]) swap(u, v);
    op(treePos[u], treePos[v] + 1);
  }

  void modify(int v, const T &val) {
    modify(v, v, val);
  }
  void modify(int u, int v, const T &val) { // [u, v]
    processPath(u, v, [this, &val](int l, int r) { // [l, r)
      treeAnd.modify(l, r, val);
      treeOr.modify(l, r, val);
    });
  }

  T query(int u, int v) { // [u, v]
    int _and = NodeAnd::DEFAULT_VALUE;
    int _or = NodeOr::DEFAULT_VALUE;
    processPath(u, v, [this, &_and, &_or](int l, int r) { // [l, r)
      _and &= treeAnd.query(l, r);
      _or |= treeOr.query(l, r);
    });
    // dbg(u, v, _and, _or);
    return _and + _or;
  }
};

void solve() {
  int n;
  cin >> n;
  vector<int> as(n);
  for (auto &a : as) {
    cin >> a;
  }

  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  Hld hld(g);
  for (int v = 0; v < n; ++v) {
    hld.modify(v, as[v]);
  }

  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    cout << hld.query(x, y) << ' ';
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
