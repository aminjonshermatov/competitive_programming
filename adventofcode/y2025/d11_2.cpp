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
  std::map<std::string, std::set<std::string>> g;
  for (std::string s; ; s.clear()) {
    std::getline(std::cin, s);
    if (s.empty()) {
      break;
    }
    const auto pos = s.find(':');
    assert(pos != std::string::npos);
    assert(s[pos + 1] == ' ');
    const auto src = s.substr(0, pos);
    for (const auto dst : s.substr(pos + 2, s.size() - pos - 2) | std::ranges::views::split(' ')) {
      g[src].emplace(std::string(dst.data(), dst.size()));
    }
  }

  const std::string kSource  = "svr", kSink = "out";
  dbg(g);
  {
    std::set<std::string> vis;
    [&](this auto dfs, const std::string& v) -> void {
      assert(vis.emplace(v).second);
      vis.emplace(v);
      for (const auto& u : g[v]) {
        if (!vis.contains(u)) {
          dfs(u);
        }
      }
    }(kSource);
    decltype(g) newG;
    for (const auto& [v, us] : g) {
      if (!vis.contains(v)) {
        continue;
      }
      for (const auto& u : us) {
        if (vis.contains(u)) {
          newG[v].emplace(u);
        }
      }
    }
    std::swap(g, newG);
  }
  dbg(g);
  std::vector<std::string> cur;
  std::vector<std::map<std::string, int64_t>> cache(4);
  const auto ret = [&](this auto dfs, const std::string& v, const bool hasDac, const bool hasFft) -> int64_t {
    if (v == kSink) {
      return hasDac && hasFft;
    }
    const auto mask = (int(hasDac) << 1) | int(hasFft);
    if (const auto it = cache[mask].find(v); it != cache[mask].end()) {
      return it->second;
    }
    auto loc = int64_t{0};
    for (const auto& u : g[v]) {
      cur.emplace_back(u);
      loc += dfs(u, hasDac || u == "dac", hasFft || u == "fft");
      cur.pop_back();
    }
    return cache[mask][v] = loc;
  }(kSource, false, false);
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
