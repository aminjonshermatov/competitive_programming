//
// Created by aminjon on 4/13/23.
//
#ifdef LOCAL
#include "constants.h"
#include "debug.h"
#else
#define dbg(...) 42
#endif
#include <bits/stdc++.h>

using namespace std;

template <size_t ALPHA = 27, char MIN_ALPHA = 'a' - 1>
vector<int> suffix_array(string_view s) {
  assert(all_of(s.begin(), s.end(), [](char ch) { return clamp<char>(ch, MIN_ALPHA, MIN_ALPHA + ALPHA - 1) == ch; }));
  assert(s.back() == MIN_ALPHA);

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

template <size_t ALPHA = 27, char MIN_ALPHA = 'a' - 1>
decltype(auto) lcp_array(string_view s) {
  assert(s.back() == MIN_ALPHA);

  const auto n = static_cast<int>(s.size());
  const auto sa = suffix_array<ALPHA, MIN_ALPHA>(s);
  vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[sa[i]] = i;
  }
  vector<int> lcp(n, 0); // lcp(s[sa[i]], s[sa[i + 1]])
  int k = 0;
  for (int i = 0; i < n; ++i) {
    k = max(k - 1, 0);
    if (pos[i] == n - 1) continue;
    auto j = sa[pos[i] + 1];
    while (s[i + k] == s[j + k]) ++k;
    lcp[pos[i]] = k;
  }

  --lcp.back();
  return tuple{lcp, sa};
}

constexpr int P = 223, mod = 1000003643;
inline int add(int a, int b) { return (a + 0ll + b) % mod; }
inline int mul(int a, int b) { return (a * 1ll * b) % mod; }
inline int sub(int a, int b) { return (a + 0ll + mod - b) % mod; }

void solve(istream &in, ostream &out) {
  string a, b;
  int k;
  in >> a >> b >> k;

  a.push_back('0' - 1);
  b.push_back('0' - 1);

  const auto na = int(a.size());
  const auto nb = int(b.size());

  const auto [lcpA, saA] = lcp_array<3, '0' - 1>(a);
  const auto [lcpB, saB] = lcp_array<3, '0' - 1>(b);

  dbg(saA);
  dbg(lcpA);
  dbg(saB);
  dbg(lcpB);

  const auto nmx = max(na, nb);
  vector<int> pw(nmx + 1);
  pw[0] = 1;
  for (int i = 1; i <= nmx; ++i) {
    pw[i] = mul(pw[i - 1], P);
  }

  vector<int> hA(na);
  for (int i = 0; i < na; ++i) {
    hA[i] = add(mul(i > 0 ? hA[i - 1] : 0, P), a[i] - '0' + 1);
  }
  vector<int> hB(nb);
  for (int i = 0; i < nb; ++i) {
    hB[i] = add(mul(i > 0 ? hB[i - 1] : 0, P), b[i] - '0' + 1);
  }

  const auto get_hash = [&](vector<int> &hs, int l, int r) -> int {
    assert(0 <= l && l <= r && r < hs.size());
    return sub(hs[r], l > 0 ? mul(hs[l - 1], pw[r - l + 1]) : 0);
  };

  const auto is_less = [&](int a_i, int a_len, int b_i, int b_len) -> bool {
    int lo = 0, hi = min(a_len, b_len) + 1;
    while (hi - lo > 1) {
      auto mid = lo + (hi - lo) / 2;
      (sub(get_hash(hA, a_i, a_i + mid - 1), get_hash(hB, b_i, b_i + mid - 1)) == 0 ? lo : hi) = mid;
    }
    if (lo >= a_len && lo >= b_len) return false;
    if (lo >= a_len) return false;
    if (lo >= b_len) return true;
    return a[a_i + lo] < b[b_i + lo];
  };

  const auto get_common = [&](int i, int j) -> int {
    assert(clamp(i, 0, na - 1) == i);
    assert(clamp(j, 0, nb - 1) == j);
    int lo = 0, hi = min(na - i - 1, nb - j - 1) + 1;
    while (hi - lo > 1) {
      auto mid = lo + (hi - lo) / 2;
      (sub(get_hash(hA, i, i + mid - 1), get_hash(hB, j, j + mid - 1)) == 0 ? lo : hi) = mid;
    }
    return lo;
  };

  int ptr_a = 1, ptr_b = 1;
  int offset = 0;
  for (; ptr_a < na && ptr_b < nb && k > 0;) {
    const auto common = get_common(saA[ptr_a], saB[ptr_b]);

    auto d = common - offset;
    dbg(ptr_a, ptr_b, saA[ptr_a], saB[ptr_b], k, common, offset, d);
    if (k <= d) {
      out << a.substr(saA[ptr_a], offset + k) << '\n';
      return;
    }
    k -= max(d, 0);
    offset = common;
    // assert(a.substr(saA[ptr_a], na - saA[ptr_a]) < b.substr(saB[ptr_b], nb - saB[ptr_b]) == is_less(saA[ptr_a], na - saA[ptr_a], saB[ptr_b], nb - saB[ptr_b]));
    ++(is_less(saA[ptr_a], na - saA[ptr_a], saB[ptr_b], nb - saB[ptr_b]) ? ptr_a : ptr_b);
  }
  out << "???? i'm wrong\n";
}

int main() {
  auto in = ifstream(constants::DATA_IN);
  auto out = ofstream(constants::FAST_OUT);
  solve(in, out);

  return 0;
}
