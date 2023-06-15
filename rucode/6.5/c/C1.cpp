#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int B = 223; // sqrt(5e4)

struct Update {
  int pos, v, prv;
  Update(int pos_, int v_, int prv_) : pos(pos_), v(v_), prv(prv_) { }
};
struct Query {
  int l, r, t, id;
  Query(int l_, int r_, int t_, int id_) : l(l_), r(r_), t(t_), id(id_) { }
  bool operator<(const Query &oth) const {
    return tuple(l / B, r / B, t) < tuple(oth.l / B, oth.r / B, oth.t);
  }
};

void solve() {
  int n; cin >> n;
  vector<int> as(n);
  for (auto &a : as) cin >> a;
  vector<int> as_sorted = as;
  vector<int> last_val = as;

  int q; cin >> q;

  vector<Update> upds;
  vector<Query> qrs;
  for (int i = 0; i < q; ++i) {
    char cmd; cin >> cmd;
    if (cmd == 'U') {
      int u, v; cin >> u >> v;
      --u;
      upds.emplace_back(u, v, last_val[u]);
      last_val[u] = v;
      as_sorted.emplace_back(v);
    } else if (cmd == 'Q') {
      int l, r; cin >> l >> r;
      --l, --r;
      auto usz = int(upds.size()) - 1;
      auto qsz = qrs.size();
      qrs.emplace_back(l, r, usz, qsz);
    } else {
      assert(false);
    }
  }

  sort(as_sorted.begin(), as_sorted.end());
  as_sorted.resize(unique(as_sorted.begin(), as_sorted.end()) - as_sorted.begin());
  for (auto &a : as) {
    a = int(lower_bound(as_sorted.begin(), as_sorted.end(), a) - as_sorted.begin());
  }
  for (auto &upd : upds) {
    upd.v = int(lower_bound(as_sorted.begin(), as_sorted.end(), upd.v) - as_sorted.begin());
    upd.prv = int(lower_bound(as_sorted.begin(), as_sorted.end(), upd.prv) - as_sorted.begin());
  }
  int64_t sum = 0;
  vector<int> freq(as_sorted.size(), 0);
  auto add = [&](int val) -> void {
    if (++freq[val] == 1) sum += as_sorted[val];
  };
  auto remove = [&](int val) -> void {
    if (--freq[val] == 0) sum -= as_sorted[val];
  };
  auto addTime = [&](int t, int l, int r) -> void {
    if (l <= upds[t].pos && upds[t].pos <= r) {
      remove(upds[t].prv);
      add(upds[t].v);
    }
    as[upds[t].pos] = upds[t].v;
  };
  auto removeTime = [&](int t, int l, int r) -> void {
    if (l <= upds[t].pos && upds[t].pos <= r) {
      remove(upds[t].v);
      add(upds[t].prv);
    }
    as[upds[t].pos] = upds[t].prv;
  };


  sort(qrs.begin(), qrs.end());
  vector<int64_t> ans(qrs.size());

  int cur_l = 0, cur_r = -1, cur_t = -1;
  for (auto &[l, r, t, id] : qrs) {
    while (cur_l > l) add(as[--cur_l]);
    while (cur_r < r) add(as[++cur_r]);
    while (cur_l < l) remove(as[cur_l++]);
    while (cur_r > r) remove(as[cur_r--]);
    while (cur_t < t) addTime(++cur_t, l, r);
    while (cur_t > t) removeTime(cur_t--, l, r);
    ans[id] = sum;
  }
  for (auto s : ans) {
    cout << s << '\n';
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
