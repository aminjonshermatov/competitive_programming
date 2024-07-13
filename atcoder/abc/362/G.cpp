#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("tree-vectorize")
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

decltype(auto) SuffixArray(auto&& s, const std::size_t sigma, auto&& minAlpha) {
  static_assert(
    std::is_same_v<typename std::remove_cvref_t<decltype(s)>::value_type, std::remove_cvref_t<decltype(minAlpha)>>);
  assert(std::all_of(s.begin(), s.end(), [&sigma, &minAlpha](auto&& x) {
    return std::clamp<std::remove_cvref_t<decltype(minAlpha)>>(x, minAlpha, minAlpha + sigma - 1) == x;
  }));
  assert(s.back() == minAlpha);

  const auto n = s.size();
  const auto m = std::max(sigma, n) + 1;
  std::vector<std::size_t> sa(n), cls(n), cnt(m);
  for (auto&& ch: s) {
    ++cnt[ch - minAlpha];
  }
  for (std::size_t i{1}; i < m; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (std::size_t i{}; i < n; ++i) {
    sa[--cnt[s[i] - minAlpha]] = i;
  }
  cls[sa[0]] = std::size_t{};
  for (std::size_t i{1}; i < n; ++i) {
    cls[sa[i]] = cls[sa[i - 1]] + (s[sa[i - 1]] != s[sa[i]]);
  }

  std::vector<std::size_t> nsa(n), ncls(n);
  for (std::size_t k{1}; k < n; k <<= 1) {
    for (std::size_t i{}; i < n; ++i) {
      nsa[i] = (sa[i] + n - k) % n;
    }
    std::ranges::fill(cnt, std::size_t{});
    for (std::size_t i{}; i < n; ++i) {
      ++cnt[cls[nsa[i]]];
    }
    for (std::size_t i{1}; i < m; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (std::size_t i = n - 1; i + 1 > std::size_t{}; --i) {
      sa[--cnt[cls[nsa[i]]]] = nsa[i];
    }
    ncls[sa[0]] = std::size_t{};
    for (std::size_t i{1}; i < n; ++i) {
      ncls[sa[i]] = ncls[sa[i - 1]] + (std::pair(cls[sa[i]], cls[(sa[i] + k) % n]) !=
                                   std::pair(cls[sa[i - 1]], cls[(sa[i - 1] + k) % n]));
    }
    ncls.swap(cls);
  }

  return sa;
}

decltype(auto) LCPArray(auto&& s, const std::size_t sigma, auto&& minAlpha) {
  assert(s.back() == minAlpha);

  const auto n = s.size();
  auto&& sa = SuffixArray(std::forward<decltype(s)>(s), sigma,
                          std::forward<decltype(minAlpha)>(minAlpha));
  std::vector<std::size_t> isa(n);
  for (std::size_t i{}; i < n; ++i) {
    isa[sa[i]] = i;
  }
  std::vector<std::size_t> lcp(n); // lcp(s[sa[i]], s[sa[i + 1]])
  std::size_t k{};
  for (std::size_t i{}; i < n; ++i) {
    k = k == std::size_t{} ? std::size_t{} : (k - 1);
    if (isa[i] == n - 1) {
      continue;
    }
    auto&& j = sa[isa[i] + 1];
    while (s[i + k] == s[j + k]) {
      ++k;
    }
    lcp[isa[i]] = k;
  }

  return std::tuple(std::move(lcp), std::move(sa), std::move(isa));
}

void solve() {
  std::string s;
  int q;
  scan(s, q);
  std::vector<std::string> ss(q);
  for (auto&& s : ss) {
    scan(s);
  }

  const char min1 = char('a' - 1);
  const char min2 = char('a' - 2);
  auto S = s;
  S.push_back(min1);
  std::vector<std::tuple<int, int, int>> pos;
  for (int i = 0; i < q; ++i) {
    pos.emplace_back(S.size(), ss[i].size(), i);
    S.append(ss[i]);
    S.push_back(i + 1 == q ? min2 : min1);
  }
  auto&& [lcp, sa, isa] = LCPArray(S, 28, min2);
  std::vector<int> pf(S.size());
  for (int i = 0; i < sa.size(); ++i) {
    if (i > 0) {
      pf[i] += pf[i - 1];
    }
    if (sa[i] < s.size()) {
      ++pf[i];
    }
  }
  auto get = [&](int l, int r) {
    l = std::max(l, 0);
    r = std::min(r, int(sa.size()) - 1);
    if (l > r) {
      return 0;
    }
    return pf[r] - (l > 0 ? pf[l - 1] : 0);
  };

  const int B = std::__lg(2 * int(sa.size()) - 1) + 1;
  constexpr auto inf = std::numeric_limits<int>::max() / 2;
  std::vector rmq(B, std::vector<int>(sa.size(), inf));
  for (int i = 0; i < lcp.size(); ++i) {
    rmq[0][i] = lcp[i];
  }
  for (int l = 0; l + 1 < B; ++l) {
    for (int i = 0; i + (2 << l) <= sa.size(); i++) {
      rmq[l+1][i] = std::min(rmq[l][i], rmq[l][i + (1 << l)]);
    }
  }
  auto qry = [&](int l, int r) {
    if (l == r) return inf;
    const auto len = std::__lg(r - l);
    return std::min(rmq[len][l], rmq[len][r - (1 << len)]);
  };
  std::vector<int> ret(q);
  for (auto&& [i_, len, id] : pos) {
    auto&& i = isa[i_];
    int L = i, R = i;
    if (i > 0 && lcp[i - 1] >= len) {
      int lo = 1, hi = i + 1;
      while (hi - lo > 1) {
        const auto mid = lo + (hi - lo) / 2;
        (qry(i - mid, i) >= len ? lo : hi) = mid;
      }
      L = i - lo;
    }
    if (lcp[i] >= len) {
      int lo = 1, hi = sa.size() - i;
      while (hi - lo > 1) {
        const auto mid = lo + (hi - lo) / 2;
        (qry(i, i + mid) >= len ? lo : hi) = mid;
      }
      R = i + lo;
    }
    ret[id] = get(L, R);
  }
  for (auto&& x : ret) {
    println(x);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef LOCAL
  freopen("../../input.txt", "r", stdin);
#endif

  solve();
}