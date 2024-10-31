#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n, X;
  scan(n, X);

  std::vector<int> ret;
  int score = 0;

  std::set<int> may;
  may.emplace(X - 1);
  may.emplace(X);
  may.emplace(X + 1);
  may.emplace(n / 2 - 1);
  may.emplace(n / 2);
  may.emplace(n / 2 + 1);
  while (!may.empty() && *may.begin() < 1) {
    may.erase(may.begin());
  }
  while (!may.empty() && *may.rbegin() > n) {
    may.erase(std::prev(may.end()));
  }
  for (auto beg : may) {
    auto work = [&](int sgn) {
      std::vector<int> loc;
      std::vector<bool> used(n + 1, false);
      loc.emplace_back(X);
      used[X] = true;
      if (X != beg) {
        loc.emplace_back(beg);
        used[beg] = true;
      }
      for (int x = 1, pos = beg; std::clamp(pos + x * sgn, 1, n) == pos + x * sgn; ++x, pos += x * sgn, sgn = sgn == 1 ? -1 : 1) {
        while (std::clamp(pos + x * sgn, 1, n) == pos + sgn * x && used[pos + x * sgn]) {
          ++x;
        }
        if (std::clamp(pos + x * sgn, 1, n) == pos + sgn * x) {
          loc.emplace_back(pos + x * sgn);
          used[loc.back()] = true;
        } else {
          break;
        }
      }
      auto sc = static_cast<int>(loc.size());
      if (beg == 1) {
        dbg(loc);
      }
      for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
          loc.emplace_back(i);
        }
      }
      if (loc.size() != n) {
        dbg(sgn,loc);
      }
      assert(loc.size() == n);
      assert(loc.front() == X);
      assert(std::ranges::min(loc) == 1);
      assert(std::ranges::max(loc) == n);
      assert(std::set(loc.begin(), loc.end()).size() == n);
      return std::pair(loc, sc);
    };
    if (const auto [a, b] = work(+1); b > score) {
      dbg("fuck",a,b,beg,+1);
      score = b;
      ret = a;
    }
    if (const auto [a, b] = work(-1); b > score) {
      dbg("fuck",a,b,beg,-1);
      score = b;
      ret = a;
    }
    std::vector<int> lhs(beg - (X <= beg), -1), rhs(n - beg - (X > beg), -1);
    std::vector<int> loc;
    std::vector<bool> used(n + 1, false);
    loc.emplace_back(X);
    used[X] = true;
    int x = 1;
    for (std::size_t i = 0; i < lhs.size(); ++i, ++x) {
      if (used[x]) {
        ++x;
      }
      lhs[i] = x;
      used[x] = true;
    }
    for (std::size_t i = 0; i < rhs.size(); ++i, ++x) {
      if (used[x]) {
        ++x;
      }
      rhs[i] = x;
      used[x] = true;
    }
    assert(std::ranges::none_of(lhs, [](auto z) { return z == -1; }));
    assert(std::ranges::none_of(rhs, [](auto z) { return z == -1; }));
    assert(std::ranges::all_of(used | std::views::drop(1), std::identity{}));
    std::vector<int> lis;
    for (auto i = std::ssize(lhs) - 1, j = 0l, f = 1l; i >= 0 || j < rhs.size(); f ^= 1) {
      if (i >= 0 && j < rhs.size()) {
        loc.emplace_back(f ? lhs[i--] : rhs[j++]);
      } else if (i >= 0) {
        loc.emplace_back(lhs[i--]);
      } else {
        loc.emplace_back(rhs[j++]);
      }
      const auto cand = std::abs(loc.back() - loc[loc.size() - 2]);
      if (auto it = std::ranges::upper_bound(lis, cand); it != lis.end()) {
        *it = cand;
      } else {
        lis.emplace_back(cand);
      }
    }
    assert(loc.size() == n);
    assert(loc.front() == X);
    assert(std::ranges::min(loc) == 1);
    assert(std::ranges::max(loc) == n);
    assert(std::set(loc.begin(), loc.end()).size() == n);
    if (score < lis.size()) {
      dbg(lis);
      score = lis.size();
      ret = loc;
    }
  }
  for (auto z : ret) {
    print(z);
  }
  println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}