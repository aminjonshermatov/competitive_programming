#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

typedef struct item * pitem;
struct item {
  int prior, value, cnt;
  bool rev;
  pitem l, r;
};

int cnt (pitem it) {
  return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
  if (it)
    it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push (pitem it) {
  if (it && it->rev) {
    it->rev = false;
    swap (it->l, it->r);
    if (it->l)  it->l->rev ^= true;
    if (it->r)  it->r->rev ^= true;
  }
}

void merge (pitem & t, pitem l, pitem r) {
  push (l);
  push (r);
  if (!l || !r)
    t = l ? l : r;
  else if (l->prior > r->prior)
    merge (l->r, l->r, r),  t = l;
  else
    merge (r->l, l, r->l),  t = r;
  upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
  if (!t)
    return void( l = r = 0 );
  push (t);
  int cur_key = add + cnt(t->l);
  if (key <= cur_key)
    split (t->l, l, t->l, key, add),  r = t;
  else
    split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
  upd_cnt (t);
}

void reverse (pitem t, int l, int r) {
  pitem t1, t2, t3;
  split (t, t1, t2, l);
  split (t2, t2, t3, r-l+1);
  t2->rev ^= true;
  merge (t, t1, t2);
  merge (t, t, t3);
}

void output (pitem t) {
  if (!t)  return;
  push (t);
  output (t->l);
  printf ("%c", t->value);
  output (t->r);
}

void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  pitem root = nullptr;
  for (auto c : s) {
    auto x = new item{};
    x->l = x->r = nullptr;
    x->rev = 0;
    x->cnt = 1;
    x->value = c;
    x->prior = rnd();
    merge(root, root, x);
  }
  vector<int> L(k), R(k);
  for (auto &l : L) {
    cin >> l;
  }
  for (auto &r : R) {
    cin >> r;
  }
  set<pair<int, int>> lr;
  for (int i = 0; i < k; ++i) {
    lr.emplace(L[i], R[i]);
  }
  int q;
  cin >> q;

  while (q--) {
    int x;
    cin >> x;
    auto it = lr.upper_bound(pair(x, n));
    assert(it != lr.begin());
    it = prev(it);

    auto a = min(x, it->first + it->second - x);
    auto b = max(x, it->first + it->second - x);
    assert(clamp(a, 1, n) == a);
    assert(clamp(b, 1, n) == b);
    reverse(root, a - 1, b - 1);
  }
  output(root);
  printf("\n");
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