//
// Created by aminjon on 10/9/22.
//
#include <bits/stdc++.h>

using namespace std;

template <typename Node, typename Tag>
struct LazySegmentTree {
  std::size_t n{};
  std::vector<Node> nodes;
  std::vector<Tag> tags;

  static constexpr auto npos = static_cast<size_t>(-1);

  LazySegmentTree() = default;

  explicit LazySegmentTree(std::size_t n_) { init(std::vector(n_, Node())); }

  LazySegmentTree(std::size_t n_, Node&& node) {
    init(std::vector(n_, std::forward<Node>(node)));
  }

  template <typename T>
  explicit LazySegmentTree(const std::vector<T>& init_) { init(init_); }

  template <typename T>
  void init(const std::vector<T>& init_) {
    n = 1u << std::__lg(2 * init_.size() - 1);
    nodes.assign(2 * n - 1, Node());
    tags.assign(2 * n - 1, Tag());
    auto build = [&](auto&& self, std::size_t x, std::size_t lx, std::size_t rx) -> void {
      if (rx - lx == 1u) {
        if (lx < init_.size()) {
          nodes[x] = Node{init_[lx]};
        }
        return;
      }
      const auto mid = lx + (rx - lx) / 2;
      self(self, 2 * x + 1, lx, mid);
      self(self, 2 * x + 2, mid, rx);
      nodes[x] = Node::unite(std::forward<Node>(nodes[2 * x + 1]),
                             std::forward<Node>(nodes[2 * x + 2]));
    };
    build(build, 0u, 0u, n);
  }

  void apply(std::size_t x, Tag&& tag) {
    nodes[x].apply(std::forward<Tag>(tag));
    tags[x].apply(std::forward<Tag>(tag));
  }

  void push(std::size_t x) {
    apply(2 * x + 1, std::forward<Tag>(tags[x]));
    apply(2 * x + 2, std::forward<Tag>(tags[x]));
    tags[x] = Tag();
  }

  void pull(std::size_t x) {
    nodes[x] = Node::unite(std::forward<Node>(nodes[2 * x + 1]),
                           std::forward<Node>(nodes[2 * x + 2]));
  }

  void modify(std::size_t pos, Node&& node,
              std::size_t x, std::size_t lx, std::size_t rx) {
    if (rx - lx == 1u) {
      nodes[x] = node;
      return;
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      modify(pos, std::forward<Node>(node), 2 * x + 1, lx, mid);
    } else {
      modify(pos, std::forward<Node>(node), 2 * x + 2, mid, rx);
    }
    pull(x);
  }

  void modify(std::size_t pos, Node&& node) {
    modify(pos, std::forward<Node>(node), 0u, 0u, n);
  }

