#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <typename T> struct FenwickTreePointUpdateRangeQuery {
  int n = 0;
  std::vector<T> bit;

  FenwickTreePointUpdateRangeQuery() = default;
  explicit FenwickTreePointUpdateRangeQuery(int n_) : n(n_), bit(n_, T(0))  { }
  template<typename U> explicit FenwickTreePointUpdateRangeQuery(const std::vector<U> &A) : n(A.size()), bit(A.size(), T(0)) {
    for (auto idx = 0u; idx < n; ++idx) {
      modify(idx, A[idx]);
    }
  }

  void init(int n_) {
    n = n_;
    bit.assign(n, T(0));
  }

  auto modify(int idx, T val) -> void {
    for (; idx < n; idx = idx | (idx + 1)) {
      bit[idx] += val;
    }
  }

  [[nodiscard]] auto query(int idx) const -> T {
    T ret = T(0);
    for (; idx >= 0; idx = (idx & (idx + 1)) - 1) {
      ret += bit[idx];
    }
    return ret;
  }

  [[nodiscard]] auto query(int l, int r) const -> T { // [l, r)
    return query(r - 1) - query(l - 1);
  }
};

struct Point2D {
  int x, y;
};
struct Line {
  Point2D a, b;
};

enum class EType : uint8_t {
  kAdd,
  kQuery,
  kRemove,
};
struct Event {
  int y, xlo, xhi;
  EType type;
  auto operator<=>(const Event&) const = default;
};

void solve() {
  int n;
  scan(n);
  std::vector<int> xs;
  xs.reserve(2 * n);
  std::vector<Line> lines(n);
  for (auto& [a, b] : lines) {
    scan(a.x, a.y);
    scan(b.x, b.y);
    xs.emplace_back(a.x), xs.emplace_back(b.x);
  }
  std::ranges::sort(xs);
  xs.erase(std::ranges::unique(xs).begin(), xs.end());

  std::vector<Event> es;
  es.reserve(2 * n);
  for (auto&& [a, b] : lines) {
    a.x = int(std::ranges::lower_bound(xs, a.x) - xs.begin());
    b.x = int(std::ranges::lower_bound(xs, b.x) - xs.begin());

    if (a.y == b.y) {
      es.emplace_back(a.y, a.x, b.x, EType::kQuery);
    } else {
      es.emplace_back(a.y, a.x, b.x, EType::kAdd);
      es.emplace_back(b.y, a.x, b.x, EType::kRemove);
    }
  }
  std::ranges::sort(es, std::less<>{});

  FenwickTreePointUpdateRangeQuery<int> cnt_x(xs.size());
  int64_t tot = 0;
  for ([[maybe_unused]] auto&& [_, xlo, xhi, type] : es) {
    if (type == EType::kAdd || type == EType::kRemove) {
      cnt_x.modify(xlo, type == EType::kAdd ? +1 : -1);
    } else if (type == EType::kQuery) {
      tot += cnt_x.query(xlo, xhi + 1);
    } else {
      assert(false);
    }
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}