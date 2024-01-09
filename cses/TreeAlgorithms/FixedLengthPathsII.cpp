#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("tree-vectorize")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

constexpr int N = 2e5 + 5;
static std::vector<int> g[N];
static int size[N];
static i64 bit[N];
static bool died[N];

int n, k1, k2;

auto dfs_sz(int v, int p) -> int {
  size[v] = 1;
  for (auto u : g[v]) {
    if (u != p && !died[u]) {
      size[v] += dfs_sz(u, v);
    }
  }
  return size[v];
}
auto centroid(int v, int p, int desired) -> int {
  for (auto u : g[v]) {
    if (u != p && !died[u] && size[u] >= desired) {
      return centroid(u, v, desired);
    }
  }
  return v;
}
auto upd(int pos, i64 val) -> void {
  for (++pos; pos <= n; pos += pos & -pos) {
    bit[pos] += val;
  }
}
auto qry(int l, int r) -> i64 { // [l, r]
  l = std::max(l, 0);
  i64 loc = 0;
  for (++r; r > 0; r -= r & -r) {
    loc += bit[r];
  }
  for (; l > 0; l -= l & -l) {
    loc -= bit[l];
  }
  return loc;
}
i64 ans = 0;
auto dfs_calc(int v, int p, int depth, int& max_depth, bool do_update) -> void {
  if (depth > k2) {
    return;
  }
  max_depth = std::max(max_depth, depth);
  if (do_update) {
    upd(depth, 1);
  } else {
    ans += qry(k1 - depth, k2 - depth);
  }
  for (auto u : g[v]) {
    if (u != p && !died[u]) {
      dfs_calc(u, v, depth + 1, max_depth, do_update);
    }
  }
}
auto CD(int v, int p) -> void {
  auto c = centroid(v, p, dfs_sz(v, p) / 2);
  died[c] = true;
  int max_depth = 0;
  for (auto u : g[c]) {
    if (!died[u]) {
      dfs_calc(u, c, 1, max_depth, false);
      dfs_calc(u, c, 1, max_depth, true);
    }
  }
  for (int d = 1; d <= max_depth; ++d) {
    upd(d, -qry(d, d));
  }
  for (auto u : g[c]) {
    if (!died[u]) {
      CD(u, c);
    }
  }
}

void solve() {
  std::cin >> n >> k1 >> k2;

  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  upd(0, 1);
  std::fill(died, died + n, false);
  CD(0, -1);
  std::cout << ans << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef LOCAL
  auto s = std::chrono::high_resolution_clock::now();
#endif
  solve();
#ifdef LOCAL
  std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s).count() << "ms" << '\n';
#endif
}