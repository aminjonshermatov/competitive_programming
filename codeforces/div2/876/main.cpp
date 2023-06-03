#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

bool check(vector<int> path, vector<int> exp) {
  vector<int> ans;
  if (path.size() != exp.size()) return false;
  for (auto p : path) {
    if (p > ans.size()) {
      return false;
    }
    for (int i = 0; i < p; ++i) ans[i] ^= 1;
    ans.insert(ans.begin() + p, 0);
  }
  for (int i = 0; i < exp.size(); ++i) {
    if (exp[i] != ans[i]) {
      return false;
    }
  }
  return true;
}

vector<int> slow(vector<int> A) {
  vector<int> ans;
  auto rec = [&](auto &f) -> bool {
    if (ans.size() >= A.size()) {
      if (check(ans, A)) return true;
      return false;
    }
    for (int i = 0; i <= A.size(); ++i) {
      ans.emplace_back(i);
      if (f(f)) return true;
      ans.pop_back();
    }
    return false;
  };
  if (rec(rec)) return ans;
  return {};
}

void solve() {
  int n; cin >> n;
  vector<int> A(n);
  for (auto &a : A) cin >> a;
  auto nz = count(A.begin(), A.end(), 0);
  int ez = 0;
  for (int i = n - 1; i >= 0 && A[i] == 0; --i, ++ez) { }
  if ((ez % 2 == 0 && ez != n) || 2 * nz < n) {
    cout << "NO\n";
    return;
  }

  vector<int> ans(n - nz, 0);
  int ptr = n - nz - 1;
  for (int i = n - 1; i >= 0; --i) {
    if (A[i] == 0) {
      ans.push_back(ptr + 1);
    } else {
      --ptr;
    }
  }
  if (!check(ans, A)) {
    cout << "NO\n";
    auto s = slow(A);
    if (check(s, A)) {
      dbg(ans, s, A);
    }
    return;
  }
  ret:
  cout << "YES\n";
  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
