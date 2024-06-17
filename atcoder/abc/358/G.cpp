#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

std::array di{0, 0, 0, +1, -1};
std::array dj{0, +1, -1, 0, 0};

bool imax(auto&& a, auto&& b) noexcept {
  return a < b && (a = b, true);
}

void solve() {
  int h, w, k;
  scan(h, w, k);
  int si, sj;
  scan(si, sj);
  --si, --sj;
  std::vector g(h, std::vector<i64>(w));
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      scan(g[i][j]);
    }
  }

  auto ok = [&](const int i, const int j) {
    return std::clamp(i, 0, h - 1) == i && std::clamp(j, 0, w - 1) == j;
  };

  const auto lim = std::min(k, h * w);
  constexpr auto inf = std::numeric_limits<i64>::max() / 3;
  std::vector dp(h, std::vector(w, std::vector(lim + 1, -inf)));
  dp[si][sj][0] = 0;

  for (int len = 0; len < lim; ++len) {
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        for (int z = 0; z < 5; ++z) {
          const auto ni = i + di[z];
          const auto nj = j + dj[z];
          if (!ok(ni, nj)) {
            continue;
          }
          imax(dp[ni][nj][len + 1], dp[i][j][len] + g[ni][nj]);
        }
      }
    }
  }

  i64 best{};
  for (int len = 0; len <= lim; ++len) {
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        if (dp[i][j][len] != -inf) {
          imax(best, dp[i][j][len] + (k - len) * 1L * g[i][j]);
        }
      }
    }
  }
  println(best);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
