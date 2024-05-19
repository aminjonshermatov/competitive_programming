//
// Created by aminjon on 8/3/23.
//
#include <bits/stdc++.h>

decltype(auto) SuffixArray(auto&& s, const std::size_t alpha, auto&& minAlpha) {
  static_assert(
    std::is_same_v<typename std::remove_reference_t<decltype(s)>::value_type, typename std::remove_reference_t<decltype(minAlpha)>>);
  assert(std::all_of(s.begin(), s.end(), [&](auto&& x) {
    return std::clamp<typename std::remove_reference_t<decltype(minAlpha)>>(x, minAlpha, minAlpha + alpha - 1) == x;
  }));
  assert(s.back() == minAlpha);

  const auto n = s.size();
  const auto m = std::max(alpha, n) + 1;
  std::vector<std::size_t> p(n), c(n), cnt(m);
  for (auto&& ch: s) {
    ++cnt[ch - minAlpha];
  }
  for (std::size_t i{1}; i < m; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (std::size_t i{}; i < n; ++i) {
    p[--cnt[s[i] - minAlpha]] = i;
  }
  c[p[0]] = std::size_t{};
  for (std::size_t i{1}; i < n; ++i) {
    c[p[i]] = c[p[i - 1]] + (s[p[i - 1]] != s[p[i]]);
  }

  std::vector<std::size_t> np(n), nc(n);
  for (std::size_t k{1}; k < n; k <<= 1) {
    for (std::size_t i{}; i < n; ++i) {
      np[i] = (p[i] + n - k) % n;
    }
    std::fill(cnt.begin(), cnt.end(), std::size_t{});
    for (std::size_t i{}; i < n; ++i) {
      ++cnt[c[np[i]]];
    }
    for (std::size_t i = 1; i < m; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (std::size_t i = n - 1; i + 1 > std::size_t{}; --i) {
      p[--cnt[c[np[i]]]] = np[i];
    }
    nc[p[0]] = std::size_t{};
    for (std::size_t i{1}; i < n; ++i) {
      auto&& cur = std::pair(c[p[i]], c[(p[i] + k) % n]);
      auto&& prv = std::pair(c[p[i - 1]], c[(p[i - 1] + k) % n]);
      nc[p[i]] = nc[p[i - 1]] + (cur != prv);
    }
    nc.swap(c);
  }

  return p;
}

decltype(auto) LCPArray(auto&& s, const std::size_t alpha, auto&& minAlpha) {
  assert(s.back() == minAlpha);

  const auto n = s.size();
  auto&& sa = SuffixArray(std::forward<decltype(s)>(s), alpha,
                          std::forward<decltype(minAlpha)>(minAlpha));
  std::vector<std::size_t> pos(n);
  for (std::size_t i{}; i < n; ++i) {
    pos[sa[i]] = i;
  }
  std::vector<std::size_t> lcp(n); // lcp(s[sa[i]], s[sa[i + 1]])
  std::size_t k{};
  for (std::size_t i{}; i < n; ++i) {
    k = k == std::size_t{} ? std::size_t{} : (k - 1);
    if (pos[i] == n - 1) {
      continue;
    }
    auto&& j = sa[pos[i] + 1];
    while (s[i + k] == s[j + k]) {
      ++k;
    }
    lcp[pos[i]] = k;
  }

  return std::pair(std::move(lcp), std::move(sa));
}