//
// Created by aminjon on 4/13/23.
//
// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

const int N = 40010, Q = 100010, LG = 21, BLOCK_SIZE = 200, BLOCK_BOUND = (N + BLOCK_SIZE - 1) / BLOCK_SIZE + 1;

struct Query {
  int l, r, id, lca;
};

vector<int> g[N];
int W[N], timer, up[N][LG], tin[N], tout[N], time2v[2 * N], ans[Q], node_freq[N], w_sorted[N], w_id[N], w_freq[N], cnt;
Query queries[Q];

void dfs(int v, int p) {
  up[v][0] = p;
  for (int l = 1; l < LG && ~up[v][l - 1]; ++l) {
    up[v][l] = up[up[v][l - 1]][l - 1];
  }

  tin[v] = timer;
  time2v[timer] = v;
  ++timer;

  for (auto u : g[v]) {
    if (u == p) continue ;
    dfs(u, v);
  }

  tout[v] = timer;
  time2v[timer] = v;
  ++timer;
}

inline bool is_accessor(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }
int get_lca(int u, int v) {
  if (is_accessor(u, v)) return u;
  if (is_accessor(v, u)) return v;
  for (int l = LG - 1; ~l; --l) {
    if (up[u][l] == -1) continue ;
    if (!is_accessor(up[u][l], v)) u = up[u][l];
  }
  return up[u][0];
}

bool cmp(const Query &lhs, const Query &rhs) {
  auto lb = lhs.l / BLOCK_SIZE;
  auto rb = rhs.l / BLOCK_SIZE;
  if (lb != rb) return lb < rb;
  return lhs.r < rhs.r;
}

void add(int x) {
  if (++w_freq[x] == 1) {
    ++cnt;
  }
}
void remove(int x) {
  assert(w_freq[x] > 0);
  if (--w_freq[x] == 0) {
    --cnt;
  }
}

void add_mo(int time) {
  auto v = time2v[time];
  if (++node_freq[v] == 2) remove(w_id[v]);
  else if (node_freq[v] == 1) add(w_id[v]);
  else assert(false);
}
void remove_mo(int time) {
  auto v = time2v[time];
  if (--node_freq[v] == 1) add(w_id[v]);
  else if (node_freq[v] == 0) remove(w_id[v]);
  else assert(false);
}

void solve() {
  ::memset(up, -1, sizeof up);
  ::memset(node_freq, 0, sizeof node_freq);
  ::memset(w_freq, 0, sizeof w_freq);

  int n, q; cin >> n >> q;
  for (int i = 0; i < n; ++i) {
    cin >> W[i];
    w_sorted[i] = W[i];
  }
  sort(w_sorted, w_sorted + n);
  auto nn = unique(w_sorted, w_sorted + n) - w_sorted;
  for (int i = 0; i < n; ++i) {
    w_id[i] = int(lower_bound(w_sorted, w_sorted + nn, W[i]) - w_sorted);
  }

  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  timer = 0;
  dfs(0, -1);

  for (int i = 0; i < q; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;

    if (tin[u] > tin[v]) swap(u, v);
    auto lca = get_lca(u, v);
    if (lca == u) {
      queries[i].l = tin[u];
      queries[i].lca = -1;
    } else {
      queries[i].l = tout[u];
      queries[i].lca = lca;
    }
    queries[i].r = tin[v];
    queries[i].id = i;
  }

  sort(queries, queries + q, cmp);

  int cur_l = 0, cur_r = -1;
  cnt = 0;
  for (int i = 0; i < q; ++i) {
    auto l = queries[i].l;
    auto r = queries[i].r;
    auto lca = queries[i].lca;
    auto id = queries[i].id;

    while (cur_l > l) add_mo(--cur_l);
    while (cur_r < r) add_mo(++cur_r);
    while (cur_l < l) remove_mo(cur_l++);
    while (cur_r > r) remove_mo(cur_r--);

    ans[id] = cnt;
    if (~lca && !w_freq[w_id[lca]]) ++ans[id];
  }

  for (int i = 0; i < q; ++i) {
    cout << ans[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}
