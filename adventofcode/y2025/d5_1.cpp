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
  std::vector<std::pair<int64_t, int64_t>> as;
  for (std::string s; ; s.clear()) {
    std::getline(std::cin, s);
    if (s.empty()) {
      break;
    }
    const auto pos = s.find('-');
    assert(pos != std::string::npos);
    auto parse = [&s](const int l, const int r) {
      auto x = 0LL;
      for (int i = l; i <= r; ++i) {
        assert(std::isdigit(s[i]) != 0);
        x = x * 10 + s[i] - '0';
      }
      return x;
    };
    as.emplace_back(parse(0, pos - 1), parse(pos + 1, s.size() - 1));
    assert(as.back().first <= as.back().second);
  }
  dbg(as.size());
  {
    std::ranges::sort(as);
    decltype(as) bs;
    for (int i = 0; i < as.size(); ++i) {
      auto [l, r] = as[i];
      while (i + 1 < as.size() && as[i + 1].first <= r) {
        r = std::max(r, as[++i].second);
      }
      assert(l <= r);
      bs.emplace_back(l, r);
    }
    std::swap(as, bs);
  }
  auto ret = 0, z = 0;
  for (std::string s; ; s.clear()) {
    std::getline(std::cin, s);
    if (s.empty()) {
      break;
    }
    ++z;
    auto x = 0LL;
    for (auto c : s) {
      assert(std::isdigit(c) != 0);
      x = x * 10 + c - '0';
    }
    const auto it = std::ranges::lower_bound(as, std::pair(x, 0));
    auto f = false;
    f |= it != as.begin() && std::clamp(x, std::prev(it)->first, std::prev(it)->second) == x;
    f |= it != as.end() && std::clamp(x, it->first, it->second) == x;
    ret += f;
  }
  dbg(z);
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
