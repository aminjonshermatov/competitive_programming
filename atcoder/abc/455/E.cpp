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

  // pa[r] - pa[l-1] != pb[r] - pb[l-1] != pc[r] - pc[l-1]
  auto ret = n * 1LL * (n + 1) / 2;
  dbg(ret);
  { // a,b
    std::map<int, int> cnt;
    auto p = 0;
    ++cnt[p];
    for (int i = 0; i < n; ++i) {
      p += s[i] == 'A';
      p -= s[i] == 'B';
      ret -= cnt[p]++;
    }
  }
  { // b,c
    std::map<int, int> cnt;
    auto p = 0;
    ++cnt[p];
    for (int i = 0; i < n; ++i) {
      p += s[i] == 'B';
      p -= s[i] == 'C';
      ret -= cnt[p]++;
    }
  }

  { // a,c
    std::map<int, int> cnt;
    auto p = 0;
    ++cnt[p];
    for (int i = 0; i < n; ++i) {
      p += s[i] == 'A';
      p -= s[i] == 'C';
      ret -= cnt[p]++;
    }
  }
  { // a,b,c
    std::map<std::tuple<int, int, int>, int> cnt;
    ++cnt[std::tuple(0, 0, 0)];
    auto pa = 0, pb = 0, pc = 0;
    for (int i = 0; i < n; ++i) {
      pa += s[i] == 'A';
      pb += s[i] == 'B';
      pc += s[i] == 'C';
      ret += (cnt[std::tuple(pa - pb, pb - pc, pa - pc)]++) * 2;
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
