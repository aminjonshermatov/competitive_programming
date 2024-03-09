#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string t;
  int n;
  std::cin >> t >> n;
  std::vector<std::vector<std::string>> all(n);
  for (auto& r : all) {
    int m;
    std::cin >> m;
    r.resize(m);
    for (auto& s : r) {
      std::cin >> s;
    }
  }
  t = "@" + t;

  std::vector<std::map<std::string, int>> dist(n + 1);
  using T = std::tuple<int, int, std::string>;
  std::priority_queue<T, std::vector<T>, std::greater<>> pq;
  pq.emplace(dist[0]["@"] = 0, 0, "@");
  while (!pq.empty()) {
    auto [d, ith, s] = pq.top();
    pq.pop();
    if (ith >= n) {
      continue;
    }
    pq.emplace(d, ith + 1, s);
    for (auto& x : all[ith]) {
      auto ns = s + x;
      if (ns.size() <= t.size() && t.starts_with(ns) && (!dist[ith + 1].contains(ns) || dist[ith + 1][ns] > (d + 1))) {
        pq.emplace(dist[ith + 1][ns] = d + 1, ith + 1, ns);
      }
    }
  }
  int best = -1;
  for (auto& r : dist) {
    auto it = r.find(t);
    if (it != r.end() && (best == -1 || it->second < best)) {
      best = it->second;
    }
  }
  std::cout << best << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}