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

constexpr auto kBlockWidth = 600;

void Solve() {
  int n, q;
  Scan(n, q);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
    --as[i];
  }

  std::vector<Mint> fac(n + 1);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i;
  }
  std::vector<Mint> ifac(n + 1);
  ifac[n] = Mint{1} / fac[n];
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * (i + 1);
  }

  std::vector<std::tuple<int, int, int, int>> qs(q);
  for (int i = 0; auto& [l, r, x, id] : qs) {
    Scan(l, r, x);
    --l, --r, --x;
    id = i++;
  }
  std::ranges::sort(qs, [&](const auto& lhs, const auto& rhs) {
    auto lA = std::get<0>(lhs), rA = std::get<1>(lhs);
    auto lB = std::get<0>(rhs), rB = std::get<1>(rhs);
    lA /= kBlockWidth;
    lB /= kBlockWidth;
    return lA != lB ? lA < lB : lA % 2 == 1 ? rA > rB : rA < rB;
  });

  const int nBlocks = (n + kBlockWidth - 1) / kBlockWidth;

  std::vector<Mint> ret(q), prodBlock(nBlocks, 1);
  std::vector<int> cnt(n, 0), cntBlock(nBlocks, 0);

  auto upd = [&](const int id, const int delta) {
    const auto val = as[id];
    prodBlock[val / kBlockWidth] *= fac[cnt[val]];
    cnt[val] += delta;
    cntBlock[val / kBlockWidth] += delta;
    prodBlock[val / kBlockWidth] *= ifac[cnt[val]];
  };
  
  int curL = 0, curR = -1;
  for (auto [l, r, x, idx] : qs) {
    while (curL > l) {
      upd(--curL, +1);
    }
    while (curR < r) {
      upd(++curR, +1);
    }
    while (curL < l) {
      upd(curL++, -1);
    }
    while (curR > r) {
      upd(curR--, -1);
    }

    int c = 0;
    Mint p = 1;
    auto ib = 0;
    for (; (ib + 1) * kBlockWidth - 1 < x; ++ib) {
      c += cntBlock[ib];
      p *= prodBlock[ib];
    }
    for (auto i = ib * kBlockWidth; i < x; ++i) {
      c += cnt[i];
      p *= ifac[cnt[i]];
    }
    p *= fac[c];
    ret[idx] = p;
  }
  for (int i = 0; i < q; ++i) {
    Print(ret[i]);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
