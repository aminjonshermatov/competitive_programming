#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

template <typename Node> struct BottomUpSegmentTree {
  int n = 0;
  std::vector<Node> nodes;

  explicit BottomUpSegmentTree(int n_) { init(std::vector(n_, Node())); }
  BottomUpSegmentTree(int n_, Node node) { init(std::vector(n_, node)); }
  template <typename T> explicit BottomUpSegmentTree(std::vector<T> init_) { init(init_); }

  template <typename T> void init(std::vector<T> init_) {
    n = init_.size();
    nodes.assign(2 * init_.size(), Node());
    for (int i = 0; i < init_.size(); ++i) {
      modify(i, Node{init_[i]});
    }
  }

  void modify(int pos, Node val) {
    for (nodes[pos += n] = val; pos > 1;) {
      pos >>= 1;
      nodes[pos] = Node::unite(nodes[pos << 1], nodes[pos << 1 | 1]);
    }
  }
  Node query(int l, int r) {
    auto ans = Node();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ans = Node::unite(ans, nodes[l++]);
      if (r & 1) ans = Node::unite(ans, nodes[--r]);
    }
    return ans;
  }
};

struct Node {
  int val = 0;
  static Node unite(Node a, Node b) {
    return Node{std::max(a.val, b.val)};
  }
};

void solve() {
  int n, d;
  std::cin >> n >> d;
  std::vector<int> as(n);
  for (auto& a : as) {
    std::cin >> a;
  }
  const auto max_a = std::ranges::max(as);
  BottomUpSegmentTree<Node> dp(max_a + 1);
  for (auto a : as) {
    dp.modify(a, {std::max(dp.query(a, a + 1).val, dp.query(std::max(0, a - d), std::min(max_a, a + d) + 1).val + 1)});
  }
  std::cout << dp.query(0, max_a + 1).val << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}