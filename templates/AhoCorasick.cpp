//
// Created by aminjon on 8/4/23.
//
#include <bits/stdc++.h>

using namespace std;

template <size_t ALPHA = 26, char MIN_ALPHA = 'a'>
struct AhoCorasick {
  struct Node {
    int suf_link, term_suf_link;
    vector<int> ids;
    array<int, ALPHA> next{}, go{};
    Node() : suf_link(-1), term_suf_link(-1) {
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
    t[ROOT].suf_link = ROOT;
    t[ROOT].term_suf_link = ROOT;
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
        t[u].suf_link = v == ROOT ? ROOT : t[t[v].suf_link].go[ch];
        t[u].term_suf_link = !t[t[u].suf_link].ids.empty() ? t[u].suf_link : t[t[u].suf_link].term_suf_link;
        for (int d = 0; d < ALPHA; ++d) {
          if (t[u].next[d] != -1) {
            t[u].go[d] = t[u].next[d];
          } else {
            t[u].go[d] = t[t[u].suf_link].go[d];
          }
        }
        q.emplace(u);
      }
    }
  }
};