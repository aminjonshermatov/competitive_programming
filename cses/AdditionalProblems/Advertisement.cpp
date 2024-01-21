#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  using i64 = int64_t;
  std::vector<i64> as(n);
  for (auto& a:  as) {
    std::cin >> a;
  }
  std::vector<int> prev_min(n, -1);
  std::stack<int> st;
  for (int i = n - 1; i >= 0; --i) {
    while (!st.empty() && as[st.top()] > as[i]) {
      prev_min[st.top()] = i;
      st.pop();
    }
    st.push(i);
  }
  for (; !st.empty(); st.pop()) { }
  std::vector<int> next_min(n, n);
  for (int i = 0; i < n; ++i) {
    while (!st.empty() && as[st.top()] > as[i]) {
      next_min[st.top()] = i;
      st.pop();
    }
    st.push(i);
  }
  i64 max = 0;
  for (int i = 0; i < n; ++i) {
    max = std::max(max, as[i] * (next_min[i] - prev_min[i] - 1));
  }
  std::cout << max << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}