  void modify(std::size_t ql, std::size_t qr, Tag&& tag,
              std::size_t x, std::size_t lx, std::size_t rx) {
    if (ql >= rx || qr <= lx) {
      return;
    }
    if (ql <= lx && rx <= qr) {
      apply(x, std::forward<Tag>(tag));
      return;
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
    modify(ql, qr, std::forward<Tag>(tag), 2 * x + 1, lx, mid);
    modify(ql, qr, std::forward<Tag>(tag), 2 * x + 2, mid, rx);
    pull(x);
  }

  void modify(std::size_t ql, std::size_t qr, Tag&& tag) {
    modify(ql, qr, std::forward<Tag>(tag), 0u, 0u, n);
  }

  Node query(std::size_t ql, std::size_t qr,
             std::size_t x, std::size_t lx, std::size_t rx) {
    if (ql >= rx || qr <= lx) {
      return Node();
    }
    if (ql <= lx && rx <= qr) {
      return nodes[x];
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
    return Node::unite(std::forward<Node>(query(ql, qr, 2 * x + 1, lx, mid)),
                       std::forward<Node>(query(ql, qr, 2 * x + 2, mid, rx)));
  }

  Node query(std::size_t ql, std::size_t qr) {
    return query(ql, qr, 0u, 0u, n);
  }

  Node query(std::size_t pos) {
    return query(pos, pos + 1, 0u, 0u, n);
  }

  template <typename F>
  std::size_t findFirst(std::size_t ql, std::size_t qr, F&& pred,
                        std::size_t x, std::size_t lx, std::size_t rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return npos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
    auto res = findFirst(ql, qr, std::forward<F>(pred), 2 * x + 1, lx, mid);
    if (res == npos) {
      res = findFirst(ql, qr, std::forward<F>(pred), 2 * x + 2, mid, rx);
    }
    return res;
  }

  template <typename F>
  std::size_t findFirst(std::size_t ql, std::size_t qr, F&& pred) {
    return findFirst(ql, qr, std::forward<F>(pred), 0u, 0u, n);
  }

  template <typename F>
  std::size_t findLast(std::size_t ql, std::size_t qr, F&& pred,
                       std::size_t x, std::size_t lx, std::size_t rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return npos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    push(x);
    const auto mid = lx + (rx - lx) / 2;
    auto res = findLast(ql, qr, std::forward<F>(pred), 2 * x + 2, mid, rx);
    if (res == npos) {
      res = findLast(ql, qr, std::forward<F>(pred), 2 * x + 1, lx, mid);
    }
    return res;
  }

  template <typename F>
  std::size_t findLast(std::size_t ql, std::size_t qr, F&& pred) {
    return findLast(ql, qr, std::forward<F>(pred), 0u, 0u, n);
  }
};

struct Tag {
  int val = 0;
  void apply(auto&& tag) {
    val += tag.val;
  }
};

struct Node {
  int min = std::numeric_limits<int>::max() / 2;
  void apply(auto&& tag) {
    min += tag.val;
  }
  static Node unite(auto&& a, auto&& b) {
    return {std::min(a.min, b.min)};
  }
};

template <typename Node>
struct SegmentTree {
  std::size_t n{};
  std::vector<Node> nodes;

  static constexpr auto npos = static_cast<size_t>(-1);

  SegmentTree() = default;

  explicit SegmentTree(std::size_t n_) { init(std::vector(n_, Node())); }

  SegmentTree(int n_, Node&& node) { init(std::vector(n_, std::forward<Node>(node))); }

  template <typename T>
  explicit SegmentTree(const std::vector<T>& init_) { init(init_); }

  template <typename T>
  void init(const std::vector<T>& init_) {
    n = 1u << std::__lg(2 * init_.size() - 1);
    nodes.assign(2 * n - 1, Node());
    auto build = [&](auto&& self, std::size_t x, std::size_t lx, std::size_t rx) -> void {
      if (rx - lx == 1u) {
        if (lx < init_.size()) {
          nodes[x] = Node{init_[lx]};
        }
        return;
      }
      const auto mid = lx + (rx - lx) / 2;
      self(self, 2 * x + 1, lx, mid);
      self(self, 2 * x + 2, mid, rx);
      nodes[x] = Node::unite(std::forward<Node>(nodes[2 * x + 1]),
                             std::forward<Node>(nodes[2 * x + 2]));
    };
    build(build, 0u, 0u, n);
  }

  void modify(std::size_t pos, Node&& node,
              std::size_t x, std::size_t lx, std::size_t rx) {
    if (rx - lx == 1u) {
      nodes[x] = node;
      return;
    }
    const auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      modify(pos, std::forward<Node>(node), 2 * x + 1, lx, mid);
    } else {
      modify(pos, std::forward<Node>(node), 2 * x + 2, mid, rx);
    }
    nodes[x] = Node::unite(std::forward<Node>(nodes[2 * x + 1]),
                           std::forward<Node>(nodes[2 * x + 2]));
  }

  void modify(std::size_t pos, Node&& node) {
    modify(pos, std::forward<Node>(node), 0u, 0u, n);
  }

  Node query(std::size_t ql, std::size_t qr,
             std::size_t x, std::size_t lx, std::size_t rx) {
    if (ql >= rx || qr <= lx) {
      return Node();
    }
    if (ql <= lx && rx <= qr) {
      return nodes[x];
    }
    const auto mid = lx + (rx - lx) / 2;
    return Node::unite(std::forward<Node>(query(ql, qr, 2 * x + 1, lx, mid)),
                       std::forward<Node>(query(ql, qr, 2 * x + 2, mid, rx)));
  }

  Node query(std::size_t ql, std::size_t qr) {
    return query(ql, qr, 0u, 0u, n);
  }

  Node query(std::size_t pos) {
    return query(pos, pos + 1, 0u, 0u, n);
  }

  template <typename F>
  std::size_t findFirst(std::size_t ql, std::size_t qr, F&& pred,
                        std::size_t x, std::size_t lx, std::size_t rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return npos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    const auto mid = lx + (rx - lx) / 2;
    auto res = findFirst(ql, qr, std::forward<F>(pred), 2 * x + 1, lx, mid);
    if (res == npos) {
      res = findFirst(ql, qr, std::forward<F>(pred), 2 * x + 2, mid, rx);
    }
    return res;
  }

  template <typename F>
  std::size_t findFirst(std::size_t ql, std::size_t qr, F&& pred) {
    return findFirst(ql, qr, std::forward<F>(pred), 0u, 0u, n);
  }

  template <typename F>
  std::size_t findLast(std::size_t ql, std::size_t qr, F&& pred,
                       std::size_t x, std::size_t lx, std::size_t rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) {
      return npos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    const auto mid = lx + (rx - lx) / 2;
    auto res = findLast(ql, qr, std::forward<F>(pred), 2 * x + 2, mid, rx);
    if (res == npos) {
      res = findLast(ql, qr, std::forward<F>(pred), 2 * x + 1, lx, mid);
    }
    return res;
  }

  template <typename F>
  std::size_t findLast(std::size_t ql, std::size_t qr, F&& pred) {
    return findLast(ql, qr, std::forward<F>(pred), 0u, 0u, n);
  }
};

struct Node {
  int val = 0;
  static Node unite(auto&& a, auto&& b) {
    return {std::max(a.val, b.val)};
  }
};


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

struct Node {
  int val = 0;
  static Node unite(const Node& a, const Node& b) {
    return {std::max(a.val, b.val)};
  }
};