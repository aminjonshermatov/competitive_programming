//
// Created by aminjon on 4/13/23.
//
#ifdef LOCAL
#include "constants.h"
#else
#define dbg(...) 42
#endif
#include <bits/stdc++.h>

using namespace std;

using i64 = int64_t;

struct Node {
  Node *l = nullptr, *r = nullptr;
  int cnt = 0;
  i64 sum = 0;
  Node() = default;
  explicit Node(int cnt_, i64 sum_) : l(nullptr), r(nullptr), cnt(cnt_), sum(sum_) { }
  Node(Node *l, Node *r) : l(l), r(r), cnt(0),  sum(0) {
    if (l != nullptr) {
      cnt += l->cnt;
      sum += l->sum;
    }
    if (r != nullptr) {
      cnt += r->cnt;
      sum += r->sum;
    }
  }
};

inline i64 sum(Node *node) { return node == nullptr ? 0 : node->sum; }
inline int cnt(Node *node) { return node == nullptr ? 0 : node->cnt; }

Node* build(int lx, int rx) {
  if (rx - lx == 1) {
    return new Node();
  }
  auto mid = lx + (rx - lx) / 2;
  return new Node(build(lx, mid), build(mid, rx));
}

Node* modify(int pos, int val, Node *node, int lx, int rx) {
  assert(node != nullptr);
  if (rx - lx == 1) {
    return new Node(cnt(node) + 1, sum(node) + val);
  }
  auto mid = lx + (rx - lx) / 2;
  if (pos < mid) {
    return new Node(modify(pos, val, node->l, lx, mid), node->r);
  } else {
    return new Node(node->l, modify(pos, val, node->r, mid, rx));
  }
}

inline std::pair<int, i64> unite(std::pair<int, i64> a, std::pair<int, i64> b) {
  return std::pair(a.first + b.first, a.second + b.second);
}

std::pair<int, i64> query(int ql, int qr, Node *a, Node *b, int lx, int rx) {
  if (ql >= rx || qr <= lx) return std::pair(0, 0);
  if (ql <= lx && rx <= qr) return std::pair(cnt(b) - cnt(a), sum(b) - sum(a));
  auto mid = lx + (rx - lx) / 2;
  return unite(query(ql, qr, a->l, b->l, lx, mid), query(ql, qr, a->r, b->r, mid, rx));
}

void solve(istream &in, ostream &out) {
  int n, q;
  in >> n >> q;
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    in >> as[i];
  }
  auto sorted = as;
  std::sort(sorted.begin(), sorted.end());
  sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());

  auto pos = as;
  for (auto &p : pos) {
    p = int(std::lower_bound(sorted.begin(), sorted.end(), p) - sorted.begin());
  }
  const auto m = int(sorted.size());

  std::vector<Node*> roots(n + 1);
  roots[0] = build(0, m);
  for (int i = 0; i < n; ++i) {
    roots[i + 1] = modify(pos[i], as[i], roots[i], 0, m);
  }

  while (q-- > 0) {
    int l1, r1, l2, r2;
    in >> l1 >> r1 >> l2 >> r2;
    int tot_cnt = r1 - l1 + 1 + r2 - l2 + 1;

    int lo = -1, hi = m - 1;
    while (hi - lo > 1) {
      auto mid = lo + (hi - lo) / 2;
      auto [c1, s1] = query(0, mid + 1, roots[l1 - 1], roots[r1], 0, m);
      auto [c2, s2] = query(0, mid + 1, roots[l2 - 1], roots[r2], 0, m);
      ((c1 + c2) * 2 > tot_cnt ? hi : lo) = mid;
    }
    auto [c1, s1] = query(hi, m, roots[l1 - 1], roots[r1], 0, m);
    auto [c2, s2] = query(0, hi + 1, roots[l2 - 1], roots[r2], 0, m);
    i64 v = sorted[hi];
    out << s1 - v * c1 + v * c2 - s2 << '\n';
  }
}

int main() {
  auto in = ifstream(constants::DATA_IN);
  auto out = ofstream(constants::FAST_OUT);
  solve(in, out);

  return 0;
}
