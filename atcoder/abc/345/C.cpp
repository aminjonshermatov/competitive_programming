#include <bits/stdc++.h>
// #include "stress/utils.h"

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s;
  std::cin >> s;
  // s = utils::randomString(4, 'a', 'z');
  std::array<int, 26> cnt{};
  for (auto c : s) {
    ++cnt[c - 'a'];
  }
  const auto n = int(s.size());
  int tot = 0;
  bool any = false;
  for (int i = 0; i < n; ++i) {
    --cnt[s[i] - 'a'];
    for (int c = 0; c < 26; ++c) {
      if (cnt[c] == 0 || c == (s[i] - 'a')) {
        continue;
      }
      tot += cnt[c];
    }
    if (cnt[s[i] - 'a'] > 0) {
      tot += !any;
      any = true;
    }
  }
  if (false) {
    std::set<std::string> xs;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        std::swap(s[i], s[j]);
        xs.emplace(s);
        std::swap(s[i], s[j]);
      }
    }
    if (xs.size() != tot) {
      std::cerr << s << '\n';
      dbg(tot, xs.size(), xs);
      exit(1);
    }
  }
  std::cout << tot << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}