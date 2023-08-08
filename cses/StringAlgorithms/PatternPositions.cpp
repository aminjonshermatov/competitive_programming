#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

template <size_t ALPHA = 27, char MIN_ALPHA = 'a' - 1>
vector<int> suffix_array(string_view s) {
  assert(all_of(s.begin(), s.end(), [](char ch) { return clamp<char>(ch, MIN_ALPHA, MIN_ALPHA + ALPHA - 1) == ch; }));

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

auto Min = []<typename T>(const T &lhs, const T &rhs) -> T { return lhs < rhs ? lhs : rhs; };
auto Max = []<typename T>(const T &lhs, const T &rhs) -> T { return lhs > rhs ? lhs : rhs; };

template <typename T, typename Op> struct SparseTable {
  using value_type = T;
  Op op;
  vector<vector<T>> table;
  vector<int> lg;

  template<typename U = T> auto build(const vector<U> &A) -> void {
    table.assign(A.size(), {});
    lg.resize(A.size() + 1);
    lg[0] = -1;
    for (int i = 1; i <= A.size(); ++i) {
      lg[i] = 31 - __builtin_clz(i);
    }
    for (auto i = 0u; i < A.size(); ++i) table[i] = {A[i]};
    for (auto l = 1u, j = 0u; 2 * l <= A.size(); ++j, l <<= 1) {
      for (auto i = 0u; i + 2 * l <= A.size(); ++i) {
        table[i].emplace_back(op(table[i][j], table[i + l][j]));
      }
    }
  }

  SparseTable() = default;
  template<typename U = T> explicit SparseTable(Op &&op_) : op(op_) { }
  template<typename U = T> SparseTable(const vector<U> &A, Op &op_) : op(op_) { build(A); }

  [[nodiscard]] auto query(int l, int r) const -> int {
    assert(l < r);
    const auto b = lg[r - l];
    return op(table[l][b], table[r - (1 << b)][b]);
  }
};

void solve() {
  string t; cin >> t;
  t.push_back('a' - 1);

  const auto n = int(t.size());
  const auto sa = suffix_array(t);

  const SparseTable<int, decltype(Min)> rmq(sa, Min);

  dbg(sa);

  int q; cin >> q;
  for (int i = 0; i < q; ++i) {
    string s; cin >> s;
    const auto ns = int(s.size());

    int ge, g;
    {
      int lo = -1, hi = n;
      while (hi - lo > 1) {
        auto mid = lo + (hi - lo) / 2;
        (t.substr(sa[mid], min(n - sa[mid], ns)) < s ? lo : hi) = mid;
      }
      ge = hi;
    }
    {
      int lo = -1, hi = n;
      while (hi - lo > 1) {
        auto mid = lo + (hi - lo) / 2;
        (t.substr(sa[mid], min(n - sa[mid], ns)) <= s ? lo : hi) = mid;
      }
      g = hi;
    }
    cout << (ge == g ? -1 : rmq.query(ge, g) + 1) << '\n';
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
