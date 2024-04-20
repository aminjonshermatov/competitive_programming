#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

// https://nyaannyaan.github.io/library/rbst/treap.hpp
namespace internal {
  unsigned long long non_deterministic_seed() {
    unsigned long long m =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    m ^= 9845834732710364265uLL;
    m ^= m << 24, m ^= m >> 31, m ^= m << 35;
    return m;
  }
  unsigned long long deterministic_seed() { return 88172645463325252UL; }

// 64 bit の seed 値を生成 (手元では seed 固定)
// 連続で呼び出すと同じ値が何度も返ってくるので注意
// #define RANDOMIZED_SEED するとシードがランダムになる
  unsigned long long seed() {
#if defined(NyaanLocal) && !defined(RANDOMIZED_SEED)
    return deterministic_seed();
#else
    return non_deterministic_seed();
#endif
  }

}  // namespace internal

namespace my_rand {
  using i64 = long long;
  using u64 = unsigned long long;

// [0, 2^64 - 1)
  u64 rng() {
    static u64 _x = internal::seed();
    return _x ^= _x << 7, _x ^= _x >> 9;
  }

// [l, r]
  i64 rng(i64 l, i64 r) {
    assert(l <= r);
    return l + rng() % u64(r - l + 1);
  }

// [l, r)
  i64 randint(i64 l, i64 r) {
    assert(l < r);
    return l + rng() % u64(r - l);
  }

// choose n numbers from [l, r) without overlapping
  std::vector<i64> randset(i64 l, i64 r, i64 n) {
    assert(l <= r && n <= r - l);
    std::unordered_set<i64> s;
    for (i64 i = n; i; --i) {
      i64 m = randint(l, r + 1 - i);
      if (s.find(m) != s.end()) m = r - i;
      s.insert(m);
    }
    std::vector<i64> ret;
    for (auto& x : s) ret.push_back(x);
    return ret;
  }

// [0.0, 1.0)
  double rnd() { return rng() * 5.42101086242752217004e-20; }
// [l, r)
  double rnd(double l, double r) {
    assert(l < r);
    return l + rnd() * (r - l);
  }

  template <typename T>
  void randshf(std::vector<T>& v) {
    int n = v.size();
    for (int i = 1; i < n; i++) swap(v[i], v[randint(0, i + 1)]);
  }

}  // namespace my_rand

using my_rand::randint;
using my_rand::randset;
using my_rand::randshf;
using my_rand::rnd;
using my_rand::rng;

template <typename Node>
struct TreapBase {
  using Ptr = Node *;
  template <typename... Args>
  inline Ptr my_new(Args... args) {
    return new Node(args...);
  }
  Ptr make_tree() { return nullptr; }

  // for avoiding memory leak, activate below
  /*
  using Ptr = shared_ptr<Node>;
  template <typename... Args>
  inline Ptr my_new(Args... args) {
    return make_shared<Node>(args...);
  }
  Ptr make_tree() {return Ptr();}
  */

  int size(Ptr t) const { return count(t); }

  Ptr merge(Ptr l, Ptr r) {
    if (!l || !r) return l ? l : r;
    if (l->pr >= r->pr) {
      push(l);
      l->r = merge(l->r, r);
      return update(l);
    } else {
      push(r);
      r->l = merge(l, r->l);
      return update(r);
    }
  }

  std::pair<Ptr, Ptr> split(Ptr t, int k) {
    if (!t) return {nullptr, nullptr};
    push(t);
    if (k <= count(t->l)) {
      auto s = split(t->l, k);
      t->l = s.second;
      return {s.first, update(t)};
    } else {
      auto s = split(t->r, k - count(t->l) - 1);
      t->r = s.first;
      return {update(t), s.second};
    }
  }

  Ptr build(const std::vector<decltype(Node::key)> &v) {
    int n = v.size();
    std::vector<Ptr> ps;
    ps.reserve(n);
    for (int i = 0; i < n; i++) ps.push_back(my_new(v[i]));
    std::vector<int> p(n, -1), st;
    for (int i = 0; i < n; i++) {
      int prv = -1;
      while (!st.empty() && ps[i]->pr > ps[st.back()]->pr) {
        prv = st.back();
        st.pop_back();
      }
      if (prv != -1) p[prv] = i;
      if (!st.empty()) p[i] = st.back();
      st.push_back(i);
    }
    int root = -1;
    for (int i = 0; i < n; i++) {
      if (p[i] != -1) {
        if (i < p[i]) {
          ps[p[i]]->l = ps[i];
        } else {
          ps[p[i]]->r = ps[i];
        }
      } else
        root = i;
    }
    dfs(ps[root]);
    return ps[root];
  }

