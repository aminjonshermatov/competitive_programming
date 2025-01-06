#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <int P>
class Z {
 public:
  static_assert(0 < P && P <= std::numeric_limits<int>::max() / 2);

  constexpr Z() noexcept = default;
  constexpr Z(int64_t y) noexcept : X_(Norm(y)) { }

  static constexpr int GetMod() noexcept { return P; }

  [[nodiscard]] constexpr static int Norm(int64_t y) noexcept {
    if (y < -GetMod() || y >= GetMod()) {
      y %= GetMod();
    }
    if (y < 0) {
      y += GetMod();
    }
    return static_cast<int>(y);
  }

  [[nodiscard]] constexpr int Val() const noexcept { return X_; }
  constexpr explicit operator int() const noexcept { return X_; }

  constexpr Z operator-() const noexcept {
    return {GetMod() - X_};
  }
  [[nodiscard]] constexpr Z Inverse() const noexcept {
    return Pow(GetMod() - 2);
  }

  constexpr Z& operator+=(Z other) noexcept {
    X_ = Norm(X_ + other.Val());
    return *this;
  }
  constexpr Z& operator-=(Z other) noexcept {
    X_ = Norm(X_ - other.Val());
    return *this;
  }
  constexpr Z& operator*=(Z other) noexcept {
    X_ = Norm(X_ * 1LL * other.Val());
    return *this;
  }
  constexpr Z& operator/=(Z other) noexcept {
    return *this *= other.Inverse();
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
    return {X_ + other.Val()};
  }
  constexpr Z operator-(Z other) const noexcept {
    return {X_ - other.Val()};
  }
  constexpr Z operator*(Z other) const noexcept {
    return {X_ * 1LL * other.Val()};
  }
  constexpr Z operator/(Z other) const noexcept {
    return other.Inverse() * X_;
  }

  constexpr bool operator==(Z other) const noexcept {
    return Val() == other.Val();
  }
  constexpr bool operator!=(Z other) const noexcept {
    return Val() != other.Val();
  }

  [[nodiscard]] Z Pow(int64_t n) const {
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
    int64_t y;
    in >> y;
    z = Z{y};
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Z& z) {
    return out << z.Val();
  }

 private:
  int X_{0};
};

constexpr int kMod = 998244353;
using Mint = Z<kMod>;

void Solve() {
  int n, m;
  Scan(n, m);
  std::vector<std::vector<int>> g(n), ig(n);
  for (int i = 0; i < n; ++i) {
    int j;
    Scan(j);
    --j;
    g[i].emplace_back(j);
    ig[j].emplace_back(i);
  }
  std::vector vis(n, false);
  auto dfs = [&](auto&& self, int v, auto&& curG, std::vector<int>& xs) -> void {
    assert(!vis[v]);
    vis[v] = true;
    for (auto u : curG[v]) {
      if (!vis[u]) {
        self(self, u, curG, xs);
      }
    }
    xs.emplace_back(v);
  };
  std::vector<int> ord;
  for (int v = 0; v < n; ++v) {
    if (!vis[v]) {
      dfs(dfs, v, g, ord);
    }
  }
  std::fill(vis.begin(), vis.end(), false);
  std::vector<int> cId(n);
  int c = 0;
  for (auto v : ord | std::ranges::views::reverse) {
    if (vis[v]) {
      continue;
    }
    std::vector<int> comp;
    dfs(dfs, v, ig, comp);
    for (auto u : comp) {
      cId[u] = c;
    }
    ++c;
  }
  dbg(cId,c);
  auto tmpG = g;
  g.assign(c, {});
  ig.assign(c, {});
  for (int v = 0; v < n; ++v) {
    for (auto u : tmpG[v]) {
      if (cId[v] != cId[u]) {
        g[cId[v]].emplace_back(cId[u]);
        ig[cId[u]].emplace_back(cId[v]);
      }
    }
  }
  dbg(g);
  dbg(ig);
  vis.assign(c, false);
  ord.clear();
  for (int v = 0; v < c; ++v) {
    if (!vis[v]) {
      dfs(dfs, v, g, ord);
    }
  }
  dbg(ord);
  std::vector dp(c, std::vector(m, Mint{}));
  for (auto v : ord | std::ranges::views::reverse) {
    if (ig[v].empty()) {
      for (int col = 0; col < m; ++col) {
        dp[v][col] = 1;
      }
    } else {
      std::vector<Mint> ps(m, 1);
      for (auto u : ig[v]) {
        Mint s{0};
        for (int prvC = 0; prvC < m; ++prvC) {
          s += dp[u][prvC];
          ps[prvC] *= s;
        }
      }
      dbg(v,m,ps);
      for (int col = 0; col < m; ++col) {
        dp[v][col] += ps[col];
      }

    }
  }
  Mint tot{0};
  for (int v = 0; v < c; ++v) {
    if (g[v].empty()) {
      tot += std::accumulate(dp[v].begin(), dp[v].end(), Mint{});
      dbg(v);
    }
  }
  dbg(dp);
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
