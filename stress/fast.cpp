//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "constants.h"

constexpr int A = 2;
struct Node {
  std::array<int, A> to{};
  std::vector<int> nodes;
  Node() : to({-1, -1}) { }
};

void solve(std::istream &in, std::ostream &out) {
  int n;
  in >> n;

  // 2*i   - if `0`
  // 2*i+1 - if `1`
  // 2*n+i - if there is no `?`
  std::vector<Node> nodes;
  const auto root = int(nodes.size());
  nodes.emplace_back();
  std::vector<bool> with_q(n, true);
  std::vector<int> alt(n);
  auto add = [&](auto &f, int node_id, int s_id, int s_pos, std::string_view s, int replaced_to) -> void {
    if (s_pos >= s.size()) {
      if (replaced_to == -1) {
        with_q[s_id] = false;
        replaced_to = s.back() - '0';
      }
      alt[s_id] = replaced_to;
      nodes[node_id].nodes.emplace_back(s_id * 2 + replaced_to);
      return;
    }
    for (int c = 0; c < A; ++c) {
      if (s[s_pos] - '0' == c || s[s_pos] == '?') {
        if (nodes[node_id].to[c] == -1) {
          nodes[node_id].to[c] = int(nodes.size());
          nodes.emplace_back();
        }
        if (s[s_pos] == '?') {
          replaced_to = c;
        }
        f(f, nodes[node_id].to[c], s_id, s_pos + 1, s, replaced_to);
      }
    }
  };
  std::vector<std::string> ss(n);
  for (int i = 0; i < n; ++i) {
    in >> ss[i];
    add(add, root, i, 0, ss[i], -1);
  }

  auto not_ = [](int id) -> int { return id ^ 1; };

  bool ok = true;
  std::vector<std::vector<int>> g(2 * n), ig(2 * n);
  auto build = [&](auto &f, int node_id) -> void {
    int cnt_without_question_mark = 0;
    for (int i = 0; i < nodes[node_id].nodes.size(); ++i) {
      cnt_without_question_mark += nodes[node_id].nodes[i] >= 2 * n;
      for (int j = i + 1; j < nodes[node_id].nodes.size(); ++j) {
        if (with_q[nodes[node_id].nodes[i] / 2] && with_q[nodes[node_id].nodes[j] / 2]) {
          g[not_(nodes[node_id].nodes[i])].emplace_back(nodes[node_id].nodes[j]);
          ig[nodes[node_id].nodes[j]].emplace_back(not_(nodes[node_id].nodes[i]));

          g[not_(nodes[node_id].nodes[j])].emplace_back(nodes[node_id].nodes[i]);
          ig[nodes[node_id].nodes[i]].emplace_back(not_(nodes[node_id].nodes[j]));
        } else if (with_q[nodes[node_id].nodes[i] / 2]) {
          g[not_(nodes[node_id].nodes[i])].emplace_back(nodes[node_id].nodes[j]);
          ig[nodes[node_id].nodes[j]].emplace_back(not_(nodes[node_id].nodes[i]));
        } else if (with_q[nodes[node_id].nodes[j] / 2]) {
          g[not_(nodes[node_id].nodes[j])].emplace_back(nodes[node_id].nodes[i]);
          ig[nodes[node_id].nodes[i]].emplace_back(not_(nodes[node_id].nodes[j]));
        }
      }
    }
    for (int c = 0; c < A; ++c) {
      if (nodes[node_id].to[c] != -1) {
        f(f, nodes[node_id].to[c]);
        for (auto u : nodes[node_id].nodes) {
          for (auto v : nodes[nodes[node_id].to[c]].nodes) {
            cnt_without_question_mark += v >= 2 * n;
            // ... AND (u OR v) AND ...
            // !u -> v
            // !v -> u
            if (with_q[u / 2] && with_q[v / 2]) {
              g[not_(u)].emplace_back(v);
              ig[v].emplace_back(not_(u));
              g[not_(v)].emplace_back(u);
              ig[u].emplace_back(not_(v));
            } else if (with_q[u / 2]) {
              g[not_(u)].emplace_back(v);
              ig[v].emplace_back(not_(u));
            } else if (with_q[v / 2]) {
              g[not_(v)].emplace_back(u);
              ig[u].emplace_back(not_(v));
            }
          }
        }
      }
    }
    if (cnt_without_question_mark > 1) {
      ok = false;
      return;
    }
    for (int c = 0; c < A; ++c) {
      if (nodes[node_id].to[c] != -1) {
        if (nodes[nodes[node_id].to[c]].nodes.size() > nodes[node_id].nodes.size()) {
          for (auto u : nodes[node_id].nodes) {
            nodes[nodes[node_id].to[c]].nodes.emplace_back(u);
          }
          std::swap(nodes[nodes[node_id].to[c]].nodes, nodes[node_id].nodes);
        } else {
          for (auto u : nodes[nodes[node_id].to[c]].nodes) {
            nodes[node_id].nodes.emplace_back(u);
          }
        }
      }
    }
  };
  build(build, root);
  if (!ok) {
    std::cout << "NO\n";
    return;
  }

  std::vector<bool> used(2 * n, false);
  std::vector<int> ord;
  ord.reserve(2 * n);
  auto dfs_ord = [&](auto &f, int v) -> void {
    used[v] = true;
    for (auto u : g[v]) {
      if (used[u]) continue;
      f(f, u);
    }
    ord.emplace_back(v);
  };
  for (int v = 0; v < 2 * n; ++v) {
    if (used[v]) continue;
    dfs_ord(dfs_ord, v);
  }

  std::vector<int> comp(2 * n, -1);
  auto dfs = [&](auto &f, int v, int c) -> void {
    used[v] = true;
    comp[v] = c;
    for (auto u : ig[v]) {
      if (used[u]) continue;
      f(f, u, c);
    }
  };
  std::reverse(ord.begin(), ord.end());
  std::fill(used.begin(), used.end(), false);
  int c = 0;
  for (auto v : ord) {
    if (used[v]) continue;
    dfs(dfs, v, c++);
  }

  std::vector<bool> which(n);
  for (int v = 0; v < n; ++v) {
    if (comp[v * 2] == comp[v * 2 + 1]) {
      out << "NO\n";
      return;
    }
    which[v] = comp[v * 2] > comp[v * 2 + 1];
    if (!with_q[v] && which[v] != alt[v]) {
      out << "NO\n";
      return;
    }
  }

  for (int v = 0; v < n; ++v) {
    if (!with_q[v]) continue;
    ss[v][ss[v].find('?')] = char('0' + which[v]);
  }

  out << "YES\n";
  for (int v = 0; v < n; ++v) {
    out << ss[v] << '\n';
  }
}

int main() {
  auto in = std::ifstream(constants::DATA_IN);
  auto out = std::ofstream(constants::FAST_OUT);
  solve(in, out);

  return 0;
}
