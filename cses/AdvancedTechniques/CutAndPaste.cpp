#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

struct Node {
  Node *left, *right;
  char val;
  int64_t priority;
  int size;

  explicit Node(char val_ = '#')
    : left{nullptr}
    , right{nullptr}
    , val{val_}
    , priority{(int64_t(rand()) << 16) ^ rand()}
    , size{1} { }
};

int size(Node *node) {
  if (node == nullptr) return 0;
  return node->size;
}

void update(Node *node) {
  if (node == nullptr) return;
  node->size = 1 + size(node->left) + size(node->right);
}

Node *merge(Node *root_l, Node *root_r) {
  if (root_l == nullptr) return root_r;
  if (root_r == nullptr) return root_l;

  if (root_l->priority < root_r->priority) {
    root_l->right = merge(root_l->right, root_r);
    update(root_l);
    return root_l;
  } else {
    root_r->left = merge(root_l, root_r->left);
    update(root_r);
    return root_r;
  }
}

pair<Node*, Node*> split(Node *root, int sz) {
  if (root == nullptr) return {nullptr, nullptr};

  if (size(root->left) >= sz) {
    auto [ll, lr] = split(root->left, sz);
    root->left = lr;
    update(root);
    return {ll, root};
  } else {
    auto [rl, rr] = split(root->right, sz - size(root->left) - 1);
    root->right = rl;
    update(root);
    return {root, rr};
  }
}

void solve() {
  int n, q; cin >> n >> q;

  Node *root = nullptr;

  for (int i = 0; i < n; ++i) {
    char ch; cin >> ch;
    root = merge(root, new Node(ch));
  }

  while (q--) {
    int l, r; cin >> l >> r;
    --l, --r;
    auto [L, rest] = split(root, l);
    auto [mid, R] = split(rest, r - l + 1);
    root = merge(merge(L, R), mid);
  }
  string ans;
  ans.reserve(n);
  auto dfs = [&](auto &f, Node *node) -> void {
    assert(node != nullptr);
    if (node->left != nullptr) {
      f(f, node->left);
    }
    ans.push_back(node->val);
    if (node->right != nullptr) {
      f(f, node->right);
    }
  };
  dfs(dfs, root);
  cout << ans << '\n';
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
