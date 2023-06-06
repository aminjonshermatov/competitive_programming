#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

template<typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a;
    swap(a, m);
    u -= t * v;
    swap(u, v);
  }
  assert(m == 1);
  return u;
}

template<typename T>
class Modular {
  public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template<typename U>
  Modular(const U &x) {
    value = normalize(x);
  }

  template<typename U>
  static Type normalize(const U &x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else
      v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }

  const Type &operator()() const { return value; }
  template<typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular &operator+=(const Modular &other) {
    if ((value += other.value) >= mod()) value -= mod();
    return *this;
  }
  Modular &operator-=(const Modular &other) {
    if ((value -= other.value) < 0) value += mod();
    return *this;
  }
  template<typename U>
  Modular &operator+=(const U &other) { return *this += Modular(other); }
  template<typename U>
  Modular &operator-=(const U &other) { return *this -= Modular(other); }
  Modular &operator++() { return *this += 1; }
  Modular &operator--() { return *this -= 1; }
  Modular operator++(int) {
    Modular result(*this);
    *this += 1;
    return result;
  }
  Modular operator--(int) {
    Modular result(*this);
    *this -= 1;
    return result;
  }
  Modular operator-() const { return Modular(-value); }

  template<typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type &operator*=(const Modular &rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
            "divl %4; \n\t"
            : "=a"(d), "=d"(m)
            : "d"(xh), "a"(xl), "r"(mod()));
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template<typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type &operator*=(const Modular &rhs) {
    long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template<typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type &operator*=(const Modular &rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Modular &operator/=(const Modular &other) { return *this *= Modular(inverse(other.value, mod())); }

  friend const Type &abs(const Modular &x) { return x.value; }

  template<typename U>
  friend bool operator==(const Modular<U> &lhs, const Modular<U> &rhs);

  template<typename U>
  friend bool operator<(const Modular<U> &lhs, const Modular<U> &rhs);

  template<typename V, typename U>
  friend V &operator>>(V &stream, Modular<U> &number);

  private:
  Type value;
};

template<typename T>
bool operator==(const Modular<T> &lhs, const Modular<T> &rhs) { return lhs.value == rhs.value; }
template<typename T, typename U>
bool operator==(const Modular<T> &lhs, U rhs) { return lhs == Modular<T>(rhs); }
template<typename T, typename U>
bool operator==(U lhs, const Modular<T> &rhs) { return Modular<T>(lhs) == rhs; }

template<typename T>
bool operator!=(const Modular<T> &lhs, const Modular<T> &rhs) { return !(lhs == rhs); }
template<typename T, typename U>
bool operator!=(const Modular<T> &lhs, U rhs) { return !(lhs == rhs); }
template<typename T, typename U>
bool operator!=(U lhs, const Modular<T> &rhs) { return !(lhs == rhs); }

template<typename T>
bool operator<(const Modular<T> &lhs, const Modular<T> &rhs) { return lhs.value < rhs.value; }

template<typename T>
Modular<T> operator+(const Modular<T> &lhs, const Modular<T> &rhs) { return Modular<T>(lhs) += rhs; }
template<typename T, typename U>
Modular<T> operator+(const Modular<T> &lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template<typename T, typename U>
Modular<T> operator+(U lhs, const Modular<T> &rhs) { return Modular<T>(lhs) += rhs; }

template<typename T>
Modular<T> operator-(const Modular<T> &lhs, const Modular<T> &rhs) { return Modular<T>(lhs) -= rhs; }
template<typename T, typename U>
Modular<T> operator-(const Modular<T> &lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template<typename T, typename U>
Modular<T> operator-(U lhs, const Modular<T> &rhs) { return Modular<T>(lhs) -= rhs; }

template<typename T>
Modular<T> operator*(const Modular<T> &lhs, const Modular<T> &rhs) { return Modular<T>(lhs) *= rhs; }
template<typename T, typename U>
Modular<T> operator*(const Modular<T> &lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template<typename T, typename U>
Modular<T> operator*(U lhs, const Modular<T> &rhs) { return Modular<T>(lhs) *= rhs; }

template<typename T>
Modular<T> operator/(const Modular<T> &lhs, const Modular<T> &rhs) { return Modular<T>(lhs) /= rhs; }
template<typename T, typename U>
Modular<T> operator/(const Modular<T> &lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template<typename T, typename U>
Modular<T> operator/(U lhs, const Modular<T> &rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T> &a, const U &b) {
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

template<typename T>
bool IsZero(const Modular<T> &number) {
  return number() == 0;
}

template<typename T>
string to_string(const Modular<T> &number) {
  return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template<typename U, typename T>
U &operator<<(U &stream, const Modular<T> &number) {
  return stream << number();
}

// U == std::istream? but done this way because of fastinput
template<typename U, typename T>
U &operator>>(U &stream, Modular<T> &number) {
  typename common_type<typename Modular<T>::Type, long long>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}

/*
using ModType = int;

struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/

constexpr int md = 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

vector<Mint> fact(1, 1);
vector<Mint> tcaf(1, 1);

Mint C(int n, int k) {
  if (k < 0 || k > n) return 0;
  while ((int) fact.size() < n + 1) {
    fact.push_back(fact.back() * (int) fact.size());
    tcaf.push_back(1 / fact.back());
  }
  return fact[n] * tcaf[k] * tcaf[n - k];
}

template<typename T = int>
struct SegmentTree {

  const T DEFAULT_VALUE = T(0);
  const T DEFAULT_LAZY = T(0);

  template<typename U>
  struct Node {
    U val;
    U lazy;
    int right;
    bool has_lazy;

    void apply([[maybe_unused]] int l, [[maybe_unused]] int r, U v) {
      val += v;
      lazy += v;
      has_lazy = true;
    }

    template<typename V>
    static Node unite(const Node<V> &a, const Node<V> &b) {
      return Node{
              a.val + b.val,
              0,
              b.right,
              false};
    }
  };

  const Node<T> NEUTRAL_ELEMENT = {DEFAULT_VALUE, DEFAULT_LAZY, -1, false};

  int size;
  vector<Node<T>> tree;

  SegmentTree() = default;
  explicit SegmentTree(int n) {
    size = 1;
    while (size < n) size <<= 1;
    tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
    build(0, 0, size);
  }
  template<typename U = T>
  explicit SegmentTree(vector<U> &A) : SegmentTree(A.size()) {
    size = 1;
    while (size < A.size()) size <<= 1;
    tree.assign(2 * size - 1, NEUTRAL_ELEMENT);
    build(A, 0, 0, size);
  }

  void init(int n) {
    size = 1;
    while (size < n) size <<= 1;
    tree.resize(2 * size - 1);
    build(0, 0, size);
  }

  inline void push(int x, int lx, int rx) {
    if (rx - lx == 1 || !tree[x].has_lazy) return;

    auto mid = lx + (rx - lx) / 2;
    tree[2 * x + 1].apply(lx, mid, tree[x].lazy);
    tree[2 * x + 2].apply(mid, rx, tree[x].lazy);
    tree[x].lazy = DEFAULT_LAZY;
    tree[x].has_lazy = false;
  }

  inline void pull(int x) {
    tree[x] = Node<T>::unite(tree[2 * x + 1], tree[2 * x + 2]);
  }

  void build(int x, int lx, int rx) {
    if (rx - lx == 1) {
      tree[x] = {DEFAULT_VALUE, DEFAULT_LAZY, lx, false};
      return;
    }

    auto mid = lx + (rx - lx) / 2;
    build(2 * x + 1, lx, mid);
    build(2 * x + 2, mid, rx);
    pull(x);
  }

  template<typename U = T>
  void build(vector<U> &A, int x, int lx, int rx) {
    if (rx - lx == 1) {
      if (lx < A.size()) tree[x] = {A[lx], DEFAULT_LAZY, lx, false};
      return;
    }

    auto mid = lx + (rx - lx) / 2;
    build(A, 2 * x + 1, lx, mid);
    build(A, 2 * x + 2, mid, rx);
    pull(x);
  }

  void modify(int l, int r, T v, int x, int lx, int rx) {
    push(x, lx, rx);
    if (l >= rx || r <= lx) return;
    if (l <= lx && rx <= r) {
      tree[x].apply(lx, rx, v);
      return;
    }

    auto mid = lx + (rx - lx) / 2;
    modify(l, r, v, 2 * x + 1, lx, mid);
    modify(l, r, v, 2 * x + 2, mid, rx);
    pull(x);
  }

  void modify(int idx, T v) { modify(idx, idx, v, 0, 0, size); }
  void modify(int l, int r, T v) { modify(l, r, v, 0, 0, size); }

  Node<T> query(int l, int r, int x, int lx, int rx) {
    push(x, lx, rx);
    if (l >= rx || r <= lx) return NEUTRAL_ELEMENT;
    if (l <= lx && rx <= r) return tree[x];

    auto mid = lx + (rx - lx) / 2;
    auto res = Node<T>::unite(query(l, r, 2 * x + 1, lx, mid),
                              query(l, r, 2 * x + 2, mid, rx));
    pull(x);
    return res;
  }

  T query(int l, int r) { return query(l, r, 0, 0, size).val; }
  T query(int idx) { return query(idx, idx + 1, 0, 0, size).val; }

  template<typename Op>
  T get_first(T v, int i, int x, int lx, int rx, Op &op) {
    if (!op(tree[x].val, v) || tree[x].right < i) return -1;
    if (rx - lx == 1) return lx;

    auto mid = lx + (rx - lx) / 2;
    auto res = get_first(v, i, 2 * x + 1, lx, mid, op);
    if (res == -1) res = get_first(v, i, 2 * x + 2, mid, rx, op);
    return res;
  }

  template<typename Op>
  T get_first(T v, int i, Op &op) {
    return get_first(v, i, 0, 0, size, op);
  }

  template<typename U>
  friend ostream &operator<<(ostream &out, const SegmentTree<U> &st) {
    for (auto i = 1u, j = 0u; j < st.tree.size(); i <<= 1) {
      auto c = 0u;
      while (c++ < i) out << st.tree[j].val << ',' << st.tree[j++].lazy << ' ';
      out << '\n';
    }
    return out;
  }
};

template <typename T = int> struct FenwickTreePointUpdateRangeQuery {
  int n;
  vector<T> bit;

  FenwickTreePointUpdateRangeQuery() = default;
  explicit FenwickTreePointUpdateRangeQuery(int n_) : n(n_), bit(n_, T(0))  { }
  template<typename U = T> explicit FenwickTreePointUpdateRangeQuery(const vector<U> &A) : n(A.size()), bit(A.size(), T(0)) {
    for (auto idx = 0u; idx < n; ++idx) modify(idx, A[idx]);
  }

  void init(int n_) {
    n = n_;
    bit.assign(n, T(0));
  }

  auto modify(int idx, T val) -> void {
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += val;
  }

  [[nodiscard]] auto query(int idx) const -> T {
    T ret = T(0);
    for (; idx >= 0; idx = (idx & (idx + 1)) - 1) ret += bit[idx];
    return ret;
  }

  [[nodiscard]] auto query(int l, int r) const -> T { // [l, r)
    return query(r - 1) - query(l - 1);
  }

};

constexpr int X = 37;

void solve() {
  string a, b;
  cin >> a >> b;
  int t, q;
  cin >> t >> q;

  const int n = static_cast<int>(a.size());
  const int m = static_cast<int>(b.size());

  SegmentTree<Mint> hashA(n), hashB(m);
  FenwickTreePointUpdateRangeQuery<int> hasA(n), hasB(m);
  for (int i = 0; i < n; ++i) {
    hashA.modify(i, i + 1, power(Mint(X), n - i - 1) * (a[i] - 'a' + 1));
    hasA.modify(i, 1);
  }
  for (int i = 0; i < m; ++i) {
    hashB.modify(i, i + 1, power(Mint(X), m - i - 1) * (b[i] - 'a' + 1));
    hasB.modify(i, 1);
  }

  multiset<pair<int, int>> add;
  int AAlive = n, BAlive = m;
  for (int i = 1; i <= q; ++i) {
    while (!add.empty() && add.begin()->first <= i) {
      ++AAlive; ++BAlive;
      auto [_, pos] = *add.begin(); add.erase(add.begin());
      hasA.modify(pos, 1);
      hashA.modify(0, pos, X);
      hashA.modify(pos, pos + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos)) * (a[pos] - 'a' + 1));
      hasB.modify(pos, 1);
      hashB.modify(0, pos, X);
      hashB.modify(pos, pos + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos)) * (b[pos] - 'a' + 1));
    }

    char cmd; cin >> cmd;
    if (cmd == '1') {
      int pos; cin >> pos;
      --pos;
      auto xA = hasA.query(pos, pos + 1);
      auto xB = hasB.query(pos, pos + 1);
      assert(xA == xB);
      if (xA == 0) continue;

      hashA.modify(pos + 1, n, -X);
      hashA.modify(pos, pos + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos)) * (a[pos] - 'a' + 1) * -1);
      hasA.modify(pos, -1);
      hashB.modify(pos + 1, n, -X);
      hashB.modify(pos, pos + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos)) * (b[pos] - 'a' + 1) * -1);
      hasB.modify(pos, -1);

      --AAlive; --BAlive;
      add.emplace(i + t, pos);
    } else if (cmd == '2') {
      char t1, t2;
      int pos1, pos2;
      cin >> t1 >> pos1 >> t2 >> pos2;
      --pos1, --pos2;

      if (t1 == '1') {
        if (t2 == '1') {
          hashA.modify(pos1, pos1 + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos1)) * (a[pos1] - 'a' + 1) * -1);
          hashA.modify(pos1, pos1 + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos1)) * (a[pos2] - 'a' + 1));
          hashA.modify(pos2, pos2 + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos2)) * (a[pos2] - 'a' + 1) * -1);
          hashA.modify(pos2, pos2 + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos2)) * (a[pos1] - 'a' + 1));
        } else {
          hashA.modify(pos1, pos1 + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos1)) * (a[pos1] - 'a' + 1) * -1);
          hashA.modify(pos1, pos1 + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos1)) * (b[pos2] - 'a' + 1));
          hashB.modify(pos2, pos2 + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos2)) * (b[pos2] - 'a' + 1) * -1);
          hashB.modify(pos2, pos2 + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos2)) * (a[pos1] - 'a' + 1));
        }
      } else {
        if (t2 == '1') {
          hashB.modify(pos1, pos1 + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos1)) * (b[pos1] - 'a' + 1) * -1);
          hashB.modify(pos1, pos1 + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos1)) * (a[pos2] - 'a' + 1));
          hashA.modify(pos2, pos2 + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos2)) * (a[pos2] - 'a' + 1) * -1);
          hashA.modify(pos2, pos2 + 1, power(Mint(X), AAlive - 1 - hasA.query(0, pos2)) * (b[pos1] - 'a' + 1));
        } else {
          hashB.modify(pos1, pos1 + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos1)) * (b[pos1] - 'a' + 1) * -1);
          hashB.modify(pos1, pos1 + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos1)) * (b[pos2] - 'a' + 1));
          hashB.modify(pos2, pos2 + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos2)) * (b[pos2] - 'a' + 1) * -1);
          hashB.modify(pos2, pos2 + 1, power(Mint(X), BAlive - 1 - hasB.query(0, pos2)) * (b[pos1] - 'a' + 1));
        }
      }
    } else if (cmd == '3') {
      cout << (hashA.query(0, n) == hashB.query(0, m) ? "YES" : "NO") << '\n';
    }
  }
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
