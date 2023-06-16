#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int B = 320;

struct Query {
  int l, r, k, id;
  bool operator<(const Query &other) const {
    return pair(l / B, r) < pair(other.l / B, other.r);
  }
};

void solve() {
  int n; cin >> n;
  vector<int> as(n);
  for (auto &a : as) cin >> a;
  auto as_sorted = as;
  sort(as_sorted.begin(), as_sorted.end());
  as_sorted.resize(unique(as_sorted.begin(), as_sorted.end()) - as_sorted.begin());

  for (auto &a : as) {
    a = int(lower_bound(as_sorted.begin(), as_sorted.end(), a) - as_sorted.begin());
  }

  int q; cin >> q;
  vector<Query> qs(q);
  for (int i = 0; auto &[l, r, k, id] : qs) {
    cin >> l >> r >> k;
    --l, --r;
    id = i++;
  }

  const int nn = static_cast<int>(as_sorted.size());
  vector<int> freq(nn, 0), blk_freq((nn + B - 1) / B, 0);
  auto add = [&](int idx) -> void {
    ++freq[as[idx]];
    ++blk_freq[as[idx] / B];
  };
  auto rmv = [&](int idx) -> void {
    --freq[as[idx]];
    --blk_freq[as[idx] / B];
  };

  vector<vector<int>> ans(q);
  auto prepare_ans = [&](int id, int k) -> void {
    ans[id].reserve(k);
    for (int ib = 0; k > 0; ++ib) {
      if (blk_freq[ib] == 0) continue;
      for (int i = ib * B; i < min(nn, (ib + 1) * B) && k > 0; ++i) {
        for (int j = 0; j < freq[i] && k > 0; ++j) {
          ans[id].emplace_back(as_sorted[i]);
          --k;
        }
      }
    }
  };

  sort(qs.begin(), qs.end());
  int cur_l = 0, cur_r = -1;
  for (auto [l, r, k, id] : qs) {
    while (cur_l > l) add(--cur_l);
    while (cur_r < r) add(++cur_r);
    while (cur_l < l) rmv(cur_l++);
    while (cur_r > r) rmv(cur_r--);
    prepare_ans(id, k);
  }

  for (int i = 0; i < q; ++i) {
    for (auto x : ans[i]) {
      cout << x << ' ';
    }
    cout << '\n';
  }
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
