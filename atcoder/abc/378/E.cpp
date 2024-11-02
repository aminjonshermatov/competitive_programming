#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

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

using i64 = int64_t;

struct Node {
  i64 sum = 0, cnt = 0;
  static Node unite(const Node& a, const Node& b) {
    return {a.sum + b.sum, a.cnt + b.cnt};
  }
};

void solve() {
  int n, m;
  scan(n, m);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    scan(as[i]);
    if ((as[i] %= m) < 0) {
      as[i] += m;
    }
  }

  auto add = [m](int a, int b) {
    if ((a += b) >= m) {
      a -= m;
    }
    return a;
  };

  std::vector<i64> pf(n);
  for (int i = 0; i < n; ++i) {
    pf[i] = add(i > 0 ? pf[i - 1] : 0, as[i]);
  }

  dbg(pf);
  BottomUpSegmentTree<Node> st(m);
  auto Add = [&](int val) {
    const auto [s, c] = st.query(val);
    st.modify(val, {s + val, c + 1});
  };
  Add(0);
  i64 tot = 0;
  for (int i = 0; i < n; ++i) {
    const auto [lS, lC] = st.query(0, pf[i] + 1);
    const auto [rS, rC] = st.query(pf[i] + 1, m);
    dbg(pf[i],lS,lC,rS,rC);
    tot += pf[i] * lC - lS;
    tot += (pf[i] + m) * rC - rS;
    Add(pf[i]);
//    for (int j = 0; j <= i; ++j) {
//      auto x = j > 0 ? pf[j - 1] : 0;
//      if (x <= pf[i]) {
//        tot += pf[i] - x;
//      } else {
//        tot += pf[i] - x + m;
//      }
//    }
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}