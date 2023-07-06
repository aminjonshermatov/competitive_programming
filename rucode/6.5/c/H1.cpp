#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int LG = 21, B = 447;

void solve() {
  int n, q; cin >> n >> q;
  struct Edge { int u, v, w; };
  vector<vector<int>> g(n);
  vector<Edge> es(n - 1);
  for (int i = 0; auto &[u, v, w] : es) {
    cin >> u >> v >> w;
    --u, --v;
    g[u].emplace_back(i);
    g[v].emplace_back(i);
    ++i;
  }

  vector<int> tin(n), tout(n), t2v(2 * n), ws(n, -1);
  vector<vector<int>> jmp(n, vector<int>(LG, -1));
  int timer = 0;
  auto dfs = [&](auto &f, int v, int p) -> void {
    jmp[v][0] = p;
    for (int l = 1; l < LG && ~jmp[v][l - 1]; ++l) {
      jmp[v][l] = jmp[jmp[v][l - 1]][l - 1];
    }

    tin[v] = timer;
    t2v[timer] = v;
    ++timer;

    for (auto i : g[v]) {
      auto u = v ^ es[i].v ^ es[i].u;
      if (u == p) continue;
      ws[u] = es[i].w;
      f(f, u, v);
    }

    tout[v] = timer;
    t2v[timer] = v;
    ++timer;
  };
  dfs(dfs, 0, -1);

  auto is_acc = [&](int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; };
  auto get_lca = [&](int u, int v) {
    if (is_acc(u, v)) return u;
    if (is_acc(v, u)) return v;
    for (int l = LG - 1; l >= 0; --l) {
      if (jmp[u][l] == -1) continue;
      if (!is_acc(jmp[u][l], v)) u = jmp[u][l];
    }
    return jmp[u][0];
  };

  struct Query {
    int l, r, lca, id;
    bool operator<(const Query &other) const {
      return pair(l / B, r / B) < pair(other.l / B, other.r / B);
    }
  };
  vector<Query> qs(q);
  for (int i = 0; auto &[l, r, lca, id] : qs) {
    int u, v; cin >> u >> v;
    --u, --v;
    if (tin[u] > tin[v]) swap(u, v);
    lca = get_lca(u, v);
    if (lca == u) {
      l = tin[u];
    } else {
      l = tout[u];
      lca = -1;
    }
    r = tin[v];
    id = i++;
  }
  sort(qs.begin(), qs.end());

  const int mx = 2 * n;
  const int nb = (mx + B - 1) / B;
  vector<int> mex(mx, 0), blk_mex_bin(nb, 0);
  auto add = [&](int v) -> void {
    if (clamp(ws[v], 0, mx - 1) != ws[v]) return;
    if (++mex[ws[v]] == 1) {
      ++blk_mex_bin[ws[v] / B];
    }
  };
  auto rmv = [&](int v) -> void {
    if (clamp(ws[v], 0, mx - 1) != ws[v]) return;
    if (--mex[ws[v]] == 0) {
      --blk_mex_bin[ws[v] / B];
    }
  };
  auto get_mex = [&]() -> int {
    int ib = 0;
    for (; ib + 1 < nb; ++ib) {
      if (blk_mex_bin[ib] < B) {
        break;
      }
    }
    for (int i = ib * B; i < min((ib + 1) * B, mx); ++i) {
      if (mex[i] == 0) {
        return i;
      }
    }
    assert(false);
  };
  vector<int> node_fr(n, 0);
  auto add_mo = [&](int time) -> void {
    auto v = t2v[time];
    assert(clamp(node_fr[v], 0, 2) == node_fr[v]);
    if (++node_fr[v] == 1) {
      add(v);
    } else if (node_fr[v] == 2) {
      rmv(v);
    }
  };
  auto rmv_mo = [&](int time) -> void {
    auto v = t2v[time];
    assert(clamp(node_fr[v], 0, 2) == node_fr[v]);
    if (--node_fr[v] == 1) {
      add(v);
    } else if (node_fr[v] == 0) {
      rmv(v);
    }
  };

  vector<int> ans(q);
  dbg(tin);
  dbg(tout);
  dbg(t2v);
  int cur_l = 0, cur_r = -1;
  for (auto [l, r, lca, id] : qs) {
    assert(l <= r);
    while (cur_l > l) add_mo(--cur_l);
    while (cur_r < r) add_mo(++cur_r);
    while (cur_l < l) rmv_mo(cur_l++);
    while (cur_r > r) rmv_mo(cur_r--);
    if (~lca) rmv(lca);
    ans[id] = get_mex();
    if (~lca) add(lca);
  }

  for (auto x : ans) {
    cout << x << '\n';
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
