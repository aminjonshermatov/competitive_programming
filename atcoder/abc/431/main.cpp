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

template <typename Info, typename Tag>
class LazySegmentTree {
 public:
  static constexpr auto kNpos = static_cast<size_t>(-1);

 public:
  LazySegmentTree() = default;

  explicit LazySegmentTree(std::size_t n) {
    Init(std::vector(n, Info{}));
  }
  LazySegmentTree(std::size_t n, Info info) {
    Init(std::vector(n, info));
  }
  template <typename T>
  explicit LazySegmentTree(const std::vector<T>& init) {
    Init(init);
  }

  template <typename T>
  void Init(const std::vector<T>& init) {
    assert(!init.empty());
    N_ = 1u << (std::bit_width(2 * init.size() - 1) - 1);
    Infos_.assign(2 * N_ - 1, Info{});
    Tags_.assign(2 * N_ - 1, Tag{});

    auto build = [&](auto&& self, std::size_t x, std::size_t lx, std::size_t rx) -> void {
      if (rx - lx == 1u) {
        if (lx < init.size()) {
          Infos_[x] = {init[lx]};
        }
        return;
      }
      const auto mid = lx + (rx - lx) / 2;
      self(self, 2 * x + 1, lx, mid);
      self(self, 2 * x + 2, mid, rx);
      Infos_[x] = Infos_[2 * x + 1] + Infos_[2 * x + 2];
    };
    build(build, 0u, 0u, N_);
  }

  void Modify(std::size_t pos, Info info) {
    ModifyImpl(pos, info, 0u, 0u, N_);
  }
  void Modify(std::size_t ql, std::size_t qr, Tag tag) {
    ModifyImpl(ql, qr, tag, 0u, 0u, N_);
  }

  Info Query(std::size_t ql, std::size_t qr) {
    return QueryImpl(ql, qr, 0u, 0u, N_);
  }
  Info Query(std::size_t pos) {
    return QueryImpl(pos, pos + 1, 0u, 0u, N_);
  }

  template <typename Functor>
  std::size_t FindFirst(std::size_t ql, std::size_t qr, Functor&& functor) {
    return FindFirstImpl(ql, qr, std::move(functor), 0u, 0u, N_);
  }
  template <typename Functor>
  std::size_t FindLast(std::size_t ql, std::size_t qr, Functor&& functor) {
    return FindLastImpl(ql, qr, std::move(functor), 0u, 0u, N_);
  }

 private:
  void Apply(std::size_t x, Tag tag) {
    Infos_[x].Apply(tag);
    Tags_[x].Apply(tag);
  }

  void Push(std::size_t x) {
    Apply(2 * x + 1, Tags_[x]);
    Apply(2 * x + 2, Tags_[x]);
    Tags_[x] = Tag{};
  }

  void Pull(std::size_t x) {
    Infos_[x] = Infos_[2 * x + 1] + Infos_[2 * x + 2];
  }

  void ModifyImpl(std::size_t pos, Info info, std::size_t x, std::size_t lx, std::size_t rx) {
    if (rx - lx == 1u) {
      Infos_[x] = info;
      return;
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;
    if (pos < mid) {
      ModifyImpl(pos, info, 2 * x + 1, lx, mid);
    } else {
      ModifyImpl(pos, info, 2 * x + 2, mid, rx);
    }
    Pull(x);
  }

  void ModifyImpl(std::size_t ql, std::size_t qr, Tag tag, std::size_t x, std::size_t lx, std::size_t rx) {
    if (ql >= rx || qr <= lx) {
      return;
    }
    if (ql <= lx && rx <= qr) {
      Apply(x, tag);
      return;
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;
    ModifyImpl(ql, qr, tag, 2 * x + 1, lx, mid);
    ModifyImpl(ql, qr, tag, 2 * x + 2, mid, rx);
    Pull(x);
  }

  Info QueryImpl(std::size_t ql, std::size_t qr, std::size_t x, std::size_t lx, std::size_t rx) {
    if (ql >= rx || qr <= lx) {
      return {};
    }
    if (ql <= lx && rx <= qr) {
      return Infos_[x];
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;
    return QueryImpl(ql, qr, 2 * x + 1, lx, mid) + QueryImpl(ql, qr, 2 * x + 2, mid, rx);
  }

  template <typename Functor>
  std::size_t FindFirstImpl(
    std::size_t ql, std::size_t qr, Functor&& functor,
    std::size_t x, std::size_t lx, std::size_t rx
  ) {
    if (lx >= qr || rx <= ql || !functor(Infos_[x])) {
      return kNpos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;

    auto res = FindFirstImpl(ql, qr, std::move(functor), 2 * x + 1, lx, mid);
    if (res == kNpos) {
      res = FindFirstImpl(ql, qr, std::move(functor), 2 * x + 2, mid, rx);
    }
    return res;
  }
  template <typename Functor>
  std::size_t FindLastImpl(
    std::size_t ql, std::size_t qr, Functor&& functor,
    std::size_t x, std::size_t lx, std::size_t rx
  ) {
    if (lx >= qr || rx <= ql || !functor(Infos_[x])) {
      return kNpos;
    }
    if (rx - lx == 1u) {
      return lx;
    }
    Push(x);
    const auto mid = lx + (rx - lx) / 2;

    auto res = FindLastImpl(ql, qr, std::move(functor), 2 * x + 2, mid, rx);
    if (res == kNpos) {
      res = FindLastImpl(ql, qr, std::move(functor), 2 * x + 1, lx, mid);
    }
    return res;
  }

 private:
  std::size_t N_{0};
  std::vector<Info> Infos_;
  std::vector<Tag> Tags_;
};

class Tag {
 public:
  void Apply(auto&& tag) {
    Val += tag.Val;
  }

 public:
  Mint Val = 0;
};

class Info {
 public:
  void Apply(const Tag& tag) {
    Val += tag.Val;
  }

 public:
  Mint Val = 0;
};
Info operator+(const Info& lhs, const Info& rhs) {
  return {lhs.Val + rhs.Val};
}

void Solve() {
  int n, d;
  Scan(n, d);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  auto bs = as;
  std::ranges::sort(bs);
  bs.erase(std::ranges::unique(bs).begin(), bs.end());
  for (int i = 0; i < n; ++i) {
    as[i] = std::ranges::lower_bound(bs, as[i]) - bs.begin();
  }

  const auto m = int(bs.size());
  LazySegmentTree<Info, Tag> st(m);

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
