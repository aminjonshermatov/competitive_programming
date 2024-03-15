//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

using namespace std;

template <typename Node, typename Tag> struct LazySegmentTree {
  int n = 0;
  std::vector<Node> nodes;
  std::vector<Tag> tags;

  LazySegmentTree() = default;
  explicit LazySegmentTree(int n_) { init(std::vector(n_, Node())); }
  LazySegmentTree(int n_, const Node& node) { init(std::vector(n_, node)); }
  template <typename T> explicit LazySegmentTree(const std::vector<T>& init_) { init(init_); }

  template <typename T> void init(const std::vector<T>& init_) {
    for (n = 1; n < init_.size(); n <<= 1) { }
    nodes.assign(2 * n - 1, Node());
    tags.assign(2 * n - 1, Tag());
    auto build = [&](auto&& self, int x, int lx, int rx) -> void {
      if (rx - lx == 1) {
        if (lx < init_.size()) {
          nodes[x] = Node{init_[lx]};
        }
        return;
      }
      const auto mid = lx + (rx - lx) / 2;
      self(self, 2 * x + 1, lx, mid);
      self(self, 2 * x + 2, mid, rx);
      nodes[x] = Node::unite(nodes[2 * x + 1], nodes[2 * x + 2]);
    };
    build(build, 0, 0, n);
  }

  inline void apply(int x, const Tag& tag) {
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

  void modify(int pos, const Node& node, int x, int lx, int rx) {
    if (rx - lx == 1) {
      nodes[x] = node;
      return;
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      modify(pos, node, 2 * x + 1, lx, mid);
    } else {
      modify(pos, node, 2 * x + 2, mid, rx);
    }
    pull(x);
  }
  void modify(int pos, const Node& node) {
    modify(pos, node, 0, 0, n);
  }
  void modify(int ql, int qr, const Tag& tag, int x, int lx, int rx) {
    if (ql >= rx || qr <= lx) return;
    if (ql <= lx && rx <= qr) {
      apply(x, tag);
      return;
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
    modify(ql, qr, tag, 2 * x + 1, lx, mid);
    modify(ql, qr, tag, 2 * x + 2, mid, rx);
    pull(x);
  }
  void modify(int ql, int qr, const Tag& tag) {
    modify(ql, qr, tag, 0, 0, n);
  }
  Node query(int ql, int qr, int x, int lx, int rx) {
    if (ql >= rx || qr <= lx) {
      return Node();
    }
    if (ql <= lx && rx <= qr) {
      return nodes[x];
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
    return Node::unite(query(ql, qr, 2 * x + 1, lx, mid), query(ql, qr, 2 * x + 2, mid, rx));
  }
  Node query(int ql, int qr) {
    return query(ql, qr, 0, 0, n);
  }
  Node query(int pos) {
    return query(pos, pos + 1, 0, 0, n);
  }

  template <typename F> int findFirst(int ql, int qr, F&& pred, int x, int lx, int rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return -1;
    }
    if (rx - lx == 1) {
      return lx;
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
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
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return -1;
    }
    if (rx - lx == 1) {
      return lx;
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
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
  int val = -1;
  void apply(const Tag& tag) {
    val += tag.val;
  }
};

struct Node {
  int sum = 0;
  void apply(const Tag& tag) {
    sum += tag.val;
  }
  static Node unite(const Node& a, const Node& b) {
    return {a.sum + b.sum};
  }
};


template <typename Node> struct SegmentTree {
  int n = 0;
  std::vector<Node> nodes;

  SegmentTree() = default;
  explicit SegmentTree(int n_) { init(std::vector(n_, Node())); }
  SegmentTree(int n_, const Node& node) { init(std::vector(n_, node)); }
  template <typename T> explicit SegmentTree(const std::vector<T>& init_) { init(init_); }

  template <typename T> void init(const std::vector<T>& init_) {
    for (n = 1; n < init_.size(); n <<= 1) { }
    nodes.assign(2 * n - 1, Node());
    auto build = [&](auto&& self, int x, int lx, int rx) -> void {
      if (rx - lx == 1) {
        if (lx < init_.size()) {
          nodes[x] = Node{init_[lx]};
        }
        return;
      }
      const auto mid = lx + (rx - lx) / 2;
      self(self, 2 * x + 1, lx, mid);
      self(self, 2 * x + 2, mid, rx);
      nodes[x] = Node::unite(nodes[2 * x + 1], nodes[2 * x + 2]);
    };
    build(build, 0, 0, n);
  }

  void modify(int pos, const Node& node, int x, int lx, int rx) {
    if (rx - lx == 1) {
      nodes[x] = node;
      return;
    }
    const auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      modify(pos, node, 2 * x + 1, lx, mid);
    } else {
      modify(pos, node, 2 * x + 2, mid, rx);
    }
    nodes[x] = Node::unite(nodes[2 * x + 1], nodes[2 * x + 2]);
  }
  void modify(int pos, const Node& node) {
    modify(pos, node, 0, 0, n);
  }
  Node query(int ql, int qr, int x, int lx, int rx) {
    if (ql >= rx || qr <= lx) {
      return Node();
    }
    if (ql <= lx && rx <= qr) {
      return nodes[x];
    }
    const auto mid = lx + (rx - lx) / 2;
    return Node::unite(query(ql, qr, 2 * x + 1, lx, mid), query(ql, qr, 2 * x + 2, mid, rx));
  }
  Node query(int ql, int qr) {
    return query(ql, qr, 0, 0, n);
  }
  Node query(int pos) {
    return query(pos, pos + 1, 0, 0, n);
  }
  template <typename F> int findFirst(int ql, int qr, F&& pred, int x, int lx, int rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return -1;
    }
    if (rx - lx == 1) {
      return lx;
    }
    const auto mid = lx + (rx - lx) / 2;
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
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return -1;
    }
    if (rx - lx == 1) {
      return lx;
    }
    const auto mid = lx + (rx - lx) / 2;
    auto res = findLast(ql, qr, std::forward<F>(pred), 2 * x + 2, mid, rx);
    if (res == -1) res = findLast(ql, qr, std::forward<F>(pred), 2 * x + 1, lx, mid);
    return res;
  }
  template <typename F> int findLast(int ql, int qr, F&& pred) {
    return findLast(ql, qr, std::forward<F>(pred), 0, 0, n);
  }
};

struct Node {
  int val = 0;
  static Node unite(const Node& a, const Node& b) {
    return {std::max(a.val, b.val)};
  }
};


template <typename Node> struct BottomUpSegmentTree {
  int n = 0;
  std::vector<Node> nodes;

  BottomUpSegmentTree() = default;
  explicit BottomUpSegmentTree(int n_) { init(std::vector(n_, Node())); }
  BottomUpSegmentTree(int n_, const Node& node) { init(std::vector(n_, node)); }
  template <typename T> explicit BottomUpSegmentTree(const std::vector<T>& init_) { init(init_); }

  template <typename T> void init(const std::vector<T>& init_) {
    for (n = 1; n < init_.size(); n *= 2) { }
    nodes.assign(2 * n, Node());
    for (int i = 0; i < init_.size(); ++i) {
      nodes[i + n] = Node(init_[i]);
    }
    for (int i = n - 1; i >= 1; --i) {
      nodes[i] = Node::unite(nodes[i << 1], nodes[i << 1 | 1]);
    }
  }

  void modify(int pos, const Node& val) {
    nodes[pos += n] = val;
    for (pos >>= 1; pos >= 1; pos >>= 1) {
      nodes[pos] = Node::unite(nodes[pos << 1], nodes[pos << 1 | 1]);
    }
  }
  Node query(int l, int r) {
    auto retL = Node(), retR = Node();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        retL = Node::unite(retL, nodes[l++]);
      }
      if (r & 1) {
        retR = Node::unite(nodes[--r], retR);
      }
    }
    return Node::unite(retL, retR);
  }
};

struct Node {
  int val = 0;
  static Node unite(const Node& a, const Node& b) {
    return {std::max(a.val, b.val)};
  }
};