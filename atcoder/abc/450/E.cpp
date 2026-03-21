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
  std::string x, y;
  Scan(x, y);

  constexpr int64_t kLim = 2E18;
  std::vector<int64_t> lens;
  lens.emplace_back(x.size());
  lens.emplace_back(y.size());
  while (lens[lens.size() - 1] <= kLim - lens[lens.size() - 2]) {
    lens.emplace_back(lens[lens.size() - 2] + lens[lens.size() - 1]);
  }

  std::vector pfX(x.size(), std::array<int64_t, 26>{});
  std::vector pfY(y.size(), std::array<int64_t, 26>{});
  std::vector pfTot(lens.size(), std::array<int64_t, 26>{});
  for (int i = 0; i < x.size(); ++i) {
    if (i > 0) {
      pfX[i] = pfX[i - 1];
    }
    ++pfTot[0][x[i] - 'a'];
    ++pfX[i][x[i] - 'a'];
  }
  for (int i = 0; i < y.size(); ++i) {
    if (i > 0) {
      pfY[i] = pfY[i - 1];
    }
    ++pfTot[1][y[i] - 'a'];
    ++pfY[i][y[i] - 'a'];
  }
  for (int i = 2; i < lens.size(); ++i) {
    for (int c = 0; c < 26; ++c) {
      pfTot[i][c] = pfTot[i - 1][c] + pfTot[i - 2][c];
    }
  }

  auto get = [](const auto& pf, const int l, const int r, const char c) {
    assert(0 <= l && l <= r && r < pf.size());
    return pf[r][c - 'a'] - (l > 0 ? pf[l - 1][c - 'a'] : 0);
  };

  auto go = [&](const int64_t len, const char c) -> int64_t {
    auto id = 0;
    while (lens[id] < len) {
      ++id;
    }
    if (len <= 0) {
      return 0;
    }
    if (len <= x.size()) {
      return get(pfY, 0, len - 1, c);
    }
    assert(id < lens.size() && len <= lens[id]);
    return [&](this auto self, const int b, const int64_t pref) -> int64_t {
      if (pref <= 0) {
        return 0;
      }
      if (b < 2) {
        return get(b == 0 ? pfX : pfY, 0, pref - 1, c);
      }
      if (pref <= lens[b - 1]) {
        return self(b - 1, pref);
      }
      return pfTot[b - 1][c - 'a'] + self(b - 2, pref - lens[b - 1]);
    }(id, len);
  };

  int q;
  Scan(q);
  while (q-- > 0) {
    int64_t l, r;
    char c;
    Scan(l, r, c);

    Println(go(r, c) - go(l - 1, c));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
