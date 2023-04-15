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

const int N = 100010, Q = 100010, BLOCK_SIZE = 1000, LG = 21, BLOCK_BOUND = (N + BLOCK_SIZE - 1) / BLOCK_SIZE + 1;

struct Query {
  int l, r, k, id, lca;
};

vector<int> g[N];
int up[N][LG];
int val[N], tin[N], tout[N], time2v[2 * N], node_freq[N], cnt[N], blk_cnt[BLOCK_BOUND], ans[Q], sorted_id[N];
pair<int, int> val_id_sorted[N];
Query queries[Q];

int timer;
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

void add(int pos) {
  ++cnt[pos];
  ++blk_cnt[pos / BLOCK_SIZE];
}
void remove(int pos) {
  --cnt[pos];
  --blk_cnt[pos / BLOCK_SIZE];
}
int kth(int k) {
  int i = 0;
  for (; i < BLOCK_BOUND; ++i) {
    if (k - blk_cnt[i] <= 0) break ;
    k -= blk_cnt[i];
  }
  i *= BLOCK_SIZE;
  for (; i < N; ++i) {
    if (k - cnt[i] <= 0) {
      return i;
    }
    k -= cnt[i];
  }
  assert(false);
}

void add_mo(int time) {
  auto v = time2v[time];
  auto id = sorted_id[v];
  // cout << "add " << v << ' ' << id << '\n';
  if (++node_freq[v] == 2) remove(id);
  else if (node_freq[v] == 1) add(id);
  else assert(false);
}
void remove_mo(int time) {
  auto v = time2v[time];
  auto id = sorted_id[v];
  // cout << "remove " << v << ' ' << id << '\n';
  if (--node_freq[v] == 1) add(id);
  else if (node_freq[v] == 0) remove(id);
  else assert(false);
}

void solve() {
  ::memset(node_freq, 0, sizeof node_freq);
  ::memset(cnt, 0, sizeof cnt);
  ::memset(blk_cnt, 0, sizeof blk_cnt);
  ::memset(up, -1, sizeof up);

  int n, q; cin >> n >> q;
  for (int v = 0; v < n; ++v) {
    cin >> val[v];
    val_id_sorted[v] = make_pair(val[v], v);
  }
  sort(val_id_sorted, val_id_sorted + n);

  for (int i = 0; i < n; ++i) {
    sorted_id[val_id_sorted[i].second] = i;
  }

  for (int i = 0; i + 1 < n; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  timer = 0;
  dfs(0, -1);

  // for (int v = 0; v < n; ++v) cout << v + 1 << ' ' << tin[v] << ' ' << tout[v] << '\n';

  for (int i = 0; i < q; ++i) {
    int u, v;
    cin >> u >> v >> queries[i].k;
    --u, --v;
    queries[i].id = i;
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
  }
  sort(queries, queries + q, cmp);

  int cur_l = 0, cur_r = -1;
  for (int i = 0; i < q; ++i) {
    auto l = queries[i].l;
    auto r = queries[i].r;
    auto k = queries[i].k;
    auto id = queries[i].id;
    auto lca = queries[i].lca;

    while (cur_l > l) add_mo(--cur_l);
    while (cur_r < r) add_mo(++cur_r);
    while (cur_l < l) remove_mo(cur_l++);
    while (cur_r > r) remove_mo(cur_r--);

    if (~lca) add(sorted_id[lca]);
    // for (int j = 0; j < n; ++j) cout << cnt[j] << " \n"[j + 1 == n];
    ans[id] = val_id_sorted[kth(k)].first;
    if (~lca) remove(sorted_id[lca]);
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
