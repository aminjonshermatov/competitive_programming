//
// Created by aminjon on 4/13/23.
//
#ifdef LOCAL
#include "constants.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using i64 = int64_t;

void solve(istream &cin, ostream &cout) {
  struct Node {
    int idx, cnt, term;
    array<int, 26> to{};
    Node() : idx(-1), cnt(0), term(0) {
      to.fill(-1);;
    }
  };
  vector<Node> t;
  t.emplace_back();

  auto add = [&](auto &f, int node, string_view s, int idx, int i) -> void {
    if (idx >= s.size()) {
      t[node].idx = i + 1;
      ++t[node].term;
      ++t[node].cnt;
      return;
    }
    if (t[node].to[s[idx] - 'a'] == -1) {
      t[node].to[s[idx] - 'a'] = int(t.size());
      t.emplace_back();
    }
    auto to = t[node].to[s[idx] - 'a'];
    f(f, to, s, idx + 1, i);
    t[node].cnt = t[node].term;
    for (int ch = 0; ch < 26; ++ch) {
      to = t[node].to[ch];
      if (to != -1) {
        t[node].cnt += t[to].cnt;
      }
    }
  };

  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    assert(all_of(s.begin(), s.end(), [](char ch) { return clamp(ch, 'a', 'z') == ch; }));
    add(add, 0, s, 0, i);
  }

  auto dfs = [&](auto &f, int node, string_view s, int idx, int k) -> int {
    if (idx < s.size()) {
      if (t[node].to[s[idx] - 'a'] == -1) {
        return -1;
      }
      return f(f, t[node].to[s[idx] - 'a'], s, idx + 1, k);
    }
    int lhs = t[node].term;
    if (lhs >= k && t[node].idx != -1) {
      return t[node].idx;
    }
    for (int ch = 0; ch < 26; ++ch) {
      auto nxt = t[node].to[ch];
      if (nxt == -1) {
        continue;
      }
      if (lhs + t[nxt].cnt >= k) {
        return f(f, nxt, s, idx, k - lhs);
      } else {
        lhs += t[nxt].cnt;
      }
    }
    return -1;
  };

  int q = 1; cin >> q;
  for (int i = 0; i < q; ++i) {
    string s;
    int k;
    cin >> s >> k;
    cout << dfs(dfs, 0, s, 0, k) << '\n';
  }
}

int main() {
#ifdef LOCAL
  auto in = ifstream(constants::DATA_IN);
  auto out = ofstream(constants::FAST_OUT);
  solve(in, out);
#else
  solve(cin, cout);
#endif

  return 0;
}
