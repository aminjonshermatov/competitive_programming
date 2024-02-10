#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

template <typename Node, typename Tag>
struct LazySegmentTree {
  int n = 0;
  std::vector<Node> nodes;
  std::vector<Tag> tags;

  explicit LazySegmentTree(int n_) { init(std::vector(n_, Node())); }
  LazySegmentTree(int n_, Node node) { init(std::vector(n_, node)); }
  template <typename T> explicit LazySegmentTree(std::vector<T> init_) { init(init_); }

  template <typename T> void init(std::vector<T> init_) {
    for (n = 1; n < init_.size(); n <<= 1) { }
    nodes.assign(2 * n - 1, Node());
    tags.assign(2 * n - 1, Tag());
    auto build = [&](auto &f, int x, int lx, int rx) -> void {
      if (rx - lx == 1) {
        if (lx < init_.size()) {
          nodes[x] = Node{init_[lx]};
        }
        return;
      }
      auto mid = lx + (rx - lx) / 2;
      f(f, 2 * x + 1, lx, mid);
      f(f, 2 * x + 2, mid, rx);
      nodes[x] = Node::unite(nodes[2 * x + 1], nodes[2 * x + 2]);
    };
    build(build, 0, 0, n);
  }

  inline void apply(int x, const Tag &tag) {
    nodes[x].apply(tag);
    tags[x].apply(tag);
  }
  inline void push(int x) {
    apply(2 * x + 1, tags[x]);
    apply(2 * x + 2, tags[x]);
    tags[x] = Tag();
  }
  inline void pull(int x) {
    nodes[x] = Node::unite(nodes[2 * x + 1], nodes[2 * x + 2]);
  }

  void modify(int pos, Node node, int x, int lx, int rx) {
    if (rx - lx == 1) {
      nodes[x] = node;
      return;
    }
    push(x);
    auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      modify(pos, node, 2 * x + 1, lx, mid);
    } else {
      modify(pos, node, 2 * x + 2, mid, rx);
    }
    pull(x);
  }
  void modify(int pos, Node node) {
    modify(pos, node, 0, 0, n);
  }
  void modify(int ql, int qr, Tag tag, int x, int lx, int rx) {
    if (ql >= rx || qr <= lx) return;
    if (ql <= lx && rx <= qr) {
      apply(x, tag);
      return;
    }
    push(x);
    auto mid = lx + (rx - lx) / 2;
    modify(ql, qr, tag, 2 * x + 1, lx, mid);
    modify(ql, qr, tag, 2 * x + 2, mid, rx);
    pull(x);
  }
  void modify(int ql, int qr, Tag tag) {
    modify(ql, qr, tag, 0, 0, n);
  }
  Node query(int ql, int qr, int x, int lx, int rx) {
    if (ql >= rx || qr <= lx) return Node();
    if (ql <= lx && rx <= qr) return nodes[x];
    push(x);
    auto mid = lx + (rx - lx) / 2;
    return Node::unite(query(ql, qr, 2 * x + 1, lx, mid), query(ql, qr, 2 * x + 2, mid, rx));
  }
  Node query(int ql, int qr) { return query(ql, qr, 0, 0, n); }
  Node query(int pos) { return query(pos, pos + 1, 0, 0, n); }

  template <typename F> int findFirst(int ql, int qr, F&& pred, int x, int lx, int rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) return -1;
    if (rx - lx == 1) return lx;
    push(x);
    auto mid = lx + (rx - lx) / 2;
    auto res = findFirst(ql, qr, std::forward<F>(pred), 2 * x + 1, lx, mid);
    if (res == -1) {
      res = findFirst(ql, qr, std::forward<F>(pred), 2 * x + 2, mid, rx);
    }
    return res;
  }
  template <typename F> int findFirst(int ql, int qr, F&& pred) {
    return findFirst(ql, qr, std::forward<F>(pred), 0, 0, n);
  }
  template <typename F> int findLast(int ql, int qr, F&& pred, int x, int lx, int rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) return -1;
    if (rx - lx == 1) return lx;
    push(x);
    auto mid = lx + (rx - lx) / 2;
    auto res = findLast(ql, qr, std::forward<F>(pred), 2 * x + 2, mid, rx);
    if (res == -1) {
      res = findLast(ql, qr, std::forward<F>(pred), 2 * x + 1, lx, mid);
    }
    return res;
  }
  template <typename F> int findLast(int ql, int qr, F&& pred) {
    return findLast(ql, qr, std::forward<F>(pred), 0, 0, n);
  }
};

struct Tag {
  int64_t val = 0;
  void apply(const Tag &tag) {
    val += tag.val;
  }
};

struct Node {
  int64_t val = 0;
  void apply(const Tag &tag) {
    val += tag.val;
  }
  static Node unite(Node a, Node b) {
    return Node{a.val + b.val};
  }
};

void solve() {
  int n, m;
  std::cin >> n >> m;
  LazySegmentTree<Node, Tag> st(n);
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    st.modify(i, {x});
  }
  for (int i = 0; i < m; ++i) {
    int b;
    std::cin >> b;
    auto cnt = st.query(b).val;
    st.modify(b, b + 1, {-cnt});
    auto [q, r] = std::lldiv(cnt, n);
    st.modify(0, n, {q});
    auto forw = std::min<int64_t>(r, n - b - 1);
    st.modify(b + 1, b + 1 + forw, {1});
    auto rest = r - forw;
    st.modify(0, rest, {1});
  }
  for (int i = 0; i < n; ++i) {
    std::cout << st.query(i).val << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}