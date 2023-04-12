// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

const string FIND{"Find"};
const string NOT_FIND{"NotFind"};
// if BLOCK_SIZE == sqrt(Q) ~= 450 => got TLE
// but if BLOCK_SIZE == 1000 got AC
// WHYYYYYY???
const int BLOCK_SIZE = 1000, N = 100010, Q = 200010, LG = 21;

struct Query {
  int l, r, c, id, lca;
};

vector<int> g[N];
int up[N][LG];
int tin[N], tout[N], time2v[2 * N], node_freq[N], val_freq[N], val[N];
bool ans[Q];
Query queries[Q];

int timer;
void dfs(int v, int p) {
  up[v][0] = p;

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
int lca(int u, int v) {
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

void add(int time) {
  auto v = time2v[time];
  if (++node_freq[v] == 2) --val_freq[val[v]];
  else if (node_freq[v] == 1) ++val_freq[val[v]];
  else assert(false);
}
void remove(int time) {
  auto v = time2v[time];
  if (--node_freq[v] == 1) ++val_freq[val[v]];
  else if (node_freq[v] == 0) --val_freq[val[v]];
  else assert(false);
}

void solve() {
  int n, q;
  while (cin >> n >> q) {
    for (int v = 0; v < n; ++v) cin >> val[v];
    for (int v = 0; v < n; ++v) g[v].clear();

    for (int i = 0; i + 1 < n; ++i) {
      int u, v; cin >> u >> v;
      --u, --v;
      g[u].emplace_back(v);
      g[v].emplace_back(u);
    }

    ::memset(up, -1, sizeof up);
    ::memset(node_freq, 0, sizeof node_freq);
    ::memset(val_freq, 0, sizeof val_freq);

    timer = 0;
    dfs(0, -1);

    for (int v = 0; v < n; ++v) {
      for (int l = 1; l < LG && ~up[v][l - 1]; ++l) {
        up[v][l] = up[up[v][l - 1]][l - 1];
      }
    }

    for (int i = 0; i < q; ++i) {
      int u, v;
      cin >> u >> v >> queries[i].c;
      --u, --v;
      queries[i].id = i;
      if (tin[u] > tin[v]) swap(u, v);
      auto lca_ = lca(u, v);
      if (lca_ == u) {
        queries[i].l = tin[u];
        queries[i].lca = -1;
      } else {
        queries[i].l = tout[u];
        queries[i].lca = lca_;
      }
      queries[i].r = tin[v];
    }

    sort(queries, queries + q, cmp);

    int cur_l = 0, cur_r = -1;
    for (int i = 0; i < q; ++i) {
      auto l = queries[i].l;
      auto r = queries[i].r;
      auto c = queries[i].c;
      auto id = queries[i].id;
      auto lca_ = queries[i].lca;

      while (cur_l > l) add(--cur_l);
      while (cur_r < r) add(++cur_r);
      while (cur_l < l) remove(cur_l++);
      while (cur_r > r) remove(cur_r--);

      ans[id] = val_freq[c] > 0;
      if (~lca_ && !ans[id]) ans[id] = val[lca_] == c;
    }

    for (int i = 0; i < q; ++i) {
      cout << (ans[i] ? FIND : NOT_FIND) << '\n';
    }
  }
}

//#define MEASURE_TIME
bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#ifdef MEASURE_TIME
  auto start = chrono::steady_clock::now();
#endif
  solve();
#ifdef MEASURE_TIME
  auto finish = chrono::steady_clock::now();
  auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
  cerr << endl
       << "Time: " << elapsed_ms.count() << " ms\n";
#endif
  return 0;
}
