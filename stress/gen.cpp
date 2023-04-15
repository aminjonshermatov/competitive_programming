//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "utils.h"
#include "constants.h"

using namespace std;

inline constexpr int N = 1000;

int LG;
vector<vector<int>> g, up;
vector<int> tin, tout, dist;
int timer;

void dfs(int v, int p) {
  up[v][0] = p;
  tin[v] = timer++;
  for (auto u : g[v]) {
    if (u == p) continue ;
    dist[u] = dist[v] + 1;
    dfs(u, v);
  }
  tout[v] = timer++;
}

inline bool is_accessor(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }
int get_lca(int u, int v) {
  if (is_accessor(u, v)) return u;
  if (is_accessor(v, u)) return v;
  for (int l = LG; ~l; --l) {
    if (up[u][l] == -1) continue ;
    if (!is_accessor(up[u][l], v)) u = up[u][l];
  }
  return up[u][0];
}

void gen(ofstream &out) {
  const int n = utils::random(5, N);
  const int q = utils::random(N, 2 * N);

  LG = 31 - __builtin_clz(n);

  g.resize(n + 1);
  up.assign(n + 1, vector<int>(LG + 1, -1));
  tin.resize(n + 1), tout.resize(n + 1), dist.resize(n + 1);

  out << n << ' ' << q << '\n';

  for (int i = 0; i < n; ++i) {
    out << utils::random(1, N) << " \n"[i + 1 == n];
  }

  for (int u = 2; u <= n; ++u) {
    int v = utils::random(1, u - 1);
    g[u].emplace_back(v);
    g[v].emplace_back(u);
    out << u << ' ' << v << '\n';
  }

  timer = 0;
  dist[1] = 0;
  dfs(1, -1);

  for (int i = 0; i < q; ++i) {
    auto u = utils::random(1, n);
    auto v = utils::random(1, n);
    auto lca = get_lca(u, v);
    auto len = dist[u] + dist[v] - 2 * dist[lca];
    if (len < 0) { --i; continue; }
    auto k = utils::random(1, len + 1);
    out << u << ' ' << v << ' ' << k << '\n';
  }
}

int main() {
  ofstream out(constants::DATA_IN);
  gen(out);
}