  template <typename... Args>
  void insert(Ptr &t, int k, const Args &...args) {
    auto x = split(t, k);
    t = merge(merge(x.first, my_new(args...)), x.second);
  }

  void erase(Ptr &t, int k) {
    auto x = split(t, k);
    t = merge(x.first, split(x.second, 1).second);
  }

protected:
  void dfs(Ptr r) {
    if (r->l) dfs(r->l);
    if (r->r) dfs(r->r);
    update(r);
  }

  inline int count(const Ptr t) const { return t ? t->cnt : 0; }

  virtual void push(Ptr) {}

  virtual Ptr update(Ptr) = 0;
};

template <typename T, typename E>
struct LazyReversibleTreapNode {
  using Treap = TreapBase<LazyReversibleTreapNode>;
  typename Treap::Ptr l, r;
  T key, sum;
  E lazy;
  int cnt;
  uint32_t pr;
  bool rev;

  LazyReversibleTreapNode(const T &t = T(), const E &e = E())
      : l(),
        r(),
        key(t),
        sum(t),
        lazy(e),
        cnt(1),
        pr(my_rand::rng()),
        rev(false) {}
};

template <typename T, typename E, T (*f)(T, T), T (*g)(T, E), E (*h)(E, E),
    T (*ts)(T)>
struct LazyReversibleTreap : TreapBase<LazyReversibleTreapNode<T, E>> {
  using Node = LazyReversibleTreapNode<T, E>;
  using base = TreapBase<LazyReversibleTreapNode<T, E>>;
  using base::merge;
  using base::split;
  using typename base::Ptr;

  LazyReversibleTreap() = default;

  void toggle(Ptr t) {
    if (!t) return;
    std::swap(t->l, t->r);
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

  void apply(Ptr &t, int a, int b, const E &e) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    propagate(y.first, e);
    t = merge(x.first, merge(y.first, y.second));
  }

protected:
  inline T sum(const Ptr t) const { return t ? t->sum : T(); }

  Ptr update(Ptr t) override {
    push(t);
    t->cnt = 1;
    t->sum = t->key;
    if (t->l) t->cnt += t->l->cnt, t->sum = f(t->l->sum, t->sum);
    if (t->r) t->cnt += t->r->cnt, t->sum = f(t->sum, t->r->sum);
    return t;
  }

  void push(Ptr t) override {
    if (t->rev) {
      if (t->l) toggle(t->l);
      if (t->r) toggle(t->r);
      t->rev = false;
    }
    if (t->lazy != E()) {
      if (t->l) propagate(t->l, t->lazy);
      if (t->r) propagate(t->r, t->lazy);
      t->lazy = E();
    }
  }

  void propagate(Ptr t, const E &x) {
    t->lazy = h(t->lazy, x);
    t->key = g(t->key, x);
    t->sum = g(t->sum, x);
  }
};

using T = std::pair<char, bool>;
using E = bool;
T f(T a, T b) { return T(a.first, a.second ^ b.second); }
T g(T a, E b) { return T(a.first, a.second ^ b); }
E h(E a, E b) { return a ^ b; }
T ts(T a) { return a; }

void solve() {
  std::string s;
  std::cin >> s;

  const auto n = int(s.size());

  std::vector<int> pf(n);
  for (int i = 0; i < n; ++i) {
    pf[i] = (i > 0 ? pf[i - 1] : 0) + 1 - (s[i] == '(' || s[i] == ')');
  }
  auto get = [&](int l, int r) {
    return pf[r] - (l > 0 ? pf[l - 1] : 0);
  };

  LazyReversibleTreap<T, E, f, g, h, ts> treap;
  decltype(treap)::Ptr root = nullptr;
  std::stack<std::pair<int, int>> st; // [id, sz]
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(') {
      st.emplace(i, treap.size(root));
    } else if (s[i] == ')') {
      const auto [j, sz] = st.top();
      st.pop();
      const auto cnt = get(j, i);
      if (cnt == 0) {
        continue;
      }
      treap.apply(root, sz, sz + cnt, true);
      treap.reverse(root, sz, sz + cnt);
    } else {
      const auto sz = treap.size(root);
      treap.insert(root, sz, T(s[i], false));
    }
  }
  const auto sz = treap.size(root);
  for (int i = 0; i < sz; ++i) {
    auto [c, f] = treap.fold(root, i, i + 1);
    if (f) {
      if (std::clamp(c, 'a', 'z') == c) {
        c = 'A' + c - 'a';
      } else {
        c = 'a' + c - 'A';
      }
    }
    std::cout << c;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}