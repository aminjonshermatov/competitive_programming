#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
  Node *l, *r;
  int sz, val;
  i64 sm, priority;
  bool need_reverse;
  explicit Node(int val_, Node *l_ = nullptr, Node *r_ = nullptr)
      : l(l_), r(r_), sz(1), val(val_), sm(val_), priority(i64(rnd())), need_reverse(false) { }
  Node() : Node(0) { }
};

void add_promise(Node *node, bool need_reverse) {
  if (node == nullptr) return;
  node->need_reverse ^= need_reverse;
}

void push(Node *node) {
  if (node == nullptr) return;

  if (node->need_reverse) swap(node->l, node->r);
  add_promise(node->l, node->need_reverse);
  add_promise(node->r, node->need_reverse);
  node->need_reverse = false;
}

inline i64 sum(Node *node) { return node == nullptr ? 0 : node->sm; }
inline int size(Node *node) { return node == nullptr ? 0 : node->sz; }

void update(Node *node) {
  if (node == nullptr) return;
  push(node->l);
  push(node->r);
  node->sm = sum(node->l) + node->val + sum(node->r);
  node->sz = size(node->l) + 1 + size(node->r);
}

pair<Node*, Node*> split(Node *node, int n) {
  if (node == nullptr) return {nullptr, nullptr};

  push(node);
  if (size(node->l) >= n) {
    auto [ll, lr] = split(node->l, n);
    node->l = lr;
    update(node);
    return {ll, node};
  } else {
    auto [rl, rr] = split(node->r, n - size(node->l) - 1);
    node->r = rl;
    update(node);
    return {node, rr};
  }
}

Node *merge(Node *lhs, Node *rhs) {
  push(lhs);
  push(rhs);
  if (lhs == nullptr) return rhs;
  if (rhs == nullptr) return lhs;

  if (lhs->priority < rhs->priority) {
    lhs->r = merge(lhs->r, rhs);
    update(lhs);
    return lhs;
  } else {
    rhs->l = merge(lhs, rhs->l);
    update(rhs);
    return rhs;
  }
}

void solve() {
  int n, q; cin >> n >> q;
  Node *root = nullptr;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    root = merge(root, new Node(x));
  }

  auto range_reverse = [&](int l, int r) -> void { // [l, r)
    auto [node, R] = split(root, r);
    auto [L, mid] = split(node, l);
    add_promise(mid, true);
    root = merge(merge(L, mid), R);
  };

  auto range_sum = [&](int l, int r) -> i64 { // [l, r)
    auto [node, R] = split(root, r);
    auto [L, mid] = split(node, l);
    auto sm = sum(mid);
    root = merge(merge(L, mid), R);
    return sm;
  };

  while (q--) {
    char cmd;
    int l, r;
    cin >> cmd >> l >> r;
    --l;
    if (cmd == '0') {
      cout << range_sum(l, r) << '\n';
    } else if (cmd == '1') {
      range_reverse(l, r);
    } else {
      assert(false);
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
