#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

template <size_t ALPHA = 26, char MIN_ALPHA = 'a'>
struct AhoCorasick {
  struct Node {
    int link;
    vector<int> ids;
    array<int, ALPHA> next{}, go{};
    Node() : link(-1) {
      next.fill(-1);
      go.fill(-1);
    }
  };

  vector<Node> t;
  static constexpr int ROOT = 0;
  AhoCorasick() {
    t.emplace_back();
  }

  void add(string_view s, int idx = -1) {
    assert(all_of(s.begin(), s.end(), [](char ch) { return clamp<char>(ch, MIN_ALPHA, MIN_ALPHA + ALPHA - 1) == ch; }));

    int v = ROOT;
    for (auto ch : s) {
      if (t[v].next[ch - MIN_ALPHA] == -1) {
        t[v].next[ch - MIN_ALPHA] = int(t.size());
        t.emplace_back();
      }
      v = t[v].next[ch - MIN_ALPHA];
    }
    t[v].ids.emplace_back(idx);
  }

  void build() {
    t[ROOT].link = ROOT;
    for (int ch = 0; ch < ALPHA; ++ch) {
      if (t[ROOT].next[ch] != -1) {
        t[ROOT].go[ch] = t[ROOT].next[ch];
      } else {
        t[ROOT].go[ch] = ROOT;
      }
    }

    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      auto v = q.front();
      for (int ch = 0; ch < ALPHA; ++ch) {
        auto u = t[v].next[ch];
        if (u == -1) continue;
        t[u].link = v == ROOT ? ROOT : t[t[v].link].go[ch];
        for (int d = 0; d < ALPHA; ++d) {
          if (t[u].next[d] != -1) {
            t[u].go[d] = t[u].next[d];
          } else {
            t[u].go[d] = t[t[u].link].go[d];
          }
        }
        q.emplace(u);
      }
    }
  }
};

void solve() {
  string t;
  cin >> t;
  int n; cin >> n;
  AhoCorasick ac;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    ac.add(s, i);
  }
  ac.build();

  vector<bool> ans(n, false);
  auto v = AhoCorasick<>::ROOT;
  set<int> seen;
  for (auto ch : t) {
    v = ac.t[v].go[ch - 'a'];
    for (auto u = v; u != AhoCorasick<>::ROOT && seen.count(u) == 0; u = ac.t[u].link) {
      for (auto i : ac.t[u].ids) {
        ans[i] = true;
      }
      seen.emplace(u);
    }
  }
  for (auto x : ans) {
    cout << (x ? "YES" : "NO") << '\n';
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
