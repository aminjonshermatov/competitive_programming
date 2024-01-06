#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

constexpr auto inf = std::numeric_limits<int>::max();
struct State {
  int min, cnt;
  State(int min_, int cnt_) : min(min_), cnt(cnt_) { }
  State() : State(inf, 0) { }
  bool better(const State& o) const {
    if (cnt > o.cnt) return true;
    if (cnt == o.cnt) return min < o.min;
    return false;
  }
  bool eq(const State& o) const {
    return cnt == o.cnt && min == o.min;
  }
  friend std::ostream& operator<<(std::ostream& out, const State& st) {
    return out << '{' << st.min << ',' << st.cnt << '}';
  }
};

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> as(n);
  for (auto& a : as) {
    std::cin >> a;
  }
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  std::vector<int> level(n, inf);
  std::queue<int> q;
  level[0] = 0;
  q.emplace(0);
  while (!q.empty()) {
    auto v = q.front();
    q.pop();
    for (auto u : g[v]) {
      if (level[v] + 1 < level[u]) {
        level[u] = level[v] + 1;
        q.emplace(u);
      }
    }
  }

  using T = std::tuple<int, State>;
  auto cmp = [](const T& a, const T& b) {
    auto& l = std::get<1>(a);
    auto& r = std::get<1>(b);
    return r.better(l);
  };
  std::priority_queue<T, std::vector<T>, decltype(cmp)> pq(cmp);
  std::vector<State> state(n);
  pq.emplace(0, state[0] = {as[0], 1});
  while (!pq.empty()) {
    auto [v, st] = pq.top();
    pq.pop();
    if (!st.eq(state[v])) continue;
    dbg(v, st);
    for (auto u : g[v]) {
      auto nst = st.min <= as[u] ? State{as[u], st.cnt + (st.min < as[u])} : State{};
      if (nst.better(state[u])) {
        pq.emplace(u, state[u] = nst);
      }
    }
  }
  dbg(state);
  std::cout << state[n - 1].cnt << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}