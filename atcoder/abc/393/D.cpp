#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Solve() {
  int n;
  std::string s;
  Scan(n, s);

  std::vector<int64_t> Sum0(n, 0), Cnt0(n, 0), Sum1(n, 0), Cnt1(n, 0);

  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      Sum0[i] += Sum0[i - 1];
      Cnt0[i] += Cnt0[i - 1];
      Sum1[i] += Sum1[i - 1];
      Cnt1[i] += Cnt1[i - 1];
    }
    if (s[i] == '1') {
      Sum1[i] += i;
      ++Cnt1[i];
    } else {
      Sum0[i] += i;
      ++Cnt0[i];
    }
  }
  auto Query = [&](auto&& pf, int lo, int hi) -> int64_t {
    if (lo == hi) {
      return 0;
    }
    return pf[hi - 1] - (lo > 0 ? pf[lo - 1] : 0);
  };
  auto ret = std::numeric_limits<int64_t>::max() / 3;
  const int64_t width = std::ranges::count(s, '1');
  for (int i = 0; i + width <= n; ++i) {
    auto fromL = Query(Cnt1, 0, i);
    auto fromR = Query(Cnt1, i + width, n);

    auto prog = [](int64_t a0, int64_t an) {
      return (a0 + an) * (an - a0 + 1) / 2;
    };
    int64_t loc = 0;
    if (fromL > 0) {
      int lo = 0, hi = width;
      while (hi - lo > 1) {
        const auto mid = std::midpoint(lo, hi);
        (Query(Cnt0, i, i + mid) >= fromL ? hi : lo) = mid;
      }
      loc += prog(i, i + hi - 1) - Query(Sum1, 0, i + hi);
    }
    if (fromR > 0) {
      int lo = 0, hi = width;
      while (hi - lo > 1) {
        const auto mid = std::midpoint(lo, hi);
        (Query(Cnt0, i + width - mid, i + width) >= fromR ? hi : lo) = mid;
      }
      auto rPos = i + width - hi;
      loc += Query(Sum1, rPos, n) - prog(rPos, i + width - 1);
    }
    ret = std::min(ret, loc);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
