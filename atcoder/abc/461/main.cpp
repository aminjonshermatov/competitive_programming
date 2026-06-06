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
  int64_t n;
  Scan(n);

  std::vector<std::pair<int64_t, int>> fs;
  for (int64_t d = 2; d * d <= n; ++d) {
    if (n % d != 0) {
      continue;
    }
    auto c = 0;
    while (n % d == 0) {
      ++c;
      n /= d;
    }
    fs.emplace_back(d, c);
  }
  if (n > 1) {
    fs.emplace_back(n, 1);
  }
  dbg(fs);

#ifndef LOCALL
  const auto maxA = std::ranges::max(fs, {}, &decltype(fs)::value_type ::second).second;
#else
  const auto maxA = 34;
#endif
  dbg(maxA);

  std::vector<std::vector<std::vector<int>>> ways(maxA + 1);
  for (int x = 1; x <= maxA; ++x) {
    std::vector<int> cur;
    [&](this auto self, int lst, int rem) -> void {
      if (lst < rem) {
        cur.emplace_back(rem);
        ways[x].emplace_back(cur);
        cur.pop_back();
      }
      for (int a = lst + 1; 2 * a + 1 <= rem; ++a) {
        cur.emplace_back(a);
        self(a, rem - a);
        cur.pop_back();
      }
    }(0, x);
    dbg(x,ways[x].size());
  }

  constexpr int kMx = 2000;
  std::array<Mint, kMx> fac{};
  fac[0] = 1;
  for (int i = 1; i < kMx; ++i) {
    fac[i] = fac[i - 1] * i;
  }
  dbg(ways[2]);

  Mint ret;
  [&](this auto self, int id, int len, Mint sum) -> void {
    if (id >= fs.size()) {
      dbg(len,sum);
      ret += sum * fac[len] + (sum + 1) * fac[len] * (len + 1);
      return;
    }
    for (const auto& w : ways[fs[id].second]) {
      auto nsum = sum;
      for (const auto a : w) {
        nsum += Mint(fs[id].first).Pow(a);
      }
      self(id + 1, len + w.size(), nsum);
    }
  }(0, 0, 0);
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
