//
// Created by aminjon on 8/3/23.
//
#include <bits/stdc++.h>

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