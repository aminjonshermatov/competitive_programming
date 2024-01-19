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

constexpr i64 Mod = 1e9 + 7;
using Mint = Z<Mod>;

bool seen[int(1e5 + 10)][110][2];
Mint cache[int(1e5 + 10)][110][2];

void solve() {
  std::string s;
  int d;
  std::cin >> s >> d;
  const auto n = int(s.size());

  std::memset(seen, 0, sizeof seen);
  auto dfs = [&](auto& f, int pos, int sum, bool can_use_any) -> Mint {
    if (pos >= n) {
      return sum == 0;
    }
    if (seen[pos][sum][can_use_any]) {
      return cache[pos][sum][can_use_any];
    }
    Mint loc = 0;
    auto c = s[pos] - '0';
    for (int z = 0; z <= (can_use_any ? 9 : c); ++z) {
      loc += f(f, pos + 1, (sum + z) % d, can_use_any || (z < c));
    }
    seen[pos][sum][can_use_any] = true;
    return cache[pos][sum][can_use_any] = loc;
  };
  std::cout << dfs(dfs, 0, 0, false) - 1 << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
