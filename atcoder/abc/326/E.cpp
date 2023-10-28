#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

template <typename T> T power(T a, i64 b) noexcept {
  T res = 1;
  for (; b > 0; b >>= 1, a *= a) {
    if (b & 1) {
      res *= a;
    }
  }
  return res;
}

template <i64 P> struct Z {
  i64 x = 0;
  constexpr Z() noexcept = default;
  constexpr Z(i64 x) noexcept : x(norm(x % getMod())) { }

  static i64 getMod() noexcept { return P; }
  [[nodiscard]] constexpr i64 norm(i64 y) const noexcept {
    if (y < 0) {
      y += getMod();
    }
    if (y >= getMod()) {
      y -= getMod();
    }
    return y;
  }

  [[nodiscard]] constexpr i64 val() const noexcept { return x; }
  constexpr explicit operator i64() const noexcept { return x; }

  constexpr Z operator-() const noexcept {
    return Z(getMod() - x);
  }
  [[nodiscard]] constexpr Z inv() const noexcept {
    return power(*this, getMod() - 2);
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
    x = norm((x * other.val()) % getMod());
    return *this;
  }
  constexpr Z& operator/=(Z other) noexcept {
    return *this *= other.inv();
  }

  constexpr Z operator+(Z other) const noexcept {
    return {x + other.val()};
  }
  constexpr Z operator-(Z other) const noexcept {
    return {norm(x - other.val())};
  }
  constexpr Z operator*(Z other) const noexcept {
    return {norm((x * other.val()) % getMod())};
  }
  constexpr Z operator/(Z other) const noexcept {
    return {other.inv() * x};
  }

  constexpr bool operator==(Z other) const noexcept {
    return val() == other.val();
  }
  constexpr bool operator!=(Z other) const noexcept {
    return val() != other.val();
  }

  template<i64 Mod> friend std::istream& operator>>(std::istream &in, Z<Mod> &z) {
    i64 y;
    in >> y;
    z = Z{y};
    return in;
  }
  template<i64 Mod> friend std::ostream& operator<<(std::ostream &out, const Z<Mod> &z) {
    return out << z.val();
  }
};

constexpr i64 mod = 998244353;
using Mint = Z<mod>;

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

struct Node {
  Mint val = 0;
  static Node unite(Node a, Node b) {
    return Node{a.val + b.val};
  }
};

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> as(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> as[i];
  }
  BottomUpSegmentTree<Node> dp(n + 1);
  for (int j = n; j >= 0; --j) {
    auto sm = dp.query(j + 1, n + 1).val;
    dp.modify(j, Node{sm / n + as[j]});
  }
  std::cout << dp.query(0, 1).val << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  solve();
}