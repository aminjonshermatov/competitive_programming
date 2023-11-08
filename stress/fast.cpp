//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "constants.h"

template <typename Node, typename Tag>
struct LazySegmentTree {
  int n = 0;
  std::vector<Node> nodes;
  std::vector<Tag> tags;

  explicit LazySegmentTree(int n_) { init(std::vector(n_, Node())); }
  explicit LazySegmentTree(int n_, Node node) { init(std::vector(n_, node)); }
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

  template<typename F> int findFirst(int ql, int qr, F pred, int x, int lx, int rx) {
    if (lx >= qr || rx <= ql || !pred(nodes[x])) return -1;
    if (rx - lx == 1) return lx;
    push(x);
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
    if (lx >= qr || rx <= ql || !pred(nodes[x])) return -1;
    if (rx - lx == 1) return lx;
    push(x);
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

struct TagSum {
  int val = 0;
  void apply(const TagSum &tag) {
    val += tag.val;
  }
};

struct NodeSum {
  int val = 0, size = 1;
  void apply(const TagSum &tag) {
    val += tag.val * size;
  }
  static NodeSum unite(NodeSum a, NodeSum b) {
    return NodeSum{a.val + b.val, a.size + b.size};
  }
};

NodeSum operator+(const NodeSum &a, const NodeSum &b) {
  return NodeSum{a.val + b.val};
}

template <typename Node> struct BottomUpSegmentTree {
  int n = 0;
  std::vector<Node> nodes;

  explicit BottomUpSegmentTree(int n_) { init(std::vector(n_, Node())); }
  explicit BottomUpSegmentTree(int n_, Node node) { init(std::vector(n_, node)); }
  template <typename T> explicit BottomUpSegmentTree(std::vector<T> init_) { init(init_); }

  template <typename T> void init(std::vector<T> init_) {
    n = init_.size();
    nodes.assign(2 * init_.size(), Node());
    for (int i = 0; i < init_.size(); ++i) {
      modify(i, Node{init_[i]});
    }
  }

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

constexpr auto inf = std::numeric_limits<int>::max();
struct NodeMin {
  int val = inf, id = -1;
  static NodeMin unite(NodeMin a, NodeMin b) {
    return a.val < b.val ? a : b;
  }
};
constexpr auto ninf = std::numeric_limits<int>::min();
struct NodeMax {
  int val = ninf, id = -1;
  static NodeMax unite(NodeMax a, NodeMax b) {
    return a.val > b.val ? a : b;
  }
};

struct Segment {
  int l, r, id;
  bool operator<(const Segment &other) const {
    return l != other.l ? l < other.l : r < other.r;
  }
  friend std::ostream& operator<<(std::ostream &out, const Segment &seg) {
    return out << '{' << seg.l << ',' << seg.r << ',' << seg.id << '}';
  }
};

void solve(std::istream &in, std::ostream &out) {
  int n, m;
  in >> n >> m;

  BottomUpSegmentTree<NodeMax> by_start(n + 1);
  BottomUpSegmentTree<NodeMin> by_end(n + 1);
  LazySegmentTree<NodeSum, TagSum> lzst(n + 1);

  std::set<Segment> segments;
  std::vector<Segment> seen(m);
  for (int i = 0; i < m; ++i) {
    auto &[l, r, idx] = seen[i];
    idx = i;
    in >> l >> r;

    auto cur = r - l + 1;

    auto min_start = by_end.query(l, r + 1).id;
    auto max_end = by_start.query(l, r + 1).id;

    int prv = 0;
    if (min_start != -1) {
      if (max_end == -1 || min_start == max_end) {
        prv += seen[min_start].r - seen[min_start].l + 1;
      } else {
        prv += seen[min_start].r - seen[min_start].l + 1 + seen[max_end].r - seen[max_end].l + 1;
        assert(seen[min_start].r + 1 <= seen[max_end].l);
        prv += lzst.query(seen[min_start].r + 1, seen[max_end].l).val;
      }
    } else if (max_end != -1) {
      prv += seen[max_end].r - seen[max_end].l + 1;
    } else if (min_start == -1) {
      auto [min_l, id] = by_end.query(r, n + 1);
      if (min_l < l) {
        prv += seen[id].r - seen[id].l + 1;
      }
    }

    if (prv > cur) {
      out << "0 0\n";
      continue;
    }
    std::vector<int> ids;
    if (min_start != -1) {
      for (
        auto it = segments.lower_bound(seen[min_start]);
        it != segments.end() && it->l <= r;
        it = std::next(it))
      {
        ids.emplace_back(it->id);
      }
    } else if (max_end != -1) {
      for (
        auto it = segments.lower_bound(seen[max_end]);
        it != segments.end() && it->l <= r;
        it = std::next(it))
      {
        ids.emplace_back(it->id);
      }
    }

    for (auto id : ids) {
      segments.erase({seen[id].l, seen[id].r, seen[id].id});
      by_start.modify(seen[id].l, NodeMax{});
      by_end.modify(seen[id].r, NodeMin{});
      lzst.modify(seen[id].l, seen[id].r + 1, {-1});
    }
    segments.emplace(seen[i]);
    by_start.modify(l, NodeMax{r, idx});
    by_end.modify(r, NodeMin{l, idx});
    lzst.modify(l, r + 1, {+1});
    out << "1 " << ids.size() << ' ';
    std::sort(ids.begin(), ids.end());
    for (auto id : ids) {
      out << id + 1 << ' ';
    }
    out << '\n';
  }
}

int main() {
  auto in = std::ifstream(constants::DATA_IN);
  auto out = std::ofstream(constants::FAST_OUT);
  solve(in, out);

  return 0;
}
