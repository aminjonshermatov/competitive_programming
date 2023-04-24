// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

bool check(vector<int> &A) {
  set<int> st;
  size_t s = 0u;
  for (auto x : A) {
    s += x;
    s %= A.size();
    st.emplace(s);
  }
  return st.size() == A.size();
}

pair<bool, vector<int>> fast(int n) {
  vector<int> A(n);
  int l = 0, r = n - 1;
  int lo = 1, hi = n;
  while (l <= r) {
    A[l++] = hi--;
    if (l <= r) {
      A[r--] = hi--;
    }

    if (l < r) {
      A[l++] = lo++;
    }
    if (l <= r) {
      A[r--] = lo++;
    }
  }

  return {check(A), A};
}

pair<bool, vector<int>> slow(int n) {
  vector<int> cur;
  bool ok = false;
  vector<bool> used(n, false);
  auto rec = [&](auto f) -> void {
    if (cur.size() >= n) {
      if (check(cur)) {
        dbg(cur);
      }
      ok = check(cur);
      return ;
    }
    for (int x = 1; x <= n; ++x) {
      if (used[x - 1]) continue ;
      cur.emplace_back(x);
      used[x - 1] = true;
      f(f);
      used[x - 1] = false;
      if (ok) return ;
      cur.pop_back();
    }
  };
  rec(rec);

  return {check(cur) && cur.size() == n, cur};
}

void solve() {
  int n; cin >> n;

  auto [ok, A] = fast(n);
  if (!ok) {
    cout << "-1\n";
    return ;
  }
  for (auto x : A) cout << x << ' '; cout << '\n';
  return ;
  for (int i = 1; i <= 10; ++i) {
    auto [ok1, A1] = fast(i);
    auto [ok2, A2] = slow(i);
    if (ok1 != ok2) {
      cout << i << ' ' << ok1 << ' ' << ok2 << '\n';
      for (auto x : A1) cout << x << ' '; cout << '\n';
      for (auto x : A2) cout << x << ' '; cout << '\n';
      return ;
    }
  }
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
}
