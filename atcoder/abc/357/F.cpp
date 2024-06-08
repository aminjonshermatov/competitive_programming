#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <int P> class Z {
  int x = 0;
public:
  static_assert(P <= std::numeric_limits<int>::max() / 2);

  constexpr Z() noexcept = default;
  constexpr Z(long long y) noexcept : x(norm(y)) { }

  static constexpr int getMod() noexcept { return P; }
  [[nodiscard]] constexpr static int norm(long long y) noexcept {
    if (y < -getMod() || y >= getMod()) {
      y %= getMod();
    }
    if (y < 0) {
      y += getMod();
    }
    return static_cast<int>(y);
  }

  [[nodiscard]] constexpr int val() const noexcept { return x; }
  constexpr explicit operator int() const noexcept { return x; }

  constexpr Z operator-() const noexcept {
    return {getMod() - x};
  }
  [[nodiscard]] constexpr Z inverse() const noexcept {
    return pow(getMod() - 2);
  }

  constexpr Z& operator+=(Z other) noexcept {
    x = norm(x + other.val());
    return *this;
  }
  constexpr Z& operator-=(Z other) noexcept {
    x = norm(x - other.val());
    return *this;
  }
  constexpr Z& operator*=(Z other) noexcept {
    x = norm(x * 1LL * other.val());
    return *this;
  }
  constexpr Z& operator/=(Z other) noexcept {
    return *this *= other.inverse();
  }

  constexpr Z& operator++() noexcept {
    operator+=(1);
    return *this;
  }
  constexpr Z operator++(int) const noexcept {
    auto z = *this;
    ++(*this);
    return z;
  }
  constexpr Z& operator--() noexcept {
    operator-=(1);
    return *this;
  }
  constexpr Z operator--(int) const noexcept {
    auto z = *this;
    --(*this);
    return z;
  }

  constexpr Z operator+(Z other) const noexcept {
    return {x + other.val()};
  }
  constexpr Z operator-(Z other) const noexcept {
    return {x - other.val()};
  }
  constexpr Z operator*(Z other) const noexcept {
    return {x * 1LL * other.val()};
  }
  constexpr Z operator/(Z other) const noexcept {
    return other.inverse() * x;
  }

  constexpr bool operator==(Z other) const noexcept {
    return val() == other.val();
  }
  constexpr bool operator!=(Z other) const noexcept {
    return val() != other.val();
  }

  [[nodiscard]] Z pow(long long n) const {
    auto ret = Z(*this);
    Z res = 1;
    for (; n > 0; n >>= 1, ret *= ret) {
      if (n % 2 == 1) {
        res *= ret;
      }
    }
    return res;
  }

  friend std::istream& operator>>(std::istream& in, Z& z) {
    long long y;
    in >> y;
    z = Z{y};
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Z& z) {
    return out << z.val();
  }
};

constexpr int Mod = 998244353;
using Mint = Z<Mod>;

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

// ab -> (a+x)(b+y)=ab+bx+ay+xy
struct Tag {
  Mint x, y;
  void apply(auto&& tag) {
    x += tag.x;
    y += tag.y;
  }
};

struct Node {
  Mint a, b, ab;
  int len{};
  Node() = default;
  Node(const Mint aa, const Mint bb, const Mint aabb, const int sz) : a(aa), b(bb), ab(aabb), len(sz) { }
  void apply(const Tag& tag) {
    ab += a * tag.y + b * tag.x + tag.x * tag.y * len;
    a += tag.x * len;
    b += tag.y * len;
  }
  static Node unite(const Node& lhs, const Node& rhs) {
    return {lhs.a + rhs.a, lhs.b + rhs.b, lhs.ab + rhs.ab, lhs.len + rhs.len};
  }
};

void solve() {
  int n, q;
  scan(n, q);
  std::vector<Node> init(n);
  for (int i = 0; i < n; ++i) {
    scan(init[i].a);
  }
  for (int i = 0; i < n; ++i) {
    scan(init[i].b);
    init[i].ab = init[i].a * init[i].b;
    init[i].len = 1;
  }
  LazySegmentTree<Node, Tag> st(init);
  while (q-- > 0) {
    char cmd;
    int l, r;
    scan(cmd, l, r);
    --l;
    if (cmd == '1') {
      Mint x;
      scan(x);
      st.modify(l, r, {x, 0});
    } else if (cmd == '2') {
      Mint x;
      scan(x);
      st.modify(l, r, {0, x});
    } else {
      println(st.query(l, r).ab);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}