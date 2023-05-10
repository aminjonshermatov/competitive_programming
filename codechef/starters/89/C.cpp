#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

struct SegmentTree {
  int n;
  vector<int> tree;
  explicit SegmentTree(vector<int> &A) {
    n = 1;
    while (n < A.size()) n <<= 1;
    tree.assign(2 * n - 1, 0);
    build(A, 0, 0, n);
  }
  void build(vector<int> &A, int x, int lx, int rx) {
    if (rx - lx == 1) {
      if (lx < A.size()) tree[x] = A[lx];
      return;
    }
    auto mid = lx + (rx - lx) / 2;
    build(A, 2 * x + 1, lx, mid);
    build(A, 2 * x + 2, mid, rx);
    tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
  }
  int get(int ql, int qr, int x, int lx, int rx) {
    if (ql >= rx || qr <= lx) return -1;
    if (ql <= lx && rx <= qr) return tree[x];
    auto mid = lx + (rx - lx) / 2;
    return max(get(ql, qr, 2 * x + 1, lx, mid), get(ql, qr, 2 * x + 2, mid, rx));
  }
  int get(int ql, int qr) {
    return get(ql, qr, 0, 0, n);
  }
};

void solve() {
  int n; cin >> n;
  vector<int> P(n), id(n);
  for (int i = 0; i < n; ++i) {
    cin >> P[i];
    id[--P[i]] = i;
  }
  SegmentTree sg(P);

  int l = 0, r = n - 1;
  set<int> nxt;
  for (int i = 0; i < n; ++i) {
    nxt.emplace(i);
  }
  set<int> seen;
  int asd = 0;
  while (asd++ < 2 * n) {
    if (!seen.empty() && *prev(seen.end()) < *nxt.begin()) {
      break;
    }
    auto pos = id[*nxt.begin()];
    if (pos == l) {
      nxt.erase(P[l]);
      seen.emplace(P[l]);
      ++l;
    } else if (pos == r) {
      nxt.erase(P[r]);
      seen.emplace(P[r]);
      --r;
    } else {
      auto lhs = sg.get(l, pos);
      auto rhs = sg.get(pos, r + 1);
      if (lhs < rhs) {
        while (l <= pos) {
          nxt.erase(P[l]);
          seen.emplace(P[l]);
          ++l;
        }
      } else {
        while (r >= pos) {
          nxt.erase(P[r]);
          seen.emplace(P[r]);
          --r;
        }
      }
    }
  }
  cout << r - l + 1 << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
