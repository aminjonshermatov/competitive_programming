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
  bool swap = false;
  void apply(const Tag &tag) {
    swap ^= tag.swap;
  }
};

struct Node {
  char L = '#', R = '#';
  bool ok = false;
  int len = 0;
  void apply(const Tag &tag) {
    if (tag.swap) {
      L ^= '0' ^ '1';
      R ^= '0' ^ '1';
    }
  }
  static Node unite(Node a, Node b) {
    if (a.len == 0) {
      return b;
    }
    if (b.len == 0) {
      return a;
    }
    Node ret{a.L, b.R, a.ok && b.ok, a.len + b.len};
    ret.ok &= (ret.len % 2 == 1) ? (ret.L == ret.R) : (ret.L != ret.R);
    return ret;
  }
};

void solve() {
  int n, q;
  std::cin >> n >> q;
  std::string s;
  std::cin >> s;
  LazySegmentTree<Node, Tag> st(n);
  for (int i = 0; i < n; ++i) {
    st.modify(i, {s[i], s[i], true, 1});
  }
  while (q-- > 0) {
    char cmd;
    int l, r;
    std::cin >> cmd >> l >> r;
    --l;
    if (cmd == '1') {
      st.modify(l, r, {true});
    } else {
      std::cout << (st.query(l, r).ok ? "Yes" : "No") << '\n';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}