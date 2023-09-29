//
// Created by aminjon on 4/13/23.
//
#ifdef LOCAL
#include "constants.h"
//#include "debug.h"
#else
#define dbg(...) 42
#endif
#include <bits/stdc++.h>

using namespace std;

template <size_t ALPHA = 27, char MIN_ALPHA = 'a' - 1>
vector<int> suffix_array(string_view s) {
  assert(all_of(s.begin(), s.end(), [](char ch) { return clamp<char>(ch, MIN_ALPHA, MIN_ALPHA + ALPHA - 1) == ch; }));
  assert(s.back() == MIN_ALPHA);

  const auto n = static_cast<int>(s.size());
  const auto nn = max<int>(ALPHA, n) + 1;
  vector<int> p(n), c(n), cnt(nn, 0);
  for (auto ch : s) {
    ++cnt[ch - MIN_ALPHA];
  }
  for (int i = 1; i < nn; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = 0; i < n; ++i) {
    p[--cnt[s[i] - MIN_ALPHA]] = i;
  }
  c[p[0]] = 0;
  for (int i = 1; i < n; ++i) {
    c[p[i]] = c[p[i - 1]] + (s[p[i - 1]] != s[p[i]]);
  }

  vector<int> np(n), nc(n);
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; ++i) {
      np[i] = (p[i] + n - k) % n;
    }
    fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < n; ++i) {
      ++cnt[c[np[i]]];
    }
    for (int i = 1; i < nn; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      p[--cnt[c[np[i]]]] = np[i];
    }
    nc[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
      auto cur = pair(c[p[i]], c[(p[i] + k) % n]);
      auto prv = pair(c[p[i - 1]], c[(p[i - 1] + k) % n]);
      nc[p[i]] = nc[p[i - 1]] + (cur != prv);
    }
    nc.swap(c);
  }

  return p;
}

template <size_t ALPHA = 27, char MIN_ALPHA = 'a' - 1>
decltype(auto) lcp_array(string_view s) {
  assert(s.back() == MIN_ALPHA);

  const auto n = static_cast<int>(s.size());
  const auto sa = suffix_array<ALPHA, MIN_ALPHA>(s);
  vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[sa[i]] = i;
  }
  vector<int> lcp(n, 0); // lcp(s[sa[i]], s[sa[i + 1]])
  int k = 0;
  for (int i = 0; i < n; ++i) {
    k = max(k - 1, 0);
    if (pos[i] == n - 1) continue;
    auto j = sa[pos[i] + 1];
    while (s[i + k] == s[j + k]) ++k;
    lcp[pos[i]] = k;
  }

  --lcp.back();
  return tuple{lcp, sa};
}

constexpr auto inf = numeric_limits<int>::max();

struct SegmentTree {
    struct Node { int mn, l, r; };
    const Node neutral = {inf, -1, inf};
    static Node unite(Node a, Node b) { return Node{min(a.mn, b.mn), a.l, b.r}; }
    int n;
    vector<Node> tree;
    explicit SegmentTree(const vector<int> &as) {
      n = 1;
      while (n < as.size()) n <<= 1;
      tree.assign(2 * n - 1, neutral);
      auto build = [&](auto &f, int x, int lx, int rx) -> void {
          if (rx - lx == 1) {
            if (lx < as.size()) {
              tree[x] = {as[lx], lx, lx};
            }
            return;
          }
          auto mid = lx + (rx - lx) / 2;
          f(f, 2 * x + 1, lx, mid);
          f(f, 2 * x + 2, mid, rx);
          tree[x] = unite(tree[2 * x + 1], tree[2 * x + 2]);
      };
      build(build, 0, 0, n);
    }
    int next_less(int pos, int val, int x, int lx, int rx) const {
      if (tree[x].mn >= val || tree[x].r < pos) return -1;
      if (rx - lx == 1) return lx;
      auto mid = lx + (rx - lx) / 2;
      auto res = next_less(pos, val, 2 * x + 1, lx, mid);
      if (res == -1) {
        res = next_less(pos, val, 2 * x + 2, mid, rx);
      }
      return res;
    }
    int next_less(int pos, int val) const {
      return next_less(pos, val, 0, 0, n);
    }
    int prev_less(int pos, int val, int x, int lx, int rx) const {
      if (tree[x].mn >= val || tree[x].l > pos) return -1;
      if (rx - lx == 1) return lx;
      auto mid = lx + (rx - lx) / 2;
      auto res = prev_less(pos, val, 2 * x + 2, mid, rx);
      if (res == -1) {
        res = prev_less(pos, val, 2 * x + 1, lx, mid);
      }
      return res;
    }
    int prev_less(int pos, int val) const {
      return prev_less(pos, val, 0, 0, n);
    }
};

using i64 = int64_t;

void solve(istream &in, ostream &out) {
  int n, m;
  in >> n >> m;
  string s(n, '#');

  for (auto &c : s) {
    int x;
    in >> x;
    assert(x > 0);
    c = char('a' + x);
  }
  s.push_back('a');

  n = int(s.size());

  const auto [lcp, sa] = lcp_array<15, 'a'>(s);

  const auto sg = SegmentTree(lcp);

  i64 tot = n - 1;
  int start = 0, len = n - 1;
  for (int i = 0; i < n; ++i) {
    auto prv = sg.prev_less(i, lcp[i]);
    auto nxt = sg.next_less(i, lcp[i]);
    if (nxt == -1) nxt = n;
    i64 cur_len = nxt - prv;
    if (tot < cur_len * lcp[i]) {
      tot = cur_len * lcp[i];
      start = sa[prv + 1];
      len = lcp[i];
    }
  }
  assert(start != -1);
  out << tot << '\n';
  out << len << '\n';
  for (int i = 0; i < len; ++i) {
    out << s[start + i] - 'a' << ' ';
  }
  out << '\n';
}

int main() {
  auto in = ifstream(constants::DATA_IN);
  auto out = ofstream(constants::FAST_OUT);
  solve(in, out);

  return 0;
}
