#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

struct MachineInfo final {
  int Mask = 0, Width = 0;
  std::vector<std::vector<int>> Buttons;
  std::vector<int> Voltages;
};

void Solve() {
  std::vector<MachineInfo> infos;
  for (std::string s; ; s.clear()) {
    std::getline(std::cin, s);
    if (s.empty()) {
      break;
    }
    MachineInfo info{};
    auto pos = 0;
    {
      assert(s[pos] == '[');
      const auto end = s.find(']', pos + 1);
      assert(end != std::string::npos);
      info.Width = end - pos - 1;
      for (int i = end - 1; i > pos; --i) {
        info.Mask = (info.Mask << 1) | (s[i] == '#');
      }
      pos = end + 1;
    }
    auto trim = [&] {
      while (pos < s.size() && std::isspace(s[pos]) != 0) {
        ++pos;
      }
    };
    for (trim(); pos < s.size() && s[pos] == '('; trim()) {
      assert(s[pos] == '(');
      const auto end = s.find(')', pos + 1);
      assert(end != std::string::npos);
      info.Buttons.emplace_back();
      for (int i = pos + 1, x = 0; i <= end; ++i) {
        if (i == end || s[i] == ',') {
          info.Buttons.back().emplace_back(std::exchange(x, 0));
        } else {
          assert(std::isdigit(s[i]) != 0);
          x = x * 10 + s[i] - '0';
        }
      }
      pos = end + 1;
    }
    trim();
    assert(s[pos] == '{');
    const auto end = s.find('}', pos + 1);
    assert(end != std::string::npos);
    for (int i = pos + 1, x = 0; i <= end; ++i) {
      if (i == end || s[i] == ',') {
        info.Voltages.emplace_back(std::exchange(x, 0));
      } else {
        assert(std::isdigit(s[i]) != 0);
        x = x * 10 + s[i] - '0';
      }
    }
    assert(end + 1 == s.size() && s[end] == '}');
    infos.emplace_back(info);
  }

  auto ret = 0;
  for (const auto& info : infos) {
    constexpr auto kInf = std::numeric_limits<int>::max() / 2;
    std::vector dp(1 << info.Width, kInf);
    dp[0] = 0;
    for (const auto bs : info.Buttons) {
      auto mask = 0;
      for (const auto i : bs) {
        assert(i < info.Width);
        mask |= 1 << i;
      }
      assert(mask < (1 << info.Width));
      auto ndp = dp;
      for (int x = 0; x < (1 << info.Width); ++x) {
        ndp[x ^ mask] = std::min(ndp[x ^ mask], dp[x] + 1);
      }
      std::swap(dp, ndp);
    }
    ret += dp.at(info.Mask);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
