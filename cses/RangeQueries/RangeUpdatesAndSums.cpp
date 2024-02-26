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

// 0 - add
// 1 - set

enum class TagType : uint8_t {
  kAdd, kSet
};

struct Tag {
  int64_t val = 0;
  TagType type = TagType::kAdd;
  void apply(const Tag &tag) {
    if (tag.type == TagType::kSet) {
      val = tag.val;
      type = tag.type;
    } else {
      val += tag.val;
    }
  }
};

struct Node {
  int64_t val = 0, len = 0;
  void apply(const Tag &tag) {
    if (tag.type == TagType::kSet) {
      val = 0;
    }
    val += tag.val * len;
  }
  static Node unite(Node a, Node b) {
    return Node{a.val + b.val, a.len + b.len};
  }
};

void solve() {
  int n, q;
  std::cin >> n >> q;
  std::vector<Node> init(n);
  for (auto& [val, len] : init) {
    std::cin >> val;
    len = 1;
  }
  LazySegmentTree<Node, Tag> st(init);
  while (q-- > 0) {
    char cmd;
    int a, b;
    std::cin >> cmd >> a >> b;
    --a;
    if (cmd == '1') {
      int x;
      std::cin >> x;
      st.modify(a, b, {x, TagType::kAdd});
    } else if (cmd == '2') {
      int x;
      std::cin >> x;
      st.modify(a, b, {x, TagType::kSet});
    } else {
      std::cout << st.query(a, b).val << '\n';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}