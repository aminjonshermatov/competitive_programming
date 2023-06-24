#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  stack<pair<char, bool>> st;
  for (int i = 0; i < n; ++i) {
    char ch; cin >> ch;
    if (ch == ')' && !st.empty() && st.top().second) {
      while (st.top().first != '(') {
        st.pop();
      }
      assert(!st.empty() && st.top().first == '(');
      st.pop();
    } else {
      st.emplace(ch, st.empty() ? ch == '(' : st.top().second || ch == '(');
    }
  }
  string ans;
  while (!st.empty()) {
    ans.push_back(st.top().first);
    st.pop();
  }
  reverse(ans.begin(), ans.end());
  cout << ans << '\n';
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
