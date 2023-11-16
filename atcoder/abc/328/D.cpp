#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s;
  std::cin >> s;

  std::string st;
  for (auto c : s) {
    auto sz = int(st.size());
    if (st.size() > 1 && c == 'C' && st[sz - 1] == 'B' && st[sz - 2] == 'A') {
      st.pop_back();
      st.pop_back();
      continue;
    } else {
      st.push_back(c);
    }
  }
  std::cout << st << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}