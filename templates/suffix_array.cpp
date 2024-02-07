//
// Created by aminjon on 8/3/23.
//
#include <bits/stdc++.h>

template <size_t ALPHA = 27, char MIN_ALPHA = 'a' - 1>
decltype(auto) suffix_array(std::string_view s) {
  assert(std::all_of(s.begin(), s.end(), [](char ch) { return std::clamp<int>(ch - '\0', MIN_ALPHA, MIN_ALPHA + ALPHA - 1 - '\0') == (ch - '\0'); }));
  assert(s.back() == MIN_ALPHA);

  const auto n = static_cast<int>(s.size());
  const auto nn = std::max<int>(ALPHA, n) + 1;
  std::vector<int> p(n), c(n), cnt(nn, 0);
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

  std::vector<int> np(n), nc(n);
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
      auto cur = std::pair(c[p[i]], c[(p[i] + k) % n]);
      auto prv = std::pair(c[p[i - 1]], c[(p[i - 1] + k) % n]);
      nc[p[i]] = nc[p[i - 1]] + (cur != prv);
    }
    nc.swap(c);
  }

  return p;
}

template <size_t ALPHA = 27, char MIN_ALPHA = 'a' - 1>
decltype(auto) lcp_array(std::string_view s) {
  assert(s.back() == MIN_ALPHA);

  const auto n = static_cast<int>(s.size());
  const auto sa = suffix_array<ALPHA, MIN_ALPHA>(s);
  std::vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    pos[sa[i]] = i;
  }
  std::vector<int> lcp(n, 0); // lcp(s[sa[i]], s[sa[i + 1]])
  int k = 0;
  for (int i = 0; i < n; ++i) {
    k = std::max(k - 1, 0);
    if (pos[i] == n - 1) continue;
    auto j = sa[pos[i] + 1];
    while (s[i + k] == s[j + k]) ++k;
    lcp[pos[i]] = k;
  }

  return lcp;
}