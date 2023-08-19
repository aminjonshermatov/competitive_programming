#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m; cin >> n >> m;
  vector<string> g(n);
  vector<array<int, 26>> rs(n), cs(m);
  vector<int> r_cnt(n, m), c_cnt(m, n);
  for (int i = 0; i < n; ++i) {
    cin >> g[i];
    for (int j = 0; j < m; ++j) {
      ++rs[i][g[i][j] - 'a'];
      ++cs[j][g[i][j] - 'a'];
    }
  }
  set<int> not_used_rows, not_used_cols;
  for (int i = 0; i < n; ++i) {
    not_used_rows.emplace(i);
  }
  for (int i = 0; i < m; ++i) {
    not_used_cols.emplace(i);
  }
  while (true) {
    vector<pair<int, int>> to_rem_row, to_rem_col;
    auto R = [&]() -> void {
      for (auto i : not_used_rows) {
        for (int ch = 0; ch < 26 && r_cnt[i] > 1; ++ch) {
          if (r_cnt[i] == rs[i][ch]) {
            to_rem_row.emplace_back(i, ch);
            break;
          }
        }
      }
    };
    auto C = [&]() -> void {
      for (auto j : not_used_cols) {
        for (int ch = 0; ch < 26 && c_cnt[j] > 1; ++ch) {
          if (c_cnt[j] == cs[j][ch]) {
            to_rem_col.emplace_back(j, ch);
            break;
          }
        }
      }
    };

    R();
    C();
    if (to_rem_row.empty() && to_rem_col.empty()) break;
    for (auto [i, ch] : to_rem_row) {
      for (auto j : not_used_cols) {
        if (cs[j][ch] > 0) {
          --cs[j][ch];
          --c_cnt[j];
        }
      }
      r_cnt[i] = 0;
    }
    for (auto [j, ch] : to_rem_col) {
      for (auto i : not_used_rows) {
        if (rs[i][ch] > 0) {
          --rs[i][ch];
          --r_cnt[i];
        }
      }
      c_cnt[j] = 0;
    }
    for (auto [i, _] : to_rem_row) {
      not_used_rows.erase(i);
    }
    for (auto [j, _] : to_rem_col) {
      not_used_cols.erase(j);
    }
  }
  for (int i = 0; i < n; ++i) {
    r_cnt[i] = max(r_cnt[i], 0);
  }
  for (int j = 0; j < m; ++j) {
    c_cnt[j] = max(c_cnt[j], 0);
  }
  dbg(r_cnt);
  dbg(c_cnt);
  assert(accumulate(r_cnt.begin(), r_cnt.end(), 0) == accumulate(c_cnt.begin(), c_cnt.end(), 0));
  cout << accumulate(r_cnt.begin(), r_cnt.end(), 0) << '\n';
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
