#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}

template <typename T>
class Modular {
  public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }

  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }

  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }

  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
            "divl %4; \n\t"
            : "=a" (d), "=d" (m)
            : "d" (xh), "a" (xl), "r" (mod())
    );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type& operator*=(const Modular& rhs) {
    long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

  friend const Type& abs(const Modular& x) { return x.value; }

  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename V, typename U>
  friend V& operator>>(V& stream, Modular<U>& number);

  private:
  Type value;
};

template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

template <typename T>
bool IsZero(const Modular<T>& number) {
  return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
  return stream << number();
}

// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, long long>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay_t<decltype(md)>, md>>;

class Dsu {
  int n;
  vector<int> parent, rank;

  public:
  explicit Dsu(int n_) : n(n_) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    rank.assign(n, 1);
  }

  auto find(int v) -> int {
    assert(0 <= v && v < n);
    if (parent[v] != v) parent[v] = find(parent[v]);
    return parent[v];
  }

  auto merge(int v, int u) -> int {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    auto pv = find(v);
    auto pu = find(u);
    if (pv == pu) return pv;

    if (rank[pv] < rank[pu]) swap(pv, pu);
    parent[pu] = pv;
    rank[pv] += rank[pv] == rank[pu];
    return pv;
  }

  auto is_same(int v, int u) -> bool {
    assert(0 <= v && v < n);
    assert(0 <= u && u < n);
    return find(v) == find(u);
  }
};

struct Node {
  Node *left, *right;
  int64_t priority;
  int size;
  Mint promise;
  Mint exp;
  int id;

  explicit Node(int id_ = -1)
      : left{nullptr}, right{nullptr}
        , priority{(int64_t(rand()) << 16) ^ rand()}
        , size{1}
        , promise{0}
        , exp{0}
        , id(id_) { }
};

int size(Node *node) {
  if (node == nullptr) return 0;
  return node->size;
}

Mint exp(Node *node) {
  if (node == nullptr) return 0;
  return node->exp;
}

void add_promise(Node *node, Mint pr) {
  if (node == nullptr) return;
  node->promise += pr;
}

void push(Node *node) {
  if (node == nullptr) return;
  node->exp += node->promise;

  add_promise(node->left, node->promise);
  add_promise(node->right, node->promise);
  node->promise = 0;
}

void update(Node *node) {
  if (node == nullptr) return;
  push(node->left);
  push(node->right);
  node->size = 1 + size(node->left) + size(node->right);
}

Node *merge(Node *root_l, Node *root_r) {
  push(root_l);
  push(root_r);
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

pair<Node*, Node*> split(Node *root, int32_t sz) {
  if (root == nullptr) return {nullptr, nullptr};

  push(root);
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
  int n; cin >> n;
  Dsu dsu(n);

  vector<Node*> nodes(n, nullptr);
  for (int i = 0; i < n; ++i) {
    nodes[i] = new Node(i);
  }

  auto F = [&](auto &f, Node *node) -> void {
    push(node);
    dbg(node->id, node->exp);
    for (auto ch : {node->left, node->right}) {
      if (ch != nullptr) {
        f(f, ch);
      }
    }
  };

  for (int i = 1; i < n; ++i) {
    int p, q; cin >> p >> q;
    --p, --q;
    assert(!dsu.is_same(p, q));
    p = dsu.find(p);
    q = dsu.find(q);
    assert(nodes[p] != nullptr);
    assert(nodes[q] != nullptr);
    auto pn = nodes[p];
    auto qn = nodes[q];
    auto p_sz = size(pn);
    auto q_sz = size(qn);
    auto pe = Mint(p_sz) / (p_sz + q_sz);
    add_promise(pn, pe);
    // dbg(p_sz, p_sz+q_sz, pe);
    F(F, pn);
    auto qe = Mint(q_sz) / (p_sz + q_sz);
    add_promise(qn, qe);
    // dbg(q_sz, p_sz+q_sz, qe);
    F(F, qn);
    nodes[p] = nodes[q] = nullptr;
    auto x = dsu.merge(p, q);
    nodes[x] = merge(pn, qn);
  }
  vector<Mint> ans(n);
  vector<bool> seen(n, false);
  auto dfs = [&](auto &f, Node *node) -> void {
    assert(node->id != -1);
    assert(!seen[node->id]);
    seen[node->id] = true;
    ans[node->id] = node->exp;
    for (auto ch : {node->left, node->right}) {
      if (ch == nullptr) continue;
      assert(ch->id != -1);
      if (!seen[ch->id]) {
        f(f, ch);
      }
    }
  };
  for (auto node : nodes) {
    if (node == nullptr) continue;
    assert(node->id != -1);
    if (!seen[node->id]) {
      dfs(dfs, node);
    }
  }
  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << '\n';
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
