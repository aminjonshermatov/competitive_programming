#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int B = 320;

void solve() {
  int n, m; cin >> n >> m;
  vector<pair<int, int>> segs(m);
  for (auto &[l, r] : segs) {
    cin >> l >> r;
    --l, --r;
  }
  sort(segs.begin(), segs.end());
  segs.resize(unique(segs.begin(), segs.end()) - segs.begin());

  vector<int> when(n, -1);
  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    int x; cin >> x;
    --x;
    if (~when[x]) continue;
    when[x] = i;
  }

  const int nb = (n + B - 1) / B;
  vector<int> cnt(n, 0), blk_cnt(nb, 0);
  auto add = [&](int id) {
    if (when[id] == -1) return;
    ++cnt[when[id]];
    ++blk_cnt[when[id] / B];
  };
  auto rmv = [&](int id) {
    if (when[id] == -1) return;
    --cnt[when[id]];
    --blk_cnt[when[id] / B];
  };
  auto get_ans = [&](int k) -> int {
    int i = 0;
    for (; i < nb; ++i) {
      if (k - blk_cnt[i] <= 0) break ;
      k -= blk_cnt[i];
    }
    i *= B;
    for (; i < n; ++i) {
      if (k - cnt[i] <= 0) {
        return i;
      }
      k -= cnt[i];
    }
    return 1e9;
  };
  sort(segs.begin(), segs.end(), [](const auto &lhs, const auto &rhs) {
    auto ll = lhs;
    auto rr = rhs;
    ll.first /= B; ll.second /= B;
    rr.first /= B; rr.second /= B;
    return ll < rr;
  });
  int cur_l = 0, cur_r = -1, ans = 1e9;

  for (auto [l, r] : segs) {
    while (cur_l > l) add(--cur_l);
    while (cur_r < r) add(++cur_r);
    while (cur_l < l) rmv(cur_l++);
    while (cur_r > r) rmv(cur_r--);
    ans = min(ans, get_ans((r - l + 1) / 2 + 1));
  }
  cout << (ans == 1e9 ? -1 : ans + 1) << '\n';
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
