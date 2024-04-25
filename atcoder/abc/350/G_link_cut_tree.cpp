#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

// https://nyaannyaan.github.io/library/lct/link-cut-tree.hpp
#line 2 "lct/link-cut-tree.hpp"

#line 2 "lct/splay-reversible.hpp"

#line 2 "lct/reversible-bbst-base.hpp"

template <typename Tree, typename Node, typename T, T (*f)(T, T), T (*ts)(T)>
struct ReversibleBBST : Tree {
  using Tree::merge;
  using Tree::split;
  using typename Tree::Ptr;

  ReversibleBBST() = default;

  virtual void toggle(Ptr t) {
    if(!t) return;
    swap(t->l, t->r);
    t->sum = ts(t->sum);
    t->rev ^= true;
  }

  T fold(Ptr &t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    auto ret = sum(y.first);
    t = merge(x.first, merge(y.first, y.second));
    return ret;
  }

  void reverse(Ptr &t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    toggle(y.first);
    t = merge(x.first, merge(y.first, y.second));
  }

  Ptr update(Ptr t) override {
    if (!t) return t;
    t->cnt = 1;
    t->sum = t->key;
    if (t->l) t->cnt += t->l->cnt, t->sum = f(t->l->sum, t->sum);
    if (t->r) t->cnt += t->r->cnt, t->sum = f(t->sum, t->r->sum);
    return t;
  }

protected:
  inline T sum(const Ptr t) { return t ? t->sum : T(); }

  void push(Ptr t) override {
    if (!t) return;
    if (t->rev) {
      if (t->l) toggle(t->l);
      if (t->r) toggle(t->r);
      t->rev = false;
    }
  }
};

/**
 * @brief 反転可能平衡二分木(基底クラス)
 */
#line 2 "lct/splay-base.hpp"

template <typename Node>
struct SplayTreeBase {
  using Ptr = Node *;
  template <typename... Args>
  Ptr my_new(const Args &...args) {
    return new Node(args...);
  }
  void my_del(Ptr p) { delete p; }

  bool is_root(Ptr t) { return !(t->p) || (t->p->l != t && t->p->r != t); }

  int size(Ptr t) const { return count(t); }

  virtual void splay(Ptr t) {
    if (!t) return;
    push(t);
    while (!is_root(t)) {
      Ptr q = t->p;
      if (is_root(q)) {
        push(q), push(t);
        rot(t);
      } else {
        Ptr r = q->p;
        push(r), push(q), push(t);
        if (pos(q) == pos(t))
          rot(q), rot(t);
        else
          rot(t), rot(t);
      }
    }
  }

  Ptr get_left(Ptr t) {
    while (t->l) push(t), t = t->l;
    return t;
  }

  Ptr get_right(Ptr t) {
    while (t->r) push(t), t = t->r;
    return t;
  }

  std::pair<Ptr, Ptr> split(Ptr t, int k) {
    if (!t) return {nullptr, nullptr};
    if (k == 0) return {nullptr, t};
    if (k == count(t)) return {t, nullptr};
    push(t);
    if (k <= count(t->l)) {
      auto x = split(t->l, k);
      t->l = x.second;
      t->p = nullptr;
      if (x.second) x.second->p = t;
      return {x.first, update(t)};
    } else {
      auto x = split(t->r, k - count(t->l) - 1);
      t->r = x.first;
      t->p = nullptr;
      if (x.first) x.first->p = t;
      return {update(t), x.second};
    }
  }

  Ptr merge(Ptr l, Ptr r) {
    if (!l && !r) return nullptr;
    if (!l) return splay(r), r;
    if (!r) return splay(l), l;
    splay(l), splay(r);
    l = get_right(l);
    splay(l);
    l->r = r;
    r->p = l;
    update(l);
    return l;
  }

