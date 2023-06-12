#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int K = 26;

struct Node {
  array<Node*, K> go{};
  int cnt = 0;
  bool is_term = false;
  Node() { go.fill(nullptr); }
};

void solve() {
  auto root = Node();

  auto add = [&](string_view s) -> void {
    auto cur = &root;
    for (auto ch : s) {
      if (cur->go[ch - 'a'] == nullptr) {
        cur->go[ch - 'a'] = new Node();
      }
      cur = cur->go[ch - 'a'];
      ++cur->cnt;
    }
    cur->is_term = true;
  };

  auto dfs = [&](auto &f, Node *cur, int k, string &kth) -> void {
    if (k == 0) return;
    for (int ch = 0; ch < K; ++ch) {
      if (cur->go[ch] == nullptr) continue;
      if (cur->go[ch]->cnt >= k) {
        k -= cur->go[ch]->is_term;
        kth.push_back(char('a' + ch));
        f(f, cur->go[ch], k, kth);
        return;
      } else {
        k -= cur->go[ch]->cnt;
      }
    }
  };

  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    string s; cin >> s;
    if (isdigit(s.front())) {
      int k = stoi(s);
      string kth;
      dfs(dfs, &root, k, kth);
      cout << kth << '\n';
    } else {
      add(s);
    }
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