  using Key = decltype(Node::key);
  Ptr build(const std::vector<Key> &v) { return build(0, v.size(), v); }
  Ptr build(int l, int r, const std::vector<Key> &v) {
    if (l == r) return nullptr;
    if (l + 1 == r) return my_new(v[l]);
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

  template <typename... Args>
  void insert(Ptr &t, int k, const Args &...args) {
    splay(t);
    auto x = split(t, k);
    t = merge(merge(x.first, my_new(args...)), x.second);
  }

  void erase(Ptr &t, int k) {
    splay(t);
    auto x = split(t, k);
    auto y = split(x.second, 1);
    my_del(y.first);
    t = merge(x.first, y.second);
  }

  virtual Ptr update(Ptr t) = 0;

protected:
  inline int count(Ptr t) const { return t ? t->cnt : 0; }

  virtual void push(Ptr t) = 0;

  Ptr build(const std::vector<Ptr> &v) { return build(0, v.size(), v); }

  Ptr build(int l, int r, const std::vector<Ptr> &v) {
    if (l + 1 >= r) return v[l];
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

  inline int pos(Ptr t) {
    if (t->p) {
      if (t->p->l == t) return -1;
      if (t->p->r == t) return 1;
    }
    return 0;
  }

  virtual void rot(Ptr t) {
    Ptr x = t->p, y = x->p;
    if (pos(t) == -1) {
      if ((x->l = t->r)) t->r->p = x;
      t->r = x, x->p = t;
    } else {
      if ((x->r = t->l)) t->l->p = x;
      t->l = x, x->p = t;
    }
    update(x), update(t);
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }
};

/**
 * @brief Splay Tree(base)
 */
#line 5 "lct/splay-reversible.hpp"

template <typename T>
struct ReversibleSplayTreeNode {
  using Ptr = ReversibleSplayTreeNode *;
  Ptr l, r, p;
  T key, sum;
  int cnt;
  bool rev;

  ReversibleSplayTreeNode(const T &t = T())
      : l(), r(), p(), key(t), sum(t), cnt(1), rev(false) {}
};

template <typename T, T (*f)(T, T), T (*ts)(T)>
struct ReversibleSplayTree
    : ReversibleBBST<SplayTreeBase<ReversibleSplayTreeNode<T>>,
        ReversibleSplayTreeNode<T>, T, f, ts> {
  using Node = ReversibleSplayTreeNode<T>;
};

/**
 * @brief 反転可能Splay Tree
 */
#line 4 "lct/link-cut-tree.hpp"

//
#line 2 "lct/link-cut-base.hpp"

template <typename Splay>
struct LinkCutBase : Splay {
  using Node = typename Splay::Node;
  using Ptr = Node*;

  virtual Ptr expose(Ptr t) {
    Ptr rp = nullptr;
    for (Ptr cur = t; cur; cur = cur->p) {
      this->splay(cur);
      cur->r = rp;
      this->update(cur);
      rp = cur;
    }
    this->splay(t);
    return rp;
  }

  virtual void link(Ptr u, Ptr v) {
    evert(u);
    expose(v);
    u->p = v;
  }

  void cut(Ptr u, Ptr v) {
    evert(u);
    expose(v);
    assert(u->p == v);
    v->l = u->p = nullptr;
    this->update(v);
  }

  void evert(Ptr t) {
    expose(t);
    this->toggle(t);
    this->push(t);
  }

  Ptr lca(Ptr u, Ptr v) {
    if (get_root(u) != get_root(v)) return nullptr;
    expose(u);
    return expose(v);
  }

  Ptr get_kth(Ptr x, int k) {
    expose(x);
    while (x) {
      this->push(x);
      if (x->r && x->r->sz > k) {
        x = x->r;
      } else {
        if (x->r) k -= x->r->sz;
        if (k == 0) return x;
        k -= 1;
        x = x->l;
      }
    }
    return nullptr;
  }

  Ptr get_root(Ptr x) {
    expose(x);
    while (x->l) this->push(x), x = x->l;
    return x;
  }

  Ptr get_parent(Ptr x) {
    expose(x);
    Ptr p = x->l;
    if(p == nullptr) return nullptr;
    while (true) {
      this->push(p);
      if (p->r == nullptr) return p;
      p = p->r;
    }
    exit(1);
  }

  virtual void set_key(Ptr t, const decltype(Node::key)& key) {
    this->splay(t);
    t->key = key;
    this->update(t);
  }

  virtual decltype(Node::key) get_key(Ptr t) { return t->key; }

  decltype(Node::key) fold(Ptr u, Ptr v) {
    evert(u);
    expose(v);
    return v->sum;
  }
};

/**
 * @brief Link/Cut Tree(base)
 * @docs docs/lct/link-cut-tree.md
 */
#line 7 "lct/link-cut-tree.hpp"

template <typename T, T (*f)(T, T), T (*ts)(T)>
struct LinkCutTree : LinkCutBase<ReversibleSplayTree<T, f, ts>> {};

using T = std::pair<int, int>;
T f(T a, T b) { return {a.first + b.first, a.second ^ b.second}; }
T ts(T a) { return a; }

inline int reduce(auto&& a, auto&& mod) noexcept {
  if (a >= mod) {
    a %= mod;
  }
  if (a < 0) {
    a += mod;
  }
  return a;
}

constexpr int mod = 998244353;

void solve() {
  int n, q;
  scan(n, q);

  using LCT = LinkCutTree<T, f, ts>;
  LCT lct;

  std::vector<LCT::Ptr> vs(n + 1);
  for (int i = 0; i <= n; ++i) {
    vs[i] = lct.my_new(T{1, i});
  }

  int X = 0;
  while (q-- > 0) {
    int a, b, c;
    scan(a, b, c);

    const auto A = 1 + reduce(reduce(a * 1LL * (1 + X), mod), 2);
    const auto B = 1 + reduce(reduce(b * 1LL * (1 + X), mod), n);
    const auto C = 1 + reduce(reduce(c * 1LL * (1 + X), mod), n);

    if (A == 1) {
      lct.link(vs[B], vs[C]);
    } else {
      if (lct.get_root(vs[B]) != lct.get_root(vs[C])) {
        X = 0;
      } else {
        const auto [cnt, all] = lct.fold(vs[B], vs[C]);
        X = cnt == 3 ? (all ^ B ^ C) : 0;
      }
      println(X);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}